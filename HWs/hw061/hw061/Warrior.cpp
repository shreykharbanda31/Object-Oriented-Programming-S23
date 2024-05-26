//
//  Warrior.cpp
//  hw06
//
//  Created by Shrey Kharbanda on 3/14/23.
//

#include <iostream>
#include <vector>
#include <string>
#include "Warrior.h"
#include "Noble.h"
using namespace std;

// writing methods of Warrior Class under namespace WarriorCraft
namespace WarriorCraft{
// methods of Warrior class

    // constructor, they are born as "not hired" initially
    Warrior::Warrior(const string& name, double wstrength) : wname(name), strength(wstrength), noble(nullptr) {};
    // getter method to return hired status
    bool Warrior::isHired() const{
            return (noble!=nullptr);
    };
    // mutator method to change connect warrior to its noble
    void Warrior::assign_noble(Noble* mynoble){
            noble = mynoble;
    };
    // mutator method to change the warrior strength
    void Warrior::set_strength(double wstrength){
            strength = wstrength;
    };
    // getter method to return warrior name
    const string& Warrior::get_name() const{
            return wname;
    };
    // getter method to return warrior strength
    double Warrior::get_strength() const{
            return strength;
    };
    // returns true when the warrior runs away from its noble and informs him about his status, else returns false
    bool Warrior::runaway(){
        if (!(noble->is_alive())){
            cout << noble->get_noblename() << "is dead!" << endl;
            return false;
        }
        if (!isHired()){
            cout << wname << "does not have a noble lord" << endl;
            return false;
        }
        string noblename = noble->get_noblename();
        if(noble->remove(*this)){
            cout << wname << " flees in terror, abandoning his lord, " << noblename << endl;
            return true;
        }
        return false;
    };

    // overloading of the output operator for the warrior objects
    ostream& operator<< (ostream& os, const Warrior& warr){
        os << warr.wname << ": " << warr.strength;
        return os;
    };
};
