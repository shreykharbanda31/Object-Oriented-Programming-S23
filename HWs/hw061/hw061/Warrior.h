//
//  Warrior.h
//  hw06
//
//  Created by Shrey Kharbanda on 3/14/23.
//

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <vector>
#include <string>

//declaring a Warrior class within namespace WarriorCraft
namespace WarriorCraft{
    //fixing cyclic association
    class Noble;
    // declaring a Warrior class
    class Warrior{
        public:
        // giving the overloaded output operator access to the private part of the Warrior class
        friend std::ostream& operator<< (std::ostream& os, const Warrior& warr);
        // constructor, they are born as "not hired" initially
        Warrior(const std::string& name, double wstrength);
        // getter method to return hired status
        bool isHired() const;
        // mutator method to change the hired status and connect to its noble
        void assign_noble(Noble* mynoble);
        // mutator method to change the warrior strength
        void set_strength(double wstrength);
        // getter method to return warrior name
        const std::string& get_name() const;
        // getter method to return warrior strength
        double get_strength() const;
        // when the warrior runs away from its noble and informs him about his status
        bool runaway();
        // declare warrior name, strength, and noble who hired thw warrior variables
        private:
        std::string wname;
        double strength;
        Noble* noble;
    };
};

#endif
