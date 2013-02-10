#ifndef APP_H
#define APP_H

#include "Student.h"

#include <iostream>
using namespace std;

class Application {

  friend class Student;
  
  public:
    // Applicant, application number, term, course, related courses, work experience, references
    Application(Student* = NULL, string = "0", string = "0", string = "0", string = "0", string = "0");
    ~Application();
    const void printApplication();
    int saveApplication();

  private:
    int nextAppNumber;
    int applicationNumber; 
    Student* applicant;
    string term;
    string course;
    string relatedCourses;
    string workExperience;
    string references;
    string status;
};

#endif
