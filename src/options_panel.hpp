#ifndef OPTIONS_PANEL_GUARD_123
#define OPTIONS_PANEL_GUARD_123

#include <gtkmm.h>
#include <thread>

#include "types.hpp"
#include "calculation_handler.hpp"
#include "display.hpp"
#include "range-panel.hpp"
#include "functions_panel.hpp"
#include "parameters_panel.hpp"

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
  Parameters_panel _params_panel;
  Gtk::ProgressBar _progress_bar;

  calculation_params _calc_params;
  Display *_display;

  std::thread _calc_thread;

  Calculation_handler *_calc_handler;

  void read_params();
  void start_calculation();

protected:
  void on_button_draw_clicked();

public:
  Options_panel(Display *display, const Combo_entries& combo_entries);
  ~Options_panel();
};

#endif // !OPTIONS_PANEL_GUARD