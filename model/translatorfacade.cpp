#include "translatorfacade.h"

TranslatorFacade::TranslatorFacade(SyntaxAnalyzer& syntaxAnalyzer): syntaxAnalyzer(syntaxAnalyzer) { }

std::string TranslatorFacade::process(std::string code)
{    
    std::regex isDelims = regex("^[ \t\n]+$");

    if (code.empty() || std::regex_match (code, isDelims)) {
        return "";
    }

    try {
        auto lexicalAnalyzerOutput = analyzeLexems(code);

        this->lexicalAnalyzerOutput = lexicalAnalyzerOutput;

        analyzeSyntax(lexicalAnalyzerOutput);
        analyzeSemantic(lexicalAnalyzerOutput);

        return generateCode(lexicalAnalyzerOutput);

    } catch (const TranslatorException& e) {
        throw e;
    }

}

LexicalAnalyzerOutput TranslatorFacade::getLexicalAnalyzerOutput()
{
    return lexicalAnalyzerOutput;
}

LexicalAnalyzerOutput TranslatorFacade::analyzeLexems(std::string code)
{
    Translator::StringInputStream input(code);

    StatesDiagram algorythm(input);

    std::vector<InputLexemTuple> inputLexems;

    // Types
    inputLexems.push_back(InputLexemTuple{ "int", 1 });
    inputLexems.push_back(InputLexemTuple{ "float", 2 });

    // Cycles and conditional transitions
    inputLexems.push_back(InputLexemTuple{ "do", 3 });
    inputLexems.push_back(InputLexemTuple{ "while", 4 });
    inputLexems.push_back(InputLexemTuple{ "if", 5 });
    inputLexems.push_back(InputLexemTuple{ "then", 6 });
    inputLexems.push_back(InputLexemTuple{ "goto", 7 });

    // IO
    inputLexems.push_back(InputLexemTuple{ "cin", 8 });
    inputLexems.push_back(InputLexemTuple{ "cout", 9 });
    inputLexems.push_back(InputLexemTuple{ ">>", 10 });
    inputLexems.push_back(InputLexemTuple{ "<<", 11 });

    // Mustach
    inputLexems.push_back(InputLexemTuple{ "}", 12 });
    inputLexems.push_back(InputLexemTuple{ "{", 13 });

    // Delimiters
    inputLexems.push_back(InputLexemTuple{ ";", 14 });
    inputLexems.push_back(InputLexemTuple{ ",", 15 });

    // Initialize
    inputLexems.push_back(InputLexemTuple{ "=", 16 });

    // Logical operators
    inputLexems.push_back(InputLexemTuple{ "==", 17 });
    inputLexems.push_back(InputLexemTuple{ "!=", 18 });
    inputLexems.push_back(InputLexemTuple{ ">", 19 });
    inputLexems.push_back(InputLexemTuple{ "<", 20 });
    inputLexems.push_back(InputLexemTuple{ ">=", 21 });
    inputLexems.push_back(InputLexemTuple{ "<=", 22 });

    // Arithmetic operators
    inputLexems.push_back(InputLexemTuple{ "+", 23 });
    inputLexems.push_back(InputLexemTuple{ "-", 24 });
    inputLexems.push_back(InputLexemTuple{ "*", 25 });
    inputLexems.push_back(InputLexemTuple{ "/", 26 });

    // brackets
    inputLexems.push_back(InputLexemTuple{ "(", 27 });
    inputLexems.push_back(InputLexemTuple{ ")", 28 });
    inputLexems.push_back(InputLexemTuple{ "[", 29 });
    inputLexems.push_back(InputLexemTuple{ "]", 30 });

    // logical
    inputLexems.push_back(InputLexemTuple{ "and", 31 });
    inputLexems.push_back(InputLexemTuple{ "or", 32 });
    inputLexems.push_back(InputLexemTuple{ "not", 33 });

    // literals
    inputLexems.push_back(InputLexemTuple{ "true", 34 });
    inputLexems.push_back(InputLexemTuple{ "false", 35 });

    InputLexemTable inputLexemsTable(inputLexems);

    inputLexemsTable.isIdent = [](string lexem, string type) { return (type == "IDN")? true:false; };
    inputLexemsTable.isConst = [](string lexem, string type) { return (regex_match(type, regex("(CONST|FLOAT|EXP)"))) ? true : false; };
    inputLexemsTable.isMark = [](string lexem, string type) { return (type == "MARK") ? true : false; };

    inputLexemsTable.ident = InputLexemTuple{ "IDN", 100 };
    inputLexemsTable.constant = InputLexemTuple{ "CONST", 101 };
    inputLexemsTable.mark = InputLexemTuple{ "MARK", 102 };

    std::vector<char> whiteDeilems({ ' ', '\t' });


    LexicalAnalyzer analyzer{ inputLexemsTable, algorythm, whiteDeilems };

    return analyzer.parse(input);
}

bool TranslatorFacade::analyzeSyntax(LexicalAnalyzerOutput result)
{
    return syntaxAnalyzer.analyze(result);
}

bool TranslatorFacade::analyzeSemantic(LexicalAnalyzerOutput result)
{
    this->lexicalAnalyzerOutput = SemanticUtils::defineTypesAndSemanticCheck(result, {"int", "float"}, 15, 14, "IDN", 7);
    return true;
}

std::string TranslatorFacade::generateCode(LexicalAnalyzerOutput)
{
    return "";
}

