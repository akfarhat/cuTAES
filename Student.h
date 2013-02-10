#ifndef STUDENT_H
#define STUDENT_H

#define ERROR 0
#define SUCCESS 1

#include <iostream>
using namespace std;

class Student {

// Student information: student number, first and last names, email address, major, year standing, CGPA, and major GPA
  public:
    Student(string = "0", string = "0", string = "0", string = "0", string = "0", int = -1, float = -1.0, float = -1.0);
    ~Student();
    void printStudent();
    const string getName();
    const string getStuNum();
    void saveStudent();
    int applyConfirmed(string, string, string = "none", string = "none",
           string = "none");   // They confirm a submission of an application

  private:
    string studentNumber;
    string firstName;
    string lastName;
    string email;
    string major;
    int yearStanding;
    float CGPA;
    float MGPA;
};

#endif 
