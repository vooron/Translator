#ifndef RECURSIVESYNTAXANALYZER_H
#define RECURSIVESYNTAXANALYZER_H


#include <lexicalAnalyzer/lexicalanalyzeroutput.h>
#include <syntaxAnalyzer/Exceptions/syntaxiserror.h>
#include <vector>
#include "lexicalAnalyzer/utils.h"
#include "syntaxAnalyzer/syntaxanalyzer.h"
#include <QDebug>

class RecursiveSyntaxAnalyzer: public SyntaxAnalyzer
{
public:
    RecursiveSyntaxAnalyzer();

    bool analyze(const LexicalAnalyzerOutput&);

private:
    bool isProgram(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isCommands(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isCommand(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isDefining(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isInit(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isType(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isExpression(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isTerm(const std::vector<OutputLexemTuple>&, size_t& i);
    bool ismMultiplier(const std::vector<OutputLexemTuple>&, size_t& i);
    bool isRelation(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isLogicalSign(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isIdent(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isSign(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isInput(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isOutput(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isLogicalExpr(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isLogicalTerm(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isLogicalF(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isRL(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isCycle(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isCondStatement(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isExp(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isMark(const std::vector<OutputLexemTuple>&, size_t &i);
    bool isMarkCall(const std::vector<OutputLexemTuple>&, size_t &i);

    LexicalAnalyzerOutput lexicalAnalyzerOutput;

};

#endif // RECURSIVESYNTAXANALYZER_H
