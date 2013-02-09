#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include "Application.h"

// Constructor
Application::Application(Student* stu, string t, string c, string rc, string we, string r) {

  ifstream inFile("appNumber.txt", ios::in);

  if(!inFile) {
    nextAppNumber = 1;
  }
  else {
    inFile >> nextAppNumber;    
  }

  inFile.close();

  applicant		= stu;                        // applicant is a pointer
  applicationNumber 	= nextAppNumber++;
  term                  = t;
  course 		= c;
  relatedCourses 	= rc;
  workExperience 	= we;
  references 		= r;
  status 		= "pending";


  ofstream outFile("appNumber.txt", ios::out);

  if(outFile) {
    outFile << nextAppNumber;
  }
  else {
    cout << "Can't open appNumber.txt for writing" << endl;
  }

  cout << "Application constructor called" << endl;
}

// Destructor
Application::~Application() {
}

const void Application::printApplication() {
  if (applicant == NULL){
    return;
  }
  cout << "Application for: " << applicant->getName() << endl;     
  cout << "Course: " << course << endl;
  cout << "Application #" << applicationNumber << endl << endl;
}

// Saves an application to a file
// Returns either ERROR or SUCCESS (preprocessor definitions)
int Application::saveApplication() {
  ofstream outFile("applications.txt", ios::app);

  if (!outFile){
    return ERROR;                 
  }

  //output the values to a file, delimited by newlines

  string delimiter = "\n";                                                        outFile << applicationNumber << delimiter << term << delimiter;
  outFile << course << delimiter;
  outFile << relatedCourses << delimiter << workExperience << delimiter;        
  outFile << references << delimiter << applicant->getStuNum() << delimiter;      outFile << status << delimiter;

  outFile.close();

  return SUCCESS;                                                  // Success is a preprocessor definition. Value is 1
}
