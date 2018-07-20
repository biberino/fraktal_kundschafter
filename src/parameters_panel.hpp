#ifndef PARAMETERS_PANEL
#define PARAMETERS_PANEL
#include <gtkmm.h>


class Parameters_panel : public Gtk::Grid
{
  private:
    Gtk::Label _lbl_max_iter;
    Gtk::Label _lbl_koppl;

    Gtk::Entry _txt_max_iter;
    Gtk::Entry _txt_koppl;
  public:
    Parameters_panel(/* args */);
    ~Parameters_panel();
};

#endif // !PARAMETERS_PANEL