#ifndef MESSAGE_H
#define MESSAGE_H
#include "adler32_hash.h"
#include <vector>
#include <string>
#include <iostream>

class message {
    public:
        message();
        adler32_hash ad32hash;
        std::vector<std::string> data;
        std::string targetHash;
        int targetNumber;

        bool inputMessage(std::string msg);
        void clearMessage();

        virtual ~message();

    protected:

    private:
        int hashMessageLength;
        std::string lastIt;
        int iterations;
        std::vector<std::string> codeHash;

        std::string hashData();
        void inputHash(std::string msg);
        void inputData(std::string msg);

        int complete();
};

#endif // MESSAGE_H
