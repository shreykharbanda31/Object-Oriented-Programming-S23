#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
/*
  rec01_start.cpp
  spring 2023
*/


//
// Function prototypes for tasks 15-17
//

// Task 15. Function to display a vector of ints

void displayvectorOfints(const vector<int>& vcI);

// Task 16. Function to modify the vector, using indices

void modifyvectorOfints(vector<int>& vcI);

// Task 17. Function to modify the vector, using a ranged for

void modifyUsingForvectorOfints(vector<int>& vcI);


//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"
  std::cout << "hello ..." << std::endl;

    // Task 2  Printing hello ...  Using "using namespace"

  cout << "hello ..." << endl;

    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable
  int x;
  cout << "x: " << x << endl;
    
    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.

    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;

    cout << "size of x: " << sizeof(x) << endl;
    cout << "size of y: " << sizeof(y) << endl;
    cout << "size of z: " << sizeof(z) << endl;
    cout << "size of pie: " << sizeof(pie) << endl;
    // Task 5  Attempt to assign the wrong type of thing to a variable

    //string felix = x;  Compilation Error

    //
    // Conditions
    //

    // Task 6  Testing for a range

    if (y>=10 && y<=20){
      cout << "y: " << y << " lies between 10 and 20" << endl;
    }
    else{
      cout << "y: " << y << " does not lie between 10 and 20" << endl;
    }

    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop

    // Then with a while loop

    // Finally with a do-while loop

  for (int i=10; i<=20; ++i){
    cout << i << ' ';
  }
  cout << endl;

  int k = 10;
  while (k<=20){
    cout << k << ' ';
    ++k;
  }
  cout << endl;

  int m = 10;
  do{
    cout << m << ' ';
    ++m;
  } while (m<=20);
  cout << endl;

    // Task 8  Looping to successfully open a file, asking user for the name

    ifstream ifs;
  do {
    cout << "name of file: ";
    string name;
    cin >> name;
      ifs.open(name);
  } while(!ifs);
    // Task 9  Looping, reading file word by "word".

  string word;
  while (ifs >> word) {
   cout << word << endl;
  }

  ifs.close();
    // Task 10 Open a file of integers, read it in, and display the sum.

  ifstream integersfs("integers.txt");
  
  if (!integersfs) {
   cerr << "Could not open the file.\n";
   exit(1);
  }
    int sum = 0;
  int anInt=0;
  while (integersfs >> anInt) {
   sum = sum + anInt;
  }
cout << "sum: " << sum << endl;
    integersfs.close();

    // Taks 11 Open and read a file of integers and words. Display the sum.
    ifstream mixedfs("integers.txt");
    
    if (!mixedfs) {
     cerr << "Could not open the file.\n";
     exit(1);
    }
      int sum2 = 0;
    int anInt2=0;
    while (mixedfs >> anInt2) {
     sum2 = sum2 + anInt2;
    }
  cout << "sum: " << sum << endl;
      mixedfs.close();

    //
    // Vectors
    //

    // Task 12 Filling a vector of ints
    vector<int> vectorOfInts;
    for (int l=10; l<=100; ++l){
        vectorOfInts.push_back(l);
    }
    
    // Task 13 Displaying the vector THREE times
    //         a) using the indices,
    for (size_t num = 0; num < vectorOfInts.size(); ++num) {
        int x = vectorOfInts[num];
        cout << x << ' ';
    }
    cout << endl;
    //         b) using a "ranged for"
    for (int num : vectorOfInts){
        cout << num << ' ';
    }
    cout << endl;
    //         c) using indices again but backwards
    for (size_t num = vectorOfInts.size(); num>0 ; --num) {
        int x = vectorOfInts[num-1];
        cout << x << ' ';
    }
    cout << endl;
    // Task 14. Initialize a vector with the primes less than 20.
    vector<int> vectorOfPrimes{2, 3, 5, 7, 11, 13, 17, 19,};
    for (int pnum : vectorOfPrimes){
        cout << pnum << ' ';
    }
    cout << endl;
    //
    // Function calls
    //
    
    // Task 15  Function to print a vector

    displayvectorOfints(vectorOfInts);
    // Task 16  Function to double the values in a vector
    
    vector<int> v{1,2,3};
    modifyvectorOfints(v);
    displayvectorOfints(v);

    // Task 17  Function to double the values in a vector, using a ranged for
    vector<int> v2{1,2,3};
    modifyUsingForvectorOfints(v2);
    displayvectorOfints(v2);
    
}

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints

void displayvectorOfints(const vector<int>& vcI){
    for (int num : vcI){
        cout << num << ' ';
    }
    cout << endl;
}

// Task 16. Function to modify the vector, using indices

void modifyvectorOfints(vector<int>& vcI){
    for (size_t num = 0; num < vcI.size(); ++num) {
        int x = vcI[num];
        vcI[num] = x*2;
    }
}

// Task 17. Function to modify the vector, using a ranged for

void modifyUsingForvectorOfints(vector<int>& vcI){
    for (int& num: vcI) {
        num = num*2;
    }
}

