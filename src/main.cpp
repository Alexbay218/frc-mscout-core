#include "qrcode_stream.h"
#include "message.h"
#include <iostream>

int main(int argc, char** argv) {
    std::cout << "Initializing" << std::endl;
    cv::VideoCapture cap;
    qrcode_stream qr;
    message ms;
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
    std::string output;
    cv::Mat frame;
    while(true) {
        cap.grab();
        cap.retrieve(frame);
        cv::imshow("Video Capture", frame);
        if(qr.decodeSingular(&frame, &output) > 0) {
            std::cout << "Full Hash: " << ms.inputMessage(output) << std::endl;
        }
		if(cv::waitKey(1) == 27) {
            ms.clearMessage();
		}
    }
}
