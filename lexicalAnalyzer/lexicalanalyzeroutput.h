#ifndef LEXICALANALYZEROUTPUT_H
#define LEXICALANALYZEROUTPUT_H

#include <vector>
#include "lexicalAnalyzer/utils.h"

struct LexicalAnalyzerOutput
{
private:
    std::vector<OutputLexemTuple> lexems;
    std::vector<OutputIdentTuple> idents;
    std::vector<OutputConstTuple> consts;

public:

    void setLexems(const std::vector<OutputLexemTuple>& lexems) {
        this->lexems = lexems;
    }

    void setIdents(const std::vector<OutputIdentTuple>& idents) {
        this->idents = idents;
    }

    void setConsts(const std::vector<OutputConstTuple>& consts) {
        this->consts = consts;
    }



    std::vector<OutputLexemTuple> getLexems() const noexcept {
        return lexems;
    }

    std::vector<OutputIdentTuple> getIdents() const noexcept {
        return idents;
    }

    std::vector<OutputConstTuple> getConsts() const noexcept {
        return consts;
    }

    void addLexem(
        std::string name,
        size_t code,
        size_t row,
        bool isIdent = false,
        bool isConst = false,
        bool isMark = false,
        size_t identCode = 0,
        size_t constCode = 0,
        size_t markCode = 0
    ) {
        lexems.push_back(OutputLexemTuple{name, code, isIdent, isConst, isMark, identCode, constCode, markCode, row});
    }

    void addConst(std::string name, std::string type) {
        consts.push_back(OutputConstTuple{name, type});
    }

    long addIdent(std::string name, std::string type, std::string value, bool isMark = false) {
        long code = identCode(name);
        if (code != -1) {
            if (isMark) {
                //if (!idents[code].isMark) {
                //	//throw SemanticError(name + "was defined erlier");
                //	throw LexicalError(name + " mark used before defined "); // FIX: Semantic Analyzer logic in Lexem Analyzer
                //}

                idents[code].isMark = true;
            }

            return code;
        }
        else {
            idents.push_back(OutputIdentTuple{ name, type, value, isMark });
            return idents.size() - 1;
        }
    }

private:
    long identCode(std::string name) {
        long code = 0;
        for (const auto& tuple: idents)
        {
            if (tuple.name == name) {
                return code;
            }

            code++;
        }

        return -1;
    }


};



#endif // LEXICALANALYZEROUTPUT_H
