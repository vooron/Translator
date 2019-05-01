#ifndef SEMANTICANALYZER_H
#define SEMANTICANALYZER_H
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include "symanticAnalyzer/utils.h"


class SemanticAnalyzer
{
public:
    SemanticAnalyzer();

    virtual LexicalAnalyzerOutput analyze(LexicalAnalyzerOutput&);

    virtual ~SemanticAnalyzer() {}
};

#endif // SEMANTICANALYZER_H
