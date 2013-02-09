/* //////////////////////////////////////////////////////////////////////////////////////////////

        cuTAES - W13 COMP 2404 Assignment 1

        Date: February 1, 2013

        Authors:
        - Abdul-Karim Farhat
        - Andrew Belu

        Purpose:
        - TA Application and Evaluation System for Carleton University.
        - Allows students to submit applications to be a TA.

        Inputs:
        - courses.txt : list of available courses, one per line.

        Outputs:
        - students.txt : list of students who've applied to be a TA with their personal info.
        - applications.txt : list of application information for the submitted applications

        Notes:
        - Some of the Gtkmm code was copied from their tutorial and website.
        - There's an assertion failure at some points in the code due to trying to remove
          widgets that aren't actually children of a certain container. I haven't found any
          way to get around this except by using std::vector, which we are not allowed to.
        - The UI is still fairly primitive because we spent a lot of time trying to figure 
          out how Gtkmm works. It will improved for the second assignment.
        - There was no time to properly design subclasses for interface elements after we
          had finally figured out Gtkmm but, again, this will be fixed next assignment.

       Compilation:
       - Compile using command: $ make

       Execution:
       - Execute the application using: $ ./cutaes
       
////////////////////////////////////////////////////////////////////////////////////////////// */

#include <gtkmm/application.h>
#include "ApplicationWindow.h"

int main (int argc, char* argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc,argv,
                                         "com.carleton.cuteas");

  ApplicationWindow appWindow;

  return app->run(appWindow);
}
