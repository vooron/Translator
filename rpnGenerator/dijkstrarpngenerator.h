#ifndef DIJKSTRARPNGENERATOR_H
#define DIJKSTRARPNGENERATOR_H

#include <vector>
#include <map>
#include "rpnGenerator/rpnunit.h"

#include "rpnGenerator/inputitemfactory.h"
#include "rpnGenerator/inputitem.h"
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include "lexicalAnalyzer/utils.h"

#include "rpnGenerator/rpnlogger.h"

#include <QDebug>
#include <iostream>

using namespace std;

class DijkstraRpnGenerator
{ 

    map<int, vector<string>> priorities = {
        {0, {"(", "[", "do", "if"}},
        {1, {")", "]", "while", "then", ";"}},
        {2, {"=", "goto", "<<", ">>"}},
        {3, {"or"}},
        {4, {"and"}},
        {5, {"not"}},
        {6, {"<", ">", "<=", ">=", "==", "!="}},
        {7, {"+", "-"}},
        {8, {"*", "/", "@-", "@+"}},
    };


    InputItemFactory inputItemFactory = InputItemFactory(priorities);
    rpn::Logger logger;

public:

    DijkstraRpnGenerator() {
    }


    vector<rpn::LogItem> getLog() {
        return logger.getLog();
    }


    vector<RpnUnit *> generate(LexicalAnalyzerOutput& lexicalAnalyzerOutput) {
        vector<RpnUnit*> rpn;
        vector<InputItem*> stack;

        map<string, string> config;


        size_t i = 0;

        vector<OutputLexemTuple> lexems = lexicalAnalyzerOutput.getLexems();

        while (i < lexems.size()) {

            auto& lexem = lexems[i];

            if (lexem.isMark) {
                logger.log(rpn, stack, new InputItem(103, lexem.name, -1));
                rpn.push_back(new RpnUnit(103, lexem.name));
                i++;
                continue;
            }

            if (lexem.isIdent || lexem.isConst) {
                logger.log(rpn, stack, new InputItem(lexem.code, lexem.name, -1));
                rpn.push_back(new RpnUnit(lexem.code, lexem.name));
                i++;
                continue;
            }

            InputItem* inputItem = inputItemFactory.create(i, lexems, config);

            logger.log(rpn, stack, inputItem);

            if (stack.empty()) {

                inputItem->onStackAppending(rpn, stack, i, config);
                i++;

            } else if (stack.back()->priorityFromStack() >= inputItem->priorityFromInput()) {
                stack.back()->onRpnAppending(rpn, stack, i, config);
                inputItem->onPushingValueFromStack(rpn, stack, i, config);

            } else {
                inputItem->onStackAppending(rpn, stack, i, config);
                i++;
            }
        }


        if (stack.size() > 0) {
            while (!stack.empty()) {

                logger.log(rpn, stack, nullptr);

                stack.back()->onRpnAppending(rpn, stack, i, config);

                delete stack.back();
                stack.pop_back();
            }
        }

        return rpn;
    }


    string getString(vector<RpnUnit*> rpn, string sep = " ") {
        string result;

        result += rpn.front()->getLexem();
        rpn.erase(rpn.begin());

        for (auto i: rpn) {
            result += sep;
            result += i->getLexem();
        }

        return result;
    }


};

#endif // DIJKSTRARPNGENERATOR_H
