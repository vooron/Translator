#ifndef SEMANTICANALYZERTEST_H
#define SEMANTICANALYZERTEST_H

#include "tests/testcase.h"
#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include <QString>
#include "model/translatorfacade.h"
#include "rpnGenerator/dijkstrarpngenerator.h"
#include "rpnGenerator/rpnunit.h"
#include <QDebug>
#include <iostream>
#include <symanticAnalyzer/semanticanalyzer.h>
#include <symanticAnalyzer/Exceptions/symanticerror.h>

using namespace std;

class SemanticAnalyzerTest: public TestCase {


    LexicalAnalyzerOutput getLexems(string code) {
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

    LexicalAnalyzerOutput analyze(string code) {
        SemanticAnalyzer semanticAnalyzer;
        LexicalAnalyzerOutput lexicalAnalyzerOutput = getLexems(code);
        return semanticAnalyzer.analyze(lexicalAnalyzerOutput);
    }

    void testDefiningWithLiteral() {
        TEST_BEGIN

        string code  = "int a = 1;";
        analyze(code);

        TEST_PASSED
    }

    void testDefiningWithExistingVar() {
        TEST_BEGIN

        string code  = "int a = 1; int b = a;";
        analyze(code);

        TEST_PASSED
    }

    void testDefiningWithExistingVarInline() {
        TEST_BEGIN

        string code  = "int a = 1, b = a;";
        analyze(code);

        TEST_PASSED
    }

    void testDefiningWithUndefinedIdent() {
        TEST_BEGIN

        try {
            string code  = "int a = b;";
            analyze(code);

            shouldThrowBefore(__FUNCTION__);
        } catch (SemanticError) {}

        TEST_PASSED
    }

    void testDefiningWithUndefinedIdentComplex() {
        TEST_BEGIN

        try {
            string code  = "int a = b + 1;";
            analyze(code);

            shouldThrowBefore(__FUNCTION__);
        } catch (SemanticError) {}

        TEST_PASSED
    }

    void testDefiningWithSelf() {
        TEST_BEGIN

        try {
            string code  = "int a = a;";
            analyze(code);

            shouldThrowBefore(__FUNCTION__);
        } catch (SemanticError) {}

        TEST_PASSED
    }

    void testDefiningWithSelfComplex() {
        TEST_BEGIN

        try {
            string code  = "int a = a + 1;";
            analyze(code);

            shouldThrowBefore(__FUNCTION__);
        } catch (SemanticError) {}

        TEST_PASSED
    }

    void testDefiningWithSelfAndUndefinedComplex() {
        TEST_BEGIN

        try {
            string code  = "int a = a + b;";
            analyze(code);

            shouldThrowBefore(__FUNCTION__);
        } catch (SemanticError) {}

        TEST_PASSED
    }

    void testSigningToUndefinedVar() {
        TEST_BEGIN

        try {
            string code  = "a = 2 + 3;";
            analyze(code);
        } catch (SemanticError) {}

        TEST_PASSED
    }

    void testSigningUndefinedVarToDefinedVar() {
        TEST_BEGIN

        try {
            string code  = "int a = 2; b = a + 1;";
            analyze(code);
        } catch (SemanticError) {}

        TEST_PASSED
    }



public:
    void test() {
        testDefiningWithLiteral();
        testDefiningWithExistingVar();
        testDefiningWithExistingVarInline();
        testDefiningWithUndefinedIdent();
        testDefiningWithUndefinedIdentComplex();
        testDefiningWithSelf();
        testDefiningWithSelfComplex();
        testDefiningWithSelfAndUndefinedComplex();
        testSigningToUndefinedVar();
        testSigningUndefinedVarToDefinedVar();
    }
};



#endif // SEMANTICANALYZERTEST_H
