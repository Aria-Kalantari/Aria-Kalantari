#include "Term.h"
#include <string>

using namespace std;

Term::Term(const int coefficient, const int exponent)
    : coefficient(coefficient),
      exponent(exponent), 
      term(new int[2])
{
    this->term[0] = this->coefficient;
    this->term[1] = this->exponent;
}

Term::Term(const Term& termToCopy)
    : coefficient(termToCopy.coefficient),
      exponent(termToCopy.exponent),
      term(new int[2])
{
    this->term[0] = this->coefficient;
    this->term[1] = this->exponent;
}

Term::Term(const string& termString)
{
    if(termString.at(0) == '-')
    {
        this->coefficient = -(termString.at(1) - '0');
        if(termString.at(4) == '-')
            this->exponent = -(termString.at(5) - '0');
        else
            this->exponent = termString.at(4) - '0';
    }
    if(termString.at(0) != '-')
    {
        this->coefficient = termString.at(0) - '0';
        if(termString.at(3) == '-')
            this->exponent = -(termString.at(4) - '0');
        else
            this->exponent = termString.at(3) - '0';
    }
}


void Term::setCoefficient(const int coefficient)
{ 
    this->coefficient = coefficient; 
    this->term[0] = this->coefficient;
}

void Term::setExponent(const int exponent)
{
    this->exponent = exponent;
    this->term[1] = this->exponent;
}


int Term::getCoefficient(void) const { return this->coefficient; }

int Term::getExponent(void) const { return this->exponent; }


const Term& Term::operator=(const Term& right)
{
    if(this != &right)
    {
        this->coefficient = right.getCoefficient();
        this->exponent = right.getExponent();
        this->term[0] = right.getCoefficient();
        this->term[1] = right.getExponent();
    }
    return *this;
}


Term::operator string(void) const
{
    string termString;
    termString = to_string(this->coefficient) + "x^" + to_string(this->exponent);
    return termString;
}


Term::~Term() { delete[] term; }