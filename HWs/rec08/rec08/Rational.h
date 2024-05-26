//
//  Rational.h
//  rec08
//
//  Created by Shrey Kharbanda on 3/24/23.
//

// always include non-member functions as prototypes in separate compilation in the header file, including any extra functions
// all extra functions should still be in namespace and it's prototype should be in header and actual definition in cpp

#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>

namespace CS2124{
class Rational{
    friend std::istream& operator>>(std::istream& is, Rational& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    
public:
    
    Rational(int num = 0, int denom = 1);
    
    Rational& operator+=(const Rational& rhs);
    
    Rational& operator++();
    
    Rational operator++(int dummy);
    
    explicit operator bool() const;
    
private:
    void normalize();
    int numerator;
    int denominator;
};


std::istream& operator>>(std::istream& is, Rational& rhs);

std::ostream& operator<<(std::ostream& os, const Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);

bool operator<(const Rational& lhs, const Rational& rhs);

Rational& operator--(Rational& rhs);

Rational operator--(Rational& rhs, int);

bool operator!=(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);


int greatestCommonDivisor(int x, int y);

};

#endif
