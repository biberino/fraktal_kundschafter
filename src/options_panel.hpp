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
#include "info_panel.hpp"
#include "random_panel.hpp"

#include "time.hpp"

class Options_panel : public Gtk::ScrolledWindow
{
private:

  


  Gtk::Grid _grid_main;
  Gtk::Button _button_zoom_out;
  Gtk::Button _button_zoom_reset;
  Gtk::Button _button_draw;
  Range_panel _range_panel;
  Gtk::Separator _sep_1;
  Gtk::Separator _sep_2;
  Functions_panel *_func_panel;
  Parameters_panel _params_panel;
  Gtk::ProgressBar _progress_bar;
  Info_panel _info_panel;
  Random_panel _random_panel;

  calculation_params _calc_params;
  Display *_display;

  std::thread _calc_thread;
  Glib::Dispatcher _dispatcher;
  Glib::Dispatcher _dispatcher_time;

  Calculation_handler *_calc_handler;

  time_meassure _time;
  int _time_millis;

  double _calc_fraction = 0.0f;
  bool _calc_in_progress = false;



  void read_params();
  void start_calculation();

  void stop_time();

protected:
  void on_button_draw_clicked();
  void on_button_reset_zoom_click();
  void on_button_zoom_out_click();
  void on_dispatcher_notify();
  void on_dispatcher_time_notify();

public:
  Options_panel(Display *display, Functions_panel *func_panel);
  ~Options_panel();

  void update_progress(double fraction);
  void request_calculation();

  void request_param_change(random_panel_change_data random_data);

  Point_trail * request_point_trail(Pixel p);
};

#endif // !OPTIONS_PANEL_GUARD