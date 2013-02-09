#include "LabelEntryPair.h"
#include <gtkmm.h>

LabelEntryPair::LabelEntryPair(Gtk::Label l, Gtk::Entry e)
{
  label = l;
  entry = e;

  add(label);
  add(entry);
}
