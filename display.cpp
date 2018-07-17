#include "display.hpp"

Display::Display()
{
    //_image = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, 0, 8, 100, 100);
}

Display::~Display()
{
}

void Display::set_data(int width, int height, unsigned char *data)
{

    _image = Gdk::Pixbuf::create_from_data((const guint8 *)data, Gdk::Colorspace::COLORSPACE_RGB, 0, 8, width, height, width * 3);
}

bool Display::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    if (!_image)
        return false;
    /**
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // Draw the image in the middle of the drawing area, or (if the image is
  // larger than the drawing area) draw the middle part of the image.
  Gdk::Cairo::set_source_pixbuf(cr, m_image,
    (width - m_image->get_width())/2, (height - m_image->get_height())/2);

    **/

    Gdk::Cairo::set_source_pixbuf(cr, _image, 0, 0);
    cr->paint();

    return true;
}