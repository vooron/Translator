#ifndef RPNEXECUTER_H
#define RPNEXECUTER_H

#include "rpnGenerator/rpnunit.h"
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"

#include <limits>
#include <vector>
#include <string>
#include <map>
#include <math.h>

#include <QMessageBox>
#include <QString>
#include <QInputDialog>


#define TEXT_LOGIC_MOD

using namespace std;

class RpnExecuter
{
public:

    typedef struct {
        string type;
        float value;
    } IdnInfo;


    typedef struct {
        size_t i;
        string stack;
        string input;
    } LogItem;

private:

    vector <RpnUnit*> stack;
    map<string, IdnInfo> idns;

    vector<LogItem> log;


    pair<RpnUnit*, RpnUnit*> getTwoFromStack() {
        pair<RpnUnit*, RpnUnit*> result;

        result.second = stack.back();
        stack.pop_back();
        result.first = stack.back();
        stack.pop_back();

        return result;
    }

    RpnUnit* getOneFromStack() {
        RpnUnit* result = stack.back();
        stack.pop_back();
        return result;
    }

    float rpnToFloat(RpnUnit* unit) {
        float result;
        if (unit->getCode() == 100) {
            result = idns[unit->getLexem()].value;
        } else {
            result = stof(unit->getLexem());
        }

        delete unit;
        return result;
    }

    bool rpnToBool(RpnUnit* unit) {

#ifdef TEXT_LOGIC_MOD
        bool result = (unit->getLexem() == "true")?
                                    true : false;
#else
        bool result = (unit->getLexem() == "1")?
                    true : false;
#endif

        delete unit;
        return result;
    }

    string rpnToIdn(RpnUnit* unit) {
        string result = unit->getLexem();
        delete unit;
        return result;
    }

    size_t rpnToLabelIndex(RpnUnit* unit) {
        size_t result = unit->getCode();
        delete unit;
        return result;
    }


    RpnUnit* floatToRpn(float val) {
        return new RpnUnit(102, to_string(val));
    }

    RpnUnit* boolToRpn(bool val) {
#ifdef TEXT_LOGIC_MOD
        return new RpnUnit(102, val? "true" : "false");
#else
        return new RpnUnit(102, to_string(val));
#endif
    }


    string rpnToString(vector<RpnUnit*> rpn) {
        string result;
        for (auto i: rpn) {
            result += " " + i->getLexem();
        }

        return result;
    }


public:

    RpnExecuter(const LexicalAnalyzerOutput& output) {
        const auto& idn = output.getIdents();

        for (auto i: idn) {
            idns.insert({i.name, {i.type, 0}});
        }
    }

    vector<LogItem> getLog() {
        return log;
    }

    void execute(const vector<RpnUnit*>& rpn) {

        size_t i = 0;

        while (i < rpn.size()) {
            auto unit = rpn[i];

            log.push_back({i, rpnToString(stack), unit->getLexem()});
//            cout << rpnToString(stack) << " <- " << unit->getLexem() << ": " << i << endl;

            // ARITHMETIC
            if (unit->getLexem() == "+") {
                auto r = getTwoFromStack();

                stack.push_back(floatToRpn(
                                    rpnToFloat(r.first) + rpnToFloat(r.second)
                                    ));


            } else if (unit->getLexem() == "-") {
                auto r = getTwoFromStack();

                stack.push_back(floatToRpn(
                                    rpnToFloat(r.first) - rpnToFloat(r.second)
                                    ));


            } else if (unit->getLexem() == "/") {
                auto r = getTwoFromStack();

                stack.push_back(floatToRpn(
                                    rpnToFloat(r.first) / rpnToFloat(r.second)
                                    ));


            } else if (unit->getLexem() == "*") {
                auto r = getTwoFromStack();

                stack.push_back(floatToRpn(
                                    rpnToFloat(r.first) * rpnToFloat(r.second)
                                    ));


            } else if (unit->getLexem() == "@+") {
                auto r = getOneFromStack();

                auto val = abs(rpnToFloat(r));

                stack.push_back(floatToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == "@-") {
                auto r = getOneFromStack();

                auto val = rpnToFloat(r) * -1;

                stack.push_back(floatToRpn(
                                    val
                                    ));


                // LOGIC
            } else if (unit->getLexem() == "<") {
                auto r = getTwoFromStack();

                auto val = rpnToFloat(r.first) < rpnToFloat(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == ">") {
                auto r = getTwoFromStack();

                auto val = rpnToFloat(r.first) > rpnToFloat(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == "<=") {
                auto r = getTwoFromStack();

                auto val = rpnToFloat(r.first) <= rpnToFloat(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == ">=") {
                auto r = getTwoFromStack();

                auto val = rpnToFloat(r.first) >= rpnToFloat(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == "==") {
                auto r = getTwoFromStack();

                auto val = rpnToFloat(r.first) == rpnToFloat(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == "!=") {
                auto r = getTwoFromStack();

                auto val = rpnToFloat(r.first) != rpnToFloat(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == "and") {
                auto r = getTwoFromStack();

                auto val = rpnToBool(r.first) && rpnToBool(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));



            } else if (unit->getLexem() == "or") {
                auto r = getTwoFromStack();

                auto val = rpnToBool(r.first) || rpnToBool(r.second);

                stack.push_back(boolToRpn(
                                    val
                                    ));


            } else if (unit->getLexem() == "not") {
                auto r = getOneFromStack();

                auto val = !rpnToBool(r);

                stack.push_back(boolToRpn(
                                    val
                                    ));


                // ASSIGNMENT
            } else if (unit->getLexem() == "=") {
                auto r = getTwoFromStack();

                string idnName = rpnToIdn(r.first);
                float value = rpnToFloat(r.second);

                if (idns[idnName].type == "int") {
                    value = floor(value);
                }
                idns[idnName].value = value;



                // Move
            } else if (unit->getLexem() == "jne") {
                auto r = getTwoFromStack();

                bool cond = rpnToBool(r.first);
                size_t nextIndex = rpnToLabelIndex(r.second);

                if (!cond) {
                    i = nextIndex - 1;
                }


            } else if (unit->getLexem() == "goto") {
                auto r = getOneFromStack();
                size_t nextIndex = rpnToLabelIndex(r);
                i = nextIndex - 1;


            } else if (unit->getLexem() == "<<") {
                auto r = getTwoFromStack();

                string idnName = rpnToIdn(r.second);

                QMessageBox msgBox;
                msgBox.setText(QString::number(idns[idnName].value));
                msgBox.exec();


            } else if (unit->getLexem() == ">>") {
                auto r = getTwoFromStack();

                string idnName = rpnToIdn(r.second);

                float value = getFloatFromUser();

                if (idns[idnName].type == "int") {
                    idns[idnName].value = floor(value);
                } else {
                    idns[idnName].value = value;
                }
            }



            else {
                stack.push_back(new RpnUnit(*unit));
            }

            i++;
        }

    }

    float getFloatFromUser() {
        bool ok = false;

        double value = 0;
        while (!ok) {
            value = QInputDialog::getDouble(0,
                                            "Input",
                                            "Enter float:",
                                            0,
                                            std::numeric_limits<float>::min(),
                                            std::numeric_limits<float>::max(),
                                            2,
                                            &ok);

            if (!ok) {
                QMessageBox msgBox;
                msgBox.setText("It is necessarily");
                msgBox.exec();
            }
        }

        return value;
    }

};



#endif // RPNEXECUTER_H
