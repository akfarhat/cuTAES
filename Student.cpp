#include <iostream>
using namespace std;

#include "Student.h"
#include "Application.h"

#include <fstream>

// Constructor (will change to constructor initializer syntax if needed)
Student::Student(string stu, string fn, string ln, string em, string maj, int year, float CG, float MG) {
  studentNumber 	= stu;
  firstName 		= fn;
  lastName 		= ln;
  email 		= em;
  major 		= maj;
  yearStanding 		= year;
  CGPA 			= CG;
  MGPA 			= MG;

  cout << "Student constructor called" << endl;
}

// Destructor
Student::~Student() {
}

// Getters
const string Student::getName(){
  return firstName + " " + lastName;
}

const string Student::getStuNum(){
  return studentNumber;
}

// Prints the student's information
void Student::printStudent(){
  cout << "Student: " << firstName << " " << lastName << endl;
  cout << "Student number: " << studentNumber << endl;
  cout << "Student email: " << email << endl;
  cout << "Student major: " << major << endl;
  cout << "Student in year: " << yearStanding << " with CGPA: " << CGPA << " and major GPA: " << MGPA << endl << endl; 
}

// Saves the student's information to a file
void Student::saveStudent() {
  ofstream outFile("students.txt", ios::app);

  string delimiter = "\n";                       
  outFile << studentNumber << delimiter << firstName << delimiter;
  outFile << lastName << delimiter << email << delimiter;
  outFile << major << delimiter << yearStanding << delimiter;
  outFile << CGPA << delimiter << MGPA << delimiter;  

  outFile.close();

}

// Create an application if the user submits one
// Parameters are: the student,the term, the course, the related courses, the work experience and the references
// Returns value from saveApplication, ERROR or SUCCESS
int Student::applyConfirmed(string t, string c, string rc, string we, string r){                   
  saveStudent();

  Application newApp(this, t, c, rc, we, r);
  return newApp.saveApplication();
}


