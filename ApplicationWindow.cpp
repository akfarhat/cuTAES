#include "ApplicationWindow.h"

using namespace std;

ApplicationWindow::ApplicationWindow()
  : mainContainer    (false, 10),
    menuContainer    (false, 10),
    welcomeContainer (false, 10),
    newAppContainer1 (false, 10),
    newAppContainer2 (false, 10)
{
  set_title("cuTAES - by Abdul-Karim Farhat and Andrew Belu");
  set_default_size(500,500);
  set_border_width(10);

  createMenu        (menuContainer);
  createWelcomePage (welcomeContainer);
  createNewAppForm1 (newAppContainer1);
  createNewAppForm2 (newAppContainer2);

  mainContainer.pack_start(menuContainer,false,false);
  menuContainer.show();

  mainContainer.pack_start(welcomeContainer,false,false);
  welcomeContainer.show();

  add(mainContainer);

  show_all_children();

}

ApplicationWindow::~ApplicationWindow()
{

}

void ApplicationWindow::createMenu(Gtk::VBox& containerBox)
{
  menuActionGroup = Gtk::ActionGroup::create();

  //File Menu
  menuActionGroup->add( Gtk::Action::create("MenuFile", "_File") );
  menuActionGroup->add( Gtk::Action::create("New", "Create Application"),
    sigc::mem_fun(*this, &ApplicationWindow::onActionFileNew) );
  menuActionGroup->add( Gtk::Action::create("Quit", Gtk::Stock::QUIT),
    sigc::mem_fun(*this, &ApplicationWindow::onActionFileQuit) );
  
  refUIManager = Gtk::UIManager::create();

  refUIManager->insert_action_group(menuActionGroup);
  add_accel_group(refUIManager->get_accel_group());

  Glib::ustring uiInfo =
    "<ui>"
    "  <menubar name='MenuBar'>"
    "    <menu action='MenuFile'>"
    "      <menuitem action='New'/>"
    "      <separator/>"
    "      <menuitem action='Quit'/>"
    "    </menu>"
    "  </menubar>"
    "</ui>";

  refUIManager->add_ui_from_string(uiInfo);

  Gtk::Widget* menuBar = refUIManager->get_widget("/MenuBar");

  if(menuBar) {
    containerBox.pack_start(*menuBar, Gtk::PACK_SHRINK);
  }
}

void ApplicationWindow::createWelcomePage(Gtk::VBox& containerBox)
{
  welcomeLabel.set_markup(
    "<span size='x-large'> Welcome to <i>cuTAES</i>\n </span>"
    "<span size='large'> The Carleton University TA Application and"
                       " Evaluation System\n</span>"
    "<span size ='large'>\n\nSelect an option from the File menu</span>");
  welcomeLabel.set_justify(Gtk::JUSTIFY_CENTER);
  containerBox.pack_start(welcomeLabel, false, false);
  welcomeLabel.show();
}

void ApplicationWindow::createNewAppForm1(Gtk::VBox& containerBox)
{
  newAppLabel.set_markup(
    "<span size='xx-large' font-weight='bold'> New Application </span>");
  newAppLabel.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
  containerBox.pack_start(newAppLabel, false, false);
  newAppLabel.show();

  termLabel.set_markup("<span size='large'> Select a Term: </span>");
  termLabel.set_padding(10,10);
  termLabel.set_alignment(0, 0);
  containerBox.pack_start(termLabel, false, false);
  termLabel.show();

  termCombo.append("Winter 2013");
  containerBox.pack_start(termCombo, false, false);
  termCombo.show();

  courseLabel.set_markup("<span size='large'> Select a Course: </span>");
  courseLabel.set_padding(10,10);
  courseLabel.set_alignment(0, 0);
  containerBox.pack_start(courseLabel, false, false);
  courseLabel.show();

  getCourses();
  containerBox.pack_start(courseCombo, false, false);
  courseCombo.show();

  buttonContainer.set_layout(Gtk::BUTTONBOX_END);
  buttonContainer.set_spacing(10);
  containerBox.pack_end(buttonContainer, false, false);
  buttonContainer.show();

  cancelButton.set_label("Cancel");
  cancelButton.signal_clicked().connect(
    sigc::mem_fun(*this, &ApplicationWindow::onCancelButtonClicked) );
  buttonContainer.add(cancelButton); 
  cancelButton.show();

  nextButton.set_label("Next");
  nextButton.signal_clicked().connect(
    sigc::mem_fun(*this, &ApplicationWindow::onNextButtonClicked) );
  buttonContainer.add(nextButton); 
  nextButton.show();
}

