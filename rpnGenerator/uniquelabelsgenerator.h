#ifndef UNIQUELABELSGENERATOR_H
#define UNIQUELABELSGENERATOR_H

#include "rpnGenerator/rpnunit.h"
#include <string>

using namespace std;


class UniqueLabelsGenerator
{
      static size_t counter;
public:
    static RpnUnit* genetateLabel() {
        counter++;
        return new RpnUnit(103, "#" + to_string(counter));
    }

    static void setCounter(size_t n) {
        counter = n;
    }
};

#endif // UNIQUELABELSGENERATOR_H
