//
//  Noble.cpp
//  hw07
//
//  Created by Shrey Kharbanda on 4/3/23.
//

#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

namespace WarriorCraft{

    /* method definitions for Noble hierarchy */

    // constructors for the Noble hierarchy

    // constructor for the base class Noble, they are born as alive initially
    Noble::Noble(const string& name) : noblename(name), alive(true){};

    // constructor for derived class Lord
    Lord::Lord(const string& name) : Noble(name), armystrength(0) {};

    // constructor for derived class PersonWithStrengthToFight
    PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strengthh) : Noble(name), strength(strengthh) {};

    /* method definitions for the base class Noble */

    // getter method to return noble name
    const string& Noble::get_noblename() const{
        return noblename;
    };

    // getter method to return noble's alive status
    bool Noble::is_alive() const{
        return alive;
    };

    // method to set all variables accordingly when the noble dies
    void Noble::die(){
        alive = false;
    }

    // initiates a battle between the noble and the enemy noble
    void Noble::battle(Noble& enemy){
        cout << noblename << " battles " << enemy.noblename << endl;
        // checking for nobles who're dead
        if (!alive && !enemy.alive){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!alive){
            enemy.defend();
            cout << "He's dead, " << enemy.noblename << endl;
        }
        else if (!enemy.alive){
            defend();
            cout << "He's dead, " << noblename << endl;
        }
        else{
            // calling get_strength() for initializing nobles' strengths to compare below
            double strength = get_strength();
            double enemystrength = enemy.get_strength();
            defend();
            enemy.defend();
            // initiating a battle and changing army strengths by deciding which noble is stronger,
            // plus overriding get_strength() based on the type of the noble if both are alive
            if (strength == enemystrength){
                // calling die methods for both of them
                die();
                enemy.die();
                cout << "Mutual Annihilation: " << noblename << " and " << enemy.noblename << " die at each other's hands" << endl;
            }
            else if (strength > enemystrength){
                change_strength(strength, enemystrength);
                enemy.die();
                cout << noblename << " defeats " << enemy.noblename << endl;
            }
            else { //strength < enemystrength
                enemy.change_strength(enemystrength, strength);
                // set lost noble's strengths to 0 and declare them dead
                die();
                cout << enemy.noblename << " defeats " << noblename << endl;
            }
        }
    };

    /* method definitions for the derived class Lord */

    // returns true/false based on the protector's hire status
    bool Lord::hires(Protector& pro){
        // checks if noble is alive and returns an appropriate response
        if (!is_alive()){
            return false;
        }
        if(pro.get_strength()==0){
            return false;
        }
        // checks if protector is not already hired
        if(!pro.isHired()){
            // adds a pointer to protector object to the army vector
            army.push_back(&pro);
            // changes protector hired status and tells the protector who hired him
            pro.assign_lord(this);
            // updates army strength by adding the new protector hired's strength
            armystrength = armystrength + pro.get_strength();
            return true;
        }
        else{
            return false;
        }
    };

    //checks if the protector exists in the noble's army and then removes the desired protector, if found and changes it's lord status
    bool Lord::remove(Protector& pro){
        // loops over the army vector until it finds the protector and then fires the protector by changing their
        // lord status and decreasing the army strength and eventually pushing all the values
        // after it one step back
        bool removed = false;
        for (size_t i = 0; i < army.size(); i++) {
            if (removed == false) {
                if (army[i]->get_name() == pro.get_name()) {
                    pro.assign_lord(nullptr);
                    armystrength = armystrength - pro.get_strength();
                    removed = true;
                }
            }
            else {
                army[i - 1] = army[i];
            }
        };
        if (removed==true){
            // if it did find the protector, the last repetitive element is deleted
            army.pop_back();
        }
        return removed;
    };

    // returns true/false based on if the protector was fired
    bool Lord::fires(Protector& pro){
        // checks if lord is alive and returns an appropriate response
        if (!is_alive()){
            return false;
        };
        bool fired = remove(pro);
        // if the loop is run over in the remove method and the protector does not exist in the lord's army
        // then firing of the protetcor by the lord makes no sense
        if (fired==false){
            return fired;
        }
        else{
            cout << pro.get_name() << ", you don't work for me anymore ! -- " << get_noblename() << "." << endl;
        }
        return fired;
    }

    // to change the strength of each protector in the army vector to 0
    void Lord::change_army_strength_0(){
        for (size_t index = 0; index < army.size(); ++index){
            army[index]->set_strength(0);
        };
    };

    // to change the strength of each protector in the army vector to their new strength based on the ratio from
    // the battle results
    void Lord::change_strength(double winner, double loser){
        double ratio = 0;
        // if enemy strength is 1/4 of the noble's strength, all strengths
        // of the noble get reduced by 1/4
        if (loser == winner*0.25){
            ratio = 0.25;
        }
        else{
            ratio = (winner-loser)/winner;
        }
        armystrength = 0;
        for (size_t index = 0; index < army.size(); ++index){
            army[index]->set_strength((army[index]->get_strength()*(ratio)));
            armystrength += army[index]->get_strength();
        };
    };

    //getter method for Lord's army strength
    double Lord::get_strength() const {
        return armystrength;
    };

    // to set all variables accordingly when the lord dies
    void Lord::die(){
        change_army_strength_0();
        armystrength = 0;
        Noble::die();
    };

    // for overriding and defending a lord by blurting out a specific dialogues
    void Lord::defend() const{
        if(is_alive()){
            // loops over all Protectors within the lord army
            for (size_t index = 0; index < (army.size()); ++index){
                (army[index]->defend()); cout << endl;
            };
        };
    };

    //display method for outputting Lord specifics
    void Lord::display(ostream& os) const{
        os << get_noblename() << " has an army of size: " << army.size();
        if (army.size()){
            os << "\n\t\t";
            // loops over all Protectors within the lord army except for the last one
            for (size_t index = 0; index < (army.size()-1); ++index){
                os << *(army[index]) << "\n\t\t";
            };
            // call over last protector here
            os << *(army[army.size()-1]);
        };
    };

    /* method definitions for the derived class PersonWithStrengthToFight */

    // to set all variables accordingly when the personwithstrength dies
    void PersonWithStrengthToFight::die(){
        strength = 0;
        // calling parent class' die() protected method to change alive status
        Noble::die();
    };

    //getter method for personwithstrength's strength
    double PersonWithStrengthToFight::get_strength() const {
        return strength;
    };

    // mutator method to change the strength of the personwithstrength based on the ratio
    void PersonWithStrengthToFight::change_strength(double winner, double loser){
        strength = strength - (loser);
    };

    // for overriding and defending a personwithstrength by blurting out a specific dialogues
    void PersonWithStrengthToFight::defend() const{
        cout << "UGH!!!" << endl;
    };

    // to print all the personwithstrength's specifics for the output operator
    void PersonWithStrengthToFight::display(ostream& os) const{
        os << get_noblename() << " has strength: " << strength;
    };

    //the overloaded output operator calls defend() for the Noble hierarchy
    ostream& operator<< (ostream& os, const Noble& nob){
        nob.display(os);
        return os;
    };

};
