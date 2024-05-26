//
//  rec04.cpp
//  Created by Shrey Kharbanda on 2/17/23.
//

#include <iostream>
#include <vector>
using namespace std;

struct Complex {
   double real;
   double img;
};

class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   void setX( int x)  { this->x = x; }
private:
   int x;
};

class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
        : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};

class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers)
         cout << "already have speakers attached!\n";
      else
        
         attachedSpeakers = &spkrs;
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
       if (attachedSpeakers){
           attachedSpeakers = nullptr;}
       else{
           cout << "No speakers attached\n" << endl;
       }
   }
  
   void playMusic( ) const {
      if (attachedSpeakers)
         attachedSpeakers -> vibrateSpeakerCones(440);
      else
         cout << "No speakers attached\n";
   }
private:
    const SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
public:
    Person(const string& name) : name(name) {}
    bool movesInWith(Person& newRoomate) {
        if (roomie){
            cout << "You already have a roommate" << endl;
            return false;
        }
        if ((&newRoomate)==this){
            cout << "You can't be your own roommate" << endl;
            return false;
        }
        if (!newRoomate.roomie){
            roomie = &newRoomate;        // now I have a new roomie
            newRoomate.roomie = this; } // and now they do too
        else {
            cout << "They already have a roomate" << endl;
            return false;
        }
        return true;
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};


int main() {
    // Task 2
    int x;
    x = 10;
    cout << "x = " << x << endl;
    
    int* p;
    p = &x;
    cout << "p = " << p << endl;
    
  // p = 100000;
// p = 0x16fdff20c; // using the value from my Watch window
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;
    
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;
    
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;
    
    double d(33.44);
    double* pD(&d);
    *pD = *p; // can store int in a double
    *pD = 73.2343;
    *p  = *pD; // you can store a double in an int which gets rounded down
    *q  = *p;
   // pD  = p;  can't store int* memory in double* memory address
   // p   = pD; can't store double* memory in int* memory address
    
    int kol = 2;
    const int* cod = &kol;
    kol += 1;
    cout << "heyyyyyyyyyyyy" << *cod;
    
//    int* const haan = new int(2);
//    haan += 1;
    
    int joe = 24;
    const int sal = 19;
    int* pI;
    pI = &joe;
    *pI = 234;
   // pI = &sal; // cannot change sal in memory or value
    *pI = 7623;

    const int* pcI;
    pcI = &joe;
    // *pcI = 234; // treats the value as constant and not changable
    pcI = &sal; // can change memory address if const before *
    // *pcI = 7623; // treats the value as constant and not changable

   // int* const cpI; // it's imp to initialize any object of const type int*
    int* const cpI(&joe);
    // int* const cpI(&sal); // re-defination of cpI is not possible because memory is fixed
    // cpI = &joe; // re-defination of cpI is not possible because memory is fixed
    *cpI = 234;
    // cpI = &sal; // re-defination of cpI is not possible because memory is fixed
    *cpI = 7623;

    // const int* const cpcI; // it's imp to initialize any object of const type int*
    // const int* const cpcI(&joe); // re-defination of cpI is not possible because memory is fixed
    const int* const cpcI(&sal);
    // cpcI = &joe; // re-defination of cpI is not possible because memory is fixed
    // *cpcI = 234; // re-assigning of cpI's value is not possible because value is fixed
    // cpcI = &sal; // re-defination of cpI is not possible because memory is fixed
    // *cpcI = 7623; // re-assigning of cpI's value is not possible because value is fixed
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    // cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
    
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;
    
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    
    cout << "The " << *pDyn
         << " is stored at address " << pDyn
         << " which is in the heap\n";
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

    pDyn = nullptr;
    double* pDouble = nullptr;
    //cout << "Can we dereference nullptr?  " << *pDyn << endl;
    //cout << "Can we dereference nullptr?  " << *pDouble << endl; // cannot dereference a nullptr
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe
    
    short* pShrt = new short(5);
    delete pShrt;
    // delete pShrt; can't delete a deleted pointer
    
    long jumper = 12238743;
    // delete jumper; // cannot delete a value
    long* ptrTolong = &jumper;
    // delete ptrTolong;  // cannot delete a memory address not on heap
    Complex cmplx;
    // delete cmplx;      // cannot delete a struct object
    
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
       tmpPCmplx = new Complex; // create a new Complex object on the heap
       tmpPCmplx->real = ndx;   // set real and img to be the
       tmpPCmplx->img  = ndx;   // value of the current ndx
       complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear();
    
    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;
    
    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

    // display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear();
    
    Amplifier a;
    Amplifier* lol = &a;
    lol -> attachSpeakers(SpeakerSystem());
    lol -> playMusic();
    
    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;

}

// remember *memory leak* which is when you dont delete and *dangling pointer* which is when you dont assign to nullptr
