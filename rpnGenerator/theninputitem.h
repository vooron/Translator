#ifndef THENINPUTITEM_H
#define THENINPUTITEM_H

#include "rpnGenerator/inputitem.h"
#include "rpnGenerator/uniquelabelsgenerator.h"

class ThenInputItem: public InputItem
{
public:
    ThenInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}

    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        rpn.push_back(new RpnUnit(103, config["m1"]));
        rpn.push_back(new RpnUnit(0, "jne"));
        config.erase("m1");
    }

    void onRpnAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
    }

};


#endif // THENINPUTITEM_H
