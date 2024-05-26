//
//  student.cpp
//  rec071
//
//  Created by Shrey Kharbanda on 3/10/23.
//

#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include "course.h"
#include "student.h"

namespace BrooklynPoly {
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
};
