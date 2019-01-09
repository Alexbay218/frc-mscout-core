#include "file_writer.h"

file_writer::file_writer() {
}

file_writer::~file_writer() {
}

std::string file_writer::writeFile(std::string input, std::string path) {
    std::fstream file;
    std::string inputCopy = input;
    std::string sourceTeam = inputCopy.substr(0,inputCopy.find_first_of(";"));
    inputCopy = inputCopy.substr(inputCopy.find_first_of(";") + 1);
    std::string targetTeam = inputCopy.substr(0,inputCopy.find_first_of(";"));
    inputCopy = inputCopy.substr(inputCopy.find_first_of(";") + 1);
    std::string matchTime = inputCopy.substr(0,inputCopy.find_first_of(";"));
    inputCopy = inputCopy.substr(inputCopy.find_first_of(";") + 1);
    std::string matchType = inputCopy.substr(0,inputCopy.find_first_of(";"));
    inputCopy = inputCopy.substr(inputCopy.find_first_of(";") + 1);
    std::string matchNumber = inputCopy.substr(0,inputCopy.find_first_of(";"));
    inputCopy = inputCopy.substr(inputCopy.find_first_of(";") + 1);
    std::string filename = matchType + matchNumber + "_" + sourceTeam + ".fmt";

    if(!fs::exists(fs::path(path.substr(0,path.size()-1)))) {
        std::cout << "Creating Directory: " << path.substr(0,path.size()-1) << std::endl;
        fs::create_directory(fs::path(path));
        std::cout << "Created Directory: " << path.substr(0,path.size()-1) << std::endl;
    }

    if(!fs::exists(fs::path(path+targetTeam))) {
        std::cout << "Creating Directory: " << path+targetTeam << std::endl;
        fs::create_directory(fs::path(path+targetTeam));
        std::cout << "Created Directory: " << path+targetTeam << std::endl;
    }

    if(!fs::exists(fs::path(path+targetTeam+"\\"+filename))) {
        std::cout << "Creating File: " << path+targetTeam+"\\"+filename << std::endl;
        file.open(path+targetTeam+"\\"+filename, std::ios::out | std::ios::binary);
        for(int i = 0;i < input.size();i++) {
            if(input[i] != '\0') {
                file << input[i];
            }
        }
        file.close();
        return "File written to: " + path+targetTeam+"\\"+filename;
    }
    else {
        return "File already exists at: " + path+targetTeam+"\\"+filename;
    }
}

void file_writer::check(const fs::path& p, fs::file_status s) {
    std::cout << p;
    if(fs::status_known(s) ? fs::exists(s) : fs::exists(p))
        std::cout << " exists\n";
    else
        std::cout << " does not exist\n";
}
