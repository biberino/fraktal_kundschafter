#ifndef DISPLAY_GUARD_123
#define DISPLAY_GUARD_123

#include <gtkmm.h>
//#include <gdkmm/pixbuf.h>
#include <gdkmm.h>
#include "types.hpp"

//forward declare
class Options_panel;

class Display : public Gtk::DrawingArea
{
public:
  Display();
  void assign_opt_panel(Options_panel *opt_panel);
  ~Display();

  struct Rectangle
  {
    double x1;
    double y1;
    double x2;
    double y2;
  };

  void set_data(int width, int height, unsigned char *data);
  bool zoom_active();
  Rectangle get_zoom_rect();
  bool remove_zoom();
  void remove_point_trail();

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

  bool on_display_clicked(GdkEventButton *event);
  bool on_display_motion(GdkEventMotion *event);

  struct Mouse_pos
  {
    double x;
    double y;
  };


  Glib::RefPtr<Gdk::Pixbuf> _image;
  Glib::RefPtr<Gdk::Pixbuf> _zoom_box;

  Mouse_pos _mouse_pos_start;
  Mouse_pos _mouse_pos_cursor;

  bool _zoom_mode = false;
  bool _show_rectangle = false;

  int _current_width = 0;
  int _current_height = 0;

private:
  Options_panel *_opt_panel;
  bool _point_trail_active = false;
  Point_trail *_point_trail = nullptr;
};

#endif // !DISPLAY_GUARD