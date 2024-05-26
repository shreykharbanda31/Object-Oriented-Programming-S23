//
//  main.cpp
//  exam2
//
//  Created by Shrey Kharbanda on 4/17/23.
//

class TA;
#include <iostream>
#include <utility>
using namespace std;

#include <iostream>
using namespace std;



struct ZeroDivException : public exception {

 const char* what() const noexcept {
 return "attempt to divide by 0";
 }
};

//int divide_int(int num, int denom) {
// if (denom == 0) throw "attempt to divide by 0";
// return num / denom;
//}

class Room{
public:
    Room(double size) : size(200){
    };
private:
    double size;
};

//void func(const int& something) {
//// definition for the variable p goes here...
//     const int*  p = &something;
//    *p = 17;
//}

class Parent{
public:
    Parent(){cout << "A";};
    virtual ~Parent(){cout << "B";};
};

class Child: public Parent{
public:
    Child(){cout << "C";};
    ~Child(){cout << "D";};
};

class Grandchild: public Child{
public:
    Grandchild(){cout << "E";};
    ~Grandchild(){cout << "F";};
};


class Student {
public:
 virtual void display() const { cout << "Student\n"; }
};
class Instructor {
public:
 virtual void display() const { cout << "Instructor\n"; }
};
class TA : public Student, public Instructor {
public:
    void display() const { cout << "TA\n"; }
};


class A {
public:
    void x() {
        this->y();
        this->z();
        
    };
    void y() {
        cout << "A::y()" << endl;
    };
    virtual void z() {
        cout << "A::z()" << endl;
    };
};

class B: public A {
public:
    void y() {
        cout << "B::y()" << endl;
    };
    void z() {
        cout << "B::z()" << endl;
    };
};

class C: public B {
public:
    void z() {
        
        cout << "C::z()" << endl;};
};

const int* ptr;
void some(const int* const sp){
    ptr = sp;
}

class SoftDrink {
public:
    virtual void display () const = 0;
};


class Soda: public SoftDrink {
public:
    void display () const override { cout << "Soda "; }
};

auto foo(auto x) {x += 1;}
int parity(int n){
    if(n<2){ return n;}
    else{return n%2+parity(n/2);}
}
// Line B
class GingerAle: public Soda {
public:
    void display () { cout << "GingerAle "; } // Line C
};

int main() {
    cout << endl;
    cout << parity(11);
    cout<< endl;
    [] (int num) {return true;};
    foo(3);
    int arr[7];
    arr[100] = 3;
    cout << arr[100] << " " <<
    arr[99];
GingerAle ga;
// Line
    Soda* sd = &ga;
    // Line E
    // Line F
    // Line G
    sd->display();
    ga.display();

        
        Room(750);
        Parent* p = new Grandchild();
        delete p;
        
        int* d = new int[10];
        d[9]=11;
        int* q = d + 8;
        cout << q[1];
        TA sam;
        sam.display();
    double num1(8.9), num2(3.3);
     double num3(0);

     cout << "Integer division: ";
     cout << num1 << " / ";
     cout << num3 << endl;
     try {
     cout << "Result: ";
     cout << divide_int(num1, num3);
     cout << endl;
     } catch (string ex) {
     cerr << ex << endl;
     }
    }


struct ZeroDivisionException: public exception {
    const char* what() const noexcept {
        cerr << endl;
        return new char('x');
    }
};

//class Pet {
//public:
//    virtual void eat() { cout << "Pet::eat\n"; }
//};
//
//class Cat : public Pet {
//public:
//    void eat() { cout << "Cat::eat\n"; }
//};
//
//








class FlyingMachine { public:
    FlyingMachine() {}
    virtual void fly() { cout << "In FlyingMachine fly()"; }
};

class HangGlider : public FlyingMachine {
public:
    virtual void crash() { cout << "In HangGlider crashing()"; } void fly() { cout << "In HangGlider fly()"; }
};




class FederationStarship { public:
    FederationStarship() {}
    void attack(string weapon) {
        cout << "FederationStarship firing" << weapon;
    }
};

class Constitution : public FederationStarship { public:
virtual void transport() { cout << "Beam me up!"; }
    void attack() {
cout<<"Constitution firing photon torpedos";
}
};




class Base {
public:
 virtual void where_am_i() const { cout << "Base\n"; }
};
class Derived : public Base {
public:
 void where_am_i() const override { cout << "Derived\n"; }
};

class Pet{
public:
 virtual void communicate() = 0;
};
class Dog : public Pet {
public:
 void communicate() final { cout << "Woof!" << endl; }
};
// final is a compile-time error
//class Poodle : public Dog {
//public:
// void communicate() {
// cout << "woof..." << endl;
// }
//};
//class Bulldog : public Dog {
//public:
// void communicate() {
// cout << "WOOF!!!" << endl;
// }
//};
