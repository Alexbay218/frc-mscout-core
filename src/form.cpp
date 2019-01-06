#include "form.h"

form::form() {
    initPath = fs::current_path().string() + "\\data\\";
    videoPath = "0";
    defaultFilename = "default.fmt";
    overrideSourceTeam = false;
    videoIsNum = true;

    cv::VideoCapture cap;
    qrcode_stream qr;
    message ms;

    nana::form fm(nana::rectangle(20,20,500,205));
    fm.caption("FRC MScout Core");

    nana::label lb_pathstring(fm, nana::rectangle(10,10,70,25));
    lb_pathstring.caption("Folder Path:");
    nana::textbox tb_pathstring(fm, nana::rectangle(80,10, 350, 25));
    tb_pathstring.caption(initPath);
    nana::button bt_pathstring(fm, nana::rectangle(440,10,50,25));
    bt_pathstring.caption("...");

    nana::label lb_filename(fm, nana::rectangle(10,45,132,25));
    lb_filename.caption("Source Team Override:");
    nana::textbox tb_filename(fm, nana::rectangle(142,45,348,25));
    tb_filename.caption(defaultFilename);

    nana::label lb_videopath(fm, nana::rectangle(10,80,70,25));
    lb_videopath.caption("Video Path:");
    nana::textbox tb_videopath(fm, nana::rectangle(80,80,410,25));
    tb_videopath.caption(videoPath);

    nana::label lb_videoisnum(fm, nana::rectangle(10,115,120,25));
    lb_videoisnum.caption("Video Path is Number:");
    nana::checkbox cb_videoisnum(fm, nana::rectangle(135,115,20,25));
    cb_videoisnum.check(videoIsNum);

    nana::button bt_start(fm, nana::rectangle(10,145,480,50));
    bt_start.caption("Start QR Code Stream");
    bt_start.events().click([&](){
        tb_pathstring.getline(0,initPath);
        tb_filename.getline(0,defaultFilename);
        tb_videopath.getline(0, videoPath);
        videoIsNum = cb_videoisnum.checked();
        bool isFinished = false;
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
        while(!isFinished) {
            cap.grab();
            cap.retrieve(frame);
            if(qr.decodeSingular(&frame, &output, &qrx, &qry) > 0) {
                if(ms.inputMessage(output)) {
                    writeData(ms.data);
                    ms.clearMessage();
                    isFinished = true;
                }
                poi.x = qrx;
                poi.y = qry;
                cv::circle(frame, poi, 5, green);
            }
            else {
                cv::circle(frame, poi, 5, red);
            }
            cv::imshow("Video Capture", frame);
            if(cv::waitKey(1) == 27) {
                ms.clearMessage();
            }
        }
        cv::destroyWindow("Video Capture");
        cv::destroyWindow("Gray");
        cap.release();
    });
    fm.show();
    nana::exec();
}

void form::writeData(std::vector<std::string> input) {
    std::fstream file;
    if(!fs::exists(initPath) || !fs::is_directory(initPath)) {
        fs::create_directory(initPath);
    }
    file.open(initPath + defaultFilename, std::ios::out | std::ios::binary);
    for(int i = 0;i < input.size();i++) {
        file << input[i];
    }
    file.close();
}

form::~form() {
    //dtor
}
