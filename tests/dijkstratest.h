#ifndef DIJKSTRATEST_H
#define DIJKSTRATEST_H


#include "lexicalAnalyzer/lexicalanalyzeroutput.h"
#include <QString>
#include "model/translatorfacade.h"
#include "rpnGenerator/dijkstrarpngenerator.h"
#include "rpnGenerator/rpnunit.h"
#include <QDebug>
#include <iostream>

#include "tests/testcase.h"

using namespace std;

class DijrstraTest: public TestCase
{
private:

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

    string getString(vector<RpnUnit*> rpn, string sep = " ") {
        string result;

        result += rpn.front()->getLexem();
        rpn.erase(rpn.begin());

        for (auto i: rpn) {
            result += sep;
            result += i->getLexem();
        }

        return result;
    }

    string getPolisString(string code) {
        DijkstraRpnGenerator rpnGenerator;
        auto lexicalAnalyzerOutput = getLexems(code);
        auto rpn = rpnGenerator.generate(lexicalAnalyzerOutput);
        return getString(rpn);
    }

    void testArithmeticInput() {
        TEST_BEGIN
        string code = "-5 + 6/2 - 5*3";
        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "5 @- 6 2 / + 5 3 * -", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithBrackets() {
        TEST_BEGIN
        string code = "-(5-4)*(2+1)-1";
        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "5 4 - @- 2 1 + * 1 -", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithVarsDeclaration() {
        TEST_BEGIN
        string code = "int a = 3, b = 4; a = 2 + a;";
        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "a 3 = b 4 = a 2 a + =", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithGoto() {
        TEST_BEGIN
        string code = "int a = 3; goto M; a = 3 - 4 * 4";
        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "a 3 = M goto a 3 4 4 * - =", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithLE() {
        TEST_BEGIN
        string code = "not [12 <= 2 + 10] or [true and false]";
        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "12 2 10 + <= not true false and or", __FUNCTION__);
        TEST_PASSED
    }


    void testInputWithCycle() {
        TEST_BEGIN

        UniqueLabelsGenerator::setCounter(0);

        string code = "int a = 2, b = 4;"
                      "do"
                      " a = a + 1;"
                      " b = a + b;"
                      "while [a < 10];"
                      "a = b;";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "a 2 = b 4 = #1 a a 1 + = b a b + = a 10 < #2 jne #1 goto #2 a b =", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithCycleNestedInCycle() {
        TEST_BEGIN

        UniqueLabelsGenerator::setCounter(0);

        string code = "do"
                      " a = a + 1;"
                      " do"
                      "     b = b + 1;"
                      " while b < 3;"
                      "while a < 10;";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "#1 a a 1 + = #3 b b 1 + = b 3 < #4 jne #3 goto #4 a 10 < #2 jne #1 goto #2", __FUNCTION__);
        TEST_PASSED
    }


    void testInputWithCondSt() {
        TEST_BEGIN
        UniqueLabelsGenerator::setCounter(0);

        string code = "if [true] then a = a + 1 }; a = a + 1;";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "true #1 jne a a 1 + = #1 a a 1 + =", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithNestedCondSt() {
        TEST_BEGIN
        UniqueLabelsGenerator::setCounter(0);

        string code = "if true then"
                      "     if false then"
                      "          a = a + 1"
                      "     };"
                      "b = a + 2;"
                      "};"
                      "b = a";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "true #1 jne false #2 jne a a 1 + = #2 b a 2 + = #1 b a =", __FUNCTION__);
        TEST_PASSED
    }

    void testInputWithCycleNestedInCondSt() {
        TEST_BEGIN
        UniqueLabelsGenerator::setCounter(0);

        string code = "if true then"
                      "     do"
                      "         a = a + 1;"
                      "     while a <= 3;"
                      "     a = 2;"
                      "};";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "true #1 jne #2 a a 1 + = a 3 <= #3 jne #2 goto #3 a 2 = #1", __FUNCTION__);
        TEST_PASSED
    }


    void testInputWithCondStNestedInCycle() {
        TEST_BEGIN
        UniqueLabelsGenerator::setCounter(0);

        string code = "do"
                      "     if a < 5 then"
                      "         a = a + 2 };"
                      "while a <= 10;";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "#1 a 5 < #3 jne a a 2 + = #3 a 10 <= #2 jne #1 goto #2", __FUNCTION__);
        TEST_PASSED
    }


    void testInputWithCout() {
        TEST_BEGIN
        UniqueLabelsGenerator::setCounter(0);

        string code = "a = 1; int b = 2;"
                      "cout << a << b;"
                      "b = a;";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "a 1 = b 2 = cout a << cout b << b a =", __FUNCTION__);
        TEST_PASSED
    }


    void testInputWithCin() {
        TEST_BEGIN
        UniqueLabelsGenerator::setCounter(0);

        string code = "int a = 1; int b = 2;"
                      "cin >> a >> b;"
                      "b = a;";

        string rpnStr = getPolisString(code);

        assertTrue(rpnStr == "a 1 = b 2 = cin a >> cin b >> b a =", __FUNCTION__);
        TEST_PASSED
    }

public:

    void test() {
        this->testArithmeticInput();
        this->testInputWithBrackets();
        this->testInputWithVarsDeclaration();
        this->testInputWithGoto();
        this->testInputWithLE();
        this->testInputWithCycle();
        this->testInputWithCycleNestedInCycle();
        this->testInputWithCondSt();
        this->testInputWithNestedCondSt();
        this->testInputWithCycleNestedInCondSt();
        this->testInputWithCondStNestedInCycle();
        this->testInputWithCout();
        this->testInputWithCin();
    }

};
#endif // DIJKSTRATEST_H
