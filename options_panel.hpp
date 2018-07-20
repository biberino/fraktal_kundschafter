#ifndef OPTIONS_PANEL_GUARD_123
#define OPTIONS_PANEL_GUARD_123

#include <gtkmm.h>

#include "calculation_handler.hpp"
#include "display.hpp"
#include "range-panel.hpp"
#include "functions_panel.hpp"

class Options_panel : public Gtk::ScrolledWindow
{
private:
  Gtk::Grid _grid_main;
  Gtk::Button _button_zoom_out;
  Gtk::Button _button_zoom_reset;
  Gtk::Button _button_draw;
  Range_panel _range_panel;
  Gtk::Separator _sep_1;
  Functions_panel _func_panel;

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