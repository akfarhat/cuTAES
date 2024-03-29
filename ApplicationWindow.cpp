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
  newAppLabel2.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
  containerBox.pack_start(newAppLabel2, false, false);
  newAppLabel2.show();

  selectedTermLabel.set_markup("<span size='large'> Term:"
                               + selectedTerm + "</span>");
  selectedTermLabel.set_padding(10,10);
  selectedTermLabel.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
  selectedTermLabel.show();

  selectedCourseLabel.set_markup("<span size='large'> Course:"
                                 + selectedCourse + "</span>");
  selectedCourseLabel.set_padding(10,10);
  selectedCourseLabel.set_alignment(Gtk::ALIGN_CENTER, Gtk::ALIGN_CENTER);
  selectedCourseLabel.show();

  labelBox.pack_start(selectedTermLabel);
  labelBox.pack_start(selectedCourseLabel);
  containerBox.pack_start(labelBox);

  generalInfoLabel.set_markup("<span size='x-large' underline='single'>General Information</span>");
  generalInfoLabel.set_padding(10,10);
  generalInfoLabel.set_alignment(Gtk::ALIGN_CENTER,Gtk::ALIGN_CENTER);
  containerBox.pack_start(generalInfoLabel);
  generalInfoLabel.show();  

  stuNumLabel.set_markup("<span>Student Number:</span>");
  stuNumLabel.set_padding(5,5);
  stuNumLabel.set_alignment(0,0);
  stuNumLabel.set_width_chars(LABEL_WIDTH);
  stuNumLabel.show();

  stuNumEntry.set_max_length(STU_NUM_LENGTH);
  stuNumEntry.show();

  stuNumBox.pack_start(stuNumLabel, Gtk::PACK_SHRINK);
  stuNumBox.pack_end(stuNumEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(stuNumBox, false, false);

  firstNameLabel.set_markup("<span>First Name:</span>");
  firstNameLabel.set_padding(5,5);
  firstNameLabel.set_alignment(0,0);
  firstNameLabel.set_width_chars(LABEL_WIDTH);
  firstNameLabel.show();

  firstNameEntry.show();

  firstNameBox.pack_start(firstNameLabel, Gtk::PACK_SHRINK);
  firstNameBox.pack_end(firstNameEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(firstNameBox, false, false);

  lastNameLabel.set_markup("<span>Last Name:</span>");
  lastNameLabel.set_padding(5,5);
  lastNameLabel.set_alignment(0,0);
  lastNameLabel.set_width_chars(LABEL_WIDTH);
  lastNameLabel.show();

  lastNameEntry.show();

  lastNameBox.pack_start(lastNameLabel, Gtk::PACK_SHRINK);
  lastNameBox.pack_end(lastNameEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(lastNameBox, false, false);

  emailLabel.set_markup("<span>Email:</span>");
  emailLabel.set_padding(5,5);
  emailLabel.set_alignment(0,0);
  emailLabel.set_width_chars(LABEL_WIDTH);
  emailLabel.show();

  emailEntry.set_text(" ... carleton.ca");
  emailEntry.show();

  emailBox.pack_start(emailLabel, Gtk::PACK_SHRINK);
  emailBox.pack_end(emailEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(emailBox, false, false);

  majorLabel.set_markup("<span>Major:</span>");
  majorLabel.set_padding(5,5);
  majorLabel.set_alignment(0,0);
  majorLabel.set_width_chars(LABEL_WIDTH);
  majorLabel.show();

  majorEntry.show();

  majorBox.pack_start(majorLabel, Gtk::PACK_SHRINK);
  majorBox.pack_end(majorEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(majorBox, false, false);

  standingLabel.set_markup("<span>Year Standing:</span>");
  standingLabel.set_padding(5,5);
  standingLabel.set_alignment(0,0);
  standingLabel.set_width_chars(LABEL_WIDTH);
  standingLabel.show();

  standingEntry.show();

  standingBox.pack_start(standingLabel, Gtk::PACK_SHRINK);
  standingBox.pack_end(standingEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(standingBox, false, false);

  cgpaLabel.set_markup("<span>CGPA:</span>");
  cgpaLabel.set_padding(5,5);
  cgpaLabel.set_alignment(0,0);
  cgpaLabel.set_width_chars(LABEL_WIDTH);
  cgpaLabel.show();

  cgpaEntry.show();

  cgpaBox.pack_start(cgpaLabel, Gtk::PACK_SHRINK);
  cgpaBox.pack_end(cgpaEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(cgpaBox, false, false);

  mcgpaLabel.set_markup("<span>Major CGPA:</span>");
  mcgpaLabel.set_padding(10,10);
  mcgpaLabel.set_alignment(0,0);
  mcgpaLabel.set_width_chars(LABEL_WIDTH - 1);
  mcgpaLabel.show();

  mcgpaEntry.show();

  mcgpaBox.pack_start(mcgpaLabel, Gtk::PACK_SHRINK);
  mcgpaBox.pack_end(mcgpaEntry, Gtk::PACK_EXPAND_WIDGET);
  containerBox.pack_start(mcgpaBox, false, false);

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

void ApplicationWindow::onActionFileNew()
{
  cout << "File->New clicked" << endl;

  displayNewAppForm1();  
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
