#ifndef FILEINPUTSTREAM_H
#define FILEINPUTSTREAM_H


#include <fstream>
#include "string"

#include "IO/inputstream.h"
#include "IO/Exceptions/filenotfoundexception.h"
#include "IO/Exceptions/endoffileexception.h"

namespace Translator {
    class FileInputStream: public InputStream
    {
        std::ifstream input;
    public:
        FileInputStream();
        FileInputStream(std::string fileName);

        virtual char getChar() override;
        virtual char getCharWithoutExtracting() override;

        virtual ~FileInputStream() override;
    };
}



#endif // FILEINPUTSTREAM_H
