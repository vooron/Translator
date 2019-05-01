#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H


#include <exception>

class FileNotFoundException: public std::exception {
    const char * what() const noexcept
    {
        return "FileNotFoundException";
    }
};


#endif // FILENOTFOUNDEXCEPTION_H
