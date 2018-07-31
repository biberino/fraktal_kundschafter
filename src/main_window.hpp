#ifndef MAIN_WINDOW_GUARD
#define MAIN_WINDOW_GUARD

#include <gtkmm.h>

#include "types.hpp"
//Gtk components
#include "display.hpp"
#include "options_panel.hpp"
#include "functions_panel.hpp"

class Main_window : public Gtk::Window
{
  private:
    Functions_panel _func_panel;
    Display _display;
    Options_panel _opt_panel;
    Gtk::Paned _v_box;
    Gtk::Paned _h_box;

  protected:
    bool on_main_window_key_press(GdkEventKey *event);

  public:
    Main_window(Combo_entries combo_entries);
    ~Main_window();
};

#endif // !MAIN_WINDOW_GUARD