#ifndef FORM_H
#define FORM_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/checkbox.hpp>
#include <nana/gui/widgets/label.hpp>
#include "message.h"
#include "qrcode_stream.h"
#include "file_writer.h"

class form {
    public:
        form();
        virtual ~form();

    protected:
    private:
        message ms;
        file_writer fw;
        std::string initPath;
        std::string videoPath;
        std::string defaultFilename;
        bool videoIsNum;
        bool overrideSourceTeam;

        std::string writeData(std::vector<std::string> input);
};

#endif // FORM_H
