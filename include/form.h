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
#include <experimental/filesystem>
#include "message.h"
#include "qrcode_stream.h"

namespace fs = std::experimental::filesystem;

class form {
    public:
        form();
        virtual ~form();

    protected:
    private:
        message ms;
        std::string initPath;
        std::string videoPath;
        std::string defaultFilename;
        bool videoIsNum;
        bool overrideSourceTeam;

        void writeData(std::vector<std::string> input);
};

#endif // FORM_H
