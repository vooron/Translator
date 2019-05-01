#ifndef IFINPUTITEM_H
#define IFINPUTITEM_H

#include "rpnGenerator/inputitem.h"
#include "rpnGenerator/uniquelabelsgenerator.h"
#include "climits"

class IfInputItem: public InputItem
{
    RpnUnit* m1;
    static const int MAX_PRIORITY = INT_MAX;
public:

    IfInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    int priorityFromInput() override {
        return MAX_PRIORITY;
    }


    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        stack.push_back(this);
        m1 = UniqueLabelsGenerator::genetateLabel();

        config.insert({"m1", m1->getLexem()});
    }

    void onRpnAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        rpn.push_back(m1);
    }

};




#endif // IFINPUTITEM_H
