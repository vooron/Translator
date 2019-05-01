#include "precedencetableformer.h"



void PrecedenceTableFormer::firstR(const std::string unit, std::vector<std::string> &result)
{
    grammarRow rules = grammar.at(unit);

    for (auto alternative: rules) {
        if (alternative[0]->getType() == Types::TERMINAL) {

            std::string search = terminals.at(std::stoi(alternative[0]->getValue()));

            auto it = find(result.begin(), result.end(), search);
            if (it == result.end()) {
                // not found
                result.push_back(search);
            }
        } else {
            std::string search = alternative[0]->getValue();
            auto it = find(result.begin(), result.end(), search);
            if (it == result.end()) {
                // not found
                result.push_back(search);
                firstR(search, result);
            }
        }
    }

    //    return result;
}

std::string PrecedenceTableFormer::getRuleLabel(const PrecedenceTableFormer::GrammarUnit *unit)
{
    if (unit->getType() == Types::TERMINAL) {
        return terminals.at(std::stoi(unit->getValue()));
    }

    return unit->getValue();
}

std::map<std::string, PrecedenceTableFormer::grammarRow> PrecedenceTableFormer::getGrammar() {
    return grammar;
}


void PrecedenceTableFormer::lastR(const std::string unit, std::vector<std::string>& result)
{
    grammarRow rules = grammar.at(unit);

    for (auto alternative: rules) {

        size_t lastIndex = alternative.size()-1;

        if (alternative[lastIndex]->getType() == Types::TERMINAL) {
            std::string search = terminals.at(std::stoi(alternative[lastIndex]->getValue()));

            auto it = find(result.begin(), result.end(), search);
            if (it == result.end()) {
                // not found
                result.push_back(search);
            }
        } else {
            std::string search = alternative[lastIndex]->getValue();
            auto it = find(result.begin(), result.end(), search);
            if (it == result.end()) {
                // not found
                result.push_back(alternative[lastIndex]->getValue());
                lastR(alternative[lastIndex]->getValue(), result);
            }
        }
    }

}


std::string PrecedenceTableFormer::getNameByCode(int code) {
    return terminals[code];
}


