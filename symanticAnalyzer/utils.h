#ifndef SEMANTIC_ANALYZER_UTILS_H
#define SEMANTIC_ANALYZER_UTILS_H

#include <vector>
#include <string>
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include "symanticAnalyzer/Exceptions/symanticerror.h"
#include <iostream>
#include <vector>

#define DEFINED_STATUS "DEFINED"

using namespace std;


class SemanticUtils {

    struct DefiningUnit {
        OutputLexemTuple* lSide = nullptr;
        std::vector<OutputLexemTuple*> rSide;
    };

    typedef vector<OutputIdentTuple> Idents;

public:
    static LexicalAnalyzerOutput defineTypesAndSemanticCheck(
            LexicalAnalyzerOutput& source,
            const std::vector<std::string>& identTypes,
            size_t softDelimiterCode,
            size_t delimiterCode,
            const std::string& defIdentType,
            size_t gotoCode
        ) {
            auto lexems = source.getLexems();
            auto idents = source.getIdents();

            bool isDefining = false;
            std::string curType;

            DefiningUnit definingUnit;


            for (auto it = lexems.begin(); it != lexems.end(); ++it) {

                if ((*it).isMark) {
                    bool isMarkDefining = (gotoCode != (*(it - 1)).code);
                    if (isMarkDefining) {

                        if (idents[(*it).markCode].value != DEFINED_STATUS) {
                            idents[(*it).markCode].value = DEFINED_STATUS;
                        }
                        else {
                            throw SemanticError("Mark " + (*it).name + " was redeclared ", (*it).row);
                        }
                    }

                    continue;
                }

                for (const auto& type: identTypes)
                {
                    if ((*it).name == type) {
                        isDefining = true;
                        curType = type;
                        break;
                    }
                }

                if ((*it).code == delimiterCode) {
                    isDefining = false;
                    checkAndDefineVars(idents, definingUnit, curType);
                    curType = "";
                    definingUnit = DefiningUnit{};
                    continue;
                }

                if ((*it).code == softDelimiterCode) {
                    checkAndDefineVars(idents, definingUnit, curType);
                    definingUnit = DefiningUnit{};
                    continue;
                }



                if ((*it).isIdent && !isDefining) {

                    if (!isIdentWasDefined(idents, *it)) {
                        throw SemanticError("Ident " + (*it).name + " was not defined ", (*it).row);
                    }

                    continue;
                }

                if ((*it).isIdent && isDefining) {

                    if (definingUnit.lSide == nullptr) {
                        definingUnit.lSide = &*it;
                    } else {
                        definingUnit.rSide.push_back(&*it);
                    }

                }


            }

            for (const auto& lexem: lexems)
            {
                if (lexem.isMark && idents[lexem.markCode].value != DEFINED_STATUS) {
                    throw SemanticError("Mark " + lexem.name + " was not definded ", lexem.row);
                }
            }

            LexicalAnalyzerOutput out;
            out.setLexems(lexems);
            out.setIdents(idents);
            out.setConsts(source.getConsts());

            return out;
        }


private:
    static bool isIdentWasDefined(Idents& idents, OutputLexemTuple& lexem, std::string undefinedIdentType = "IDN") {
        return idents[lexem.identCode].type != undefinedIdentType;
    }

    static void checkAndDefineVars(Idents& idents, DefiningUnit& definigUnit, std::string curType) {

        if (definigUnit.lSide == nullptr) { // if code like int a = 2, ,; that will be deteckted in next step;
            return;
        }

        for (auto el: definigUnit.rSide) {

            if (!isIdentWasDefined(idents, *el)) {
                throw SemanticError("Ident " + (*el).name + " was not declared", (*el).row);
            }
        }

        idents[definigUnit.lSide->identCode].type = curType;
    }
};



#endif // SEMANTIC_ANALYZER_UTILS_H
