#include "fileinputstream.h"


namespace Translator {
    FileInputStream::FileInputStream()
    {
        input = std::ifstream("source.txt");
    }

    FileInputStream::FileInputStream(std::string fileName)
    {
        input = std::ifstream(fileName);
        if (!input.is_open()) {
            throw FileNotFoundException();
        }
    }


    FileInputStream::~FileInputStream()
    {
        InputStream::~InputStream();
        input.close();
    }

    char FileInputStream::getChar()
    {
        char character;

        if (!input.get(character)) {
            throw EndOfFileException();
        }

        return character;
    }
    char FileInputStream::getCharWithoutExtracting()
    {
        char character = input.peek();

        if (character == EOF) {
            throw EndOfFileException();
        }

        return character;
    }
}
