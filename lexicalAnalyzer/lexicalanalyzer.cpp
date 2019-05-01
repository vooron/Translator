#include "lexicalanalyzer.h"




LexicalAnalyzer::LexicalAnalyzer(
    const InputLexemTable& lexemTable,
    Algorythm& algorythm,
    const std::vector<char>& whiteDeilems
):
    lexemTable(lexemTable), algorythm(algorythm), whiteDeilems(whiteDeilems)
{
}

LexicalAnalyzer::~LexicalAnalyzer()
{
}

LexicalAnalyzerOutput LexicalAnalyzer::parse(Translator::InputStream& input) {
    LexicalAnalyzerOutput output;

    char ch;
    size_t row = 1;

    try {
        while (true) {

            ch = input.getCharWithoutExtracting();

            if (algorythm.isLast()) {
                break;
            }

            while (true) {

                if (ch == '\n') {
                    input.getChar();
                    row++;
                }
                else if (std::find(whiteDeilems.begin(), whiteDeilems.end(), ch) != whiteDeilems.end()) {
                    input.getChar(); // skip
                }
                else {
                    break;
                }

                ch = input.getCharWithoutExtracting();
            }

            auto lexem = algorythm.nextLexem();

            size_t code = 0;

            bool isIdent = lexemTable.isIdent(lexem.first, lexem.second);
            bool isConst = lexemTable.isConst(lexem.first, lexem.second);
            bool isMark = lexemTable.isMark(lexem.first, lexem.second);

            try {
                code = lexemTable.getCode(lexem.first);

                isIdent = false;
                isMark = false;
            }
            catch (const LexemNotFoundException& e) {
                if (isIdent) {
                    code = lexemTable.ident.code;
                }
                else if(isConst)
                {
                    code = lexemTable.constant.code;
                }
                else if (isMark) {
                    code = lexemTable.mark.code;
                }
            }

            size_t identCode = 0;
            size_t markCode = 0;
            if (isIdent) {
                // TODO: check is initialized
                identCode = output.addIdent(lexem.first, lexem.second, "", isMark);
            }

            if (isConst) {
                output.addConst(lexem.first, lexem.second);
            }

            if (isMark) {
                markCode = output.addIdent(lexem.first, lexem.second, "", isMark);
                // TODO: change to addMark(..);
            }

            output.addLexem(
                lexem.first,
                code,
                row,
                isIdent,
                isConst,
                isMark,
                identCode,
                (isConst) ? output.getConsts().size() : 0,
                markCode
            );

        }
    }
    catch (const EndOfFileException& e) {
        return output;
    }
    catch (LexicalError& e) {
        e.setRow(row);
        throw e;
    }

    return output;
}
