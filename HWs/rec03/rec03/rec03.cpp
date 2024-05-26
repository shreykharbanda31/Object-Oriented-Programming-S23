/*
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Task 1
// Define an Account struct
struct Account{
    string name;
    int acc_number;
};

// Task 2
// Define an Account class (use a different name than in Task 1)
class Account_C{
    friend ostream& operator<< (ostream& os, const Account_C& rhs);
    public:
    Account_C(const string& the_name, const int& anumber) : name(the_name), acc_number(anumber) {};
    Account_C() {};
    // const string& get_name() const {return name;};
    // int get_number() const {return acc_number;};
    void display() const{
        cout << "The account name is " << name << " and the account number is: "<< acc_number << endl;
    };
    
    private:
        string name;
        int acc_number;
};
    ostream& operator<< (ostream& os, const Account_C& rhs){
        // os << "The account name is " << rhs.get_name() << " and the account number is: "<< rhs.get_number() << endl;
        os << "The account name is " << rhs.name << " and the account number is: "<< rhs.acc_number << endl;
        return os;
    };

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction{
    friend ostream& operator<< (ostream& os, const Transaction& rhs);
public:
    Transaction(const string& the_type, int the_amount) : trans_type(the_type), amount(the_amount) {};
    Transaction() {};
private:
    string trans_type;
    int amount;
};
class Account_T{
    friend ostream& operator<< (ostream& os, const Account_T& rhs);
public:
    Account_T(const string& the_name, const int& anumber) : name(the_name), acc_number(anumber), balance(0) {};
    Account_T() {};
    const string& get_name() const {return name;};
    int get_number() const {return acc_number;};
    void deposit(int amount) {
        history.push_back(Transaction("deposit", amount));
        balance = balance + amount;
    };
    void withdrawal(int amount) {
        //cout << "amount << endl;
        if (amount>balance){
            cout << "Account#" << acc_number << " has only "<< balance << ". " << "Insufficient for withdrawal of " << amount << endl;
        }
        else{
            history.push_back(Transaction("withdrawal", amount));
            balance = balance - amount;
            
        }
        
    };
private:
    string name;
    int acc_number;
    vector<Transaction> history;
    int balance;
};
ostream& operator<< (ostream& os, const Transaction& rhs){
    os << rhs.trans_type << " " << rhs.amount << endl;
    return os;
};
ostream& operator<< (ostream& os, const Account_T& rhs){
    os << rhs.name << " " << rhs.acc_number << ":" << endl;
    for (const Transaction& trans : rhs.history){
        os << trans;
    }
    return os;
};

// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)
class Account_Nest{
    friend ostream& operator<< (ostream& os, const Account_Nest& rhs);
public:
    class Transaction_Nest{
        friend ostream& operator<< (ostream& os, const Transaction_Nest& rhs);
    public:
        Transaction_Nest(const string& the_type, int the_amount) : trans_type(the_type), amount(the_amount) {};
        Transaction_Nest() {};
    private:
        string trans_type;
        int amount;
    };
    Account_Nest(const string& the_name, const int& anumber) : name(the_name), acc_number(anumber), balance(0) {};
    Account_Nest() {};
    const string& get_name() const {return name;};
    int get_number() const {return acc_number;};
    void deposit(int amount) {
        history.push_back(Transaction_Nest("deposit", amount));
        balance = balance + amount;
    };
    void withdrawal(int amount) {
        //cout << "amount << endl;
        if (amount>balance){
            cout << "Account#" << acc_number << " has only "<< balance << ". " << "Insufficient for withdrawal of " << amount << endl;
        }
        else{
            history.push_back(Transaction_Nest("withdrawal", amount));
            balance = balance - amount;
            
        }
        
    };
private:
    string name;
    int acc_number;
    vector<Transaction_Nest> history;
    int balance;
};
ostream& operator<< (ostream& os, const Account_Nest::Transaction_Nest& rhs){
    os << rhs.trans_type << " " << rhs.amount << endl;
    return os;
};
ostream& operator<< (ostream& os, const Account_Nest& rhs){
    os << rhs.name << " " << rhs.acc_number << ":" << endl;
    for (const Account_Nest::Transaction_Nest& trans : rhs.history){
        os << trans;
    }
    return os;
};
// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)


int main() {

    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    ifstream acc_data("accounts.txt");
    vector<Account> accounts;
    string name; int acc_num;
    while (acc_data >> name >> acc_num){
        Account acc;
        acc.name = name;
        acc.acc_number = acc_num;
        accounts.push_back(acc);
    }
    acc_data.close();
    for (Account acc: accounts){
        cout << "The account name is " << acc.name << " and the account number is: "<< acc.acc_number << endl;
    }
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    accounts.clear();
    acc_data.open("accounts.txt");
    while (acc_data >> name >> acc_num){
        Account acc{name, acc_num};
        accounts.push_back(acc);
    }
    acc_data.close();
    for (const Account& acc: accounts){
        cout << "The account name is " << acc.name << " and the account number is: "<< acc.acc_number << endl;
    }

    //==================================
    // Task 2: account as class

    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    vector<Account_C> accounts_v;
    acc_data.open("accounts.txt");
    while (acc_data >> name >> acc_num){
        Account_C acc(name,acc_num);
        accounts_v.push_back(acc);
    }
    acc_data.close();
    for (const Account_C& acc: accounts_v){
        acc.display();
    }

    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    accounts_v.clear();
    acc_data.open("accounts.txt");
    while (acc_data >> name >> acc_num){
        Account_C acc(name,acc_num);
        accounts_v.push_back(acc);
    }
    acc_data.close();
    for (const Account_C& acc: accounts_v){
        cout << acc;
    }

    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    accounts_v.clear();
    acc_data.open("accounts.txt");
    while (acc_data >> name >> acc_num){
        Account_C acc(name,acc_num);
        accounts_v.push_back(acc);
    }
    acc_data.close();
    for (const Account_C& acc: accounts_v){
        cout << acc;
    }

    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    accounts_v.clear();
    acc_data.open("accounts.txt");
    while (acc_data >> name >> acc_num){
        accounts_v.push_back(Account_C(name,acc_num));
    }
    acc_data.close();
    for (const Account_C& acc: accounts_v){
        cout << acc;
    }
    
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    accounts_v.clear();
    acc_data.open("accounts.txt");
    while (acc_data >> name >> acc_num){
        accounts_v.emplace_back(name, acc_num);
    }
    acc_data.close();
    for (const Account_C& acc: accounts_v){
        cout << acc;
    }
    
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    ifstream trans("transactions.txt");
    vector<Account_T> trans_accs;
    string input;
    int num;
    while (trans >> input){
        if (input == "Account"){
            trans >> input >> num;
            trans_accs.push_back(Account_T(input, num));
        }
        else if (input == "Deposit"){
            int acc_num, depo_num;
            trans >> acc_num >> depo_num;
            for (Account_T& acc: trans_accs){
                if (acc.get_number() == acc_num){
                    acc.deposit(depo_num);
                    break;
                }
            }
        }
        else if (input == "Withdraw"){
            int acc_num, with_num;
            trans >> acc_num >> with_num;
            for (Account_T& acc: trans_accs){
                if (acc.get_number() == acc_num){
                    acc.withdrawal(with_num);
                    break;
                }
            }
        }
    }
    trans.close();
    for (const Account_T& acc: trans_accs){
        cout << acc;
    }

    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    trans.open("transactions.txt");
    trans_accs.clear();
    while (trans >> input){
        if (input == "Account"){
            trans >> input >> num;
            trans_accs.push_back(Account_T(input, num));
        }
        else if (input == "Deposit"){
            int acc_num, depo_num;
            trans >> acc_num >> depo_num;
            for (Account_T& acc: trans_accs){
                if (acc.get_number() == acc_num){
                    acc.deposit(depo_num);
                    break;
                }
            }
        }
        else if (input == "Withdraw"){
            int acc_num, with_num;
            trans >> acc_num >> with_num;
            for (Account_T& acc: trans_accs){
                if (acc.get_number() == acc_num){
                    acc.withdrawal(with_num);
                    break;
                }
            }
        }
    }
    trans.close();
    for (const Account_T& acc: trans_accs){
        cout << acc;
    }
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";

    
}
