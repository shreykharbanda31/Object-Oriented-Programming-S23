//
//  Noble.cpp
//  hw06
//
//  Created by Shrey Kharbanda on 3/14/23.
//

// Methods of Noble class

#include <iostream>
#include <vector>
#include <string>
#include "Noble.h"
#include "Warrior.h"
using namespace std;

namespace WarriorCraft {
    // constructor, they are born as alive and with 0 initial army strength
    Noble::Noble(const string& name) : noblename(name), alive(true), armystrength(0){};
    // getter method to return noble name
    const string& Noble::get_noblename() const{
        return noblename;
    };
    // getter method to return noble's alive status
    bool Noble::is_alive() const{
        return alive;
    };
    // returns true/false based on the warrior's hire status
    bool Noble::hire(Warrior& warrior){
        // checks if noble is alive and returns an appropriate response
        if (!alive){
            cout << noblename << " failed to hire " << warrior.get_name() << endl;
            return false;
        }
        // checks if warrior is not already hired
        if(!warrior.isHired()){
            // adds a pointer to warrior object to the army vector
            army.push_back(&warrior);
            // changes warrior hired status and tells the warrior who hired him
            warrior.assign_noble(this);
            // updates army strength by adding the new warrior hired's strength
            armystrength = armystrength + warrior.get_strength();
            return true;
        }
        else{
            // tells the user if the warrior is already hired and hence, the noble failed to hire the warrior
            cout << noblename << " failed to hire " << warrior.get_name() << endl;
            return false;
        }
    };

    bool Noble::remove(Warrior& warr){
        // loops over the army vector until it finds the warrior and then fires the warrior by changing their
        // noble status and decreasing the army strength and eventually pushing all the values
        // after it one step back
        bool removed = false;
        for (size_t i = 0; i < army.size(); i++) {
            if (removed == false) {
                if (army[i]->get_name() == warr.get_name()) {
                    warr.assign_noble(nullptr);
                    armystrength = armystrength - warr.get_strength();
                    removed = true;
                }
            }
            else {
                army[i - 1] = army[i];
            }
        };
        if (removed==true){
            // if it did find the warrior, the last repetitive element is deleted
            army.pop_back();
        }
        return removed;
    };

    // returns true/false based on if the warrior was fired
    bool Noble::fire(Warrior& warr){
        // checks if noble is alive and returns an appropriate response
        if (!alive){
            cout << noblename << " failed to fire " << warr.get_name() << endl;
            return false;
        };
        bool fired = remove(warr);
        // if the loop is run over in the remove method and the warrior does not exist in the noble's army
        // then the noble cannot fire the warrior
        if (fired==false){
            cout << noblename << " failed to fire " << warr.get_name() << endl;
        }
        else{
            cout << warr.get_name() << ", you don't work for me anymore ! -- " << noblename << "." << endl;
        }
        return fired;
    }

    // to change the strength of each warrior in the army vector to 0
    void Noble::change_army_strength_0(){
        for (size_t index = 0; index < army.size(); ++index){
            army[index]->set_strength(0);
        };
    };

    // to change the strength of each warrior in the army vector to their new strength based on the ratio from
    // the battle results
    void Noble::change_army_strength_lose(double ratio){
        for (size_t index = 0; index < army.size(); ++index){
            army[index]->set_strength((army[index]->get_strength())-((army[index]->get_strength())*(ratio)));
        };
    };

    // initiates a battle between the noble and the enemy noble
    void Noble::battle (Noble& enemy){
        cout << noblename << " battles " << enemy.noblename << endl;
        // checking for nobles who're dead
        if (!alive && !enemy.alive){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (!alive){
            cout << "He's dead, " << enemy.noblename << endl;
        }
        else if (!enemy.alive){
            cout << "He's dead, " << noblename << endl;
        }
        else{ // initiating a battle and changing army strengths by deciding which noble army is stronger, if both are alive
            if (armystrength == enemy.armystrength){
                // change both to not alive and 0 strengths of all its warriors and overall army strength
                armystrength = 0;
                enemy.armystrength = 0;
                change_army_strength_0();
                enemy.change_army_strength_0();
                alive = false;
                enemy.alive = false;
                cout << "Mutual Annihilation: " << noblename << " and " << enemy.noblename << " die at each other's hands" << endl;
            }
            else if (armystrength > enemy.armystrength){
                // if enemy army strength is 1/4 of the noble's army strength, all warriors' strengths
                // of the noble army get reduced by 1/4
                if (enemy.armystrength == (0.25*armystrength)){
                    change_army_strength_lose(0.25);
                }
                else {
                    // changes noble army strength based on the strength ratio
                    change_army_strength_lose((enemy.armystrength)/armystrength);
                    armystrength = armystrength - ((enemy.armystrength)/armystrength);
                }
                enemy.armystrength = 0;
                enemy.alive = false;
                enemy.change_army_strength_0();
                cout << noblename << " defeats " << enemy.noblename << endl;
            }
            else {
                // if the noble's army strength is 1/4 of the enemy noble's army strength, all warriors' strengths
                // of the noble army get reduced by 1/4
                if (armystrength == (0.25*enemy.armystrength)){
                    enemy.change_army_strength_lose(0.25);
                }
                else {
                    // changes enemy noble army strength based on the strength ratio
                    enemy.change_army_strength_lose((armystrength/enemy.armystrength));
                    enemy.armystrength -= armystrength/enemy.armystrength;
                }
                // set lost noble's army strength and warrior strengths to 0 and declare them dead
                armystrength = 0;
                alive = false;
                change_army_strength_0();
                cout << enemy.noblename << " defeats " << noblename << endl;
            }
        }
    };

    // overloading of the output operator for the noble objects
    ostream& operator<< (ostream& os, const Noble& nob){
        os << nob.noblename << " has an army of " << nob.army.size() << "\n\t\t";
        // loops over all warriors within the noble army except for the last one
        for (size_t index = 0; index < nob.army.size()-1; ++index){
            os << *nob.army[index] << "\n\t\t";
        };
        // call over last warrior here
        os << *(nob.army[nob.army.size()-1]);
        return os;
    };
};
