#ifndef LEXICAL_ANALYZER_UTILS_H
#define LEXICAL_ANALYZER_UTILS_H

#include <string>
//#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include <iostream>
#include <iomanip>

struct InputLexemTuple
{
    std::string lexem;
    size_t code;
};


struct OutputLexemTuple {
    std::string name;
    size_t code;
    bool isIdent = false;
    bool isConst = false;
    bool isMark = false;
    size_t identCode;
    size_t constCode;
    size_t markCode;
    size_t row;
};

struct OutputIdentTuple {
    std::string name;
    std::string type;
    std::string value;
    bool isMark = false;
};

struct OutputConstTuple {
    std::string name;
    std::string type;
};

#endif // LEXICAL_ANALYZER_UTILS_H
