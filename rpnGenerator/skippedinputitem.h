#ifndef SKIPPEDINPUTITEM_H
#define SKIPPEDINPUTITEM_H


#include "rpnGenerator/inputitem.h"
#include "climits"


class SkippedInputItem: public InputItem
{

    static const int MAX_PRIORITY = INT_MAX;

public:

    SkippedInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    int priorityFromInput() override {
        return MAX_PRIORITY;
    }


    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {

    }

    virtual ~SkippedInputItem() override {}
};

#endif // SKIPPEDINPUTITEM_H
