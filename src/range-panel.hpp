#ifndef RANGE_GUARD
#define RANGE_GUARD

#include <gtkmm.h>
#include "types.hpp"

class Range_panel : public Gtk::Grid
{
private:
  //Gtk::Grid _grid_main;
  Gtk::Label _lbl_x_min;
  Gtk::Label _lbl_x_max;
  Gtk::Label _lbl_y_min;
  Gtk::Label _lbl_y_max;

  Gtk::Entry _txt_x_min;
  Gtk::Entry _txt_x_max;
  Gtk::Entry _txt_y_min;
  Gtk::Entry _txt_y_max;


public:
  Range_panel();
  ~Range_panel();

  Axis_info get_data();
  void set_data(Axis_info axis);
};

#endif // !RANGE_GUARD