void ApplicationWindow::createNewAppForm2(Gtk::VBox& containerBox)
{
  newAppLabel2.set_markup(
    "<span size='xx-large' font-weight='bold'> New Application </span>");
  newAppLabel2.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_START);
  containerBox.pack_start(newAppLabel2, false, false);
  newAppLabel2.show();

  selectedTermLabel.set_markup("<span size='large'> Term: "
                               + selectedTerm + "</span>");
  selectedTermLabel.set_padding(10,10);
  selectedTermLabel.set_alignment(0, 0);
  containerBox.pack_start(selectedTermLabel, false, false);
  selectedTermLabel.show();

  selectedCourseLabel.set_markup("<span size='large'> Course: "
                                 + selectedCourse + "</span>");
  selectedCourseLabel.set_padding(10,10);
  selectedCourseLabel.set_alignment(0, 0);
  containerBox.pack_start(selectedCourseLabel, false, false);
  selectedCourseLabel.show();

  generalInfoLabel.set_markup("<span size='large'>General Information</span>");
  generalInfoLabel.set_padding(10,10);
  generalInfoLabel.set_alignment(0,0);
  containerBox.pack_start(generalInfoLabel, false, false);
  generalInfoLabel.show();

  stuNumLabel.set_markup("<span>Student Number:</span>");
  stuNumLabel.set_padding(5,5);
  stuNumLabel.set_alignment(0,0);
  containerBox.pack_start(stuNumLabel, false, false);
  stuNumLabel.show();

  stuNumEntry.set_max_length(STU_NUM_LENGTH);
  containerBox.pack_start(stuNumEntry);
  stuNumEntry.show();

  firstNameLabel.set_markup("<span>First Name:</span>");
  firstNameLabel.set_padding(5,5);
  firstNameLabel.set_alignment(0,0);
  containerBox.pack_start(firstNameLabel, false, false);
  firstNameLabel.show();

  containerBox.pack_start(firstNameEntry);
  firstNameEntry.show();

  lastNameLabel.set_markup("<span>Last Name:</span>");
  lastNameLabel.set_padding(5,5);
  lastNameLabel.set_alignment(0,0);
  containerBox.pack_start(lastNameLabel, false, false);
  lastNameLabel.show();

  containerBox.pack_start(lastNameEntry);
  lastNameEntry.show();

  emailLabel.set_markup("<span>Email:</span>");
  emailLabel.set_padding(5,5);
  emailLabel.set_alignment(0,0);
  containerBox.pack_start(emailLabel, false, false);
  emailLabel.show();

  emailEntry.set_text("...carleton.ca");
  containerBox.pack_start(emailEntry);
  emailEntry.show();

  majorLabel.set_markup("<span>Major:</span>");
  majorLabel.set_padding(5,5);
  majorLabel.set_alignment(0,0);
  containerBox.pack_start(majorLabel, false, false);
  majorLabel.show();

  containerBox.pack_start(majorEntry);
  majorEntry.show();

  standingLabel.set_markup("<span>Year Standing:</span>");
  standingLabel.set_padding(5,5);
  standingLabel.set_alignment(0,0);
  containerBox.pack_start(standingLabel, false, false);
  standingLabel.show();

  containerBox.pack_start(standingEntry);
  standingEntry.show();

  cgpaLabel.set_markup("<span>CGPA:</span>");
  cgpaLabel.set_padding(5,5);
  cgpaLabel.set_alignment(0,0);
  containerBox.pack_start(cgpaLabel, false, false);
  cgpaLabel.show();

  containerBox.pack_start(cgpaEntry);
  cgpaEntry.show();

  mcgpaLabel.set_markup("<span>Major CGPA:</span>");
  mcgpaLabel.set_padding(10,10);
  mcgpaLabel.set_alignment(0,0);
  containerBox.pack_start(mcgpaLabel, false, false);
  mcgpaLabel.show();

  containerBox.pack_start(mcgpaEntry);
  mcgpaEntry.show();

  buttonContainer2.set_layout(Gtk::BUTTONBOX_END);
  buttonContainer2.set_spacing(10);
  containerBox.pack_end(buttonContainer2, false, false);
  buttonContainer2.show();

  cancelButton2.set_label("Cancel");
  cancelButton2.signal_clicked().connect(
    sigc::mem_fun(*this, &ApplicationWindow::onCancelButtonClicked) );
  buttonContainer2.add(cancelButton2); 
  cancelButton2.show();

  submitButton.set_label("Submit");
  submitButton.signal_clicked().connect(
    sigc::mem_fun(*this, &ApplicationWindow::onSubmitButtonClicked) );
  buttonContainer2.add(submitButton); 
  submitButton.show();

}

void ApplicationWindow::onActionFileNew()
{
  cout << "File->New clicked" << endl;

  displayNewAppForm1();  
}

