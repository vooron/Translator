#ifndef ALGORYTHM_H
#define ALGORYTHM_H


#include <string>


class Algorythm {
public:
    virtual std::pair<std::string, std::string> nextLexem() = 0;
    virtual bool isLast() const noexcept = 0;

    virtual ~Algorythm() {}
};

#endif // ALGORYTHM_H
