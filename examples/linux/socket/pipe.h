#include <stdio.h>
#include <streambuf>
#include <ostream>

class stdiobuf : public std::streambuf {
    enum { bufsize = 2048 };
    char buffer[bufsize];
    FILE* myfp;
    int   (*myclose)(FILE*);
    int overflow(int c) {
        if (c != std::char_traits<char>::eof()) {
            *this->pptr() = std::char_traits<char>::to_char_type(c);
            this->pbump(1);
        }
        return this->sync()
               ? std::char_traits<char>::eof()
               : std::char_traits<char>::not_eof(c);
    }
    int sync() {
        std::streamsize size(this->pptr() - this->pbase());
        std::streamsize done(this->myfp? fwrite(this->pbase(), 1, size, this->myfp): 0);
        this->setp(this->pbase(), this->epptr());
        return size == done? 0: -1;
    }
public:
    stdiobuf(FILE* fp, int(*close)(FILE*) = fclose)
        : myfp(fp)
        , myclose(close) {
        this->setp(this->buffer, this->buffer + (this->myfp? bufsize - 1: 0));
    }
    ~stdiobuf() {
        this->sync();
        this->myfp && this->myclose(this->myfp);
    }
};
class opipestream
    : private virtual stdiobuf
    , public std::ostream {
public:
    opipestream(std::string const& pipe)
        : stdiobuf(popen(pipe.c_str(), "w"), pclose)
        , std::ios(static_cast<std::streambuf*>(this))
        , std::ostream(static_cast<std::streambuf*>(this)) {
    }
};

