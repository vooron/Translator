#ifndef INPUTITEMFACTORY_H
#define INPUTITEMFACTORY_H

#include <string>
#include <vector>
#include <map>
#include "rpnGenerator/inputitem.h"
#include "lexicalAnalyzer/utils.h"
#include <algorithm>

#include "rpnGenerator/openbracketinputitem.h"
#include "rpnGenerator/closebracketinputitem.h"
#include "rpnGenerator/skippedinputitem.h"
#include "rpnGenerator/operatorendinginputitem.h"
#include "rpnGenerator/booleanliteralinputitem.h"
#include "rpnGenerator/doinputitem.h"
#include "rpnGenerator/whileinputitem.h"
#include "rpnGenerator/cycleoperatorendinginputitem.h"
#include "rpnGenerator/ifinputitem.h"
#include "rpnGenerator/theninputitem.h"
#include "rpnGenerator/instreaminputitem.h"
#include "rpnGenerator/outstreaminputitem.h"
#include "rpnGenerator/condstatementendinginputitem.h"

using namespace std;


class InputItemFactory
{
protected:
    map<int, vector<string>> priorities;


    int getPrioity(OutputLexemTuple & lexem, int defaultPriority = -1) {
        for (auto [priority, values]: priorities) {
            if (isIn(lexem.name, values)) {
                return priority;
            }
        }

        return defaultPriority;
    }

    template <class T>
    bool isIn(T value, vector<T> values) {
        auto it = find(values.begin(), values.end(), value);

        if (it != values.end()) {
            return true;
        }

        return false;
    }



    bool isUnaryMinusOrPlus(size_t i, vector<OutputLexemTuple> & lexems) {
        if (isIn(lexems[i].name, {"-", "+"})) {

            if (i > 0) {
                auto prevLexem = lexems[i-1];
                if (
                        prevLexem.name != ")" &&
                        !prevLexem.isConst &&
                        !prevLexem.isIdent
                    ) {
                    return true;

                }
            } else {
                return true;
            }
        }

        return false;
    }

public:

    InputItemFactory(const map<int, vector<string>>& priorities): priorities(priorities) {}


    InputItem* create(size_t i, vector<OutputLexemTuple>& lexems, map<string, string>& config) {

        auto lexem = lexems[i];

        if (isUnaryMinusOrPlus(i, lexems)) {
            lexem.name = "@" + lexem.name;
        }

        int priority = getPrioity(lexem);

        if (isIn(lexem.name, {"(", "["})) {
            return new OpenBracketInputItem(lexem.code, lexem.name, priority);

        } else if (isIn(lexem.name, {")", "]"})) {
            return new CloseBracketInputItem(lexem.code, lexem.name, priority);

        } else if (lexem.name == ",") {
            return new OperatorEndingInputItem(lexem.code, lexem.name, priority);

        } else if (isIn(lexem.name, {"int", "float", "cout", "cin"})) {
            return new SkippedInputItem(lexem.code, lexem.name, priority);

        } else if (isIn(lexem.name, {"true", "false"})) {
            return new BooleanLiteralInputItem(lexem.code, lexem.name, priority);

        } else if(lexem.name == ";") {

            if (config.count("cycle")) {
                return new CycleOperatorEndingInputItem(lexem.code, lexem.name, priority);
            } else {
                return new OperatorEndingInputItem(lexem.code, lexem.name, priority);
            }

        } else if (lexem.name == "do") {
            return new DoInputItem(lexem.code, lexem.name, priority);
        } else if (lexem.name == "while") {
            return new WhileInputItem(lexem.code, lexem.name, priority);

        } else if (lexem.name == "if") {
            return new IfInputItem(lexem.code, lexem.name, priority);
        } else if (lexem.name == "then") {
            return new ThenInputItem(lexem.code, lexem.name, priority);

        } else if (lexem.name == "}") {
            return new CondStatementEndingInputItem(lexem.code, lexem.name, priority);

        } else if (lexem.name == "<<") {
            return new InStreamInputItem(lexem.code, lexem.name, priority);
        } else if (lexem.name == ">>") {
            return new OutStreamInputItem(lexem.code, lexem.name, priority);
        }


        return new InputItem(lexem.code, lexem.name, priority);
    }

};



#endif // INPUTITEMFACTORY_H
