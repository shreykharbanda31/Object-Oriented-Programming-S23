//
//  hw02.cpp
//  Created by Shrey Kharbanda on 2/4/23.
//  This program models a game of medieval times, where the warriors battle amongst each other based on their
//  strengths.
//

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// creating a struct for the entire program
struct Warrior{
    string name;
    int strength;
};

// setting up function prototypes

Warrior create_warrior(ifstream& warrior_data);

void insert_warrior(const Warrior& new_warrior, vector<Warrior>& warriors_list);

void display_status(const vector<Warrior>& warriors_list);

void battle_results(ifstream& warrior_data, vector<Warrior>& warriors_list);

int main() {
    
    // creating a vector to store all warrior structs and a variable to check command
    vector<Warrior> warriors_list;
    string command;
    
    // opening and reading the file and checking if it exists
    ifstream warrior_data("warriors.txt");
    if (!warrior_data){
        cout << "File not opened properly!" << endl;
    }
    
    // calling functions based on commands read from the file
    while (warrior_data >> command){
        if (command == "Warrior"){
            Warrior new_warrior;
            new_warrior = create_warrior(warrior_data);
            insert_warrior(new_warrior, warriors_list);
        }
        else if (command == "Status"){
            display_status(warriors_list);
        }
        else {
            battle_results(warrior_data, warriors_list);
        }
    }
    
    // closing the file
    warrior_data.close();
}

// creates and returns a new warrior struct by reading name and strength from the file inputted in the stream
Warrior create_warrior(ifstream& warrior_data){
    Warrior new_warrior;
    warrior_data >> new_warrior.name >> new_warrior.strength;
    return new_warrior;
}

// inserts each warrior after it has been created into a vector
void insert_warrior(const Warrior& new_warrior, vector<Warrior>& warriors_list){
    
    // checks if the new warrior created already exists in the vector and displays an error message,
    // if the name of the warrior already exists and does not add the warrior to the vector again
    size_t index = 0;
    bool exists = false;
    while (index < warriors_list.size()){
        if (warriors_list[index].name == new_warrior.name){
            cout << "Warrior: " << new_warrior.name << " already exists!" << endl;
            exists = true;
            break;
        }
        ++index;
    }
    
    // if warrior does not exist in the vector, then we add it to the end of the vector
    if (!exists){
        warriors_list.push_back(new_warrior);
    }
}

// performs battles between warriors and prints out the results to the user
void battle_results(ifstream& warrior_data, vector<Warrior>& warriors_list){
    string warrior_name1, warrior_name2;
    size_t warrior_index1 = 0, warrior_index2 = 0;
    
    // reading warrior names in the battle from the file
    warrior_data >> warrior_name1 >> warrior_name2;
    
    // finding the warriors from the vector based on their names
    size_t index = 0;
    while (index < warriors_list.size()){
        if (warriors_list[index].name == warrior_name1){
            warrior_index1 = index;
        }
        else if (warriors_list[index].name == warrior_name2){
            warrior_index2 = index;
        }
        ++index;
    }
    
    // checking if warrior names were not found in the vector and displaying error messages
    if (warriors_list[warrior_index1].name != warrior_name1){
        cout << "Warrior: " << warrior_name1 << " not found!" << endl;
    }
    if (warriors_list[warrior_index2].name != warrior_name2){
        cout << "Warrior: " << warrior_name2 << " not found!" << endl;
    }
    
    // if both exist, first checking if anyone's already dead, and if they both are alive,
    // the battle is initiated by re-calculating and re-assigning warriors' strengths
    // based on which warrior is stronger and displaying appropriate result messages
    else {
        cout << warrior_name1 << " battles " << warrior_name2 << endl;
        if (warriors_list[warrior_index1].strength == 0 && warriors_list[warrior_index2].strength == 0){
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
        else if (warriors_list[warrior_index1].strength == 0){
            cout << "He's dead, " << warrior_name2 << endl;
        }
        else if (warriors_list[warrior_index2].strength == 0){
            cout << "He's dead, " << warrior_name1 << endl;
        }
        else{ // initiating a battle by deciding which warrior is stronger, if both are alive
            if (warriors_list[warrior_index1].strength == warriors_list[warrior_index2].strength){
                warriors_list[warrior_index1].strength = 0;
                warriors_list[warrior_index2].strength = 0;
                cout << "Mutual Annihilation: " << warrior_name1 << " and " << warrior_name2 << " die at each other's hands" << endl;
            }
            else if (warriors_list[warrior_index1].strength > warriors_list[warrior_index2].strength){
                warriors_list[warrior_index1].strength = warriors_list[warrior_index1].strength - warriors_list[warrior_index2].strength;
                warriors_list[warrior_index2].strength = 0;
                cout << warrior_name1 << " defeats " << warrior_name2 << endl;
            }
            else {
                warriors_list[warrior_index2].strength = warriors_list[warrior_index2].strength - warriors_list[warrior_index1].strength;
                warriors_list[warrior_index1].strength = 0;
                cout << warrior_name2 << " defeats " << warrior_name1 << endl;
            }
        }
    }
    
}

// prints status of warriors (name and strength remaining), when prompted in the file, to the user
void display_status(const vector<Warrior>& warriors_list){
    
    // lists the number of warriors in the vector, regardless of their strength
    cout << "There are: " << warriors_list.size() << " warriors" << endl;
    
    // loops over the vector to print the warriors' data
    for (size_t index=0; index<warriors_list.size(); ++index){
        cout << "Warrior: " << warriors_list[index].name << ", strength: " << warriors_list[index].strength << endl;
    }
}
