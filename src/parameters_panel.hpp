#ifndef PARAMETERS_PANEL
#define PARAMETERS_PANEL
#include <gtkmm.h>
#include "types.hpp"

class Parameters_panel : public Gtk::Grid
{
private:
  Gtk::Label _lbl_max_iter;
  Gtk::Label _lbl_koppl;

  Gtk::Entry _txt_max_iter;
  Gtk::Entry _txt_koppl;

  Gtk::Label _lbl_width;
  Gtk::Label _lbl_height;

  Gtk::Entry _txt_width;
  Gtk::Entry _txt_height;

  Gtk::Label _lbl_gen_param;
  Gtk::Entry _txt_gen_param;

  Gtk::Label _lbl_bailout;
  Gtk::Entry _txt_bailout;

public:
  Parameters_panel(/* args */);
  ~Parameters_panel();

  Parameters_Info get_data();
  void set_data(Parameters_Info info);
};

#endif // !PARAMETERS_PANEL