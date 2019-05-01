#ifndef SYMANTICERROR_H
#define SYMANTICERROR_H

#include <exception>
#include <string>
#include <model/Exceptions/translatorexception.h>

class SemanticError : public TranslatorException {
public:
    SemanticError(std::string message, size_t row = 0) : TranslatorException (message, row) {}


    const char * what() const noexcept
    {
        return "SemanticError";
    }
};


#endif // SYMANTICERROR_H
