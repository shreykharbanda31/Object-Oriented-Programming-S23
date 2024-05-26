// rec13_start.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

class even{
public:
    bool operator()(int num) const { return num % 2 == 0; };
};

// Task 9
void print_list(const list<int>& lst){
    //list<int>::iterator index = lst.begin();
    list<int>::const_iterator index = lst.begin();
    while (index != lst.end()){
        cout << *index << ' ';
        ++index;
    }
    cout << endl;
}

// Task 10
void print_list2(const list<int>& lst){
    for(int k: lst){
        cout << k << ' ';
    }
    cout << endl;
}

// Task 11
void print_list_alt(const list<int>& lst){
    auto index = lst.begin();
    while (index != lst.end()){
        cout << *index << ' ';
        ++index;
    }
    cout << endl;
}

// Task 12
list<int>::const_iterator find_in_list(const list<int>& lst, int x){
    list<int>::const_iterator index = lst.begin();
    while (index != lst.end()){
        if (*index == x){
            return index;
        };
        ++index;
    }
    return lst.end();
}

// Task 13
auto find_in_list2(const list<int>& lst, int x){
    auto index = lst.begin();
    while (index != lst.end()){
        if (*index == x){
            return index;
        };
        ++index;
    }
    return lst.end();
}

// Task 14
list<int>::const_iterator find_in_list3(const list<int>& lst, int x){
    return find(lst.begin(), lst.end(), x);
}
// Task 15
bool is_even(int x){return x%2==0;};

//Task 19
list<int>::const_iterator OurFind(list<int>::const_iterator start, list<int>::const_iterator stop, int value){
    for(list<int>::const_iterator index = start; index != stop; ++index){
        if (*index == value){
            return index;
        }
    }
    return stop;
};

//Task 20
template <typename T, typename U>
T OurFind(T start, T stop, U value){
    cout << "in the template!" << endl;
    for(T index = start; index != stop; ++index){
        if (*index == value){
            return index;
        }
    }
    return stop;
};

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    
    vector<int> vec{1,4,2,6};
    for(int k: vec){
        cout << k << ' ';
    }

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    
    list<int> ls(vec.begin(),vec.end());
    for(int k: ls){
        cout << k << ' ';
    }

    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(),vec.end());
    for(int k: vec){
        cout << k << ' ';
    }
    cout << endl;
    for(int k: ls){
        cout << k << ' ';
    }
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t index = 0; index < vec.size(); index+=2){
        cout << vec[index] << ' ';
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t index = 0; index < ls.size(); index+=2){
//        cout << ls[index] << ' '    }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator index = vec.begin(); index != vec.end(); index++,index++){
        cout << *index << ' ';
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    list<int>::iterator index = ls.begin();
    while (index != ls.end()){
        cout << *index << ' ';
        ++index;
        ++index;
    }
    cout << "\n=======\n";
    
    // 8. Sorting a list
    cout << "Task 8:\n";
    ls.sort();
    for(int k: ls){
        cout << k << ' ';
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    print_list(ls);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    print_list2(ls);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    print_list_alt(ls);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::const_iterator k = find_in_list(ls,20);
    cout << *k << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    list<int>::const_iterator m = find_in_list2(ls,2);
    cout << *m << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    list<int>::const_iterator p = find_in_list3(ls,9);
    cout << *p << endl;
    p = find_in_list3(ls,2);
    cout << *p << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    // vec = {1,3};
    vector<int>::iterator o = find_if(vec.begin(), vec.end(), is_even);
    cout << *o << endl;
    list<int>::iterator ol = find_if(ls.begin(), ls.end(), is_even);
    if (ol == ls.end()) {
        cout << "not found" << endl;
    } else {
        cout << *ol << endl;
    }
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
   
    even ev;
    list<int>::iterator oll = find_if(ls.begin(), ls.end(), ev);
    cout << *oll << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    [] { cout << "Hello Lambda!"; }();
    cout << endl;
    [] (int a, int b) { cout << a + b << endl; } (4, 5);
        int result = [] (int a, int b) { return a + b; } (4, 5);
        cout << "the result is: " << result << endl;
    int result2 = [] (int a, int b) -> int { return a + b; } (4, 5);
    cout << "the result is: " << result2 << endl;
    
    list<int>::iterator olo = find_if(ls.begin(), ls.end(), [] (int num) {return num%2 == 0;});
    cout << *olo << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* arr = new int[vec.size()];
    copy(vec.begin(), vec.end(), arr);
    for(size_t index = 0; index < 4; ++index){
        cout << arr[index] << ' ';
    }
    cout << endl;
    int* pop = find(arr, arr+4, 2);
    cout << *pop << endl;
    delete[] arr;
    arr = nullptr;
    cout << "=======\n";
    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::iterator popo = OurFind(ls.begin(), ls.end(), 2);
    cout << *popo << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    vector<int>::iterator popt = OurFind(vec.begin(), vec.end(), 2);
    cout << *popt << endl;
    popo = OurFind(ls.begin(), ls.end(), 2);
    cout << *popo << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    vector<string> v;
    ifstream ifs("pooh-nopunc.txt");
    string word;
    while (ifs >> word){
        if(find(v.begin(),v.end(),word) == v.end()){
            v.push_back(word);
        };
    };
    ifs.close();
    cout << "Size: " << v.size() << endl;
    for (const string& sk: v){
        cout << sk << ' ';
    }

    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    set<string> s;
    ifstream iff("pooh-nopunc.txt");
    string wordd;
    while (iff >> wordd){
        s.insert(wordd);
        // returns a pair, where first is iterator and second is bool
    };
    iff.close();
    cout << "Size: " << s.size() << endl;
    for (const string& skk: s){
        cout << skk << ' ';
    }
    cout << endl;
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    map<string, vector<int>> wordMap;
    ifstream ifss("pooh-nopunc.txt");
    string wordl;
    int token=0;
    while (ifss >> wordl){
        wordMap[wordl].push_back(token);
        ++token;
    };
    ifss.close();
    cout << "Size: " << wordMap.size() << endl;
    for (const auto& pair: wordMap){
        cout << pair.first << ":";
        for(int k: pair.second){
            cout << k << ' ';
        }
        cout << endl;
    }
    cout << "=======\n";
}
