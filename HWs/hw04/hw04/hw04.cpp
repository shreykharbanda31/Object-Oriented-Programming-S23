/*
  hw04.cpp
  Created by Shrey Kharbanda on 2/19/2023.
    It models a game of the medieval times where Nobles battle against each other with their armies
    of warriors.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// declaring a Warrior class
class Warrior{
    public:
    // giving the overloaded output operator access to the private part of the Warrior class
    friend ostream& operator<< (ostream& os, Warrior warr);
    // constructor, they are born as "not hired" initially
    Warrior(const string& name, double wstrength) : wname(name), strength(wstrength), hired(false) {};
    // getter method to return hired status
    bool get_hired() const{
        return hired;
    };
    // mutator method to change the hired status
    void set_hired(bool newhire){
        hired = newhire;
    };
    // mutator method to change the warrior strength
    void set_strength(double wstrength){
        strength = wstrength;
    };
    // getter method to return warrior name
    const string& get_name() const{
        return wname;
    };
    // getter method to return warrior strength
    double get_strength() const{
        return strength;
    };
    // declare warrior name, strength, hired status variables
    private:
    string wname;
    double strength;
    bool hired;
    bool alive;
};

// declaring a Noble class
class Noble{
    public:
    // giving the overloaded output operator access to the private part of the Noble class
    friend ostream& operator<< (ostream& os, Noble nob);
    // constructor, they are born as alive and with 0 initial army strength
    Noble(const string& name) : noblename(name), alive(true), armystrength(0){};
    // returns true/false based on the warrior's hire status
    bool hire(Warrior& warrior){
        // checks if noble is alive and returns an appropriate response
        if (!alive){
            cout << noblename << " failed to hire " << warrior.get_name() << endl;
            return false;
        }
        // checks if warrior is not already hired
        if(!warrior.get_hired()){
            // adds a pointer to warrior object to the army vector
            army.push_back(&warrior);
            // changes warrior hired status
            warrior.set_hired(true);
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
    
    // returns true/false based on if the warrior was fired
    bool fire(Warrior& warr){
        // checks if noble is alive and returns an appropriate response
        if (!alive){
            cout << noblename << " failed to fire " << warr.get_name() << endl;
            return false;
        };
        bool fired = false;
        // loops over the army vector until it finds the warrior and then fires the warrior by changing their
        // hired status and decreasing the army strength and eventually pushing all the values
        // after it one step back
        for (size_t i = 0; i < army.size(); i++) {
            if (fired == false) {
                if (army[i]->get_name() == warr.get_name()) {
                    cout << warr.get_name() << ", you don't work for me any more! -- " << noblename << "." << endl;
                    warr.set_hired(false);
                    armystrength = armystrength - warr.get_strength();
                    fired = true;
                }
            }
            else {
                army[i - 1] = army[i];
            }
        };
        // if the loop is run over and the warrior does not exist in the noble's army
        // then the noble cannot fire the warrior
        if (fired==false){
            cout << noblename << " failed to fire " << warr.get_name() << endl;
        }
        else{
        // if it did find the warrior, the last repetitive element is deleted
            army.pop_back();;
        }
        return fired;
    }
    
    // to change the strength of each warrior in the army vector to 0
    void change_army_strength_0(){
        for (size_t index = 0; index < army.size(); ++index){
            army[index]->set_strength(0);
        };
    };
    
    // to change the strength of each warrior in the army vector to their new strength based on the ratio from
    // the battle results
    void change_army_strength_lose(double ratio){
        for (size_t index = 0; index < army.size(); ++index){
            army[index]->set_strength((army[index]->get_strength())-((army[index]->get_strength())*(ratio)));
        };
    };
    
    // initiates a battle between the noble and the enemy noble
    void battle (Noble& enemy){
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
    
    // declares private variables containing the noble army vector, name and alive status of noble, army strength of noble
    private:
    vector<Warrior*> army;
    string noblename;
    bool alive;
    double armystrength;
};

// overloading of the output operator for the warrior objects
ostream& operator<< (ostream& os, Warrior warr){
    os << warr.wname << ": " << warr.strength;
    return os;
};

// overloading of the output operator for the noble objects
ostream& operator<< (ostream& os, Noble nob){
    os << nob.noblename << " has an army of " << nob.army.size() << "\n\t";
    // loops over all warriors within the noble army except for the last one
    for (size_t index = 0; index < nob.army.size()-1; ++index){
        os << *nob.army[index] << "\n\t";
    };
    // call over last warrior here
    os << *(nob.army[nob.army.size()-1]);
    return os;
};

// game execution
int main() {
    
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
    
    
    cout << "==========\n\n" << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
    
    art.fire(cheetah);
    cout << art << endl;
    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

}
