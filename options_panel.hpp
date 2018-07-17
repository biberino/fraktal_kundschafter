#ifndef OPTIONS_PANEL_GUARD_123
#define OPTIONS_PANEL_GUARD_123

#include <gtkmm.h>

#include "calculation_handler.hpp"
#include "display.hpp"



class Options_panel : public Gtk::ScrolledWindow
{
  private:
    Gtk::Button _button_draw;


    calculation_params _calc_params;
    Resolution_info _res;
    Calculation_handler *_calc_handler;
    Display *_display;


    void set_default_params();


  protected:
    void on_button_draw_clicked();

  public:
    Options_panel(Calculation_handler *calc_handler, Display *display);
    ~Options_panel();
};

#endif // !OPTIONS_PANEL_GUARD