#include "display.hpp"
#include "options_panel.hpp"
#include <iostream>

Display::Display()
{
    this->set_can_focus(true);
    this->add_events(Gdk::EventMask::BUTTON_PRESS_MASK);
    this->add_events(Gdk::EventMask::POINTER_MOTION_MASK);
    this->add_events(Gdk::EventMask::POINTER_MOTION_HINT_MASK);
    //_image = Gdk::Pixbuf::create(Gdk::COLORSPACE_RGB, 0, 8, 100, 100);
    this->signal_button_press_event().connect(
        sigc::mem_fun(*this, &Display::on_display_clicked));

    this->signal_motion_notify_event().connect(
        sigc::mem_fun(*this, &Display::on_display_motion));
}

Display::~Display()
{
}

void Display::assign_opt_panel(Options_panel *opt_panel)
{
    _opt_panel = opt_panel;
}

void Display::set_data(int width, int height, unsigned char *data)
{
    _current_height = height;
    _current_width = width;
    _image = Gdk::Pixbuf::create_from_data((const guint8 *)data, Gdk::Colorspace::COLORSPACE_RGB, 0, 8, width, height, width * 3);
    //  _zoom_box = Gdk::Pixbuf::create_from_data((const guint8 *)data, Gdk::Colorspace::COLORSPACE_RGB, 0, 8, width, height, width * 3);
}

bool Display::on_display_clicked(GdkEventButton *event)
{
    std::cout << "HELLO CLICK" << event->x << " " << event->y << '\n';
    // std::cout << "Button: " << event->button << std::endl;

    if (event->button == 1)
    {
        // left mouse button
        _show_rectangle = true;
        if (!_zoom_mode)
        {
            _zoom_mode = true;
            _mouse_pos_start.x = event->x;
            _mouse_pos_start.y = event->y;
        }
        else
        {
            _zoom_mode = false;
            _mouse_pos_cursor.x = event->x;
            _mouse_pos_cursor.y = event->y;
        }
    }
    else if (event->button == 3)
    {

        Pixel p;
        p.x = event->x;
        p.y = event->y;
        if (_point_trail)
        {
            delete[] _point_trail->points;
            delete _point_trail;
        }
        _point_trail = _opt_panel->request_point_trail(p);
        _point_trail_active = true;
        this->queue_draw();
    }
    return true;
}

void Display::remove_point_trail()
{
    _point_trail_active = false;
}

bool Display::on_display_motion(GdkEventMotion *event)
{
    // std::cout << "MOTION" << event->x << " " << event->y << '\n';
    if (_zoom_mode)
    {
        _mouse_pos_cursor.x = event->x;
        _mouse_pos_cursor.y = event->y;
        this->queue_draw();
    }
    return true;
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

    // draw image
    Gdk::Cairo::set_source_pixbuf(cr, _image, 0, 0);
    cr->paint();

    // draw zoom rect
    if (_show_rectangle)
    {
        cr->set_source_rgb(0.8, 0.8, 0.8);
        cr->set_line_width(2);
        cr->rectangle(_mouse_pos_start.x, _mouse_pos_start.y,
                      _mouse_pos_cursor.x - _mouse_pos_start.x,
                      _mouse_pos_cursor.y - _mouse_pos_start.y);
        cr->stroke();
    }

    // cr->fill();

    // draw point trail
    if (_point_trail_active)
    {
        cr->set_source_rgb(1.0, 0.0, 0.0);
        cr->set_line_width(2);
        cr->move_to(_point_trail->points[0].real(), _point_trail->points[0].imag());
        for (size_t i = 1; i < _point_trail->valid_count; i++)
        {
            cr->line_to(_point_trail->points[i].real(), _point_trail->points[i].imag());
        }
        cr->stroke();
    }
    return true;
}

bool Display::zoom_active()
{
    return (_show_rectangle && !_zoom_mode);
}

Display::Rectangle Display::get_zoom_rect()
{
    Display::Rectangle retVal;
    retVal.x1 = _mouse_pos_start.x;
    retVal.y1 = _mouse_pos_start.y;

    retVal.x2 = _mouse_pos_cursor.x;
    retVal.y2 = _mouse_pos_cursor.y;

    return retVal;
}

void Display::remove_zoom()
{
    _show_rectangle = false;
    _zoom_mode = false;
}