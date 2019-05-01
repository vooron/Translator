#ifndef INSTREAMINPUTITEM_H
#define INSTREAMINPUTITEM_H


#include "rpnGenerator/inputitem.h"



class InStreamInputItem: public InputItem
{
public:
    InStreamInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        InputItem::onStackAppending(rpn, stack, i, config);
        rpn.push_back(new RpnUnit(9, "cout"));
    }

};




#endif // INSTREAMINPUTITEM_H
