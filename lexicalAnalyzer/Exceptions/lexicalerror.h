#ifndef LEXICALERROR_H
#define LEXICALERROR_H

#include <exception>
#include <string>
#include <model/Exceptions/translatorexception.h>

class LexicalError : public TranslatorException {

public:
    LexicalError(std::string message, size_t row = 0): TranslatorException (message, row) {}

    const char * what() const noexcept
    {
        return "LexicalError";
    }
};


#endif // LEXICALERROR_H
