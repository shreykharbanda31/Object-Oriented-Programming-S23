//
//  hw07.cpp
//
//  Created by Shrey Kharbanda on 3/31/23.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// to solve cyclic association
class Lord;

// defining the base Protector class for the Protector hierarchy
class Protector {
    
    //friending the overloaded output operator calls defend() for the Protector hierarchy to give private access
    friend ostream& operator<< (ostream& os, const Protector& pro);
    
    public:
        // constructor, they are born as "not hired" initially
        Protector(const string& name, double wstrength);
        // getter method to return hired status
        bool isHired() const;
        // mutator method to change the hired status and connect to its lord
        void assign_lord(Lord* lordd);
        // mutator method to change the protector strength
        void set_strength(double wstrength);
        // getter method to return lord's pointer
        const Lord* get_lord() const;
        // getter method to return protector name
        const string& get_name() const;
        // getter method to return protector strength
        double get_strength() const;
        // when the protector runs away from its lord and informs him about his status
        bool runaway();
        // pure virtual method for defending themselves by blurting out different dialogues
        virtual void defend() const = 0;
    // declare variables for protector name, strength, and lord who hired the protector
    private:
        string wname;
        double strength;
        Lord* lord;
};

// defining the derived Wizard class for the Protector hierarchy
class Wizard: public Protector {
    public:
        Wizard(const string& name, double wstrength);
        void defend() const;
};

// defining the derived Warrior class for the Protector hierarchy, which also serves as the base
// class for the Warrior hierarchy
class Warrior: public Protector {
    public:
        Warrior(const string& name, double wstrength);
        void defend() const;
};

// defining the derived Archer class for the Warrior hierarchy
class Archer: public Warrior {
    public:
        Archer(const string& name, double wstrength);
        void defend() const;
};

// defining the derived Swordsman class for the Warrior hierarchy
class Swordsman: public Warrior {
    public:
        Swordsman(const string& name, double wstrength);
        void defend() const;
};

// defining the base Noble Class for the Noble hierarchy
class Noble {
    
    public:
        // takes in noble name to create a noble object
        Noble(const string& name);
        // getter method to return noble name
        const string& get_noblename() const;
        // getter method to return noble's alive status
        bool is_alive() const;

        // initiates a battle between the noble and the enemy noble
        void battle (Noble& enemy);

        // pure virtual method to override in both noble derivates
        virtual double get_strength() const = 0;
    
        // pure virtual method to change strength of each type of noble
        virtual void change_strength(double ratio) = 0;
    
        // pure virtual method for defending themselves by blurting out different dialogues
        virtual void defend() const = 0;
    
        // pure virtual method to print all the Noble specifics for the output operator depending on type
        virtual void display(ostream& os) const = 0;

    protected:
        // virtual method to set all variables accordingly when the noble dies
        virtual void die();

    // declares private variables containing the noble army vector, name and alive status of noble, army strength of noble
    private:
        string noblename;
        bool alive;
};

// defining the derived Lord Class for the Noble hierarchy
class Lord : public Noble {
public:
    //constructor for Lord
    Lord(const string& name);
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
    void change_strength(double ratio);
    
    // initiates a battle between the noble and the enemy noble
    void battle (Noble& enemy);

    //getter method for Lord's army strength
    double get_strength() const;
    
    // to set all variables accordingly when the lord dies
    void die();
    
    // to print all the Lord specifics for the output operator
    void display(ostream& os) const;
    
    // for defending a lord by blurting out a specific dialogues
    void defend() const;
    
private:
    vector<Protector*> army;
    double armystrength;
};

// defining the derived PersonWithStrengthToFight Class for the Noble hierarchy
class PersonWithStrengthToFight : public Noble {
public:
    PersonWithStrengthToFight(const string& name, double strengthh);
    
    // mutator method to change the strength of the personwithstrength based on the ratio
    void change_strength(double ratio);
    
    //getter method for personwithstrength's strength
    double get_strength() const;
    
    // to set all variables accordingly when the personwithstrength dies
    void die();
    
    //for defending a personwithstrength by blurting out a specific dialogues
    void defend() const;
    
    // to print all the personwithstrength's specifics for the output operator
    void display(ostream& os) const;
    
private:
    double strength;
};


//
// Test Code
//
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    cout << "\n==========\nNobles: \n"
     << sam << endl
     << randy << endl
     << janet << endl
     << barclay << endl
     << joe << endl
     << "\n==========\n";
    joe.battle(randy);                // joe has no army and dies.
    joe.battle(sam);                // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);       // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
     << sam << endl
     << randy << endl
     << janet << endl
     << barclay << endl
     << joe << endl
     << "==========\n";
} // main


// method definitions for Protector hierarchy


// constructors for Protector and Warrior kinds

// constructor for the base class Protector, they are born as "not hired" initially
Protector::Protector(const string& name, double wstrength): wname(name), strength(wstrength), lord(nullptr) {};

// constructor for derived class Wizard
Wizard::Wizard(const string& name, double wstrength): Protector(name, wstrength) {};

// constructor for derived class Warrior
Warrior::Warrior(const string& name, double wstrength): Protector(name, wstrength) {};

// constructor for derived class Archer
Archer::Archer(const string& name, double wstrength): Warrior(name, wstrength){};

// constructor for derived class Swordsman
Swordsman::Swordsman(const string& name, double wstrength): Warrior(name, wstrength){};

// method definitions for the base class Protector

// getter method to return hired status
bool Protector::isHired() const{
        return (lord != nullptr);
};

