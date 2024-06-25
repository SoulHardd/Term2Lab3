
#ifndef COMPLEX_H
#define COMPLEX_H

#include <cmath>
#include <iostream>

class Complex
{
public:
    double re;
    double im;

    Complex()
    {
        re = 0;
        im = 0;
    }

    Complex(double re, double im)
    {
        this->re = re;
        this->im = im;
    }

    bool operator>(Complex c) const
    {
        return re * re + im * im > c.re * c.re + c.im * c.im;
    }

    bool operator<(Complex c) const
    {
        return re * re + im * im < c.re * c.re + c.im * c.im;
    }

    bool operator>=(Complex c) const
    {
        return re * re + im * im >= c.re * c.re + c.im * c.im;
    }

    bool operator<=(Complex c) const
    {
        return re * re + im * im <= c.re * c.re + c.im * c.im;
    }

    bool operator==(Complex c) const
    {
        return re == c.re && im == c.im;
    }

    bool operator!=(Complex c) const
    {
        return re != c.re || im != c.im;
    }

    Complex operator+(Complex c) const
    {
        return {re + c.re, im + c.im};
    }

    Complex operator-(Complex c) const
    {
        return {re - c.re, im - c.im};
    }

    friend std::ostream &operator<<(std::ostream &os, const Complex &c)
    {
        if (c.im >= 0)
        {
            return os << c.re << " + " << c.im << "i";
        }
        else
        {
            return os << c.re << " - " << -1 * c.im << "i";
        }
    }
};

#endif
