//
//  Rational.cpp
//  rec08
//
//  Created by Shrey Kharbanda on 3/24/23.
//

#include <iostream>
#include "Rational.h"

namespace CS2124{

// do not repeat default arguments
Rational::Rational(int num, int denom): numerator(num), denominator(denom){
    normalize();
};

Rational& Rational::operator+=(const Rational& rhs){
    numerator = (numerator*rhs.denominator) + (rhs.numerator*denominator);
    denominator *= rhs.denominator;
    normalize();
    return *this;
};

Rational& Rational::operator++(){
    numerator = (numerator+denominator);
    normalize();
    return *this;
};

Rational Rational::operator++(int){
    Rational result(*this);
    numerator = (numerator+denominator);
    normalize();
    return result;
};

// explicit can only be used inside a class

Rational::operator bool() const{
    return (numerator != 0);
}

void Rational::normalize(){
    int gcd = greatestCommonDivisor(abs(numerator), abs(denominator));
    numerator /= gcd;
    denominator /= gcd;
    if (denominator<0){
        numerator *= -1;
        denominator *= -1;
    };
};

std::istream& operator>>(std::istream& is, Rational& rhs){
    char ch;
    is >> rhs.numerator >> ch >> rhs.denominator;
    rhs.normalize();
    return is;
};

std::ostream& operator<<(std::ostream& os, const Rational& rhs){
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
};

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result(lhs);
    result += rhs;
    return result;
};

bool operator==(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator==rhs.numerator) && (lhs.denominator==rhs.denominator);
};

bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator*rhs.denominator < rhs.numerator*lhs.denominator);
};

Rational& operator--(Rational& rhs){
    rhs += Rational(-1);
    return rhs;
};

Rational operator--(Rational& rhs, int){
    Rational result(rhs);
    rhs += Rational(-1);
    return result;
};

bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs);
};

bool operator<=(const Rational& lhs, const Rational& rhs){
    return (lhs==rhs) || (lhs<rhs);
};

bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs) && !(lhs<rhs);
};

bool operator>=(const Rational& lhs, const Rational& rhs){
    return (lhs==rhs) || !(lhs<rhs);
};


int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}



};
