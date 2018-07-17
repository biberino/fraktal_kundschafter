#ifndef OPTIONS_PANEL_GUARD
#define OPTIONS_PANEL_GUARD

#include <gtkmm.h>

class Options_panel : public Gtk::ScrolledWindow
{
  private:
    Gtk::Button _button_draw;
    void (*_f)();

  protected:
    void on_button_draw_clicked();

  public:
    Options_panel(void (*f)());
    ~Options_panel();
};

#endif // !OPTIONS_PANEL_GUARD