//
//  main.cpp
//  exam 3
//
//  Created by Shrey Kharbanda on 5/9/23.
//

#include <iostream>
using namespace std;

//class B {
//public:
//B(int val = 42) : n(val) {}
//virtual void foo() const { cout << "B"; }
//private:
//int n;
//};
//class A {
//public:
//void foo() { cout << "A"; }
//private:
//B someB;
//};
class Pet {
public:
Pet(string name) : name(name) {}
void display() { cout << name << ' '; }

protected:

    void setName(string name) { this->name = name;};
    private:
        
        string name;
        
};

//class Cat : public Pet {
//public:
//
//    Cat(string name){}
//};

class Dog : public Pet {
public:
    Dog() : Pet("ruff") {}
    void setCatName(Dog& rhs) {
//        rhs.setName("Mehitabel"); // A
        
    }
    
    void setDogName(Dog& rhs) {
        rhs.setName("Fido"); // B
        
    }
    
};
class Base {

public:

    virtual void foo() { cout << " - Base::foo()\n"; };
    };
class Derived : public Base {
public:

    virtual void foo() { cout << " - Derived::foo()\n"; };
    };

void func(Base& arg) {
cout << "func(Base)";
arg.foo();

}

void func(Derived& arg) {
cout << "func(Derived)";

arg.foo();

}

void otherFunc(Base& arg) {
func(arg);

}
//class P1 {
//public:
//
//    void whoamI() { cout << "P1"; }
//};
//
//class P2 {
//public:
//    void whoamI() { cout << "P2"; }
//
//};
//
//class Child : public P2, public P1 {
//    // Inherits from both P2 and P1
//
//};
//
//int main() {
//Child c;
//c.whoamI();
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

void baseThree(unsigned val){
    if (val<3){
        cout << val << "";
    }
    else{
        baseThree(val/3);
        cout << val%3 << "";
    }
}
int* foo(){
    int x = 17;
    return &x;
}
int x = 18;
class Vector {
public:
    class Iterator{

    public:
        Iterator(int* ptr = nullptr):ptr(ptr){};
        Iterator& operator++(){
            ++ptr;
            return *this;
        }
        Iterator operator++(int){
            Iterator copy(*this);
            ++ptr;
            return copy;
        }
        int& operator*() const{
            return *ptr;
        }
    private:
        int* ptr;
    };
    Vector(size_t size = 0, int value = 0) {
     the_size = size;
     the_capacity = size;
     data = new int[size];
     for (size_t i = 0; i < the_size; ++i) {
     data[i] = value;
     }
     }
    Vector(const Vector& rhs) {
     the_size = rhs.the_size;
     the_capacity = rhs.the_capacity;
     data = new int[the_capacity];
     for (size_t i = 0; i < the_size; ++i) {
     data[i] = rhs.data[i];
     }
     }
    Vector& operator=(const Vector& rhs) {
     if (this != &rhs) {
     delete [] data;
     data = new int[rhs.the_capacity];
     the_size = rhs.the_size;
     the_capacity = rhs.the_capacity;
     for (size_t i = 0; i < the_size; ++i) {
     data[i] = rhs.data[i];
     }
     }
     return *this;
     }
    void push_back(int val) {
     // in case of a vector with capacity of 0
     if (the_capacity == 0) {
     delete [] data;
     ++the_capacity;
     data = new int[the_capacity];
     }
     if (the_size == the_capacity) {
     int* new_data = new int[2 * the_capacity];
     for (size_t i = 0; i < the_size; ++i) {
     new_data[i] = data[i];
     }
     delete [] data;
     data = new_data;
     the_capacity *= 2;
     }
     data[the_size] = val;
     ++the_size;
     }
 size_t size() const { return the_size; }
 int operator[](size_t i) const { return data[i]; }
 int& operator[](size_t i) { return data[i]; }
 void clear() { the_size = 0; }
 void pop_back() { --the_size; }
 Vector::Iterator begin() { return Iterator(data); }
 Vector::Iterator end() { return Iterator(data + the_size); }
private:
 int* data;
 size_t the_size;
 size_t the_capacity;
};

int main() {
    Vector vec(3,7);
    for(int& val : vec){
        val /= 3;
    }
    int* y = foo();
    cout << *y << endl;
    A* ob = new B();
    ob -> x();
    baseThree(5);
    vector<double> myList{1,2,4};
    double summ = 0;
    for (vector<double>::const_iterator index = myList.begin();index!=myList.end();++index){
        summ += *index;
    }
    cout << summ<<endl;
    Derived d;
    Base* b = new Derived();
    func(*b);
    otherFunc(d);
};