// getter method to return lord's pointer
const Lord* Lord::get_lord() const{
    return lord;
}
// mutator method to change connect protector to its noble
void Protector::assign_lord(Lord* lordd){
        lord = lordd;
};
// mutator method to change the protector strength
void Protector::set_strength(double wstrength){
        strength = wstrength;
};
// getter method to return protector name
const string& Protector::get_name() const{
        return wname;
};
// getter method to return protector strength
double Protector::get_strength() const{
        return strength;
};
// returns true when the protector runs away from its noble and informs him about his status, else returns false
bool Protector::runaway(){
    if (!(lord->is_alive())){
        cout << lord->get_noblename() << " is dead!" << endl;
        return false;
    }
    if (!isHired()){
        cout << wname << "does not have a noble lord" << endl;
        return false;
    }
    string noblename = lord->get_noblename();
    if(lord->remove(*this)){
        cout << wname << " flees in terror, abandoning his lord, " << noblename << endl;
        return true;
    }
    return false;
};

// method definitions for the derived classes of Protector and Warrior

void Wizard::defend() const{
    cout << "POOF!" << endl;
};

void Warrior::defend() const{
    cout << get_name() << " says: Take that in the name of my lord, " << get_lord()->get_noblename() << endl;
};

void Archer::defend() const{
    cout << "TWANG!  ";
    Warrior::defend();
};

void Swordsman::defend() const{
    cout << "CLANG!  ";
    Warrior::defend();
};

// method definitions for Noble hierarchy

// constructors for the Noble hierarchy
Noble::Noble(const string& name) : noblename(name), alive(true){};

Lord::Lord(const string& name) : Noble(name), armystrength(0) {};

PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strengthh) : Noble(name), strength(strengthh) {};

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

// returns true/false based on the protector's hire status
bool Lord::hires(Protector& pro){
    // checks if noble is alive and returns an appropriate response
    if (!is_alive()){
        cout << get_noblename() << " failed to hire " << pro.get_name() << endl;
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
        // tells the user if the warrior is already hired and hence, the noble failed to hire the warrior
        cout << get_noblename() << " failed to hire " << pro.get_name() << endl;
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
        cout << get_noblename() << " failed to fire " << pro.get_name() << endl;
        return false;
    };
    bool fired = remove(pro);
    // if the loop is run over in the remove method and the protector does not exist in the lord's army
    // then firing of the protetcor by the lord makes no sense
    if (fired==false){
        cout << get_noblename() << " failed to fire " << pro.get_name() << endl;
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
void Lord::change_strength(double ratio){
    for (size_t index = 0; index < army.size(); ++index){
        army[index]->set_strength((army[index]->get_strength())-((army[index]->get_strength())*(ratio)));
    };
};

// initiates a battle between the noble and the enemy noble
void Noble::battle (Noble& enemy){
    defend();
    enemy.defend();
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
    else{ // initiating a battle and changing army strengths by deciding which noble is stronger,
        // plus overriding get_strength() based on the type of the noble if both are alive
        if (get_strength() == enemy.get_strength()){
            // calling die methods for both of them
            die();
            enemy.die();
            cout << "Mutual Annihilation: " << noblename << " and " << enemy.noblename << " die at each other's hands" << endl;
        }
        else if (get_strength() > enemy.get_strength()){
            // if enemy strength is 1/4 of the noble's strength, all strengths
            // of the noble get reduced by 1/4
            if (enemy.get_strength() == (0.25*get_strength())){
                change_strength(0.25);
            }
            else {
                // changes noble army strength based on the strength ratio
                change_strength((enemy.get_strength())/get_strength());
            }
            enemy.die();
            cout << noblename << " defeats " << enemy.noblename << endl;
        }
        else {
            // if the noble's strength is 1/4 of the enemy noble's strength, all strengths
            // of the noble get reduced by 1/4
            if (get_strength() == (0.25*enemy.get_strength())){
                enemy.change_strength(0.25);
            }
            else {
                // changes enemy noble strength based on the strength ratio
                change_strength((get_strength()/enemy.get_strength()));
            }
            // set lost noble's strengths to 0 and declare them dead
            die();
            cout << enemy.noblename << " defeats " << noblename << endl;
        }
    }
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

// for defending a lord by blurting out a specific dialogues
void Lord::defend() const{
    // loops over all Protectors within the lord army
    for (size_t index = 0; index < army.size()-1; ++index){
        cout << army[index]->defend() << "\n\t\t";
    };
};

//display method for outputting Lord specifics
void Lord::display(ostream& os) const{
    os << get_noblename() << " has an army of " << army.size() << "\n\t\t";
    // loops over all Protectors within the lord army except for the last one
    for (size_t index = 0; index < army.size()-1; ++index){
        os << *army[index] << "\n\t\t";
    };
    // call over last warrior here
    os << *(army[army.size()-1]);
};

// to set all variables accordingly when the personwithstrength dies
void PersonWithStrengthToFight::die(){
    strength = 0;
    Noble::die();
};

//getter method for personwithstrength's strength
double PersonWithStrengthToFight::get_strength() const {
    return strength;
};

// mutator method to change the strength of the personwithstrength based on the ratio
void PersonWithStrengthToFight::change_strength(double ratio){
    strength = strength - (strength*ratio);
};

// for defending a personwithstrength by blurting out a specific dialogues
void PersonWithStrengthToFight::defend() const{
    cout << "UGH!!!" << endl;
};

// to print all the personwithstrength's specifics for the output operator
void PersonWithStrengthToFight::display(ostream& os) const{
    os << get_noblename() << " has strength: " << strength << endl;
};



//the overloaded output operator calls defend() for the Protector class
ostream& operator<< (ostream& os, const Protector& pro){
    os << pro.wname << ": " << pro.strength;
    return os;
};

//the overloaded output operator calls defend() for the Noble hierarchy
ostream& operator<<(ostream& os, const Noble& nob){
    nob.display(os);
    return os;
};
