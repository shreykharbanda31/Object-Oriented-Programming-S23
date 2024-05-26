//
//  main.cpp
//  rec12
//
//  Created by Shrey Kharbanda on 4/21/23.
//

#include <cstdlib>
#include <iostream>
using namespace std;

// Iterator that is not const should only be Iterator it and not const Iterator& it in parameters - TA

class List {
    friend ostream& operator<<(ostream& os, const List& ls){
        Node* head = ls.header -> next;
        while (head != ls.trailer){
            os << head -> data << " ";
            head = head -> next;
        }
        return os;
    };
private:
    size_t listsize;
    struct Node{
        Node(int data = 0, Node* prior = nullptr, Node* next = nullptr) : data(data), prior(prior), next(next){};
        int data;
        Node* prior;
        Node* next;
    };
    Node* header;
    Node* trailer;
public:
    
    class Iterator{
        friend class List;
        friend bool operator==(const Iterator& lhs, const Iterator& rhs){
            return (lhs.ptr == rhs.ptr);
        };
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs){
            return !(lhs == rhs);
        };
    public:
        Iterator(Node* ptr = nullptr): ptr(ptr){};

        Iterator& operator++(){
            ptr = ptr -> next;
            return *this;
        }
        Iterator& operator--(){
            ptr = ptr -> prior;
            return *this;
        }
        int& operator*() const {
            return ptr -> data;
        }
    private:
        Node* ptr;
    };

    List(): listsize(0), header(new Node()), trailer(new Node()){
        header -> next = trailer;
        trailer -> prior = header;
    };
    
    List(const List& ls) : listsize(ls.listsize), header(new Node()), trailer(new Node()) {
        Node* copycurr = ls.header -> next;
        Node* curr = header;
        while (copycurr != ls.trailer){
            curr -> next = new Node(copycurr->data, curr);
            curr = curr -> next;
            copycurr = copycurr -> next;
        };
        curr -> next = trailer;
        trailer -> prior = curr;
    };
    
    ~List(){
        cout << "~List()" << endl;
        Node* curr = header -> next;
        delete header;
        header = nullptr;
        while (curr != trailer){
            Node* after = curr -> next;
            delete curr;
            curr = after;
        };
        delete trailer;
        trailer = nullptr;
        listsize = 0;
    };
    
    List& operator=(const List& ls){
        cout << "List::op=(List)" << endl;
        if (this != &ls){
            Node* curr = header -> next;
            delete header;
            header = nullptr;
            while (curr != trailer){
                Node* after = curr -> next;
                delete curr;
                curr = after;
            };
            delete trailer;
            trailer = nullptr;
            listsize = 0;
            
            listsize = ls.listsize;
            header = new Node();
            trailer = new Node();
            Node* copycurr = ls.header -> next;
            Node* currr = header;
            while (copycurr != ls.trailer){
                currr -> next = new Node(copycurr->data, currr);
                currr = currr -> next;
                copycurr = copycurr -> next;
            };
            currr -> next = trailer;
            trailer -> prior = currr;
        }
        return *this;
    }
    void push_back(int num){
        Node* before = trailer -> prior;
        Node* newnode = new Node(num, before, trailer);
        trailer -> prior = newnode;
        before -> next = newnode;
        ++listsize;
    };
    
    Iterator insert(Iterator it, int num){
        Node* prev = it.ptr -> prior;
        Node* newnode = new Node(num, prev, it.ptr);
        prev -> next = newnode;
        it.ptr -> prior = newnode;
        listsize ++;
        Iterator ite(newnode);
        return ite;
    };
    
    Iterator begin(){
        return Iterator(header->next);
    }
    Iterator end(){
        return Iterator(trailer);
    }
    void pop_back(){
        if (listsize == 0){
            cout << "List is empty" << endl;
        }
        else{
            Node* remove = trailer -> prior;
            Node* secondlast = remove -> prior;
            secondlast -> next = trailer;
            trailer -> prior = secondlast;
            delete remove;
            --listsize;
        }
    };
    int& front(){
            return header -> next -> data;
        };
    int front() const{
            return header -> next -> data;
        };
    int& back(){
            return trailer -> prior -> data;
    };
    int back() const{
            return trailer -> prior -> data;
    };
    size_t size() const {
        return listsize;
    };
    
    void push_front(int num){
        Node* after = header -> next;
        Node* newnode = new Node(num, header, after);
        header -> next = newnode;
        after -> prior = newnode;
        ++listsize;
    };
    
    void pop_front(){
        if (listsize == 0){
            cout << "List is empty" << endl;
        }
        else{
            Node* remove = header -> next;
            Node* nodeafterremove = remove -> next;
            nodeafterremove -> prior = header;
            header -> next = nodeafterremove;
            delete remove;
            --listsize;
        }
    };
    
    void clear(){
        if (listsize == 0){
            cout << "List is empty" << endl;
        }
        else{
            while(header -> next != trailer){
                pop_back();
            };
        }
    };
    
    int& operator[](size_t index) {
        Node* head = header -> next;
        for (size_t i = 0; i < index; ++i){
            head = head -> next;
        }
        return head -> data;
    };
    int operator[](size_t index) const {
        Node* head = header -> next;
        for (size_t i = 0; i < index; ++i){
            head = head -> next;
        }
        return head -> data;
    };
    Iterator erase(Iterator it) {
        Node* prev = it.ptr -> prior;
        Node* after = it.ptr -> next;
        prev -> next = after;
        after -> prior = prev;
        delete it.ptr;
        --listsize;
        return Iterator(after);
    };
    

};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList) {
//    theList.front() = 17;
//    theList.back() = 42;
//}

void changeFrontAndBack(List& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}

int main() {
    
    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";
    
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";
    
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
        // Task 4
        cout << "\n------Task Four------\n";
        cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
        for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
        cout << "Display elements with op[]\n";
        for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
        cout << endl;
        cout << "Add one to each element with op[]\n";
        for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
        cout << "And print it out again with op[]\n";
        for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
        cout << endl;
        cout << "Now calling a function, printListSlow, to do the same thing\n";
        printListSlow(myList);
        cout << "Finally, for this task, using the index operator to modify\n"
             << "the data in the third item in the list\n"
             << "and then using printListSlow to display it again\n";
        myList[2] = 42;
        printListSlow(myList);
    
        // Task 5
        cout << "\n------Task Five------\n";
        cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
        myList.clear();
        for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
        printListInfo(myList);
        cout << "Now display the elements in a ranged for\n";
        for (int x : myList) cout << x << ' ';
        cout << endl;
        cout << "And again using the iterator type directly:\n";
        // Note you can choose to nest the iterator class or not, your choice.
        //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        for (List::Iterator iter = myList.begin(); iter != myList.end(); ++iter) {
            cout << *iter << ' ';
        }
        cout << endl;
        cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
        cout << "\n------Task Six------\n";
        cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
        myList.clear();
        for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
        printListInfo(myList);
        cout << "Filling an empty list with insert at begin(): "
             << "i*i for i from 0 to 9\n";
        myList.clear();
        for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
        printListInfo(myList);
        // ***Need test for insert other than begin/end***
        cout << "===================\n";
        // Task 7
        cout << "\n------Task Seven------\n";
        cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
        myList.clear();
        for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
        cout << "Erasing the elements in the list, starting from the beginning\n";
        while (myList.size()) {
            printListInfo(myList);
            myList.erase(myList.begin());
        }
        // ***Need test for erase other than begin/end***
        cout << "===================\n";
    
    
    
        // Task 8
        cout << "\n------Task Eight------\n";
        cout << "Copy control\n";
        cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
        myList.clear();
        for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
        printListInfo(myList);
        cout << "Calling doNothing(myList)\n";
        doNothing(myList);
        cout << "Back from doNothing(myList)\n";
        printListInfo(myList);
    
        cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
        List listTwo;
        for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
        printListInfo(listTwo);
        cout << "listTwo = myList\n";
        listTwo = myList;
        cout << "myList: ";
        printListInfo(myList);
        cout << "listTwo: ";
        printListInfo(listTwo);
        cout << "===================\n";
    
};
