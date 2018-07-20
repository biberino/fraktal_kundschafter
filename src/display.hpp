#ifndef DISPLAY_GUARD_123
#define DISPLAY_GUARD_123

#include <gtkmm/drawingarea.h>
//#include <gdkmm/pixbuf.h>
#include <gdkmm.h>


class Display : public Gtk::DrawingArea
{
public:
  Display();
  ~Display();

  void set_data(int width, int height, unsigned char *data);

protected:
  //Override default signal handler:
  bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

  Glib::RefPtr<Gdk::Pixbuf> _image;

private:
};

#endif // !DISPLAY_GUARD