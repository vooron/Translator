#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "lexicalAnalyzer/algorythm.h"
#include "IO/inputstream.h"
#include <vector>
#include "lexicalAnalyzer/inputlexemtable.h"
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include "lexicalAnalyzer/Exceptions/lexicalerror.h"
#include "IO/Exceptions/endoffileexception.h"

class LexicalAnalyzer
{
    InputLexemTable lexemTable;
    Algorythm& algorythm;
    std::vector<char> whiteDeilems;

public:
    LexicalAnalyzer(
        const InputLexemTable& lexemTable,
        Algorythm& algorythm,
        const std::vector<char>& whiteDeilems
    );

    ~LexicalAnalyzer();

    LexicalAnalyzerOutput parse(Translator::InputStream& input);
private:

};

#endif // LEXICALANALYZER_H
