//
//  Noble.h
//  hw07
//
//  Created by Shrey Kharbanda on 4/3/23.
//

#ifndef Noble_h
#define Noble_h

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft{

    // to solve cyclic association
    class Protector;

    // defining the base Noble Class for the Noble hierarchy
    class Noble {
        
        public:
        
            // takes in noble name to create a noble object
            Noble(const std::string& name);
        
            // getter method to return noble name
            const std::string& get_noblename() const;
        
            // getter method to return noble's alive status
            bool is_alive() const;

            // initiates a battle between the noble and the enemy noble
            void battle (Noble& enemy);

            // pure virtual method to override in both noble derivates
            virtual double get_strength() const = 0;
        
            // pure virtual method to override change strength of each type of noble
            virtual void change_strength (double winner, double loser) = 0;
        
            // pure virtual method for defending themselves by blurting out different dialogues
            virtual void defend() const = 0;
        
            // pure virtual method to print all the Noble specifics for the output operator depending on type
            virtual void display(std::ostream& os) const = 0;

        // it's protected so that only its derived classes can change their individual alive status
        protected:
            // pure virtual method to set all variables accordingly when the noble dies
            virtual void die() = 0;

        // declares private variables containing the noble name and alive status of noble
        private:
            std::string noblename;
            bool alive;
    };

    // defining the derived Lord Class for the Noble hierarchy
    class Lord : public Noble {
        
        public:
            //constructor for Lord
            Lord(const std::string& name);
        
            // returns true/false based on the protector's hire status
            bool hires(Protector& pro);

            //checks if the protector exists in the noble's army and then removes the desired protector, if found and changes it's noble status
            bool remove(Protector& pro);

            // returns true/false based on if the protector was fired
            bool fires(Protector& pro);
            
            // to change the strength of each protector in the army vector to 0
            void change_army_strength_0();
            
            // to change the strength of each protector in the army vector to their new strength based on the ratio from
            // the battle results
            void change_strength(double winner, double loser);
            
            //getter method for Lord's army strength
            double get_strength() const;
            
            // the overriden method to set all variables accordingly when the lord dies
            void die();
            
            // to print all the Lord specifics for the output operator
            void display(std::ostream& os) const;
            
            // for defending a lord by blurting out a specific dialogues
            void defend() const;
          
        // declares private variables containing the lord army vector and army strength of lord
        private:
            std::vector<Protector*> army;
            double armystrength;
    };

    // defining the derived PersonWithStrengthToFight Class for the Noble hierarchy
    class PersonWithStrengthToFight : public Noble {
        
        public:
            // defining the constructor for a PersonWithStrengthToFight
            PersonWithStrengthToFight(const std::string& name, double strengthh);
            
            // mutator method to change the strength of the personwithstrength based on the ratio
            void change_strength(double winner, double loser);
            
            //getter method for personwithstrength's strength
            double get_strength() const;
            
            // to set all variables accordingly when the personwithstrength dies
            void die();
            
            //for defending a personwithstrength by blurting out a specific dialogues
            void defend() const;
            
            // to print all the personwithstrength's specifics for the output operator
            void display(std::ostream& os) const;
        
        // declaring private variables containing the personwithstrength's birth strength
        private:
            double strength;
    };

    //prototype for a non-friended output operator for the Noble hierarchy
    std::ostream& operator<< (std::ostream& os, const Noble& nob);

};

#endif /* Noble_h */
