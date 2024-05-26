/*
  rec07_single.cpp
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};

// defining Course methods
Course::Course(const string& courseName): name(courseName){};
const string& Course::getName() const{
    return name;
}
bool Course::addStudent(Student* stu){
    for (size_t index=0; index<students.size();++index){
        if (students[index]==stu){
            cout << "Student already exists!" << endl;
            return false;
        }
    }
    students.push_back(stu);
    return true;
};
void Course::removeStudentsFromCourse(){
    for (size_t index=0; index<students.size();++index){
        students[index]->removedFromCourse(this);
    }
    students.clear();
};

// defining Student methods
Student::Student(const string& name): name(name){};
const string& Student::getName() const{
    return name;
};
bool Student::addCourse(Course* course){
    for (size_t index=0; index<courses.size();++index){
        if (courses[index]==course){
            cout << "Student already registered for this course!" << endl;
            return false;
        }
    }
    courses.push_back(course);
    return true;
};
void Student::removedFromCourse(Course* course){
    for (size_t index=0; index<courses.size();++index){
        if (courses[index]==course){
            courses[index]=courses[courses.size()-1];
            courses.pop_back();
            break;
        }
    }
};

Registrar::Registrar(){};

bool Registrar::addCourse(const string& course){
    if (findCourse(course)!=courses.size()){
        cout << "Student already registered for this course!" << endl;
        return false;
    };
    courses.push_back(new Course(course));
    return true;
};
bool Registrar::addStudent(const string& student){
    if (findStudent(student)!=students.size()){
        cout << "Student already exists!" << endl;
        return false;
    };
    students.push_back(new Student(student));
    return true;
};
bool Registrar::enrollStudentInCourse(const string& studentName,
                           const string& courseName){
    return
    (findStudent(studentName)!=students.size()) && students[findStudent(studentName)]->addCourse(courses[findCourse(courseName)]) && courses[findCourse(courseName)]->addStudent(students[findStudent(studentName)]);
    
};
bool Registrar::cancelCourse(const string& courseName){
    if (findCourse(courseName)!=courses.size()){
        size_t index = findCourse(courseName);
        delete courses[index];
        courses[index] = nullptr;
        courses[index] = courses[courses.size()-1];
        courses.pop_back();
        return true;
    }
    return false;
};
void Registrar::purge(){
    for (size_t index=0; index<students.size();++index){
        delete students[index];
        students[index]=nullptr;
    }
    students.clear();
    for (size_t index=0; index<courses.size();++index){
    delete courses[index];
    courses[index]=nullptr;
    }
    courses.clear();
};
size_t Registrar::findStudent(const string& student) const{
    for (size_t index=0; index<students.size();++index){
        if (students[index]->getName()==student){
            return index;
        }
    }
    return students.size();
};
size_t Registrar::findCourse(const string& course) const{
    for (size_t index=0; index<courses.size();++index){
        if (courses[index]->getName()==course){
            return index;
        }
    }
    return courses.size();
};

ostream& operator<<(ostream& os, const Course& rhs){
    os << rhs.name << ": ";
    if (rhs.students.size()==0){
        os << "No Students";
        }
    else{
    for (size_t index=0; index<rhs.students.size();++index){
        os << (rhs.students[index])->getName() << " ";
        }
    }
    return os;
};

ostream& operator<<(ostream& os, const Student& rhs){
    os << rhs.name << ": ";
    if (rhs.courses.size()==0){
        os << "No Courses";
        }
    else{
    for (size_t index=0; index<rhs.courses.size();++index){
        os << (rhs.courses[index])->getName() << " ";
        }
    }
    return os;
};

ostream& operator<<(ostream& os, const Registrar& rhs){
    os << "Registrar's Report" << endl;
    os << "Courses:" << endl;
    for (size_t index=0; index<rhs.courses.size();++index){
        os << *rhs.courses[index] << endl;
        }
    os << "Students:" << endl;
    for (size_t index=0; index<rhs.students.size();++index){
        os << *rhs.students[index] << " ";
        }
    os << endl;
    return os;
};
int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
  
