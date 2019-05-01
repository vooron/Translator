#ifndef CLOSEBRACKETINPUTITEM_H
#define CLOSEBRACKETINPUTITEM_H

#include "rpnGenerator/inputitem.h"
#include "climits"


class CloseBracketInputItem: public InputItem
{

public:
    CloseBracketInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        delete stack.back();
        stack.pop_back(); // deleting open bracket from stack
    }


    virtual ~CloseBracketInputItem() override {}
};



#endif // CLOSEBRACKETINPUTITEM_H
