#ifndef PRECEDENCETABLEFORMER_H
#define PRECEDENCETABLEFORMER_H
#include "map"
#include "string"
#include "vector"

#include "QDebug"

class PrecedenceTableFormer
{
public:

    std::pair<int, std::string> make_reversed_pair(const std::string& val2, size_t val1) {
        return std::pair<int, std::string>(val1, val2);
    }

    template<typename Base, typename T>
    inline bool instanceof(const T&) {
        return std::is_base_of<Base, T>::value;
    }

    typedef size_t lexemCode;

    enum RelationMask {EMPTY = 0, LOWWER = 1, GREATER = 2, EQUALS = 4} ;
    enum Types {TERMINAL, NON_TERMINAL};
    typedef std::map<std::string, std::map<std::string, size_t>> PrecedenceTable;

    class GrammarUnit {
    public:
        virtual std::string getValue() const {return "GrammarUnit";}
        virtual Types getType() const { throw std::runtime_error("errror");}
        virtual ~GrammarUnit() {}
    };


    class NonTerminal: public GrammarUnit {
        std::string value;
    public:
        NonTerminal(std::string value): value(value) {}
        Types getType() const override { return Types::NON_TERMINAL;}
        std::string getValue() const override {return value;}
    };


    class Terminal: public GrammarUnit {
        lexemCode value;
    public:
        Terminal(lexemCode value): value(value) {}
        Types getType() const override { return Types::TERMINAL;}
        std::string getValue() const override {return std::to_string(value);}
    };

    typedef std::vector<std::vector<GrammarUnit*>> grammarRow;

protected:
    std::map<std::string, grammarRow> grammar;
    std::map<lexemCode, std::string> terminals;

    Terminal* T(lexemCode value) {
        return new Terminal(value);
    }

    NonTerminal* NT(std::string value) {
        return new NonTerminal(value);
    }

    void lastR(const std::string unit, std::vector<std::string> &result);
    void firstR(const std::string unit, std::vector<std::string> &result);




public:
    PrecedenceTableFormer();

    std::string getNameByCode(int code);
    std::map<std::string, grammarRow> getGrammar();
    std::string getRuleLabel(const GrammarUnit *unit);

    PrecedenceTable makeTable();
    ~PrecedenceTableFormer();
};

#endif // PRECEDENCETABLEFORMER_H