PrecedenceTableFormer::PrecedenceTableFormer()
{

    // Types
    terminals.insert(make_reversed_pair("int", 1));
    terminals.insert(make_reversed_pair("float", 2 ));

    // Cycles and conditional transitions
     terminals.insert(make_reversed_pair("do", 3 ));
     terminals.insert(make_reversed_pair("while", 4 ));
     terminals.insert(make_reversed_pair("if", 5 ));
     terminals.insert(make_reversed_pair("then", 6 ));
     terminals.insert(make_reversed_pair("goto", 7 ));

    // IO
     terminals.insert(make_reversed_pair("cin", 8 ));
     terminals.insert(make_reversed_pair("cout", 9 ));
     terminals.insert(make_reversed_pair(">>", 10 ));
     terminals.insert(make_reversed_pair("<<", 11 ));

    // Mustach
     terminals.insert(make_reversed_pair("}", 12 ));
     terminals.insert(make_reversed_pair("{", 13 ));

    // Delimiters
     terminals.insert(make_reversed_pair(";", 14 ));
     terminals.insert(make_reversed_pair(",", 15 ));

    // Initialize
     terminals.insert(make_reversed_pair("=", 16 ));

    // Logical operators
     terminals.insert(make_reversed_pair("==", 17 ));
     terminals.insert(make_reversed_pair("!=", 18 ));
     terminals.insert(make_reversed_pair(">", 19 ));
     terminals.insert(make_reversed_pair("<", 20 ));
     terminals.insert(make_reversed_pair(">=", 21 ));
     terminals.insert(make_reversed_pair("<=", 22 ));

    // Arithmetic operators
     terminals.insert(make_reversed_pair("+", 23 ));
     terminals.insert(make_reversed_pair("-", 24 ));
     terminals.insert(make_reversed_pair("*", 25 ));
     terminals.insert(make_reversed_pair("/", 26 ));

    // brackets
     terminals.insert(make_reversed_pair("(", 27 ));
     terminals.insert(make_reversed_pair(")", 28 ));
     terminals.insert(make_reversed_pair("[", 29 ));
     terminals.insert(make_reversed_pair("]", 30 ));

    // logical
     terminals.insert(make_reversed_pair("and", 31 ));
     terminals.insert(make_reversed_pair("or", 32 ));
     terminals.insert(make_reversed_pair("not", 33 ));

    // literals
     terminals.insert(make_reversed_pair("true", 34 ));
     terminals.insert(make_reversed_pair("false", 35 ));


     // special
     terminals.insert(make_reversed_pair("#", 40 ));

     terminals.insert(make_reversed_pair("ID", 100 ));
     terminals.insert(make_reversed_pair("Exp", 101 ));
     terminals.insert(make_reversed_pair("Mark", 102 ));

    grammar.insert(std::make_pair<std::string, grammarRow>("program", {
                                      {NT("commands_1")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("commands", {
                                      {NT("command"), T(14), NT("commands")},
                                      {NT("command"), T(14)}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("commands_1", {
                                      {NT("commands")},
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("command", {
                                      {NT("defining")},
                                      {NT("init_1")},
                                      {NT("cycle")},
                                      {NT("conditionalSt")},
                                      {NT("input")},
                                      {NT("output")},
                                      {T(102)},
                                      {NT("markCall")}
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("defining", {
//                                      {NT("type"), T(100)},
//                                      {NT("defining"), T(15), T(100)},
                                      {NT("defining"), T(15), NT("init_1")},
                                      {NT("type"), NT("init_1")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("init", {
                                      {T(100), T(16), NT("expression_1")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("init_1", {
                                      {NT("init")}
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("type", {
                                      {T(1)},
                                      {T(2)}
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("expression", {
                                      {NT("expression"), NT("sign"), NT("term_1")},
                                      {NT("sign"), NT("term_1")},
                                      {NT("term_1")}
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("expression_1", {
                                      {NT("expression")}
                                  }));



    grammar.insert(std::make_pair<std::string, grammarRow>("term", {
                                      {NT("term"), T(25), NT("multiplier")},
                                      {NT("term"), T(26), NT("multiplier")},
                                      {NT("multiplier")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("term_1", {
                                      {NT("term")},
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("multiplier", {
                                      {T(101)},
                                      {T(100)},
                                      {T(27), NT("expression_1"), T(28)}
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("relation", {
                                      {NT("expression_1"), NT("lSign"), NT("expression_1")},
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("lSign", {
                                      {T(17)},
                                      {T(18)},
                                      {T(19)},
                                      {T(20)},
                                      {T(21)},
                                      {T(22)},
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("sign", {
                                      {T(23)},
                                      {T(24)}
                                  }));


    grammar.insert(std::make_pair<std::string, grammarRow>("input", {
                                      {T(8), T(10), T(100)},
                                      {NT("input"), T(10), T(100)}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("output", {
                                      {T(9), T(11), T(100)},
                                      {NT("output"), T(11), T(100)}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("LE", {
                                      {NT("LT_1")},
                                      {NT("LE"), T(32), NT("LT_1")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("LE_1", {
                                      {NT("LE")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("LT", {
                                      {NT("LF")},
                                      {NT("LT"), T(31), NT("LF")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("LT_1", {
                                      {NT("LT")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("LF", {
                                      {T(33), NT("LF")},
                                      {T(29), NT("LE_1"), T(30)},
                                      {NT("RL")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("RL", {
                                      {T(34)},
                                      {T(35)},
                                      {NT("relation")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("cycle", {
                                      {T(3), NT("commands_1"), T(4), NT("LE_1")}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("conditionalSt", {
                                      {T(5), NT("LE_1"), T(6), NT("command"), T(12)}
                                  }));

    grammar.insert(std::make_pair<std::string, grammarRow>("markCall", {
                                      {T(7), T(102)}
                                  }));


//    std::vector<std::string> a;
//    firstR();
}

PrecedenceTableFormer::PrecedenceTable PrecedenceTableFormer::makeTable()
{

    PrecedenceTable table;

    std::vector<std::string> keys;

    for( auto const& [key, val] : grammar )
    {
        keys.push_back(key);
    }

    const std::string BOUNDARY_TERMINAL = "#";
    keys.push_back(BOUNDARY_TERMINAL);

    for( auto const& [key, val] : terminals )
    {
        keys.push_back(val);
    }


    for (const auto& key: keys) {
        table.insert(std::make_pair(key, std::map<std::string, size_t> ()));
    }

    for( auto& [tableKey, val] : table )
    {
        for (const auto& key: keys) {

            if (tableKey == BOUNDARY_TERMINAL) {
                val.insert(std::make_pair(key, RelationMask::LOWWER));
            } else if(key == BOUNDARY_TERMINAL ) {
                val.insert(std::make_pair(key, RelationMask::GREATER));
            }
            else {
                val.insert(std::make_pair(key, RelationMask::EMPTY));
            }

        }
    }



    for( auto const& [key, val] : grammar )
    {
        for (auto& alternative: val) {
            for (int i = 0; i < (alternative.size() - 1); i++) {

                auto keyL = alternative[i];
                auto keyR = alternative[i + 1];

                table[getRuleLabel(keyL)][getRuleLabel(keyR)] |= RelationMask::EQUALS;

                if (keyR->getType() == Types::NON_TERMINAL) {
                    std::vector<std::string> keys;
                    firstR(keyR->getValue(), keys);

                    for(auto& keyP: keys) {
//                        qDebug() << QString().fromStdString(getRuleLabel(keyL)) << " < " << QString().fromStdString(keyP)
//                                 << " : " << QString().fromStdString(getRuleLabel(keyR));
                        table[getRuleLabel(keyL)][keyP] |= RelationMask::LOWWER;
                    }
                }

                if (keyL->getType() == Types::NON_TERMINAL) {

                        std::vector<std::string> keys;
                        lastR(keyL->getValue(), keys);

                        for(auto& keyP: keys) {
                            table[keyP][getRuleLabel(keyR)] |= RelationMask::GREATER;
                        }

                    if (keyR->getType() == Types::NON_TERMINAL) {
                        std::vector<std::string> keysL;
                        lastR(keyL->getValue(), keysL);

                        std::vector<std::string> keysR;
                        firstR(keyR->getValue(), keysR);

                        for(auto& last: keysL) {
                            for(auto& first: keysR) {
                                table[last][first] |= RelationMask::GREATER;
                            }
                        }
                    }
                }
            }
        }
    }

    return table;
}

PrecedenceTableFormer::~PrecedenceTableFormer()
{
    for( auto const& [key, val] : grammar )
    {
        for(auto const& prtArr: val) {
            for(auto const& ptr: prtArr) {
                delete ptr;
            }
        }
    }
}
