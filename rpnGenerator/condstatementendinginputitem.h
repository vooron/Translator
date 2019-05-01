#ifndef CONDSTATEMENTENDINGINPUTITEM_H
#define CONDSTATEMENTENDINGINPUTITEM_H


#include "rpnGenerator/inputitem.h"
#include "climits"

#include <iostream>

class CondStatementEndingInputItem: public InputItem
{
        static const int MAX_PRIORITY = INT_MAX;
public:
    CondStatementEndingInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {

        while (stack.back()->getLexem() != "if") {
            stack.back()->onRpnAppending(rpn, stack, i, config);
            delete stack.back();
            stack.pop_back();
        }

        stack.back()->onRpnAppending(rpn, stack, i, config);
        delete stack.back();
        stack.pop_back();
    }


    int priorityFromInput() override {
        return MAX_PRIORITY;
    }
};



#endif // CONDSTATEMENTENDINGINPUTITEM_H
