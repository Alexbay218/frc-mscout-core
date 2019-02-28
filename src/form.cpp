#include "form.h"

form::form() {
    initPath = fs::current_path().string() + "\\data";
    videoPath = "0";
    videoIsNum = true;
    bool isScanning = false;

    cv::VideoCapture cap;
    qrcode_stream qr;
    message ms;
    file_writer fw;

    nana::form fm(nana::rectangle(20,20,500,380));
    fm.caption("FRC MScout Core");

    nana::label lb_pathstring(fm, nana::rectangle(10,10,70,25));
    lb_pathstring.caption("Folder Path:");
    nana::textbox tb_pathstring(fm, nana::rectangle(80,10,410,25));
    tb_pathstring.caption(initPath);

    nana::label lb_videopath(fm, nana::rectangle(10,50,70,25));
    lb_videopath.caption("Video Path:");
    nana::textbox tb_videopath(fm, nana::rectangle(80,50,410,25));
    tb_videopath.caption(videoPath);

    nana::label lb_videoisnum(fm, nana::rectangle(10,85,120,25));
    lb_videoisnum.caption("Video Path is Number:");
    nana::checkbox cb_videoisnum(fm, nana::rectangle(135,85,20,25));
    cb_videoisnum.check(videoIsNum);

    nana::label lb_status(fm, nana::rectangle(10,335,480,25));
    lb_status.caption("Ready to Scan");
    lb_status.format(true);

    nana::textbox tb_rawinput(fm, nana::rectangle(10,235,385,90));
    nana::button bt_rawstart(fm, nana::rectangle(400,235,90,90));
    bt_rawstart.caption("Raw Entry");
    bt_rawstart.events().click([&](){
        std::string output;
        tb_pathstring.getline(0,initPath);
        tb_rawinput.getline(0,output);
        lb_status.caption(fw.writeFile(output,initPath));
    });

    nana::button bt_start(fm, nana::rectangle(10,110,480,50));
    bt_start.caption("Start QR Code Stream");
    bt_start.events().click([&](){
        if(!isScanning) {
            isScanning = true;
            lb_status.caption("Starting Scan");
            tb_pathstring.getline(0,initPath);
            tb_videopath.getline(0,videoPath);
            videoIsNum = cb_videoisnum.checked();
            bool isFinished = false;
            bool abort = false;
            int abortCountdown = 200;
            if(videoIsNum) {
                cap.open(std::stoi(videoPath));
            }
            else {
                cap.open(videoPath);
            }
            std::string output;
            cv::Mat frame;
            int qrx = 0;
            int qry = 0;
            cv::Point poi(5,5);
            cv::Scalar green(0,255,0);
            cv::Scalar red(0,0,255);
            while(!isFinished && !abort) {
                cap.grab();
                cap.retrieve(frame);
                lb_status.caption("<bold color=0x005f00>Scanning... " + std::to_string(round(ms.percentage*100)/100) + "% complete </><bold color=0xff0000>(Will abort in " + std::to_string(abortCountdown/20) + ")</>");
                if(qr.decodeSingular(&frame, &output, &qrx, &qry) > 0) {
                    abortCountdown = 200;
                    if(ms.inputMessage(output)) {
                        lb_status.caption(writeData(ms.data));
                        ms.clearMessage();
                        isFinished = true;
                    }
                    poi.x = qrx;
                    poi.y = qry;
                    cv::circle(frame, poi, 5, green);
                }
                else {
                    abortCountdown--;
                    cv::circle(frame, poi, 5, red);
                }
                abort = abortCountdown <= 0;
                //cv::imshow("Video Capture", frame);
                if(cv::waitKey(1) == 27) {
                    ms.clearMessage();
                }
            }
            if(abort) {
                lb_status.caption("<bold color=0xff0000>Scan Aborted</>");
            }
            cap.release();
            isScanning = false;
        }
    });

    nana::button bt_start2(fm, nana::rectangle(10,170,480,50));
    bt_start2.caption("Start Single QR Code");
    bt_start2.events().click([&](){
        if(!isScanning) {
            isScanning = true;
            lb_status.caption("Starting Scan");
            tb_pathstring.getline(0,initPath);
            tb_videopath.getline(0,videoPath);
            videoIsNum = cb_videoisnum.checked();
            bool isFinished = false;
            bool abort = false;
            int abortCountdown = 200;
            if(videoIsNum) {
                cap.open(std::stoi(videoPath));
            }
            else {
                cap.open(videoPath);
            }
            std::string output;
            cv::Mat frame;
            int qrx = 0;
            int qry = 0;
            cv::Point poi(5,5);
            cv::Scalar green(0,255,0);
            cv::Scalar red(0,0,255);
            while(!isFinished && !abort) {
                cap.grab();
                cap.retrieve(frame);
                lb_status.caption("<bold color=0x005f00>Scanning... </><bold color=0xff0000>(Will abort in " + std::to_string(abortCountdown/20) + ")</>");
                if(qr.decodeSingular(&frame, &output, &qrx, &qry) > 0) {
                    abortCountdown = 200;
                    lb_status.caption(fw.writeFile(output, initPath));
                    isFinished = true;
                    poi.x = qrx;
                    poi.y = qry;
                    cv::circle(frame, poi, 5, green);
                }
                else {
                    abortCountdown--;
                    cv::circle(frame, poi, 5, red);
                }
                abort = abortCountdown <= 0;
                cv::imshow("Video Capture", frame);
                if(cv::waitKey(1) == 27) {
                    ms.clearMessage();
                }
            }
            if(abort) {
                lb_status.caption("<bold color=0xff0000>Scan Aborted</>");
            }
            cv::destroyWindow("Video Capture");
            cv::destroyWindow("Gray");
            cap.release();
            isScanning = false;
        }
    });
    fm.show();
    nana::exec();
}

std::string form::writeData(std::vector<std::string> input) {
    std::string formatted = "";
    for(int i = 0;i < input.size();i++) {
        formatted += input[i];
    }
    return fw.writeFile(formatted, initPath);
}

form::~form() {
    //dtor
}
