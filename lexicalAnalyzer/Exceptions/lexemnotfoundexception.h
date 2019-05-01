#ifndef LEXEMNOTFOUNDEXCEPTION_H
#define LEXEMNOTFOUNDEXCEPTION_H


#include <exception>
#include <model/Exceptions/translatorexception.h>

class LexemNotFoundException: public TranslatorException
{
public:

    LexemNotFoundException(): TranslatorException ("", 0) {}

    LexemNotFoundException(std::string message, size_t row = 0): TranslatorException (message, row) {}

    const char * what() const noexcept
    {
        return "LexemNotFoundException";
    }
};




#endif // LEXEMNOTFOUNDEXCEPTION_H
