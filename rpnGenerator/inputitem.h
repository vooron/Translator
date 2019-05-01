#ifndef INPUTITEM_H
#define INPUTITEM_H

#include <string>
#include <vector>
#include "rpnGenerator/rpnunit.h"
#include <map>

using namespace std;


class InputItem
{

protected:
    int code;
    string lexem;
    int priority;


public:

    InputItem(int code, string lexem, int priority): code(code), lexem(lexem), priority(priority) {
    }

    string getLexem() {
        return lexem;
    }

    int getCode() {
        return code;
    }

    int priorityFromStack() {
        return priority;
    }

    virtual int priorityFromInput() {
        return priority;
    }

    virtual void onStackAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) {
        stack.push_back(this);
    }

    virtual void onRpnAppending(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) {
        rpn.push_back(new RpnUnit(code, lexem));
    }

    virtual void onPushingValueFromStack(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, size_t& i, map<string, string>& config) {
        delete stack.back();
        stack.pop_back();
    }

    virtual ~InputItem() {

    }

};


#endif // INPUTITEM_H
