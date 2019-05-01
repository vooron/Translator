#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include <string>
#include "model/Exceptions/translatorexception.h"
#include <vector>
#include "lexicalAnalyzer/inputlexemtable.h"
#include "lexicalAnalyzer/lexicalanalyzer.h"
#include "lexicalAnalyzer/statesdiagram.h"
#include "IO/stringinputstream.h"
#include "symanticAnalyzer/utils.h"
#include "syntaxAnalyzer/recursivesyntaxanalyzer.h"
#include "symanticAnalyzer/semanticanalyzer.h"
#include "syntaxAnalyzer/automasyntaxanalyzer.h"
#include "syntaxAnalyzer/syntaxanalyzer.h"

#include "syntaxAnalyzer/precedencetableformer.h"

#include <regex>


class TranslatorFacade    // TODO: add strategy
{

    LexicalAnalyzerOutput lexicalAnalyzerOutput;
    SyntaxAnalyzer& syntaxAnalyzer;

public:
    TranslatorFacade(SyntaxAnalyzer& syntaxAnalyzer);

    std::string process(std::string code);
    LexicalAnalyzerOutput getLexicalAnalyzerOutput();

    virtual ~TranslatorFacade() {}

private:
    virtual LexicalAnalyzerOutput analyzeLexems(std::string code);
    virtual bool analyzeSyntax(LexicalAnalyzerOutput);
    virtual bool analyzeSemantic(LexicalAnalyzerOutput);
    virtual std::string generateCode(LexicalAnalyzerOutput);
};

#endif // TRANSLATOR_H
