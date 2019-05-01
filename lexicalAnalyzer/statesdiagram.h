#ifndef STATESDIAGRAM_H
#define STATESDIAGRAM_H


#include "lexicalAnalyzer/algorythm.h"
#include "lexicalAnalyzer/Exceptions/lexicalerror.h"
#include "IO/inputstream.h"
#include "IO/Exceptions/endoffileexception.h"
#include <map>
#include <regex>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

class StatesDiagram: public Algorythm
{
    bool isLastLexem;
    Translator::InputStream& input;

    map<string, regex> symbolsTable;
public:
    StatesDiagram(Translator::InputStream& input);

    virtual pair<string, string> nextLexem();
    virtual bool isLast() const noexcept;


    ~StatesDiagram();

private:
    bool isMatch(string key, string ch) {
        return regex_match(ch, symbolsTable[key]);
    }
};

#endif // STATESDIAGRAM_H
