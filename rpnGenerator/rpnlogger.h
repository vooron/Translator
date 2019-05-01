#ifndef RPNLOGGER_H
#define RPNLOGGER_H

#include <string>
#include <vector>
#include <rpnGenerator/rpnunit.h>
#include <rpnGenerator/inputitem.h>
#include <iostream>

using namespace std;

namespace rpn {


    struct LogItem {
        string stack;
        string input;
        string rpn;
    };

    class Logger
    {

        const string sep = " ";

        vector<LogItem> _log;


        string rpnToString(vector<RpnUnit*> rpn) {
            string result;

            if (rpn.size() < 1) {
                return result;
            }

            result += rpn.front()->getLexem();
            rpn.erase(rpn.begin());

            for (auto i: rpn) {
                result += sep;
                result += i->getLexem();
            }

            return leftLast(30, result);
        }

        string stackToString(vector<InputItem*> stack) {
            string result;

            if (stack.size() < 1) {
                return result;
            }

            result += stack.front()->getLexem();
            stack.erase(stack.begin());

            for (auto i: stack) {
                result += sep;
                result += i->getLexem();
            }

            return leftLast(20, result);
        }

        string leftLast(size_t size, string str, string prefix = "...") {

            if (str.size() < size) {
                return str;
            }

            size = size - prefix.size();
            size = size >= 0 ? size : 0;

            return prefix + str.substr(str.size() - size, size);
        }


    public:


        Logger() {}

        void log(vector<RpnUnit *>& rpn, vector<InputItem *>& stack, InputItem* input) {

            LogItem item;

            item.input = input != nullptr? input->getLexem(): "";
            item.rpn = rpnToString(rpn);
            item.stack = stackToString(stack);

            _log.push_back(item);
        }


        vector<LogItem> getLog() {
            return _log;
        }


    };
}


#endif // RPNLOGGER_H2
