#ifndef TRANSLATOREXCEPTION_H
#define TRANSLATOREXCEPTION_H

#include <exception>
#include <string>

class TranslatorException : public std::exception {

    std::string message;
    size_t row;

public:
    TranslatorException(std::string message, size_t row = 0) : message(message), row(row) {}

    std::string getMessage() const noexcept {
        return message;
    }

    void setRow(size_t row) noexcept {
        this->row = row;
    }

    size_t getRow() const noexcept {
        return row;
    }

    virtual const char * what() const noexcept {
        return "TranslatorException";
    }
};

#endif // TRANSLATOREXCEPTION_H
