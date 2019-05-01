#include "upstreamanalyzer.h"

UpStreamAnalyzer::UpStreamAnalyzer(): table(PrecedenceTableFormer().makeTable())
{
}

bool UpStreamAnalyzer::isRulesInGrammarRow(std::vector<stack_item> rules, PrecedenceTableFormer::grammarRow variants) {
    for (auto variant: variants) {

        if (variant.size() != rules.size()) {
            continue;
        }

        bool isDifferent = false;

        for (int i = 0; i < variant.size(); i++) {
            if (tableFormer.getRuleLabel(variant[i]) != rules[i]) {
                isDifferent = true;
                break;
            }
        }

        if (!isDifferent) {
            return true;
        }
    }

    return false;
}


bool UpStreamAnalyzer::analyze(const LexicalAnalyzerOutput& input) {

    std::stack<stack_item> st;
    std::vector<OutputLexemTuple> lexSt;
    st.push("#");

    auto lexems = input.getLexems();


    lexems.push_back(OutputLexemTuple{"#", 40, false, false, false, 0, 0, 0, 0});

    int i = 0;
    try {
        for (; i < lexems.size();) {

            TraceItem traceItem;

            auto lexem = tableFormer.getNameByCode(lexems[i].code);

            traceItem.stack = joinStack<stack_item>(st, ", ");
            traceItem.input = lexem;

            if (st.top() == "program") {
                break;
            }

            if (table.at(st.top()).at(lexem) == PrecedenceTableFormer::GREATER) {
                traceItem.relation = " > ";
            } else if (table.at(st.top()).at(lexem) == PrecedenceTableFormer::LOWWER) {
                traceItem.relation = " < ";
            } else {
                traceItem.relation = " = ";
            }

            if (table.at(st.top()).at(lexem) == PrecedenceTableFormer::EMPTY) {
                throw SyntaxisError("Invalid syntax", lexems[i - 1].row);
            }

            if (table.at(st.top()).at(lexem) == PrecedenceTableFormer::GREATER) {

                std::vector<stack_item> rules;
                std::vector<OutputLexemTuple> lexRules;

                stack_item curItem = lexem;
                while (table.at(st.top()).at(curItem) != PrecedenceTableFormer::LOWWER) {
                    curItem = st.top();
                    rules.push_back(curItem);
                    lexRules.push_back(lexSt.back());
                    lexSt.pop_back();
                    st.pop();
                }

                std::reverse(std::begin(rules), std::end(rules));
                std::reverse(std::begin(lexRules), std::end(lexRules));

                traceItem.basis = "";
                for (auto al: rules) {
                    traceItem.basis += " " + al;
                }

                treace.push_back(traceItem);

                bool isKeyFound = false;
                for (auto [key, variants]: tableFormer.getGrammar()) {
                    if (isRulesInGrammarRow(rules, variants)) {

                        isKeyFound = true;
                        st.push(key);
                        lexSt.push_back({});

                        break;
                    }
                }

                if (!isKeyFound) {
                    throw SyntaxisError("Invalid syntax", lexems[i - 1].row);
                }


                continue;
            }


            st.push(lexem);
            lexSt.push_back(lexems[i]);

            treace.push_back(traceItem);
            i++;
        }
    } catch (const std::out_of_range& ) {
        throw SyntaxisError("Invalid symbol", lexems[i - 1].row);
    }

    if (st.size() != 2 || st.top() != "program") {
        throw SyntaxisError("Invalid syntax", lexems[i - 1].row);
    }

    return true;
}

std::vector<UpStreamAnalyzer::TraceItem> UpStreamAnalyzer::getTrace()
{
    return treace;
}
