#include "qrcode_stream.h"

qrcode_stream::qrcode_stream() {
    qrscan.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
}

int qrcode_stream::decodeSingular(cv::Mat* inputImage, std::string* modification) {
    cv::Mat grayImage;
    cv::cvtColor(*inputImage, grayImage, CV_BGR2GRAY);
    zbar::Image zImage(grayImage.cols, grayImage.rows, "Y800", (uchar *)grayImage.data, grayImage.cols * grayImage.rows);
    int n = qrscan.scan(zImage);
    if (n > 0) {
        zbar::Image::SymbolIterator firstSymbol = zImage.symbol_begin();
        *modification = firstSymbol->get_data();
    }
    return n;
}
qrcode_stream::~qrcode_stream() {
    //dtor
}
