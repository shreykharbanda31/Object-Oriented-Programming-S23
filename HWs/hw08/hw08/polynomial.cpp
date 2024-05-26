//
//  Polynomial.cpp
//  hw08
//
// Using a singly linked list, creates and performs operations on
// the Polynomial class and effectively produces appropriate output formats
//
//  Created by Shrey Kharbanda on 4/25/23.
//

#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

// creates a Node struct object for each term of the Polynomial, stores the term's coefficient, and holds a
// pointer to the next term
struct Polynomial::Node{
    Node(int num = 0, Node* next = nullptr) : coefficient(num), next(next) {};
    int coefficient;
    Node* next;
};

// default constructor for creating a zero Polynomial
Polynomial::Polynomial() : headptr(new Node()), degree(0) {};
// constructor takes in a vector as an argument and creates a Polynomial, connects all Node terms
Polynomial::Polynomial(const vector<int>& vec) : degree(int(vec.size())-1) {
            headptr = new Node(vec[0]);
            Node* curr = headptr;
            for (int index = 1; index < vec.size(); ++index){
                curr -> next = new Node(vec[index]);
                curr = curr -> next;
            };
        };
// copy constructor to create a copy of the Polynomial object by deep copying all the pointers
Polynomial::Polynomial(const Polynomial& poly) : degree(poly.degree){
            headptr = new Node(poly.headptr -> coefficient);
            Node* curr = headptr;
            Node* second = poly.headptr -> next;
            while (second != nullptr){
                curr -> next = new Node(second -> coefficient);
                curr = curr -> next;
                second = second -> next;
            };
        };
// assignment operator to assign a Polynomial object to another
Polynomial& Polynomial::operator=(const Polynomial& poly){
        // checks for self-assignment
            if (this != &poly){
                // frees up all Polynomial memory on the heap
                Node* curr = headptr;
                while (curr != nullptr){
                    Node* prior = curr;
                    curr = curr -> next;
                    delete prior;
                    --degree;
                };
                curr = nullptr;
                // copies values from the polynomial to the current polynomial
                degree = poly.degree;
                headptr = new Node(poly.headptr -> coefficient);
                Node* curr2 = headptr;
                Node* second = poly.headptr -> next;
                while (second != nullptr){
                    curr2 -> next = new Node(second -> coefficient);
                    curr2 = curr2 -> next;
                    second = second -> next;
                };
            };
            return *this;
        };
// destructor to delete any memory allocated by the Polynomial object
Polynomial::~Polynomial(){
            // frees up all Polynomial memory on the heap
            Node* curr = headptr;
            while (curr != nullptr){
                Node* prior = curr;
                curr = curr -> next;
                delete prior;
                --degree;
            };
            curr = nullptr;
        };
// adds a polynomial object to itself using the += operator
    Polynomial& Polynomial::operator+=(const Polynomial& second){
        // checks for two cases, in which the degree is greater and accordingly updates the current
        // Polynomial object
        Node* curr = headptr;
        // moves curr pointer to the pointer right before we can match terms with the second Polynomial
        if (degree > second.degree){
                Node* newhead = headptr;
                for (int i = second.degree; i < degree-1; ++i){
                    curr = curr -> next;
                };
            Node* prev = curr;
            curr = curr -> next;
            Node* secondptr = second.headptr;
            while (curr != nullptr && secondptr != nullptr){
                Node* newnode = new Node(curr -> coefficient + secondptr -> coefficient);
                prev -> next = newnode;
                curr = curr -> next;
                secondptr = secondptr -> next;
                prev = newnode;
            };
            headptr = newhead;
            };
        
        // creates new Nodes before the first term and adds the second polynomial to the updated current Polynomial
        if (second.degree >= degree){
            for (int i = degree; i < second.degree; ++i){
                Node* head = headptr;
                headptr = new Node(0, head);
            };
            curr = headptr;
            degree = second.degree;
            Node* secondptr = second.headptr;
            Node* newhead = new Node(curr -> coefficient + secondptr -> coefficient);

            Node* ptr = newhead;
            curr = curr -> next;
        
            secondptr = secondptr -> next;

            while (curr != nullptr && secondptr != nullptr){
                ptr -> next = new Node(curr -> coefficient + secondptr -> coefficient);
                ptr = ptr -> next;
                curr = curr -> next;
                secondptr = secondptr -> next;
            };
            headptr = newhead;
        };
        return *this;
    };

// evaluates a polynomial for a particular value it takes in as argument
    int Polynomial::eval(double value) const{
        // uses Horner's method to calculate in linear runtime
        Node* curr = headptr;
        int result = curr -> coefficient;
        while (curr -> next != nullptr){
            curr = curr -> next;
            result = result*value + curr -> coefficient;
        }
        return result;
    };
    

        
// creates a copy of the lhs object and then calls the += operator to add rhs to that copy and returns the cop
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
        Polynomial result(lhs);
        result += rhs;
        return result;
};

// Checks if two polynomials are equal, by comparing each term
bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    // if degrees are different, polynomial's are by default not equal
    if (lhs.degree != rhs.degree){
        return false;
    }
    Polynomial::Node* first = lhs.headptr;
    Polynomial::Node* second = rhs.headptr;
    for (int index = 0; index < lhs.degree; ++index){
        if (first -> coefficient != second -> coefficient){
            return false;
        };
        first = first -> next;
        second = second -> next;
    };
    return true;
};

// Checks if two polynomials are not equal, by negating the == operator call
bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
};

// Displays the polynomial in the appropriate format using the ^ symbol
ostream& operator<<(ostream& os, const Polynomial& poly){
    Polynomial::Node* curr = poly.headptr;
    int index = poly.degree;
    while (curr != nullptr){
        // has a different ouput when there are more than 2 terms
        if (index > 1) {
            if (curr -> next != nullptr && (curr -> coefficient == 1 || curr -> coefficient == -1) && curr -> coefficient != 0){
                // if coefficent is 1 or -1 then it doesn't output the "1"
                if (curr ->coefficient == -1) {
                    os << "-";
                };
                os << "x^" << index << "+";
            }
            else if (curr -> next != nullptr && curr -> coefficient != 1 && curr -> coefficient != 0){
                // if coefficent is not 1 or -1 then it outputs the coefficients
                os << curr -> coefficient << "x^" << index << "+";
            }
        };
        // has a different ouput when it has 2 terms
        if (index == 1) {
            if (curr -> next != nullptr && (curr -> coefficient == 1 || curr -> coefficient == -1) && curr -> coefficient != 0){
                // if coefficent is 1 or -1 then it doesn't output the "1"
                if (curr ->coefficient == -1) {
                    os << "-";
                };
                os << "x" << "+";
            }
            else if (curr -> next != nullptr && curr -> coefficient != 1 && curr -> coefficient != 0){
                // if coefficent is not 1 or -1 then it outputs the coefficients
                os << curr -> coefficient << "x" << "+";
            }
        };
        // for the constant term
        if (index == 0){
            os << curr->coefficient;
        }
        curr = curr -> next;
        --index;
    };
    return os;
};

