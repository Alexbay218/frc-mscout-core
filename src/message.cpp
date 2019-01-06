#include "message.h"

message::message() {
    clearMessage();
}

void message::clearMessage() {
    hashMessageLength = -1;
    iterations = 0;
    targetNumber = 0;
    lastIt = "";
    targetHash = "";
    data.clear();
    codeHash.clear();
}

bool message::inputMessage(std::string msg) {
    if(msg != lastIt) {
        std::cout << "Inputting Message: " << msg << std::endl;
        lastIt = msg;
        iterations++;
        std::cout << "Iteration: " << iterations << std::endl;
        if(hashMessageLength < 0 || hashMessageLength > msg.length()) {
            hashMessageLength = msg.length();
        }
        if(iterations >= 3) {
            std::cout << "Length: " << hashMessageLength << std::endl;
            if(msg.length() > hashMessageLength) {
                inputData(msg);
            }
            else {
                inputHash(msg);
            }
        }
        for(int i = 0;i < data.size();i++) {
            std::cout << "Data Array " << data[i] << " at " << i << std::endl;
        }
        for(int i = 0;i < codeHash.size();i++) {
            std::cout << "Code Hash Array " << codeHash[i] << " at " << i << std::endl;
        }
    }
    if(targetNumber != 0) {
        std::cout << "Percentage: " << (static_cast<float> (complete()))/(static_cast<float> (targetNumber*2)) << std::endl;
    }
    return ((hashData() == targetHash) && (targetHash.length() == 8));
}

void message::inputData(std::string msg) {
    std::string temp = ad32hash.hashInput(msg);
    std::cout << "Data inputted \"" << msg << "\" with hash of " << temp << std::endl;
    for(int i = 0;i < codeHash.size();i++) {
        if(temp == codeHash[i]) {
            while(data.size() < i + 1) {
                data.push_back("");
            }
            data[i] = msg;
        }
    }
}

void message::inputHash(std::string msg) {
    if(msg.find("|") != -1) {
        int index = std::stoi(msg.substr(0,msg.find("|")));
        std::string tmpHash = msg.substr(msg.find("|") + 1);
        while(codeHash.size() < index + 1) {
            codeHash.push_back("");
        }
        codeHash[index] = tmpHash;
    }
    else if(msg.find("-") != -1) {
        targetNumber = std::stoi(msg.substr(0,msg.find("-")));
        targetHash = msg.substr(msg.find("-") + 1);
    }
}

std::string message::hashData() {
    std::string concatData = "";
    int i = 0;
    while(i < data.size()) {
        concatData = concatData + data[i];
        i++;
    }
    return ad32hash.hashInput(concatData);
}

int message::complete() {
    int ret = 0;
    for(int i = 0;i < codeHash.size();i++) {
        if(codeHash[i].length() > 0) {
            ret++;
        }
    }
    for(int i = 0;i < data.size();i++) {
        if(data[i].length() > 0) {
            ret++;
        }
    }
    return ret;
}

message::~message() {
    //dtor
}
