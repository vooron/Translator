#ifndef INPUTLEXEMTABLE_H
#define INPUTLEXEMTABLE_H


#include <vector>
#include "lexicalAnalyzer/utils.h"
#include "lexicalAnalyzer/Exceptions/lexemnotfoundexception.h"
#include <string>

typedef bool(*duoParCond) (std::string lexem, std::string type);

class InputLexemTable
{
    std::vector<InputLexemTuple> lexemTable;
public:

    duoParCond isIdent;
    duoParCond isConst;
    duoParCond isMark;

    InputLexemTuple ident;
    InputLexemTuple constant;
    InputLexemTuple mark;

    InputLexemTable();
    InputLexemTable(const std::vector<InputLexemTuple>& lexemTable);
    ~InputLexemTable();

    size_t getCode(const std::string& lexem) const {
        for (InputLexemTuple tuple: lexemTable)
        {
            if (tuple.lexem == lexem) {
                return tuple.code;
            }
        }

        throw LexemNotFoundException();
    }
};



#endif // INPUTLEXEMTABLE_H
