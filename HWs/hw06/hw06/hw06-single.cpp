/*
 hw06-single.cpp
 Created by Shrey Kharbanda on March 13, 2023.
 It models a game of the medieval times where Nobles battle against each other with their armies
 of warriors.
 */

//#include "Noble.h"
//#include "Warrior.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//using namespace WarriorCraft;

// in order to fix cyclic association
class Noble;

// declaring a Warrior class
class Warrior{
    public:
    // giving the overloaded output operator access to the private part of the Warrior class
    friend ostream& operator<< (ostream& os, const Warrior& warr);
    // constructor, they are born as "not hired" initially
    Warrior(const string& name, double wstrength);
    // getter method to return hired status
    bool isHired() const;
    // mutator method to change the hired status and connect to its noble
    void assign_noble(Noble* mynoble);
    // mutator method to change the warrior strength
    void set_strength(double wstrength);
    // getter method to return warrior name
    const string& get_name() const;
    // getter method to return warrior strength
    double get_strength() const;
    // when the warrior runs away from its noble and informs him about his status
    bool runaway();
    // declare warrior name, strength, and noble who hired thw warrior variables
    private:
    string wname;
    double strength;
    Noble* noble;
};

// declaring a Noble class
class Noble{
    public:
    // giving the overloaded output operator access to the private part of the Noble class
    friend ostream& operator<< (ostream& os, const Noble& nob);
    
    // takes in noble name to create a noble object
    Noble(const string& name);
    
    // getter method to return noble name
    const string& get_noblename() const;
    
    // getter method to return noble's alive status
    bool is_alive() const;
    
    // returns true/false based on the warrior's hire status
    bool hire(Warrior& warrior);
    
    //checks if the warrior exists in the noble's army and then removes the desired warrior, if found and changes it's noble status
    bool remove(Warrior& warr);
    
    // returns true/false based on if the warrior was fired
    bool fire(Warrior& warr);
    
    // to change the strength of each warrior in the army vector to 0
    void change_army_strength_0();
    
    // to change the strength of each warrior in the army vector to their new strength based on the ratio from
    // the battle results
    void change_army_strength_lose(double ratio);
    
    // initiates a battle between the noble and the enemy noble
    void battle (Noble& enemy);
    
    // declares private variables containing the noble army vector, name and alive status of noble, army strength of noble
    private:
    vector<Warrior*> army;
    string noblename;
    bool alive;
    double armystrength;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
         << lance << endl
         << jim << endl
         << linus << endl
         << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha
         << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha
         << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

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
        cout << noble->get_noblename() << " is dead!" << endl;
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


// Methods of Noble class

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

// overloading of the output operator for the warrior objects
ostream& operator<< (ostream& os, const Warrior& warr){
    os << warr.wname << ": " << warr.strength;
    return os;
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
