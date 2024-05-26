//
//  polynomial.h
//  hw08
//
// Using a singly linked list, creates and performs operations on
// the Polynomial class and effectively produces appropriate output formats
//
//  Created by Shrey Kharbanda on 4/25/23.
//

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>
#include <vector>

class Polynomial{
    // Checks if two polynomials are equal, by comparing each term
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    // Displays the polynomial in the appropriate format using the ^ symbol
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    public:
        // default constructor for creating a zero Polynomial
        Polynomial();
        // constructor takes in a vector as an argument and creates a Polynomial
        Polynomial(const std::vector<int>& vec);
        // copy constructor to create a copy of the Polynomial object
        Polynomial(const Polynomial& poly);
        // assignment operator to assign a Polynomial object to another
        Polynomial& operator=(const Polynomial& poly);
        // destructor to delete any memory allocated by the Polynomial object
        ~Polynomial();
        // adds a polynomial object to itself using the += operator
        Polynomial& operator+=(const Polynomial& second);
        // evaluates a polynomial for a particular value it takes in as argument
        int eval(double value) const;
    
    private:
        // creates a Node struct object for each term of the Polynomial
        struct Node;
        // headptr to point towards the highest degree term of the Polynomial
        Node* headptr;
        // stores the degree of the polynomial
        int degree;
        
};

// creates a copy of the lhs object and then calls the += operator to add rhs to that copy and returns the copy
Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
// Checks if two polynomials are equal, by comparing each term
bool operator==(const Polynomial& lhs, const Polynomial& rhs);
// Checks if two polynomials are not equal, by negating the == operator call
bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
// Displays the polynomial in the appropriate format using the ^ symbol
std::ostream& operator<<(std::ostream& os, const Polynomial& poly);


#endif 