void ApplicationWindow::displayWelcomePage()
{
  //This produces an assertion failure but it's not a problem
  mainContainer.remove(newAppContainer1);
  mainContainer.remove(newAppContainer2);

  mainContainer.pack_start(welcomeContainer);

  mainContainer.show_all();
}

void ApplicationWindow::displayNewAppForm1()
{
  mainContainer.remove(welcomeContainer);
  
  mainContainer.pack_start(newAppContainer1);

  mainContainer.show_all();
}

void ApplicationWindow::displayNewAppForm2()
{
  mainContainer.remove(newAppContainer1);

  selectedTermLabel.set_markup("<span size='large'> Term: "
                               + selectedTerm + "</span>");

  selectedCourseLabel.set_markup("<span size='large'> Course:"
                                 + selectedCourse + "</span>");

  mainContainer.pack_start(newAppContainer2);

  mainContainer.show_all();
}

void ApplicationWindow::getCourses()
{
  ifstream courseFile(COURSE_FILE,ios::in);
  string course;

  if(!courseFile) {
    Gtk::MessageDialog noCoursesDialog(*this, "Course File Not Found",
      false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    
    noCoursesDialog.set_secondary_text("A file called " COURSE_FILE 
      " must be provided in the local directory with a list of course codes.");

    noCoursesDialog.run();

  }
  else {
    while( !courseFile.eof() ) {
      getline(courseFile, course);
      courseCombo.append(course); 
    }
  }
}

void ApplicationWindow::clearEntries()
{
  stuNumEntry.set_text("");
  firstNameEntry.set_text("");
  lastNameEntry.set_text("");
  emailEntry.set_text("... carleton.ca");
  majorEntry.set_text("");
  standingEntry.set_text("");
  cgpaEntry.set_text("");
  mcgpaEntry.set_text("");
}

void ApplicationWindow::onActionFileQuit()
{
  cout << "File->Quit clicked" << endl;

  hide();
}

void ApplicationWindow::onNextButtonClicked()
{
  cout << "Next button clicked" << endl;

  if( validateFields1() ) {
    selectedTerm   = termCombo.get_active_text();
    selectedCourse = courseCombo.get_active_text(); 

    displayNewAppForm2();
  }

}

bool ApplicationWindow::validateFields1()
{
  bool valid = true;

  string termText =   termCombo.get_active_text();
  string courseText = courseCombo.get_active_text();

  if(termText.empty()){
    valid = false;
  }
  else if(courseText.empty()) {
    valid = false;
  }
  else {
    valid = true;
  }

  if(!valid) {
    Gtk::MessageDialog invalidDialog(*this, "Invalid Selections",
      false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    
    invalidDialog.set_secondary_text("You must choose a term and course.");

    invalidDialog.run();

    return false;
  }

  return true;
}

bool ApplicationWindow::validateFields2()
{
  bool valid = true;

  if(stuNumEntry.get_text().empty()) {
    valid = false;
  }
  else if(firstNameEntry.get_text().empty()) {
    valid = false;
  }
  else if(lastNameEntry.get_text().empty()) {
    valid = false;
  }
  else if(emailEntry.get_text().empty()) {
    valid = false;
  }
  else if(majorEntry.get_text().empty()) {
    valid = false;
  }
  else if(standingEntry.get_text().empty()) {
    valid = false;
  }
  else if(cgpaEntry.get_text().empty()) {
    valid = false;
  }
  else if(mcgpaEntry.get_text().empty()) {
    valid = false;
  }

  if(!valid) {
    Gtk::MessageDialog invalidDialog2(*this, "Invalid Selections",
      false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    
    invalidDialog2.set_secondary_text("You must fill in all fields.");

    invalidDialog2.run();

    return false;
  }

  return true;
}

void ApplicationWindow::onSubmitButtonClicked()
{
  cout << "Submit button clicked" << endl;

  int standing;
  float cgpa;
  float mcgpa;

  istringstream ( standingEntry.get_text() ) >> standing;
  istringstream ( cgpaEntry.get_text() ) >> cgpa;
  istringstream ( mcgpaEntry.get_text() ) >> mcgpa; 

  if( validateFields2() ) {
    Student newTA( stuNumEntry.get_text(),
                   firstNameEntry.get_text(),
                   lastNameEntry.get_text(),
                   emailEntry.get_text(),
                   majorEntry.get_text(),
                   standing,
                   cgpa,
                   mcgpa );

    newTA.applyConfirmed(selectedTerm, selectedCourse);

    Gtk::MessageDialog successDialog(*this,"Application Successfully Submitted",
      false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);

    successDialog.run();

    clearEntries();

    displayWelcomePage(); 
  }
}

void ApplicationWindow::onCancelButtonClicked()
{
  cout << "Cancel button clicked" << endl;

  clearEntries();

  displayWelcomePage();
}
