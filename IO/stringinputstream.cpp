#include "stringinputstream.h"

namespace Translator {
StringInputStream::StringInputStream(std::string text): input(text) {}

char StringInputStream::getChar()
{
    char character = static_cast<char>( input.get() );

    if (character == EOF) {
        throw EndOfFileException();
    }

    return character;
}

char StringInputStream::getCharWithoutExtracting()
{
    char character = static_cast<char>( input.peek() );

    if (character == EOF) {
        throw EndOfFileException();
    }

    return character;
}




}

