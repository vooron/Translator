#ifndef SYNTAXISERROR_H
#define SYNTAXISERROR_H

#include <exception>
#include <string>
#include <model/Exceptions/translatorexception.h>

class SyntaxisError : public TranslatorException {
public:
    SyntaxisError(std::string message, size_t row = 0) : TranslatorException (message, row) {}

    const char * what() const noexcept
    {
        return "SynataxisError";
    }
};


#endif // SYNTAXISERROR_H
