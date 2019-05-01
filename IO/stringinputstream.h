#ifndef STRINGINPUTSTREAM_H
#define STRINGINPUTSTREAM_H

#include "IO/inputstream.h"
#include <string>
#include <iostream>
#include <sstream>
#include "IO/Exceptions/endoffileexception.h"

namespace Translator {
    class StringInputStream : public InputStream
    {
        std::stringstream input;
    public:
        StringInputStream(std::string);

    public:
        char getChar() override;
        char getCharWithoutExtracting() override;
    };
}

#endif // STRINGINPUTSTREAM_H
