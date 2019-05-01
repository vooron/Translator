#ifndef BOOLEANLITERALINPUTITEM_H
#define BOOLEANLITERALINPUTITEM_H


#include "rpnGenerator/inputitem.h"
#include "climits"

class BooleanLiteralInputItem: public InputItem
{
    static const int MAX_PRIORITY = INT_MAX;
public:

    BooleanLiteralInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        rpn.push_back(new RpnUnit(code, lexem));
        delete this;
    }

    int priorityFromInput() override {
        return MAX_PRIORITY;
    }

    virtual ~BooleanLiteralInputItem() override {}
};

#endif // BOOLEANLITERALINPUTITEM_H
