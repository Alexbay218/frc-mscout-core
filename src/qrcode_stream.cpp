#include "qrcode_stream.h"

qrcode_stream::qrcode_stream() {
    qrscan.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
    thresh = 0;
}

int qrcode_stream::decodeSingular(cv::Mat* inputImage, std::string* modification, int* x, int* y) {
    cv::Mat grayImage;
    cv::Mat orgImage = *inputImage;
    cv::cvtColor(*inputImage, orgImage, CV_BGR2GRAY);
    cv::resize(orgImage, orgImage, cv::Size(), 0.5, 0.5);
    cv::imshow("Gray", orgImage);
    bool quit = false;
    thresh = 0;
    int n = 0;
    while(n <= 0 && !quit) {
        thresh += 16;
        cv::threshold(orgImage, grayImage, static_cast<float>(thresh), 255, 0);
        zbar::Image zImage(grayImage.cols, grayImage.rows, "Y800", (uchar *)grayImage.data, grayImage.cols * grayImage.rows);
        n = qrscan.scan(zImage);
        if(thresh >= 255) {
            quit = true;
        }
        if (n > 0) {
            cv::imshow("Gray", grayImage);
            cv::waitKey(1);
            zbar::Image::SymbolIterator firstSymbol = zImage.symbol_begin();
            *modification = firstSymbol->get_data();
            *x = firstSymbol->get_location_x(0)*2;
            *y = firstSymbol->get_location_y(0)*2;
            quit = true;
            return n;
        }
        else if(thresh == 128) {
            cv::imshow("Gray", grayImage);
            cv::waitKey(1);
        }
    }
    return n;
}

qrcode_stream::~qrcode_stream() {
    //dtor
}
