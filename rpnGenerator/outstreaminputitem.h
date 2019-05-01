#ifndef OUTSTREAMINPUTITEM_H
#define OUTSTREAMINPUTITEM_H


#include "rpnGenerator/inputitem.h"

class OutStreamInputItem: public InputItem
{
public:
    OutStreamInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        InputItem::onStackAppending(rpn, stack, i, config);
        rpn.push_back(new RpnUnit(8, "cin"));
    }

};


#endif // OUTSTREAMINPUTITEM_H
