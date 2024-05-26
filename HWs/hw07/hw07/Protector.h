//
//  Protector.h
//  hw07
//
//  Created by Shrey Kharbanda on 4/3/23.
//

#ifndef Protector_h
#define Protector_h

#include <iostream>
#include <string>

namespace WarriorCraft {
    // to solve cyclic association
    class Lord;

    // defining the base Protector class for the Protector hierarchy
    class Protector {
        
        //friending the overloaded output operator calls defend() for the Protector hierarchy to give private access
        friend std::ostream& operator<< (std::ostream& os, const Protector& pro);
        
        public:
            // constructor, they are born as "not hired" initially
            Protector(const std::string& name, double wstrength);
            // getter method to return hired status
            bool isHired() const;
            // mutator method to change the hired status and connect to its lord
            void assign_lord(Lord* lordd);
            // mutator method to change the protector strength
            void set_strength(double wstrength);
            // getter method to return lord's pointer
            const Lord* get_lord() const;
            // getter method to return protector name
            const std::string& get_name() const;
            // getter method to return protector strength
            double get_strength() const;
            // when the protector runs away from its lord and informs him about his status
            bool runaway();
            // pure virtual method for overriding, defending themselves by blurting out different dialogues
            virtual void defend() const = 0;
        // declare variables for protector name, strength, and lord who hired the protector
        private:
            std::string wname;
            double strength;
            Lord* lord;
    };

    // defining the derived Wizard class for the Protector hierarchy
    class Wizard: public Protector {
    public:
        // defining the Wizard constructor
        Wizard(const std::string& name, double wstrength);
        // defining the defend method where the Wizard blurts out it's specific dialogue
        void defend() const;
    };

    // defining the derived Warrior class for the Protector hierarchy, which also serves as the base
    // class for the Warrior hierarchy
    class Warrior: public Protector {
    public:
        // defining the Warrior constructor
        Warrior(const std::string& name, double wstrength);
        // defining the defend method where the Warrior blurts out it's specific dialogue
        void defend() const;
    };

    // defining the derived Archer class for the Warrior hierarchy
    class Archer: public Warrior {
    public:
        // defining the Archer constructor
        Archer(const std::string& name, double wstrength);
        // defining the defend method where the Archer blurts out it's specific dialogue
        void defend() const;
    };

    // defining the derived Swordsman class for the Warrior hierarchy
    class Swordsman: public Warrior {
    public:
        // defining the Swordsman constructor
        Swordsman(const std::string& name, double wstrength);
        // defining the defend method where the Swordsman blurts out it's specific dialogue
        void defend() const;
    };

};

#endif /* Protector_h */
