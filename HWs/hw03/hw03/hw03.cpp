//
//  hw03.cpp
//  Created by Shrey Kharbanda on 2/10/23.
//  This program models a game of medieval times using a text file of commands, where the warriors
//  battle amongst each other based on their weapons' strengths.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// using a Class to define a Warrior object
class Warrior{
    private:
    // using a Class to define a Weapon object, nested inside the Warrior class
        class Weapon{
            // friending the output operator to provide it with access to Weapon's private variables
            friend ostream& operator<< (ostream& os, const Warrior::Weapon& weapon);
            
            public:
            // defining Weapon constructors with weapon name and its strength  (an empty one is recommended by the Professor)
                Weapon(const string& we_name, int streng) : weap_name(we_name), strength(streng){};
                Weapon() {};
            
            // defining a getter method to return the private variable strength
            int get_strength() const {return strength;};
            
            // defining a mutator method to change the private variable holding weapon's strength
            void set_strength(int new_strength) {strength = new_strength;};
           
            // defining private variables for a weapon: name and its strength
            private:
                string weap_name;
                int strength;
        };
    
        // defining private variables for a warrior: name and their weapon
        string warr_name;
        Weapon weapon;
    
    public:
        // friending the output operator to provide it with access to Warrior's private variables and the Weapon class objects
        friend ostream& operator<< (ostream& os, const Warrior::Weapon& weapon);
        friend ostream& operator<< (ostream& os, const Warrior& warrior);
    
        // defining Warrior constructors with warrior name and their weapon (an empty one is recommended by the Professor)
        Warrior(const string& w_name, const string& we_name, int streng) : warr_name(w_name), weapon(we_name, streng){};
        Warrior() {};
    
        // defining a getter method to return the private variable holding warrior name
        const string& get_name() const {return warr_name;};
    
        // defining a method to initiate a battle
        void battle(Warrior& warrior2) {
            cout << warr_name << " battles " << warrior2.warr_name << endl;
            // checking for warriors who're dead
            if (weapon.get_strength() == 0 && warrior2.weapon.get_strength() == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
            else if (weapon.get_strength() == 0){
                cout << "He's dead, " << warrior2.warr_name << endl;
            }
            else if (warrior2.weapon.get_strength() == 0){
                cout << "He's dead, " << warr_name << endl;
            }
            else{ // initiating a battle and changing weapon stremgths by deciding which warrior is stronger, if both are alive
                if (weapon.get_strength() == warrior2.weapon.get_strength()){
                    weapon.set_strength(0);
                    warrior2.weapon.set_strength(0);
                    cout << "Mutual Annihilation: " << warr_name << " and " << warrior2.warr_name << " die at each other's hands" << endl;
                }
                else if (weapon.get_strength() > warrior2.weapon.get_strength()){
                    weapon.set_strength(weapon.get_strength()-warrior2.weapon.get_strength());
                    warrior2.weapon.set_strength(0);
                    cout << warr_name << " defeats " << warrior2.warr_name << endl;
                }
                else {
                    warrior2.weapon.set_strength(warrior2.weapon.get_strength() - weapon.get_strength());
                    weapon.set_strength(0);
                    cout << warrior2.warr_name << " defeats " << warr_name << endl;
                }
            }
        };

};
// overloading the output operator for a Weapon object
ostream& operator<< (ostream& os, const Warrior::Weapon& weapon){
    os << "weapon: " << weapon.weap_name << ", " << weapon.strength;
    return os;
};
// overloading the output operator for a Warrior object
ostream& operator<< (ostream& os, const Warrior& warrior){
    os << "Warrior: " << warrior.warr_name << ", " << warrior.weapon << endl;
    return os;
};

// setting function prototypes
void create_warrior(vector<Warrior>& warriors_list, const string& warr_name, const string& weap_name, int streng);
bool check_validity(const vector<Warrior>& warriors_list, size_t windex1, size_t windex2, const string& wname1, const string& wname2);
void display_status(const vector<Warrior>& warriors_list);

int main() {
    
    // creating a vector to store all Warrior objects and a variable to check command
    vector<Warrior> warriors_list;
    string command;
    
    // opening and reading the file and checking if it exists
    ifstream warrior_data("warriors.txt");
    if (!warrior_data){
        cout << "File not opened properly!" << endl;
    }
    
    // calling appropriate functions and object methodsbased on commands read from the file
    while (warrior_data >> command){
        if (command == "Warrior"){
            string warr_name, weap_name;
            int streng;
            // reading warrior name, weapon name, and weapon strength
            warrior_data >> warr_name >> weap_name >> streng;
            // calling a function to create a Warrior object with the given parameters
            create_warrior(warriors_list, warr_name, weap_name, streng);
            
        }
        else if (command == "Status"){
            
            // calling a function to display the status of current warrior objects stored in the vector
            display_status(warriors_list);
        }
        else {
            string wname1, wname2;
            bool exists;
            // reads the names of the warriors who battle
            warrior_data >> wname1 >> wname2;
            // finding the warriors from the vector based on their names
            size_t windex1 = 0, windex2 = 0, index = 0;
            while (index < warriors_list.size()){
                if (warriors_list[index].get_name() == wname1){
                    windex1 = index;
                }
                else if (warriors_list[index].get_name() == wname2){
                    windex2 = index;
                }
                ++index;
            };
            // checks if the warriors exist in the given vector and displays error messages if they don't exist before calling battle
            exists = check_validity(warriors_list, windex1, windex2, wname1, wname2);
            if (exists){
                warriors_list[windex1].battle(warriors_list[windex2]);
            };
        }
    }
    
    // closing the file
    warrior_data.close();
}

// creates a Warrior object with the given parameters
void create_warrior(vector<Warrior>& warriors_list, const string& warr_name, const string& weap_name, int streng){
    
    // checks if the new warrior created already exists in the vector and displays an error message,
    // if the name of the warrior already exists and then, it does not add the warrior to the vector again
    size_t index = 0;
    bool exists = false;
    while (index < warriors_list.size()){
        if (warriors_list[index].get_name() == warr_name){
            cout << "Warrior: " << warr_name << " already exists!" << endl;
            exists = true;
            break;
        }
        ++index;
    }
    
    // if warrior does not exist in the vector, then we add it to the end of the vector
    if (!exists){
        warriors_list.emplace_back(warr_name, weap_name, streng);
    };
    
};

// checks if the warriors exist in the given vector and displays error messages if they don't exist and returns true/false
bool check_validity(const vector<Warrior>& warriors_list, size_t windex1, size_t windex2, const string& wname1, const string& wname2){
    
    // checking if warrior names were not found in the vector and displaying error messages
    if (warriors_list[windex1].get_name() != wname1){
        cout << "Warrior: " << wname1 << " not found!" << endl;
        return false;
    }
    if (warriors_list[windex2].get_name() != wname2){
        cout << "Warrior: " << wname2 << " not found!" << endl;
        return false;
    }
    return true;
};

// prints the status of the warriors and weapon strengths to the output console
void display_status(const vector<Warrior>& warriors_list){
    
    // prints the size of the warrior list
    cout << "There are: " << warriors_list.size() << " warriors" << endl;
    
    // loops over the vector to print the warrior objects
    for (size_t index=0; index<warriors_list.size(); ++index){
        cout << warriors_list[index];
    }
};
