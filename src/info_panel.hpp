#ifndef INFO_PANEL_GUARD
#define INFO_PANEL_GUARD

#include <gtkmm.h>
#include <string>

class Info_panel : public Gtk::Grid
{
  private:
    /* data */

  protected:
    Gtk::Label _lbl_headline;

    Glib::RefPtr<Gtk::TextBuffer> _ref_text_buffer;
    Gtk::TextView _view;

  public:
    Info_panel(/* args */);
    ~Info_panel();

    void clear();
    void append_message(const std::string &msg);
};

#endif // !INFO_PANEL_GUARD
