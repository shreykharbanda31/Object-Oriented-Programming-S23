//
//  Protector.cpp
//  hw07
//
//  Created by Shrey Kharbanda on 4/3/23.
//

#include "Protector.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {

    /* method definitions for Protector hierarchy */

    // constructors for Protector and Warrior kinds

    // constructor for the base class Protector, they are born as "not hired" initially
    Protector::Protector(const string& name, double wstrength): wname(name), strength(wstrength), lord(nullptr) {};

    // constructor for derived class Wizard
    Wizard::Wizard(const string& name, double wstrength): Protector(name, wstrength) {};

    // constructor for derived class Warrior
    Warrior::Warrior(const string& name, double wstrength): Protector(name, wstrength) {};

    // constructor for derived class Archer
    Archer::Archer(const string& name, double wstrength): Warrior(name, wstrength){};

    // constructor for derived class Swordsman
    Swordsman::Swordsman(const string& name, double wstrength): Warrior(name, wstrength){};

    /* method definitions for the base class Protector */

    // getter method to return hired status
    bool Protector::isHired() const{
            return (lord != nullptr);
    };

    // getter method to return lord's pointer
    const Lord* Protector::get_lord() const{
        return lord;
    }

    // mutator method to change connect protector to its noble
    void Protector::assign_lord(Lord* lordd){
            lord = lordd;
    };

    // mutator method to change the protector strength
    void Protector::set_strength(double wstrength){
            strength = wstrength;
    };

    // getter method to return protector name
    const string& Protector::get_name() const{
            return wname;
    };

    // getter method to return protector strength
    double Protector::get_strength() const{
            return strength;
    };

    // returns true when the protector runs away from its noble and informs him about his status, else returns false
    bool Protector::runaway(){
        if (!(lord->is_alive())){
            cout << lord->get_noblename() << " is dead!" << endl;
            return false;
        }
        if (!isHired()){
            cout << wname << "does not have a noble lord" << endl;
            return false;
        }
        string noblename = lord->get_noblename();
        if(lord->remove(*this)){
            cout << wname << " flees in terror, abandoning his lord, " << noblename << endl;
            return true;
        }
        return false;
    };

    /* overriding defend() method definitions for the derived classes of Protector and Warrior */

    void Wizard::defend() const{
        cout << "POOF!";
    };

    void Warrior::defend() const{
        cout << get_name() << " says: Take that in the name of my lord, " << get_lord()->get_noblename();
    };

    void Archer::defend() const{
        cout << "TWANG!  ";
        // calls defend() from the parent Warrior method so that we don't have to repeat the common defense lines
        Warrior::defend();
    };

    void Swordsman::defend() const{
        cout << "CLANG!  ";
        // calls defend() from the parent Warrior method so that we don't have to repeat the common defense lines
        Warrior::defend();
    };

    //the overloaded output operator calls for the Protector class
    ostream& operator<< (ostream& os, const Protector& pro){
        os << pro.wname << " has strength " << pro.strength;
        return os;
    };
};
