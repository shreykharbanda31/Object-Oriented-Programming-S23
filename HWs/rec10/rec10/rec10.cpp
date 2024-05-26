/*
  rec10.cpp
  Created by Shrey Kharbanda on April 7, 2023.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Instrument Class

class Instrument {
    public:
    virtual void make_sound() const = 0;
    virtual void display(ostream& os) const = 0;
    virtual void play() = 0;
};

// make sound Instrument method
void Instrument::make_sound() const{
    cout << "To make a sound... ";
}

// output operator Instrument
ostream& operator<< (ostream& os, const Instrument& ins){
    ins.display(os);
    return os;
};

// Brass Class Hierarchy

class Brass : public Instrument {
public:
    Brass(unsigned bsize) : cunt("shreyz"), size(bsize) {};
    void make_sound() const{
        Instrument::make_sound();
        cout << "blow on a mouthpiece of size " << size << endl;;
    };
    void display(ostream& os) const{
        os << ": " << size << endl;
    };
private:
    unsigned size;
    string cunt;
};

class Trumpet : public Brass{
    public:
    Trumpet(unsigned trsize) : Brass(trsize) {};
    void display(ostream& os) const{
        os << "\tTrumpet";
        Brass::display(os);
    };
    void play() {cout << "Toot";};
};

class Trombone: public Brass {
    public:
        Trombone(unsigned trsize) : Brass(trsize) {};
    void display(ostream& os) const{
        os << "\tTrombone";
        Brass::display(os);
    };
    void play() {cout << "Blat";};
};

// String Class Hierarchy

class String : public Instrument {
public:
    String(unsigned spitch) : Instrument(), pitch(spitch) {};
    void make_sound() const{
        Instrument::make_sound();
        cout << "bow a string with pitch " << pitch << endl;
    };
    void display(ostream& os) const{
        os << ": " << pitch << endl;
    };
private:
    unsigned pitch;
};

class Violin : public String{
    public:
        Violin(unsigned vpitch) : String(vpitch) {};
        void display(ostream& os) const{
            os << "\tViolin";
            String::display(os);
        };
        void play() {cout << "Screech";};
};

class Cello: public String {
    public:
        Cello(unsigned cpitch) : String(cpitch) {};
        void display(ostream& os) const{
            os << "\tCello";
            String::display(os);
        };
        void play() {cout << "Squawk";};
};

// Percussion Class Hierarchy

class Percussion : public Instrument {
public:
    Percussion(): Instrument() {};
    void make_sound() const{
        Instrument::make_sound();
        cout << "hit me!" << endl;;
    };
    // why does this work without display()
};

class Drum : public Percussion {
    public:
        Drum() : Percussion() {};
        void display(ostream& os) const{
            os << "\tDrum" << endl;
        };
        void play() {cout << "Boom";};
};

class Cymbal: public Percussion {
    public:
        Cymbal() : Percussion() {};
        void display(ostream& os) const{
            os << "\tCymbal" << endl;;
        };
        void play() {cout << "Crash";};
};

class MILL {
    friend ostream& operator<< (ostream& os, const MILL& rhs);
    public:
        void receiveInstr(Instrument& ins){
            ins.make_sound();
            
            bool inserted = false;
            for (size_t index = 0; index < inventory.size(); ++index){
                if (inventory[index]==nullptr){
                    inventory[index] = &ins;
                    inserted = true;
                    break;
                }
            }
            if (!inserted){
                inventory.push_back(&ins);
            }
        };
        void dailyTestPlay() const{
            for (size_t index = 0; index < inventory.size(); ++index){
                if (inventory[index]) {inventory[index]->make_sound();}
            }
        }
        Instrument* loanOut() {
            if (inventory.size()==0){
                return nullptr;
            }
            bool loaned = false;
            for (size_t index = 0; index < inventory.size(); ++index){
                if (inventory[index]!=nullptr){
                    loaned = true;
                    Instrument* ins = inventory[index];
                    inventory[index] = nullptr;
                    return ins;
                }
            }
            return nullptr;

        };
    private:
        vector<Instrument*> inventory;
};

// output op for MILL

ostream& operator<< (ostream& os, const MILL& rhs){
    if (rhs.inventory.size()==0){
        os << "The MILL has the following instruments: None" << endl;
    }
    else{
        os << "The MILL has the following instruments: " << endl;
        bool printed = false;
        for (size_t index = 0; index < rhs.inventory.size(); ++index){
            if (rhs.inventory[index]) {os << *(rhs.inventory[index]); printed = true;}
        }
        if (!printed) {os << "None" << endl;}
    }
    return os;
};

//
// Musician class as provided to the students. Requires an Instrument class.
//

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->make_sound();
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument
    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};

// Orchestra class

class Orch{
    public:
        void addPlayer(Musician& mus){
            orchestra.push_back(&mus);
        };
        void play() {
            for (size_t index = 0; index < orchestra.size(); ++index){
                orchestra[index]->play();
            }
            cout << endl;
        };
    private:
        vector<Musician*> orchestra;
};

int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
     Drum drum;
     Cello cello(673);
     Cymbal cymbal;
     Trombone tbone(4);
     Trumpet trpt(12) ;
     Violin violin(567) ;

    cout << "Define the MILL -----------------------------------------------\n";
     MILL mill;
     cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
     mill.receiveInstr(trpt);
     mill.receiveInstr(violin);
     mill.receiveInstr(tbone);
     mill.receiveInstr(drum);
     mill.receiveInstr(cello);
     mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
     << "dailyTestPlay()" << endl;
     mill.dailyTestPlay();
     cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
     Musician harpo("Harpo");
     Musician groucho("Groucho");
      
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
     groucho.testPlay();     // Groucho doesn't have an instrument yet.

     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
     groucho.testPlay();
     mill.receiveInstr(*groucho.giveBackInstr());
     harpo.acceptInstr(mill.loanOut());
     groucho.acceptInstr(mill.loanOut());
     groucho.testPlay();
     harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
     mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
     cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
       mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
     cout << mill << endl;

    //
    // PART TWO
    //
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
    
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
}


