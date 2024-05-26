//
//  registrar.cpp
//  rec07
//
//  Created by Shrey Kharbanda on 3/10/23.
//
#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include "registrar.h"

namespace BrooklynPoly{
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
}
