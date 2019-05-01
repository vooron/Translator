#ifndef RPNOPTIMIZER_H
#define RPNOPTIMIZER_H


#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

#include "rpnGenerator/rpnunit.h"


using namespace std;

class RpnOptimizer
{


    size_t getIndexLabel(vector<RpnUnit*>& rpn, string key) {
        size_t i = 0;

        while (i < rpn.size()) {

            if (rpn[i]->getCode() == 103 && rpn[i]->getLexem() == key) {

                if (i + 1 < rpn.size() && (rpn[i+1]->getLexem() == "jne" || rpn[i+1]->getLexem() == "goto")) {
                    i++;
                    continue;
                }

                return i;
            }
            i++;
        }

        return 0;
    }


public:
    RpnOptimizer() {}

    vector<RpnUnit*> optimize(vector<RpnUnit*>& rpn) {

        size_t i = 0;

        // pair<call, deffining>
        vector<pair<int, int>> marks;
        vector<RpnUnit*> userMakrs;

        while (i < rpn.size()) {

            if (rpn[i]->getCode() == 103) {
                if (i + 1 < rpn.size() && (rpn[i+1]->getLexem() == "jne" || rpn[i+1]->getLexem() == "goto")) {
                    size_t index = getIndexLabel(rpn, rpn[i]->getLexem());

                    marks.push_back({i, index});

                    if (rpn[index]->getLexem().at(0) == ':') {
                        userMakrs.push_back(rpn[index]);
                    }

                }
            }
            i++;
        }

        sort(marks.begin(), marks.end(), [](pair<int, int> f, pair<int, int> s) -> bool {return (f.second - s.second) < 0;});

        int shift = 0;
        for (auto i: marks) {

            int call = i.first;
            int definition = i.second - shift;

            rpn[call]->setCode(definition);
            rpn[call]->setLexem("#" + to_string(definition) + "#");

            for (auto j = shift + 1; j < marks.size(); j++) {
                if (marks[j].first > definition) {
                    marks[j].first -= 1;
                }
            }

            rpn.erase(rpn.begin() + definition);

            shift++;
        }

        for (auto i: userMakrs) {
            delete i;
        }

        return rpn;
    }

};


#endif // RPNOPTIMIZER_H
