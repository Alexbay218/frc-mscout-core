#include "qrcode_stream.h"

qrcode_stream::qrcode_stream() {
    qrscan.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
}

int qrcode_stream::decodeSingular(cv::Mat* inputImage, std::string* modification, int* x, int* y) {
    cv::Mat grayImage = *inputImage;
    cv::cvtColor(*inputImage, grayImage, CV_BGR2GRAY);
    cv::resize(grayImage, grayImage, cv::Size(), 0.5, 0.5);
    cv::threshold(grayImage, grayImage, 128, 255, 0);
    cv::imshow("gray", grayImage);
    zbar::Image zImage(grayImage.cols, grayImage.rows, "Y800", (uchar *)grayImage.data, grayImage.cols * grayImage.rows);
    int n = qrscan.scan(zImage);
    if (n > 0) {
        zbar::Image::SymbolIterator firstSymbol = zImage.symbol_begin();
        *modification = firstSymbol->get_data();
        *x = firstSymbol->get_location_x(0)*2;
        *y = firstSymbol->get_location_y(0)*2;
    }
    return n;
}
qrcode_stream::~qrcode_stream() {
    //dtor
}
