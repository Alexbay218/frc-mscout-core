#ifndef ADLER32_HASH_H
#define ADLER32_HASH_H
#include <sstream>
#include <string>

class adler32_hash {
    public:
        adler32_hash();
        virtual ~adler32_hash();
        std::string hashInput(std::string input);
        std::string int2hex(int i);
        uint32_t MOD_ADLER;

    protected:

    private:
};

#endif // ADLER32_HASH_H
