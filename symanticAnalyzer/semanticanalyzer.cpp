#include "semanticanalyzer.h"

SemanticAnalyzer::SemanticAnalyzer()
{

}

LexicalAnalyzerOutput SemanticAnalyzer::analyze(LexicalAnalyzerOutput & lexicalAnalyzerOutput)
{
    return SemanticUtils::defineTypesAndSemanticCheck(lexicalAnalyzerOutput, {"int", "float"}, 15, 14, "IDN", 7);
}
