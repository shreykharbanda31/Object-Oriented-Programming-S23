//
//  Noble.h
//  hw06
//  Created by Shrey Kharbanda on 3/14/23.
//

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>

// declaring a Noble class under namespace WarriorCraft
namespace WarriorCraft{
    // fixing cycling association
    class Warrior;
    // declaring a Noble class
    class Noble{
        public:
            // giving the overloaded output operator access to the private part of the Noble class
            friend std::ostream& operator<< (std::ostream& os, const Noble& nob);
            // takes in noble name to create a noble object
            Noble(const std::string& name);
            // getter method to return noble name
            const std::string& get_noblename() const;
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
            std::vector<Warrior*> army;
            std::string noblename;
            bool alive;
            double armystrength;
        };
};

#endif
