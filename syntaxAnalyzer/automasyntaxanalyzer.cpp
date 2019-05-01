#include "automasyntaxanalyzer.h"

AutomaSyntaxAnalyzer::AutomaSyntaxAnalyzer()
{
    subautomaName programm = "programm";
    subautomaName command = "command";
    subautomaName expression = "expression";
    subautomaName LE = "LE";

    // subautomas
    automa.insert(std::make_pair(programm, states{}));
    automa.insert(std::make_pair(command, states{}));
    automa.insert(std::make_pair(expression, states{}));
    automa.insert(std::make_pair(LE, states{}));

    // states

    StateInfo state_1;
    state_1.notEquals = makeSubautomaArc(command, 5, EMPTY_LABEL, 2);

    StateInfo state_2;
    state_2.arcs.push_back(makeArc(3, 14)); // ;

    StateInfo state_3;
    state_3.isFinal = true;
    state_3.notEquals = makeArc(1, EMPTY_LABEL);

    automa.at(programm).insert(std::make_pair(1, state_1));
    automa.at(programm).insert(std::make_pair(2, state_2));
    automa.at(programm).insert(std::make_pair(3, state_3));

    StateInfo state_5;
    state_5.arcs.push_back(makeArc(11, 1));
    state_5.arcs.push_back(makeArc(11, 2));
    state_5.arcs.push_back(makeArc(16, 100)); // id
    state_5.arcs.push_back(makeArc(71, 3));   // do
    state_5.arcs.push_back(makeSubautomaArc(LE, 50, 5, 76));    // if
    state_5.arcs.push_back(makeArc(41, 8)); // cin
    state_5.arcs.push_back(makeArc(45, 9)); // cout
    state_5.arcs.push_back(makeArc(6, 102));    // mark
    state_5.arcs.push_back(makeArc(81, 7)); // goto

    StateInfo state_11;
    state_11.arcs.push_back(makeArc(12, 100));  // id

    StateInfo state_12;
    state_12.isFinal = true;
    state_12.arcs.push_back(makeArc(11, 15)); // ,
    state_12.arcs.push_back(makeSubautomaArc(expression, 20, 16, 13)); // =

    StateInfo state_13;
    state_13.arcs.push_back(makeArc(11, 15)); // ,
    state_13.notEquals = makeArc(6, EMPTY_LABEL);

    StateInfo state_6;
    state_6.isFinal = true;

    StateInfo state_16;
    state_16.arcs.push_back(makeSubautomaArc(expression, 20, 16, 6)); // =

    StateInfo state_71;
    state_71.notEquals = makeSubautomaArc(command, 5, EMPTY_LABEL, 73);

    StateInfo state_72;
    state_72.arcs.push_back(makeSubautomaArc(LE, 50, 4, 6)); // while
    state_72.notEquals = makeArc(71, EMPTY_LABEL);

    StateInfo state_73;
    state_73.arcs.push_back(makeArc(72, 14)); // ;

    StateInfo state_76;
    state_76.arcs.push_back(makeSubautomaArc(command, 5, 6, 6)); // then

    StateInfo state_41;
    state_41.arcs.push_back(makeArc(42, 10)); // >>

    StateInfo state_42;
    state_42.arcs.push_back(makeArc(43, 100)); // id

    StateInfo state_43;
    state_43.arcs.push_back(makeArc(42, 10)); // >>
    state_43.notEquals = makeArc(6, EMPTY_LABEL);

    StateInfo state_45;
    state_45.arcs.push_back(makeArc(46, 11)); // <<

    StateInfo state_46;
    state_46.arcs.push_back(makeArc(47, 100)); // id

    StateInfo state_47;
    state_47.arcs.push_back(makeArc(46, 11)); // <<
    state_47.notEquals = makeArc(6, EMPTY_LABEL);

    StateInfo state_81;
    state_81.arcs.push_back(makeArc(6, 102)); // mark

    automa.at(command).insert(std::make_pair(5, state_5));
    automa.at(command).insert(std::make_pair(11, state_11));
    automa.at(command).insert(std::make_pair(12, state_12));
    automa.at(command).insert(std::make_pair(13, state_13));
    automa.at(command).insert(std::make_pair(6, state_6));
    automa.at(command).insert(std::make_pair(16, state_16));
    automa.at(command).insert(std::make_pair(71, state_71));
    automa.at(command).insert(std::make_pair(72, state_72));
    automa.at(command).insert(std::make_pair(73, state_73));
    automa.at(command).insert(std::make_pair(76, state_76));
    automa.at(command).insert(std::make_pair(41, state_41));
    automa.at(command).insert(std::make_pair(42, state_42));
    automa.at(command).insert(std::make_pair(43, state_43));
    automa.at(command).insert(std::make_pair(45, state_45));
    automa.at(command).insert(std::make_pair(46, state_46));
    automa.at(command).insert(std::make_pair(47, state_47));
    automa.at(command).insert(std::make_pair(81, state_81));


    StateInfo state_20;
    state_20.arcs.push_back(makeArc(30, 23)); // +
    state_20.arcs.push_back(makeArc(30, 24)); // -
    state_20.notEquals = makeArc(30, EMPTY_LABEL);

    StateInfo state_30;
    state_30.arcs.push_back(makeArc(21, 101)); // exp
    state_30.arcs.push_back(makeArc(21, 100)); // id
    state_30.arcs.push_back(makeArc(32, 27)); // (

    StateInfo state_32;
    state_32.notEquals = makeSubautomaArc(expression, 20, EMPTY_LABEL, 33);

    StateInfo state_33;
    state_33.arcs.push_back(makeArc(21, 28)); // )

    StateInfo state_21;
    state_21.isFinal = true;
    state_21.arcs.push_back(makeArc(30, 23)); // +
    state_21.arcs.push_back(makeArc(30, 24)); // -
    state_21.arcs.push_back(makeArc(30, 25)); // *
    state_21.arcs.push_back(makeArc(30, 26)); // /

    automa.at(expression).insert(std::make_pair(20, state_20));
    automa.at(expression).insert(std::make_pair(30, state_30));
    automa.at(expression).insert(std::make_pair(32, state_32));
    automa.at(expression).insert(std::make_pair(33, state_33));
    automa.at(expression).insert(std::make_pair(21, state_21));


    StateInfo state_50;
    state_50.arcs.push_back(makeArc(50, 33)); // not
    state_50.arcs.push_back(makeArc(61, 34)); // true
    state_50.arcs.push_back(makeArc(61, 35)); // false

    state_50.arcs.push_back(makeSubautomaArc(LE, 50, 29, 62)); // [
    state_50.notEquals = makeSubautomaArc(expression, 20, EMPTY_LABEL, 63);

    StateInfo state_62;
    state_62.arcs.push_back(makeArc(61, 30)); // ]

    StateInfo state_63;
    state_63.arcs.push_back(makeSubautomaArc(expression, 20, 17, 61));
    state_63.arcs.push_back(makeSubautomaArc(expression, 20, 18, 61));
    state_63.arcs.push_back(makeSubautomaArc(expression, 20, 19, 61));
    state_63.arcs.push_back(makeSubautomaArc(expression, 20, 20, 61));
    state_63.arcs.push_back(makeSubautomaArc(expression, 20, 21, 61));
    state_63.arcs.push_back(makeSubautomaArc(expression, 20, 22, 61));

    StateInfo state_61;
    state_61.isFinal = true;
    state_61.arcs.push_back(makeArc(50, 31)); // and
    state_61.arcs.push_back(makeArc(50, 32)); // or

    automa.at(LE).insert(std::make_pair(50, state_50));
    automa.at(LE).insert(std::make_pair(62, state_62));
    automa.at(LE).insert(std::make_pair(63, state_63));
    automa.at(LE).insert(std::make_pair(61, state_61));

    for (auto it = automa.begin(); it != automa.end(); ++it)
    {
        for (auto it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
        {
            auto& state = (*it2).second;


            AutomaConfItem conf;
            conf.alphaState = (*it2).first;
            conf.betaState = EMPTY_STATE;
            conf.label = EMPTY_LABEL;
            conf.stack = EMPTY_STATE;

            if (state.notEquals.label == EMPTY_LABEL) {
                conf.semanticSubpr = "[not=] ";
                if(state.notEquals.isSubautoma) {
                    conf.semanticSubpr += state.notEquals.subautoma.empty()? state.notEquals.subautoma : (*it).first;
                    conf.stack = state.notEquals.stack;
                } else {
                    conf.semanticSubpr = "";
                    conf.betaState = state.notEquals.state;
                }
            } else if (state.isFinal) {
                conf.semanticSubpr += "[not=] exit";
            } else {
                conf.semanticSubpr += "[not=] err";
            }

            conf.label = EMPTY_LABEL;

            automaConf.push_back(conf);

            for (auto it3 = state.arcs.begin(); it3 != state.arcs.end(); ++it3)
            {
                AutomaConfItem conf;
                conf.alphaState = 0;

                conf.label = (*it3).label;
                conf.stack = (*it3).stack;
                conf.betaState = (*it3).state;

                if ((*it3).isSubautoma) {
                    conf.semanticSubpr = "[=] " + (*it3).subautoma;
                }

                automaConf.push_back(conf);

            }

        }
    }

}

bool AutomaSyntaxAnalyzer::analyze(const LexicalAnalyzerOutput &lexicalAnalyzerOutput)
{
    size_t i = 0;
    size_t state = 1;
    std::string automaName = "programm";

    auto lexems = lexicalAnalyzerOutput.getLexems();
    StateInfo& curState = automa.at(automaName).at(state);

    bool statusChanged;

    while (i < lexems.size()) {
        OutputLexemTuple& lexem = lexems.at(i);
        StateInfo& curState = automa.at(automaName).at(state);

        std::stringstream str;
        for (auto val: stack) {
            str << val.second << " ";
        }

        TraceItem traceItem;
        traceItem.cState = state;
        traceItem.lexem = lexem.name;
        traceItem.stack = std::string(str.str());
        trace.push_back(traceItem);

        statusChanged = false;


        foreach (Arc arc, curState.arcs) {
            if (arc.label == lexem.code) {

                state = arc.state;

                if (arc.isSubautoma) {
                    stack.push_back(make_pair(automaName, arc.stack));

                    if (!arc.subautoma.empty()) {
                        automaName = arc.subautoma;
                    }

                }

                statusChanged = true;
                i++;
                break;
            }
        }

        if (statusChanged) {
            continue;
        }


        if (curState.notEquals.label == EMPTY_LABEL) {

            state = curState.notEquals.state;

            if (curState.notEquals.isSubautoma) {
                auto a = make_pair(automaName, curState.notEquals.stack);

                stack.push_back(a);


                if (!curState.notEquals.subautoma.empty()) {
                    automaName = curState.notEquals.subautoma;
                }

            }

            continue;
        }


        if (curState.isFinal) {

            if (!stack.empty()) {
                auto temp = stack.at(stack.size()-1);

                state = temp.second;
                automaName = temp.first;

                stack.pop_back();
                continue;
            }

            break;
        }

        throw SyntaxisError("Invalid syntax", lexem.row);
    }

    if (!automa.at(automaName).at(state).isFinal || !stack.empty()) {
        throw SyntaxisError("Incomplit syntax", lexems.at(i-1).row);
    }

    return true;

}

std::vector<AutomaSyntaxAnalyzer::TraceItem> AutomaSyntaxAnalyzer::getTrace()
{
    return trace;
}

std::vector<AutomaSyntaxAnalyzer::AutomaConfItem> AutomaSyntaxAnalyzer::getConf()
{
    return automaConf;
}

AutomaSyntaxAnalyzer::Arc AutomaSyntaxAnalyzer::makeSubautomaArc(
        AutomaSyntaxAnalyzer::subautomaName nextSubautoma,
        AutomaSyntaxAnalyzer::stateNum nextState,
        AutomaSyntaxAnalyzer::lexemCode label,
        AutomaSyntaxAnalyzer::stateNum stack)
{
    return Arc{true, nextSubautoma, nextState, label, stack};
}

AutomaSyntaxAnalyzer::Arc AutomaSyntaxAnalyzer::makeArc(AutomaSyntaxAnalyzer::stateNum nextState, AutomaSyntaxAnalyzer::lexemCode label)
{
    subautomaName currentSubautoma = "";

    return Arc{false, currentSubautoma, nextState, label, EMPTY_STATE};
}
