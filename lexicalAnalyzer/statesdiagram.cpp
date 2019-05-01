#include "statesdiagram.h"


StatesDiagram::StatesDiagram(Translator::InputStream& input): isLastLexem(false), input(input)
{
    symbolsTable.insert(make_pair("letter", "[a-df-zA-Z]"));
    symbolsTable.insert(make_pair("number", "[0-9]"));
    symbolsTable.insert(make_pair("operator", "[\\[\\]()*\\/{};,]"));
    symbolsTable.insert(make_pair(".", "\\."));
    symbolsTable.insert(make_pair("^", "\\^"));
    symbolsTable.insert(make_pair("e", "e"));
    symbolsTable.insert(make_pair("<", "\\<"));
    symbolsTable.insert(make_pair(">", "\\>"));
    symbolsTable.insert(make_pair("=", "="));
    symbolsTable.insert(make_pair("+", "[+-]"));
    symbolsTable.insert(make_pair(":", ":"));
}

std::pair<string, string> StatesDiagram::nextLexem()
{
    size_t state = 1;

    string lexem = "";
    string ch;

    while (true)
    {
        try {
            ch = string(1, input.getCharWithoutExtracting());
        }
        catch (EndOfFileException& e) {
            ch = "";
            isLastLexem = true;
        }

        switch (state)
        {
        case 1:
            lexem += ch;

            if (isMatch("letter", ch) || isMatch("e", ch)) {
                state = 2;
                input.getChar();
                continue;
            }
            else if (isMatch("number", ch)) {
                state = 3;
                input.getChar();
                continue;
            }
            else if (isMatch(".", ch)) {
                state = 5;
                input.getChar();
                continue;
            }
            else if (isMatch("=", ch)) {
                state = 6;
                input.getChar();
                continue;
            }
            else if (isMatch(">", ch)) {
                state = 7;
                input.getChar();
                continue;
            }
            else if (isMatch("<", ch)) {
                state = 8;
                input.getChar();
                continue;
            }
            else if (isMatch("!", ch)) {
                state = 9;
                input.getChar();
                continue;
            }
            else if (isMatch(":", ch)) {
                state = 10;
                input.getChar();
                continue;
            }
            else if (isMatch("operator", ch)) {
                input.getChar();
                return make_pair(lexem, "operator");
            }
            else if (isMatch("+", ch)) {
                input.getChar();
                return make_pair(lexem, "+");
            }


            break;

        case 2:
            if (isMatch("letter", ch) || isMatch("e", ch) || isMatch("number", ch)) {
                input.getChar();
                lexem += ch;
                continue;
            }
            else {
                return make_pair(lexem, "IDN");
            }
            break;

        case 3:
            if (isMatch("number", ch)) {
                input.getChar();
                lexem += ch;
                continue;
            }
            else if (isMatch(".", ch)) {
                state = 4;
                input.getChar();
                lexem += ch;
                continue;
            }
            else if (isMatch("e", ch)) {
                state = 15;
                input.getChar();
                lexem += ch;
                continue;
            }
            else {
                return make_pair(lexem, "CONST");
            }

            break;

        case 4:
            if (isMatch("number", ch)) {
                input.getChar();
                lexem += ch;
                continue;
            }
            else if (isMatch("e", ch)) {
                state = 15;
                input.getChar();
                lexem += ch;
                continue;
            }
            else {
                return make_pair(lexem, "FLOAT");
            }
            break;

        case 5:
            if (isMatch("number", ch)) {
                state = 4;
                input.getChar();
                lexem += ch;
                continue;
            }
            break;

        case 6:
            if (isMatch("=", ch)) {
                input.getChar();
                lexem += ch;
                return make_pair(lexem, "==");
            }
            else {
                return make_pair(lexem, "=");
            }
            break;

        case 7:
            if (isMatch("=", ch)) {
                input.getChar();
                lexem += ch;
                return make_pair(lexem, ">=");
            }
            else if (isMatch(">", ch)) {
                input.getChar();
                lexem += ch;
                return make_pair(lexem, ">>");
            }
            else {
                return make_pair(lexem, ">");
            }
            break;

        case 8:
            if (isMatch("=", ch)) {
                input.getChar();
                lexem += ch;
                return make_pair(lexem, "<=");
            }
            else if (isMatch("<", ch)) {
                input.getChar();
                lexem += ch;
                return make_pair(lexem, "<<");
            }
            else {
                return make_pair(lexem, "<");
            }
            break;

        case 9:
            if (isMatch("=", ch)) {
                input.getChar();
                lexem += ch;
                return make_pair(lexem, "!=");
            }
            break;

        case 10:
            if (isMatch("letter", ch) || isMatch("e", ch)) {
                state = 11;
                input.getChar();
                lexem += ch;
                continue;
            }
            else {
                return make_pair(lexem, "MARK");
            }
            break;

        case 11:
            if (isMatch("letter", ch) || isMatch("e", ch) || isMatch("number", ch)) {
                input.getChar();
                lexem += ch;
                continue;
            }
            else {
                return make_pair(lexem, "MARK");
            }
            break;

        case 15:
            lexem += ch;

            if (isMatch("number", ch)) {
                state = 16;
                input.getChar();
                continue;
            }
            else if (isMatch("+", ch)) {
                state = 17;
                input.getChar();
                continue;
            }
            break;

        case 17:
            if (isMatch("number", ch)) {
                state = 16;
                lexem += ch;
                input.getChar();
                continue;
            }
            break;

        case 16:
            if (isMatch("number", ch)) {
                input.getChar();
                lexem += ch;
                continue;
            }
            else {
                return make_pair(lexem, "EXP");
            }
            break;
        //default:
        //	throw LexicalError("Lexical error: " + lexem);
        //	break;
        }

        throw LexicalError("Lexical error: " + lexem);
    }

    //return std::pair<std::string, std::string>();
}

bool StatesDiagram::isLast() const noexcept
{
    return isLastLexem;
}


StatesDiagram::~StatesDiagram()
{
}
