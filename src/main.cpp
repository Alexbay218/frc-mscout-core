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
    int qrx = 0;
    int qry = 0;
    cv::Point poi;
    while(true) {
        cap.grab();
        cap.retrieve(frame);
        if(qr.decodeSingular(&frame, &output, &qrx, &qry) > 0) {
            if(ms.inputMessage(output)) {
                std::cout << "---Data Start---" << std::endl;
                for(int i = 0;i < ms.data.size();i++) {
                    std::cout << ms.data[i];
                }
                std::cout << std::endl << "----Data End----\nPress Space to Continue" << std::endl;
                int val = 0;
                while(val != 32) {
                    val = cv::waitKey(1);
                }
                ms.clearMessage();
            }
            //std::cout << "Done: " << ms.inputMessage(output) << " Target Hash: " << ms.targetHash << std::endl;
            poi.x = qrx;
            poi.y = qry;
            cv::circle(frame, poi, 3, cv::Scalar(0,255,0), 5);
        }
        else {
            cv::circle(frame, poi, 5, cv::Scalar(0,0,255));
        }
        cv::imshow("Video Capture", frame);
		if(cv::waitKey(1) == 27) {
            ms.clearMessage();
		}
    }
}
