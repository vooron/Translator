#ifndef AUTOMASYNTAXANALYZER_H
#define AUTOMASYNTAXANALYZER_H

#include "syntaxAnalyzer/syntaxanalyzer.h"
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include "vector"
#include "map"
#include "string"
#include "stack"
#include "syntaxAnalyzer/Exceptions/syntaxiserror.h"
#include "QDebug"
#include "QString"
#include "exception"
#include <sstream>

class AutomaSyntaxAnalyzer: public SyntaxAnalyzer
{
public:

    typedef std::string subautomaName;
    typedef size_t stateNum;
    typedef size_t lexemCode;


    const lexemCode EMPTY_LABEL = -1;
    const stateNum EMPTY_STATE = -1;


    struct Arc {
        bool isSubautoma;
        subautomaName subautoma;
        stateNum state;
        lexemCode label = 0;

        stateNum stack = 0;
    };



    struct StateInfo {
        std::vector<Arc> arcs;
        Arc notEquals;

        bool isFinal = false;
    };

    struct TraceItem {
        stateNum cState;
        std::string lexem;

        std::string stack;
    };

    struct AutomaConfItem {
        subautomaName automa;
        stateNum alphaState;
        lexemCode label;
        stateNum betaState;
        stateNum stack;

        std::string semanticSubpr;
    };

    typedef std::map<int, StateInfo> states;
    typedef  std::pair<subautomaName, states> automaItem;

private:

    std::map<subautomaName, states> automa;
    std::vector<std::pair<std::string, int>> stack;

    std::vector <TraceItem> trace;
    std::vector <AutomaConfItem> automaConf;


public:
    AutomaSyntaxAnalyzer();

    bool analyze(const LexicalAnalyzerOutput&) override;

    std::vector<TraceItem> getTrace();
    std::vector<AutomaConfItem> getConf();

private:
    Arc makeSubautomaArc(subautomaName nextSubautoma, stateNum nextState, lexemCode label, stateNum stack);
    Arc makeArc(stateNum nextState, lexemCode label);
};


#endif // AUTOMASYNTAXANALYZER_H
