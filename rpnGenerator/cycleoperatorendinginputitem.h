#ifndef CYCLEOPERATORENDINGINPUTITEM_H
#define CYCLEOPERATORENDINGINPUTITEM_H

#include "rpnGenerator/inputitem.h"
#include <iostream>

class CycleOperatorEndingInputItem: public InputItem
{
public:
    CycleOperatorEndingInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}


    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {

        while (stack.back()->getLexem() != "do") {
            stack.back()->onRpnAppending(rpn, stack, i, config);
            delete stack.back();
            stack.pop_back();
        }

        stack.back()->onRpnAppending(rpn, stack, i, config);
        delete stack.back();
        stack.pop_back();
    }

};


#endif // CYCLEOPERATORENDINGINPUTITEM_H
