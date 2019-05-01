#ifndef OPERATORENDINGINPUTITEM_H
#define OPERATORENDINGINPUTITEM_H



#include "rpnGenerator/inputitem.h"

class OperatorEndingInputItem: public InputItem
{
public:
    OperatorEndingInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
    }


    virtual ~OperatorEndingInputItem() override {}
};

#endif // OPERATORENDINGINPUTITEM_H
