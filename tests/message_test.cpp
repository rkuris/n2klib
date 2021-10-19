#include "../n2k.h"
#include <iostream>

#define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)

void bitUnpacker();

void bitUnpacker() {
    struct tc {
        unsigned char data[n2k::Message::MAX_NMEA_DATA];
        int start;
        int len;
        unsigned long expected;
    } testcases[] = {
        {"\01", 0, 1, 1},
        {"", 0, 1, 0},
        {"", 0, 2, 0},
        {"", 0, 7, 0},
        {"\0\01", 8, 1, 1},
        {"\0\01", 8, 2, 2},
        {"\0\02", 8, 2, 1},
        {"\x80\01", 0, 9, 0x101}
    };

    for ( unsigned int i = 0; i < sizeof(testcases)/sizeof(testcases[0]); i++) {
        tc testcase = testcases[i];
        n2k::MessageWithState m;
        memcpy(m.data, testcase.data, sizeof(testcase.data));
        auto got = m.Get(testcase.start, testcase.len);
        ASSERT(got == testcase.expected,
               "case " << i <<
               ": expected " << testcase.expected <<
               " got " << got);
    }
}

int main(int argc, char *argv[]) {
    bitUnpacker();
    return 0;
}
