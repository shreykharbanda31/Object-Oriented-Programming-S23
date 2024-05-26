/*
  rec05-start.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// make pointers if something doesn't own something but is assigned something
// check for consts carefully
// friend output operators for the actual object, then the private of where you are calling it in
// and then make sure you write the actual thing outside
class Section{
private:
    // class
    class StudentRecord{
    private:
        string name;
        vector<int> grades;
    public:
        friend ostream& operator<< (ostream& os, const StudentRecord& rec);
        StudentRecord(const string& student): name(student),grades(14,-1){};
        const string& get_name() const{
            return name;
        };
        void change_grades(int grade, int week){
            grades[week-1]=grade;
        }
    };
    // class
    class TimeSlot{
    private:
        string day;
        unsigned start;
    public:
        friend ostream& operator<< (ostream& os, const TimeSlot& slot);
        TimeSlot(const string& dayname, unsigned starttime): day(dayname), start(starttime){};
        
    };
    // variables
    string secname;
    TimeSlot time;
    vector<StudentRecord*> records;
    //output operators
public:
    friend ostream& operator<< (ostream& os, const Section::TimeSlot& slot);
    friend ostream& operator<< (ostream& os, const Section::StudentRecord& rec);
    friend ostream& operator<< (ostream& os, const Section& sec);
    Section(const string& sectname, const string& day_name, unsigned timestart): secname(sectname), time(day_name,timestart){};
    
    // when copying just set it to parameters and not inside because it requires default constructors
    Section(const Section& sec) : secname(sec.secname), time(sec.time){
        for (size_t index=0; index < sec.records.size();++index){
            records.push_back(new StudentRecord(*sec.records[index]));
        };
    };
    
    ~Section(){
        cout << "Section " << secname << " is being deleted" << endl;
        reset();
    };

    void addStudent(const string& studentname){
        records.push_back(new StudentRecord(studentname));
    };
    void change_record(const string& name, int grade, int week){
        size_t cindex = 0;
        for (size_t index = 0; index<records.size(); ++index){
            if ((records[index])->get_name()==name){
                cindex = index;
                break;
            }
        }
        records[cindex]->change_grades(grade, week);
    }
    void reset(){
        // delete each heap memory, set to null, clear vector
        for (size_t index = 0; index<records.size(); ++index){
            cout << "Deleting" << records[index]->get_name() << endl;
            delete records[index];
            records[index] = nullptr;
            }
        records.clear();
    }
    
};

ostream& operator<< (ostream& os, const Section& sec){
    os << "Section: " << sec.secname << ", Time slot: " << sec.time << ", Students:\n";
    for (size_t index = 0; index < sec.records.size(); ++index){
        os << *(sec.records[index]) << endl;
    }
    return os;
};

ostream& operator<< (ostream& os, const Section::TimeSlot& slot){
    os << "[Day: " << slot.day << ", Start time: ";
    if (slot.start>=12){
        os << slot.start%12 << "pm]";
    }
    else{
        os << slot.start << "am]";
    }
    return os;
};
ostream& operator<< (ostream& os, const Section::StudentRecord& rec){
    os << "Name: " << rec.name << ", Grades: ";
    for (size_t index = 0; index < rec.grades.size(); ++index){
        os << rec.grades[index] << " ";
    }
    return os;
};

class LabWorker{
    friend ostream& operator<< (ostream& os, const LabWorker& worker);
private:
    string workername;
    Section* workersec;
public:
    LabWorker(const string& name): workername(name), workersec(nullptr){};
    void addSection(Section& sec){
        workersec = &sec;
    };
    void addGrade(const string& studentname, int grade, int week){
        workersec->change_record(studentname, grade, week);
    };
};

ostream& operator<< (ostream& os, const LabWorker& worker){
    os << worker.workername;
    if (worker.workersec){
        os << " has " << *worker.workersec;
    }
    else{
        os << " does not have a section";
    }
    return os;
};
// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
     secB3.addStudent("Thorin");
     secB3.addStudent("Dwalin");
     secB3.addStudent("Balin");
     secB3.addStudent("Kili");
     secB3.addStudent("Fili");
     secB3.addStudent("Dori");
     secB3.addStudent("Nori");
     secB3.addStudent("Ori");
     secB3.addStudent("Oin");
     secB3.addStudent("Gloin");
     secB3.addStudent("Bifur");
     secB3.addStudent("Bofur");
     secB3.addStudent("Bombur");
     jane.addSection( secB3 );
     cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
     moe.addGrade("John", 17, 1);
     moe.addGrade("Paul", 19, 1);
     moe.addGrade("George", 16, 1);
     moe.addGrade("Ringo", 7, 1);
     cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
     moe.addGrade("John", 15, 3);
     moe.addGrade("Paul", 20, 3);
     moe.addGrade("Ringo", 0, 3);
     moe.addGrade("George", 16, 3);
     cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
