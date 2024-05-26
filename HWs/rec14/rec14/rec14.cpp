/*
  rec14_starter code
 */

#include <iostream>
#include <vector>
#include <algorithm>  // max
using namespace std;


// Node type for the linked list
struct Node {
    //Node (int val = 0, Node* n = nullptr) : data(val), next(n) {};
    int data;
    Node* next;
};

// Node type for the binary tree
struct TNode {
  int data;
  TNode *left, *right;
};

void listDisplay(const Node* headPtr) {
    if (headPtr == nullptr) {
        cout << endl;
    }
    else{
        cout << headPtr->data << ' ';
        listDisplay(headPtr->next);
    }
};

/////////////////////////////////////////////////////////////////////////
//
// Provided code for use in testing
//
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);

Node* listNodeAtIndex(int index, Node* headPtr) {
    // if they ask for an index beyond the end of the list, return NULL
    if (!headPtr) return NULL;
    if (index==0) {return headPtr;}
    else{
        return listNodeAtIndex(index-1, headPtr->next);
    }
}

//
// Your functions go here
//
//   Task 1 function:
Node* listSum(Node* first, Node* second){
    if (first == nullptr && second == nullptr){
        return nullptr;
    }
    if (first == nullptr){
        return new Node{second->data, listSum(first,second->next)};
    }
    if (second == nullptr){
        return new Node{first->data, listSum(first->next, second)};
    }
    return new Node{first->data + second->data, listSum(first->next, second->next)};
};
//   Task 2 function:
int treeMax(TNode* tre){
    if(tre == nullptr) throw exception();
    if (tre -> right == nullptr && tre -> left == nullptr){
        return tre -> data;
    }
    if (tre -> right == nullptr){
        return max(tre -> data, treeMax(tre -> left));
    }
    if (tre -> left == nullptr){
        return max(tre -> data, treeMax(tre -> right));
    }
    return max(tre -> data, max(treeMax(tre -> left), treeMax(tre -> right)));
};

//   Task 3 function:
bool palindrome(const char cr[], int num){
    if (num == 0 || num == 1){
        return true;
    }
//    if (cr[0] == cr[num-1]){
//        return false;
//    }
    return cr[0] == cr[num-1] && palindrome(cr + 1, num - 2);
};
//   Task 4 function:
bool parity(unsigned num){
    if (num == 0){
        return true;
    }
    if (num == 1){
        return false;
    }
    if (parity(num/2)){
        return num%2 == 0;
    }
    else {
        return num%2 == 1;
    }
};
//   Task 5 function:
unsigned towers (int n, char disk, char spindle, char target) {
    if (n==0){
        return 0;
    }
    return 1 + towers(n-1, disk, target, spindle) + towers(n-1, spindle, disk, target);
}

void mystery(int n) {
   if (n > 1) {
      cout << 'a';
      mystery(n/2);
      cout << 'b';
      mystery(n/2);
   }
   cout << 'c';
}

int main() {
    // We have provided some test code to save you time. Certainly fee
    // free to write more!

    // Task 1:
    cout << "\n==============\n#1: Testing listSum\n";
    Node* l1 = listBuild({2, 7, 1, 8});
    cout << "List (l1): ";
    listDisplay(l1);
    listPrint(l1);
    Node* lalu = listNodeAtIndex(1, l1);
    listPrint(lalu);
    Node* l2 = listBuild({9, 1, 4, 1});
    cout << "List (l2): ";
    listPrint(l2);

    Node* l3 = listBuild({3, 1, 4, 1, 5, 9});
    cout << "List (l3): ";
    listPrint(l3);

    cout << "The sum of l1 and l2: ";
    Node* l4 = listSum(l1, l2);
    listPrint(l4);

    cout << "The sum of l1 and l3: ";
    Node* l5 = listSum(l1, l3);
    listPrint(l5);

    cout << "The sum of l3 and l1: ";
    Node* l6 = listSum(l3, l1);
    listPrint(l6);

    listClear(l1);
    listClear(l2);
    listClear(l3);
    listClear(l4);
    listClear(l5);
    listClear(l6);


    
    // Task 2:
    TNode a{1}, b{2}, c{4}, d{8, &a, &b}, e{16, &c}, f{32, &d, &e};
    cout << treeMax(&f) << endl;
    try {cout << vector<int>(1,1).at(3) << endl;}
//    try {cout << treeMax(nullptr) << endl;}
    catch (const exception ex){
        cerr << ex.what() << " is empty" << endl;
    }
    

    
    // Task 3:
    cout << "\n==============\n"
	 << "#3) Testing palindrome\n";
    cout << boolalpha
	 << "palindrome(\"racecar\", 7): " << palindrome("racecar", 7) << endl
	 << "palindrome(\"noon\", 4): " << palindrome("noon", 4) << endl
	 << "palindrome(\"raceXar\", 7): " << palindrome("raceXar", 7) << endl
    << "palindrome(\"noXn\", 4): " << palindrome("noXn", 4) << endl;
    
    // Task 4:
    cout << "\n==============\n"
	 << "#4) Are there an even number of 1's in binary representation?\n";
    cout << boolalpha;
    for (int i = 0; i < 10; ++i) {
        cout << i << ": " << parity(i) << endl;
    }


    
    // Task 5:
    cout << "\n==============\n"
	 << "#5) How many moves are required for various sized towers?";
    for (int i = 1; i < 30; ++i) {
	cout << "towers(" << i << ", 'a', 'b', 'c'): "
	     << towers(i, 'a', 'b', 'c') << endl;
    }
    
    
    mystery(5);
    
}


//
// The provided utility functions:
//

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr) {
    const Node* curr = headPtr;
    while (curr != nullptr) {
        cout << curr->data << ' ';
        curr = curr->next;
    }
    cout << endl;
}

// listClear frees up all of the nodes in list setting the the head
// pointer to null.
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// listBuild returns a list with the same values as in the vector.
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
	result = new Node{vals[index-1], result};
    }
    return result;
}
