#ifndef UPSTREAMANALYZER_H
#define UPSTREAMANALYZER_H

#include "syntaxanalyzer.h"
#include "stack"
#include "precedencetableformer.h"
#include "vector"
#include "map"
#include <syntaxAnalyzer/Exceptions/syntaxiserror.h>
#include "string"
#include "QDebug"
#include "lexicalAnalyzer/utils.h"

#include <algorithm>
#include <iterator>


class UpStreamAnalyzer: public SyntaxAnalyzer
{
public:
    typedef std::string stack_item;

    struct TraceItem {
        std::string input;
        std::string stack;
        std::string relation;
        std::string basis;
    };

    UpStreamAnalyzer();

    bool analyze(const LexicalAnalyzerOutput&);
    std::vector<TraceItem> getTrace();


    ~UpStreamAnalyzer() {}

private:

    std::vector<TraceItem> treace;

    PrecedenceTableFormer::PrecedenceTable table;
    PrecedenceTableFormer tableFormer;

    bool isRulesInGrammarRow(std::vector<stack_item> rules, PrecedenceTableFormer::grammarRow variants);


    template<typename T>
    std::string joinStack(std::stack<T> st, std::string delim) {

        size_t size = st.size();

        std::string result = "";

        std::vector<T> target;

        size_t i = 0;
        while(i < size) {
            target.push_back(st.top());
            st.pop();
            i++;
        }

        st.push(target[target.size() - 1]);
        result += target[target.size() - 1];
        target.pop_back();

        std::reverse(std::begin(target), std::end(target));

        for (auto i: target) {

            st.push(i);
            result += delim;
            result += i;
        }

        return result;
    }



};

#endif // UPSTREAMANALYZER_H
