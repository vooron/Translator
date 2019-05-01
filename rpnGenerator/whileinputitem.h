#ifndef WHILEINPUTITEM_H
#define WHILEINPUTITEM_H

#include "rpnGenerator/inputitem.h"



class WhileInputItem: public InputItem
{
public:
    WhileInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}


    void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {
        config.insert({"cycle", ""});

        while (stack.back()->getLexem() != "do") {
            stack.back()->onRpnAppending(rpn, stack, i, config);
            delete stack.back();
            stack.pop_back();
        }
    }

    void onRpnAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) override {

    }


    virtual ~WhileInputItem() {}
};



#endif // WHILEINPUTITEM_H
