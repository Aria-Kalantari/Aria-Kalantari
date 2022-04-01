#include "Polynomial.h"
#include <stdexcept>

using namespace std;

Polynomial::Polynomial(int size)
{
    this->setSize(size);
    terms = new Term[this->getSize()];
}

Polynomial::Polynomial(const Polynomial& polynomialToCopy)
    : size(polynomialToCopy.size),
      terms(new Term[polynomialToCopy.size])
{
    for(int i = 0; i < size; ++i)
        this->terms[i] = polynomialToCopy.terms[i];
}


void Polynomial::setSize(const int size)
{
    if(size > 0)
        this->size = size;
    else
        throw out_of_range("Size must be greater than 0.");
}

void Polynomial::setTerms(const Term& term)
{
    static int i = 0;
    
    if(i < this->getSize())
        this->terms[i++] = term;
    else
        throw out_of_range("Index is out of range");
}


int Polynomial::getSize(void) const { return this->size; }

Term* Polynomial::getTerms(void) const { return terms; }


const Polynomial& Polynomial::operator=(const Polynomial& right)
{
    if(this != &right)
    {
        if(this->getSize() != right.getSize())
        {
            delete[] this->terms;
            this->size = right.getSize();
            this->terms = new Term[this->getSize()];
        }

        for(int i = 0; i < this->getSize(); ++i)
            this->terms[i] = right.terms[i];
    }
    return *this;
}


Term& Polynomial::operator[](const int index)
{
    if(index < 0 || index >= this->getSize())
        throw out_of_range("Index is out of range.");
    else
        return this->terms[index];
}

Term Polynomial::operator[](const int index) const
{
    if(index < 0 || index >= this->getSize())
        throw out_of_range("Index is out of range.");
    else
        return this->terms[index];    
}


Polynomial& Polynomial::operator+=(const Polynomial& right)
{
    Polynomial sum(this->getSize() + right.getSize());

    for(int i = 0; i < this->getSize(); ++i)
        sum[i] = (*this)[i];
    for(int i = this->getSize(); i < sum.getSize(); ++i)
        sum[i] = right[i - this->getSize()];

    sum.simplify();
    *this = sum;
    return *this;
}

Polynomial Polynomial::operator+(const Polynomial& right)
{
    Polynomial sum(*this);
    sum += right;
    return sum;
}


Polynomial& Polynomial::operator-=(const Polynomial& right)
{
    Polynomial difference(this->getSize() + right.getSize());

    for(int i = 0; i < this->getSize(); ++i)
        difference[i] = (*this)[i];
    for(int i = this->getSize(); i < difference.getSize(); ++i)
    {
        difference.terms[i].setCoefficient(-(right.terms[i - this->getSize()].getCoefficient()));
        difference.terms[i].setExponent(right.terms[i - this->getSize()].getExponent());
    }

    difference.simplify();
    *this = difference;
    return *this;  
}

Polynomial Polynomial::operator-(const Polynomial& right)
{
    Polynomial difference(*this);
    difference -= right;
    return difference;
}


Polynomial& Polynomial::operator*=(const Polynomial& right)
{
    Polynomial product(this->getSize() * right.getSize());
    int whichTerm = 0;

    for(int i = 0; i < this->getSize(); ++i)
        for(int j = 0; j < right.getSize(); ++j)
        {
            product.terms[whichTerm].setCoefficient(this->terms[i].getCoefficient() * right.terms[j].getCoefficient());
            product.terms[whichTerm].setExponent(this->terms[i].getExponent() + right.terms[j].getExponent());
            ++whichTerm;
        }

    product.simplify();
    *this = product;
    return *this;
}

Polynomial Polynomial::operator*(const Polynomial& right)
{
    Polynomial product(*this);
    product *= right;
    product.simplify();
    return product;
}


Polynomial::~Polynomial() { delete[] terms; }


void Polynomial::simplify(void)
{
    for(int i = 0; i < this->getSize(); ++i)
        for(int j = i + 1; j < this->getSize(); ++j)
            if(this->terms[i].getExponent() == 
               this->terms[j].getExponent())
            {
                this->terms[i].setCoefficient(this->terms[i].getCoefficient() + 
                                              this->terms[j].getCoefficient());
                                            
                Polynomial temp;
                temp.setSize(this->getSize() - 1);
                temp.terms = new Term[temp.getSize()];

                for(int k = 0; k < j; ++k)
                    temp[k] = (*this)[k];
                for(int k = j + 1; k < this->getSize(); ++k)
                    temp[k - 1] = (*this)[k];

                *this = temp;
                --j;
            }
}


ostream& operator<<(ostream& output, const Polynomial& polynomial)
{
    string str;

    for(int i = 0; i < polynomial.getSize(); ++i)
        if(polynomial.terms[i].getCoefficient() == 0)
        {
            if(i == polynomial.getSize() - 1)
            {
                output << str;
                return output;
            }
            else
                continue;
        }

    for(int i = 0; i < polynomial.getSize(); ++i)
    {
            if(polynomial.terms[i].getCoefficient() > 1 && polynomial.terms[i].getExponent() != 1 && polynomial.terms[i].getExponent() != 0)
                str += " + " + to_string(polynomial.terms[i].getCoefficient()) + "x^" +
                               to_string(polynomial.terms[i].getExponent());
            if(polynomial.terms[i].getCoefficient() > 1 && polynomial.terms[i].getExponent() == 1)
                str += " + " + to_string(polynomial.terms[i].getCoefficient()) + "x";
            if(polynomial.terms[i].getCoefficient() > 1 && polynomial.terms[i].getExponent() == 0)
                str += " + " + to_string(polynomial.terms[i].getCoefficient());
            if(polynomial.terms[i].getCoefficient() == 1 && polynomial.terms[i].getExponent() != 1 && polynomial.terms[i].getExponent() != 0)
                str += " + x^" + to_string(polynomial.terms[i].getExponent());
            if(polynomial.terms[i].getCoefficient() == 1 && polynomial.terms[i].getExponent() == 1)
                str += " + x";
            if(polynomial.terms[i].getCoefficient() == 1 && polynomial.terms[i].getExponent() == 0)
                str += " + " + to_string(polynomial.terms[i].getCoefficient());
            if(polynomial.terms[i].getCoefficient() < -1 && polynomial.terms[i].getExponent() != 1 && polynomial.terms[i].getExponent() != 0)
                str += " - " + to_string(-polynomial.terms[i].getCoefficient()) + "x^" +
                               to_string(polynomial.terms[i].getExponent());
            if(polynomial.terms[i].getCoefficient() < -1 && polynomial.terms[i].getExponent() == 1)
                str += " - " + to_string(-polynomial.terms[i].getCoefficient()) + "x";
            if(polynomial.terms[i].getCoefficient() < -1 && polynomial.terms[i].getExponent() == 0)
                str += " + " + to_string(polynomial.terms[i].getCoefficient());
            if(polynomial.terms[i].getCoefficient() == -1 && polynomial.terms[i].getExponent() != 1 && polynomial.terms[i].getExponent() != 0)
                str += " - x^" + to_string(polynomial.terms[i].getExponent());
            if(polynomial.terms[i].getCoefficient() == -1 && polynomial.terms[i].getExponent() == 1)
                str += " - x";
            if(polynomial.terms[i].getCoefficient() == -1 && polynomial.terms[i].getExponent() == 0)
                str += " + " + to_string(polynomial.terms[i].getCoefficient());
    }

    str = str.substr(3);
    
    output << str;
    return output;
}