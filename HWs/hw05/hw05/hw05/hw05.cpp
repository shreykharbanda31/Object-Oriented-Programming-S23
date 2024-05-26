/*
  hw05.cpp
  Created by Shrey Kharbanda on 3/2/2023.
    It models a game of the medieval times where Nobles battle against each other with their armies
    of warriors.
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// declaring a Warrior class
class Warrior{
    public:
    // giving the overloaded output operator access to the private part of the Warrior class
    friend ostream& operator<< (ostream& os, const Warrior& warr);
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
};

// declaring a Noble class
class Noble{
    public:
    // giving the overloaded output operator access to the private part of the Noble class
    friend ostream& operator<< (ostream& os, const Noble& nob);
    // constructor, they are born as alive and with 0 initial army strength
    Noble(const string& name) : noblename(name), alive(true),armystrength(0){};
    // getter method returns the name of the noble
    const string& get_noblename() const {return noblename;};
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
            cout << noblename << " is dead and failed to fire " << warr.get_name() << endl;
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

// setting function prototypes
Noble* find_noble(const string& nname, const vector<Noble*>& nobles);
Warrior* find_warrior(const string& wname, const vector<Warrior*>& warriors);
void displayStatus(const vector<Noble*>&, const vector<Warrior*>&);


// overloading of the output operator for the warrior objects
ostream& operator<< (ostream& os, const Warrior& warr){
    os << warr.wname << ": " << warr.strength;
    return os;
};

// overloading of the output operator for the noble objects
ostream& operator<< (ostream& os, const Noble& nob){
    os << nob.noblename << " has an army of " << nob.army.size() << "\n\t";
    // loops over all warriors within the noble army except for the last one
    for (size_t index = 0; index < nob.army.size()-1; ++index){
        os << *(nob.army[index]) << "\n\t";
    };
    // call over last warrior here
    os << *(nob.army[nob.army.size()-1]);
    return os;
};

// game execution
int main() {
    
    // vectors of noble pointers and warrior pointers
    vector<Noble*> nobles;
    vector<Warrior*> warriors;
    
    // opening the given file with commands
    ifstream commands("nobleWarriors.txt");
    string command;
    
    // looping over the file to identify each command and perform an appropriate action
    while (commands >> command){
        if (command == "Noble"){
            // extracting Noble's Name
            string nname;
            commands >> nname;
            // checks if noble already exists or adds a pointer created on the heap for the noble to the nobles vector
            if (find_noble(nname, nobles)){
                cout << "Noble " << nname << " already exists!" << endl;
            }
            else {nobles.push_back(new Noble(nname));};
        }
        else if (command == "Warrior"){
            // extracting Warrior's name and strength
            string wname;
            int wstrength;
            commands >> wname >> wstrength;
            // checks if warrior already exists or adds a pointer created on the heap for the warrior to the warriors vector
            if (find_warrior(wname, warriors)){
                cout << "Warrior " << wname << " already exists!" << endl;
            }
            else {warriors.push_back(new Warrior(wname, wstrength));};
        }
        else if (command == "Hire"){
            // extracting Noble Name and Warrior Name
            string nname, wname;
            commands >> nname >> wname;
            // checks if noble doesn't exist or if warrior doesn't exist and call the hire method
            // from the Noble class on the warrior
            Warrior* warrptr = find_warrior(wname, warriors);
            Noble* nobptr = find_noble(nname, nobles);
            if (warrptr==nullptr){
                cout << "Attempting to hire using unknown warrior: " << wname << endl;
            }
            else if (nobptr==nullptr){
                cout << "Noble " << nname << "doesn't exist and failed to hire warrior " << wname << ".";
            }
            else{
                nobptr -> hire(*warrptr);
            }
        }
        else if (command == "Status"){
            // calling the Status of the nobles and warriors
            displayStatus(nobles, warriors);
        }
        else if (command == "Fire"){
            // extracting Noble Name and Warrior Name
            string nname, wname;
            commands >> nname >> wname;
            Warrior* warrptr = find_warrior(wname, warriors);
            Noble* nobptr = find_noble(nname, nobles);
            // checks if noble doesn't exist and call the fire method from the Noble class on the warrior
            if (nobptr==nullptr){
                cout << "Noble " << nname << "doesn't exist and failed to fire warrior " << wname << ".";
            }
            else{
                nobptr -> fire(*warrptr);
            }
        }
        else if (command == "Battle"){
            // extracting the names of the Noble and the Enemy in Battle
            string nname1, nname2;
            commands >> nname1 >> nname2;
            Noble* nobptr1 = find_noble(nname1, nobles);
            Noble* nobptr2 = find_noble(nname2, nobles);
            // checks if either of the nobles don't exist or call the battle method from the Noble class on the enemy noble
            if (nobptr1==nullptr){
                cout << "Noble " << nname1 << "doesn't exist and failed to battle " << nname2 << ".";
            }
            else if (nobptr2==nullptr){
                cout << "Noble " << nname2 << "doesn't exist and failed to battle " << nname1 << ".";
            }
            else{
                nobptr1 -> battle(*(nobptr2));
            }
            
        }
        // CLEAR command
        else{
            // deleting pointers for both warriors and nobles and setting each dangling pointer to nullptr
            for (size_t index = 0; index < warriors.size(); ++index){
                delete warriors[index];
                warriors[index] = nullptr;
            }
            for (size_t index = 0; index < nobles.size(); ++index){
                delete nobles[index];
                nobles[index] = nullptr;
            }
            // clearing both vectors of the nullptrs
            nobles.clear();
            warriors.clear();
        }
        
    }
    // closing the commands file
    commands.close();
}

// cannot make the find functions as pointers to const, since when you store it into pointer variables, you are changing their
// deferences in hire/fire/battle

// finding the given warrior by name in the vector of warriors and returns the warrior ptr, otherwise returns nullptr
Warrior* find_warrior(const string& wname, const vector<Warrior*>& warriors){
        for (size_t index = 0; index < warriors.size(); ++index){
            if (warriors[index]->get_name()==wname){
                return warriors[index];
            }
        }
    return nullptr;
    }
    
// finding the given noble by name in the vector of nobles and returns the noble ptr, otherwise returns nullptr
Noble* find_noble(const string& nname, const vector<Noble*>& nobles){
        for (size_t index = 0; index < nobles.size(); ++index){
            if (nobles[index]->get_noblename()==nname){
                return nobles[index];
            }
        }
    return nullptr;
    }

// prints Status of nobles and warriors
void displayStatus(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
                cout << "Status\n" << "======\n";
                cout << "Nobles:\n";
    // prints all noble objects with their warrior armies
                for (size_t index = 0; index < nobles.size(); ++index){
                    cout << *(nobles[index]) << endl;
                    }
    // if there are no nobles in the vector, then NONE is printed
                if (nobles.size()==0){
                    cout << "NONE" << endl;
                }
                cout << "\nUnemployed Warriors:\n";
    // finds the warriors that exist in the vector but aren't hired yet and prints them
                bool found = false;
                for (size_t index = 0; index < warriors.size(); ++index){
                    if (warriors[index]->get_hired()==false){
                        cout << "\t" << *(warriors[index]) << endl;
                        found = true;
                    }
                }
    // if no unemployed warriors are found, NONE is printed
                if(!found){
                        cout << "NONE" << endl;
                    }
}
                
