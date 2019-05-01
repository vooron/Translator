#ifndef OPENBRACKETINPUTITEM_H
#define OPENBRACKETINPUTITEM_H

#include "rpnGenerator/inputitem.h"
#include "climits"

class OpenBracketInputItem: public InputItem
{

    static const int MAX_PRIORITY = INT_MAX;

public:
    OpenBracketInputItem(int code, string lexem, int priority): InputItem(code, lexem, priority) {}


    int priorityFromInput() override {
        return MAX_PRIORITY;
    }

    virtual ~OpenBracketInputItem() override {}
};



#endif // OPENBRACKETINPUTITEM_H
