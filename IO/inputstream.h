#ifndef INPUTSTREAM_H
#define INPUTSTREAM_H



namespace Translator {
    class InputStream
    {
    public:
        virtual char getChar() = 0;
        virtual char getCharWithoutExtracting() = 0;
        virtual ~InputStream() {}
    };
}

#endif // INPUTSTREAM_H
