#ifndef DOINPUTITEM_H
#define DOINPUTITEM_H

#include "rpnGenerator/inputitem.h"
#include "rpnGenerator/uniquelabelsgenerator.h"
#include "climits"

class DoInputItem: public InputItem
{
    RpnUnit* m1;
    RpnUnit* m2;
    static const int MAX_PRIORITY = INT_MAX;
public:
    DoInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    int priorityFromInput() override {
        return MAX_PRIORITY;
    }

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        stack.push_back(this);
        m1 = UniqueLabelsGenerator::genetateLabel();
        m2 = UniqueLabelsGenerator::genetateLabel();

        rpn.push_back(m1);
    }

    void onRpnAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        rpn.push_back(m2);
        rpn.push_back(new RpnUnit(0, "jne"));
        rpn.push_back(m1);
        rpn.push_back(new RpnUnit(7, "goto"));
        rpn.push_back(m2);

        config.erase("cycle");
    }

};


#endif // DOINPUTITEM_H
