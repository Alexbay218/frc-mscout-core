#include "qrcode_stream.h"
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Initializing" << std::endl;
    cv::VideoCapture cap;
    qrcode_stream qr;
    std::string output;
    std::cout << "Scanner created" << std::endl;
    if(argc > 1) {
        cap.open(argv[0]);
        while (!cap.isOpened()) {
            std::cout << "Cannot open the video cam: " << argv[1] << std::endl;
            cap.open(argv[1]);
        }
    }
    else {
        cap.open(0);
    }
    while(true) {
        cv::Mat frame;
        cap.read(frame);
        cv::imshow("Video Capture", frame);
        qr.decodeSingular(&frame, &output);

		if(cv::waitKey(1) == 27) {
            break;
		}
    }
}
