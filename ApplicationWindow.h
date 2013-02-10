#ifndef APPLICATION_WINDOW_H
#define APPLICATION_WINDOW_H

#define COURSE_FILE "courses.txt"
#define COURSE_BUF 9               //Course code has 9 characters
#define STU_NUM_LENGTH 9           //Student number has 9 digits
#define LABEL_WIDTH 14

#include "Student.h"
#include "Application.h"

#include <gtkmm.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class ApplicationWindow : public Gtk::Window
{

public:
  ApplicationWindow();
  virtual ~ApplicationWindow();

protected:
  /**** Helper Functions ****/

  void createMenu        (Gtk::VBox &);
  void createWelcomePage (Gtk::VBox &);
  void createNewAppForm1 (Gtk::VBox &);
  void createNewAppForm2 (Gtk::VBox &);

  void displayWelcomePage();
  void displayNewAppForm1();
  void displayNewAppForm2();

  void getCourses();

  bool validateFields1();
  bool validateFields2();

  void clearEntries();

  /**** Signal Handlers ****/

  void onActionFileNew();
  void onActionFileQuit();
  
  void onNextButtonClicked();
  void onCancelButtonClicked();

  void onSubmitButtonClicked();

  /**** Member widgets ****/

  //Containers
  Gtk::VBox mainContainer;
  Gtk::VBox menuContainer;
  Gtk::VBox welcomeContainer;
  Gtk::VBox newAppContainer1;
  Gtk::VBox newAppContainer2;

  //Menu
  Glib::RefPtr<Gtk::ActionGroup> menuActionGroup;
  Glib::RefPtr<Gtk::UIManager> refUIManager;

  //Welcome Page
  Gtk::Label welcomeLabel;

  //New Application Page
  Gtk::Label newAppLabel;
  Gtk::Label termLabel;
  Gtk::Label courseLabel;

  Gtk::HBox labelBox;

  Gtk::ComboBoxText termCombo;
  Gtk::ComboBoxText courseCombo;

  Gtk::HButtonBox buttonContainer;
  Gtk::Button nextButton;
  Gtk::Button cancelButton;

  Gtk::Label newAppLabel2;

  Glib::ustring selectedTerm;
  Glib::ustring selectedCourse;

  Gtk::Label generalInfoLabel;
  Gtk::Label selectedTermLabel;
  Gtk::Label selectedCourseLabel;

  Gtk::HBox stuNumBox;
  Gtk::HBox firstNameBox;
  Gtk::HBox lastNameBox;
  Gtk::HBox emailBox;
  Gtk::HBox majorBox;
  Gtk::HBox standingBox;
  Gtk::HBox cgpaBox;
  Gtk::HBox mcgpaBox;

  Gtk::Label stuNumLabel;
  Gtk::Label firstNameLabel;
  Gtk::Label lastNameLabel;
  Gtk::Label emailLabel;
  Gtk::Label majorLabel;
  Gtk::Label standingLabel;
  Gtk::Label cgpaLabel;
  Gtk::Label mcgpaLabel;

  Gtk::Entry stuNumEntry;
  Gtk::Entry firstNameEntry;
  Gtk::Entry lastNameEntry;
  Gtk::Entry emailEntry;
  Gtk::Entry majorEntry;
  Gtk::Entry standingEntry;
  Gtk::Entry cgpaEntry;
  Gtk::Entry mcgpaEntry;

  Gtk::HButtonBox buttonContainer2;
  Gtk::Button submitButton;
  Gtk::Button cancelButton2;
};

#endif
