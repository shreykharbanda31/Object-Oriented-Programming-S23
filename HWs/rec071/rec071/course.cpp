//
//  course.cpp
//  rec071
//
//  Created by Shrey Kharbanda on 3/10/23.
//



#include <iostream>
#include <string>
using namespace std;
#include "student.h"
#include "course.h"

namespace BrooklynPoly{

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
};

