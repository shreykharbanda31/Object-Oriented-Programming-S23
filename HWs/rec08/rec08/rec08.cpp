//
//  rec08.cpp
//
//  Created by Shrey Kharbanda on 3/24/23.
//

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

class Rational{
    friend istream& operator>>(istream& is, Rational& rhs);
    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);

    public:

        Rational(int num = 0, int denom = 1);

        Rational& operator+=(const Rational& rhs);

        Rational& operator++();

        Rational operator++(int);

        explicit operator bool() const;

    private:
            void normalize();
            int numerator;
            int denominator;
};

istream& operator>>(istream& is, Rational& rhs);

ostream& operator<<(ostream& os, const Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);

bool operator<(const Rational& lhs, const Rational& rhs);

Rational& operator--(Rational& rhs);

Rational operator--(Rational& rhs, int);

bool operator!=(const Rational& lhs, const Rational& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);


int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? YES, cannot compile
    // cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

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

istream& operator>>(istream& is, Rational& rhs){
    char ch;
    is >> rhs.numerator >> ch >> rhs.denominator;
    rhs.normalize();
    return is;
};

ostream& operator<<(ostream& os, const Rational& rhs){
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

