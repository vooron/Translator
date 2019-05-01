#include "recursivesyntaxanalyzer.h"

RecursiveSyntaxAnalyzer::RecursiveSyntaxAnalyzer()
{

}

bool RecursiveSyntaxAnalyzer::analyze(const LexicalAnalyzerOutput & result)
{
    const auto& lexems = result.getLexems();
    size_t counter = 0;

    this->lexicalAnalyzerOutput = result;

    try {
        return isProgram(lexems, counter);
    } catch (const std::out_of_range& ) {
        throw SyntaxisError("Incomplit command", lexems.at(counter - 1).row);
    }
}

bool RecursiveSyntaxAnalyzer::isProgram(const std::vector<OutputLexemTuple> & lexems, size_t &i)
{
    return isCommands(lexems, i);
}

bool RecursiveSyntaxAnalyzer::isCommands(const std::vector<OutputLexemTuple> & lexems, size_t &i)
{
    if(!isCommand(lexems, i)) {
        return false;
    }

    if(lexems.at(i).code != 14) { // ;
        throw SyntaxisError("Dot-Comma was left", lexems.at(i).row);
    }

    i++;

    if (i < lexems.size()) {
        if(!isCommands(lexems, i)) {
           throw SyntaxisError("Invalid command", lexems.at(i).row);
        }
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isCommand(const std::vector<OutputLexemTuple> & lexems, size_t &i)
{

    if (
            !isDefining(lexems, i) &&
            !isInit(lexems, i) &&
            !isCycle(lexems, i) &&
            !isCondStatement(lexems, i) &&
            !isInput(lexems, i) &&
            !isOutput(lexems, i) &&
            !isMark(lexems, i) &&
            !isMarkCall(lexems, i)
            ) {
        return false;
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isDefining(const std::vector<OutputLexemTuple> & lexems, size_t &i)
{
    if (!isType(lexems, i)) {
        return false;
    }

    if (!isInit(lexems, i) && !isIdent(lexems, i)) {
        throw SyntaxisError("Error variable defining", lexems.at(i).row);
    }

    while (lexems.at(i).code == 15) { // ,
        i++;

        if (!isInit(lexems, i) && !isIdent(lexems, i)) {
            throw SyntaxisError("Error variable defining", lexems.at(i).row);
        }
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isInit(const std::vector<OutputLexemTuple> & lexems, size_t &i)
{
    if (!isIdent(lexems, i)) {
        return false;
    }

    if (lexems.at(i).code != 16) { // =
        i--;
        return false;
    }

    i++;

    if (!isExpression(lexems, i)) {
        throw SyntaxisError("Is not a valid right-value expression", lexems.at(i).row);
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isType(const std::vector<OutputLexemTuple> & lexems, size_t &i)
{
    if (lexems.at(i).code != 1 && lexems.at(i).code != 2) { // int | float
        return false;
    }

    i++;
    return true;
}

bool RecursiveSyntaxAnalyzer::isExpression(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (!isSign(lexems, i)) { // it can be ^ so we can skip this check
        return false;
    }

    if (!isTerm(lexems, i)) {
        return false;
    }

    while (lexems.at(i).code == 23 || lexems.at(i).code == 24) { // + | -
        i++;

        if (!isTerm(lexems, i)) {
            throw SyntaxisError("Is not a valid term", lexems.at(i).row);
        }
    }
    return true;
}

bool RecursiveSyntaxAnalyzer::isTerm(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (!ismMultiplier(lexems, i)) {
        return false;
    }

    while (lexems.at(i).code == 25 || lexems.at(i).code == 26) { // * | /

        i++;

        if (!ismMultiplier(lexems, i)) {
            throw SyntaxisError("Is not a valid multiplier", lexems.at(i).row);
        }
    }
    return true;
}

bool RecursiveSyntaxAnalyzer::ismMultiplier(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (!isExp(lexems, i) && !isIdent(lexems, i)) {
        if (lexems.at(i).code != 27) { // (
            throw SyntaxisError("Missing `(` ", lexems.at(i).row);
        }

        i++;

        if (!isExpression(lexems, i)) {
            return false;
        }

        if (lexems.at(i).code != 28) { // )
            throw SyntaxisError("Missing `)` ", lexems.at(i).row);
        }

        i++;
    }

    return true;


//    if (isExp(lexems, i) || isIdent(lexems, i)) {
//        return true;
//    }

//    if (lexems.at(i).code == 27) { // (
//        i++;

//        if (!isExpression(lexems, i)) {
//            return false;
//        }

//        if (lexems.at(i).code != 28) { // )
//            throw SyntaxisError("Missing `)` ", lexems.at(i).row);
//        }

//        i++;

//        return true;
//    }

//    return false;
}

bool RecursiveSyntaxAnalyzer::isRelation(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (!isExpression(lexems, i)) {
        return false;
    }

    if (!isLogicalSign(lexems, i)) {
        throw SyntaxisError("Missing logical operator", lexems.at(i).row);
    }

    if (!isExpression(lexems, i)) {
        throw SyntaxisError("Missing right operator", lexems.at(i).row);
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isLogicalSign(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    size_t code = lexems.at(i).code;

    if (code == 17 || code == 18 || code == 19 || code == 20 || code == 21 || code == 22) {
        i++;
        return true;
    }

    return false;
}

bool RecursiveSyntaxAnalyzer::isIdent(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code == 100) { // IDN
        i++;
        return true;
    }

    return false;
}

bool RecursiveSyntaxAnalyzer::isSign(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code == 23 || lexems.at(i).code == 24) {
        i++;
    }

    return true;
}


bool RecursiveSyntaxAnalyzer::isInput(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code != 8) { // cin
        return false;
    }

    i++;

    if (lexems.at(i).code != 10) { // >>
        throw SyntaxisError("Missing >>", lexems.at(i).row);
    }

    i++;

    if (!isIdent(lexems, i)) {
        throw SyntaxisError("variable  was missing ", lexems.at(i).row);
    }

    while (lexems.at(i).code == 10) {
        i++;

        if (!isIdent(lexems, i)) {
            throw SyntaxisError("variable  was missing ", lexems.at(i).row);
        }
    }


    return true;
}

bool RecursiveSyntaxAnalyzer::isOutput(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code != 9) { // cout
        return false;
    }

    i++;

    if (lexems.at(i).code != 11) { // <<
        throw SyntaxisError("Missing <<", lexems.at(i).row);
    }

    i++;

    if (!isIdent(lexems, i)) {
        throw SyntaxisError("Variable  was missing ", lexems.at(i).row);
    }

    while (lexems.at(i).code == 11) {
        i++;

        if (!isIdent(lexems, i)) {
            throw SyntaxisError("Variable was missing ", lexems.at(i).row);
        }
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isLogicalExpr(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (!isLogicalTerm(lexems, i)) {
        return false;
    }

    while (lexems.at(i).code == 32) { // or
        i++;

        if (!isLogicalTerm(lexems, i)) {
            throw SyntaxisError("Missing logical term ", lexems.at(i).row);
        }
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isLogicalTerm(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (!isLogicalF(lexems, i)) {
        return false;
    }

    while (lexems.at(i).code == 31) { // and
        i++;

        if (!isLogicalF(lexems, i)) {
            throw SyntaxisError("Missing logical functor ", lexems.at(i).row);
        }
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isLogicalF(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
//    qDebug() << "Start LogF Lexem = " << QString::fromStdString(lexems.at(i).name);

    if (lexems.at(i).code == 33) { // not
        i++;

        if (!isLogicalF(lexems, i)) {
            throw SyntaxisError("Invalid operator after `not` ", lexems.at(i).row);
        }

        return true;
    }

    if (lexems.at(i).code == 29) { // [
        i++;

        if (!isLogicalExpr(lexems, i)) {
            throw SyntaxisError("Invalid expression after `[` ", lexems.at(i).row);
        }

        if (lexems.at(i).code != 30) { // ]
            throw SyntaxisError("Missing `]` ", lexems.at(i).row);
        }

        i++;

        return true;
    }

    if (isRL(lexems, i)) {
        return true;
    }

    return false;
}

bool RecursiveSyntaxAnalyzer::isRL(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code == 34) { // true
        i++;
        return true;
    }

    if (lexems.at(i).code == 35) { // false
        i++;
        return true;
    }

    if (!isRelation(lexems, i)) {
        throw SyntaxisError("Is not a relation ", lexems.at(i).row);
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isCycle(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code != 3) { // do
        return false;
    }

    i++;

    // isCommands
    do {
        if (!isCommand(lexems, i)) {
            throw SyntaxisError("Invalid command ", lexems.at(i).row);
        }

        if(lexems.at(i).code != 14) { // ;
            throw SyntaxisError("Dot-Comma was left", lexems.at(i).row);
        }

        i++;
    } while (lexems.at(i).code != 4); // while
    i++;
    // end isCommands

    if (!isLogicalExpr(lexems, i)) {
        throw SyntaxisError("missing logical expression ", lexems.at(i).row);
    }

    return true;
}

bool RecursiveSyntaxAnalyzer::isCondStatement(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code != 5) { // if
        return false;
    }

    i++;

    if (!isLogicalExpr(lexems, i)) {
        throw SyntaxisError("missing logical expression ", lexems.at(i).row);
    }

    if (lexems.at(i).code != 6) { // then
        throw SyntaxisError("missing `then` ", lexems.at(i).row);
    }

    i++;

    if (!isCommand(lexems, i)) {
        throw SyntaxisError("missing command after `then` ", lexems.at(i).row);
    }

    return true;

}

bool RecursiveSyntaxAnalyzer::isExp(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).isConst) {
        i++;
        return true;
    }

    return false;
}

bool RecursiveSyntaxAnalyzer::isMark(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).isMark) {
        i++;
        return true;
    }

    return false;
}

bool RecursiveSyntaxAnalyzer::isMarkCall(const std::vector<OutputLexemTuple> &lexems, size_t &i)
{
    if (lexems.at(i).code != 7) {  // goto
        return false;
    }

    i++;

    if (!isMark(lexems, i)) {
        throw SyntaxisError("missing label ", lexems.at(i).row);
    }

    return true;
}
