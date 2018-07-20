#ifndef FUNCTIONS_PANEL_GUARD
#define FUNCTIONS_PANEL_GUARD
#include <gtkmm.h>

class Functions_panel : public Gtk::Grid
{
  private:
    Gtk::Label _lbl_fractal;
    Gtk::Label _lbl_iterations;
    Gtk::Label _lbl_color;

    Gtk::ComboBox _combo_fractal;
    Gtk::ComboBox _combo_iterations;
    Gtk::ComboBox _combo_color;

  public:
    Functions_panel(/* args */);
    ~Functions_panel();
};

#endif // !FUNCTIONS_PANEL_GUARD