#ifndef FILE_WRITER_H
#define FILE_WRITER_H
#include <fstream>
#include <string>
#include <iostream>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

class file_writer {
    public:
        file_writer();
        virtual ~file_writer();

        std::string writeFile(std::string input, std::string path);
    protected:

    private:
};

#endif // FILE_WRITER_H
