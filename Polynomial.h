#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#pragma once

#include "Term.h"

class Polynomial
{
    friend std::ostream& operator<<(std::ostream&, const Polynomial&);

public:
    explicit Polynomial(int = 5);
    Polynomial(const Polynomial&);

    void setSize(const int);
    void setTerms(const Term&);

    int getSize(void) const;
    Term* getTerms(void) const;

    const Polynomial& operator=(const Polynomial&);

    Term& operator[](const int);
    Term operator[](const int) const;

    Polynomial& operator+=(const Polynomial&);
    Polynomial operator+(const Polynomial&);

    Polynomial& operator-=(const Polynomial&);
    Polynomial operator-(const Polynomial&);

    Polynomial& operator*=(const Polynomial&);
    Polynomial operator*(const Polynomial&);

    ~Polynomial();

private:
    int size;
    Term* terms;

    void simplify(void);
};

#endif