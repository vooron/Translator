#ifndef RPNUNIT_H
#define RPNUNIT_H

#include <string>

using namespace std;

class RpnUnit
{

    int code;
    string lexem;

public:

    RpnUnit(int code, string lexem) {
        this->code = code;
        this->lexem = lexem;
    }

    string getLexem() {
        return lexem;
    }

    int getCode() {
        return code;
    }

    void setCode(int code) {
        this->code = code;
    }

    void setLexem(string lexem) {
        this->lexem = lexem;
    }


};


#endif // RPNUNIT_H
