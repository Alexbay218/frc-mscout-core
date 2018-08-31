#include "adler32_hash.h"

adler32_hash::adler32_hash() {
    MOD_ADLER = 65521;
}

std::string adler32_hash::hashInput(std::string input) {
    MOD_ADLER = 65521;
    unsigned char *data = (unsigned char*)input.c_str();
    int len = input.length();
    uint32_t a = 1, b = 0;
    size_t index;

    // Process each byte of the data in order
    for (index = 0; index < len; ++index) {
        a = (a + data[index]) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    uint32_t ret = (b << 16) | a;
    return int2hex(ret);
}

std::string adler32_hash::int2hex(int i) {
    std::stringstream stream;
    stream << std::hex << i;
    std::string ret = stream.str();
    while(ret.length() < 8) {
        ret = "0" + ret;
    }
    return ret;
}
adler32_hash::~adler32_hash() {
    //dtor
}
