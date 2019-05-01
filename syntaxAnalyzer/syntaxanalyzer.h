#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "lexicalAnalyzer/lexicalanalyzeroutput.h"

class SyntaxAnalyzer {
public:
    virtual bool analyze(const LexicalAnalyzerOutput&) = 0;

    virtual ~SyntaxAnalyzer() {}
};

#endif // SYNTAXANALYZER_H


