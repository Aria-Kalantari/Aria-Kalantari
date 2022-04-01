#ifndef TERM_H
#define TERM_H

#pragma once

#include <string>

class Term
{
public:
    explicit Term(const int = 1, const int = 1);
    Term(const Term&);
    Term(const std::string&);

    void setCoefficient(const int);
    void setExponent(const int);

    int getCoefficient(void) const;
    int getExponent(void) const;

    const Term& operator=(const Term&);

    operator std::string(void) const;

    ~Term();

private:
    int coefficient;
    int exponent;
    int* term;
};

#endif