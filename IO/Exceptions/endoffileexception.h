#ifndef ENDOFFILEEXCEPTION_H
#define ENDOFFILEEXCEPTION_H

#include <exception>

class EndOfFileException: public std::exception
{
public:
    const char * what() const noexcept
    {
        return "EndOfFileException";
    }
};


#endif // ENDOFFILEEXCEPTION_H
