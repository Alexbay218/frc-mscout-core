#ifndef QRCODE_STREAM_H
#define QRCODE_STREAM_H
#include <time.h>
#include <zbar.h>
#include <zbar\ImageScanner.h>
#include <opencv2\core\core.hpp>
#include <opencv2\video\video.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

class qrcode_stream {
    public:
        qrcode_stream();
        virtual ~qrcode_stream();
        zbar::ImageScanner qrscan;
        int decodeSingular(cv::Mat* inputImage, std::string* returnData, int* x, int* y);
        time_t timer;
    protected:

    private:
};

#endif // QRCODE_STREAM_H
