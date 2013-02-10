#ifndef LABEL_ENTRY_PAIR_H
#define LABEL_ENTRY_PAIR_H

#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>

class LabelEntryPair : public Gtk::HBox
{
  public:
    LabelEntryPair(Gtk::Label, Gtk::Entry);
   ~LabelEntryPair();

    Gtk::Label label;
    Gtk::Entry entry;

};

#endif
