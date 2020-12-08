#include <iostream>
#include "main_window.hpp"

Main_window::Main_window(Combo_entries combo_entries) : _func_panel(combo_entries),
                                                        _opt_panel(&_display, &_func_panel),
                                                        _v_box(Gtk::ORIENTATION_VERTICAL),
                                                        _h_box(Gtk::ORIENTATION_HORIZONTAL)
{
    set_default_size(1600, 900);
    _display.assign_opt_panel(&_opt_panel);
    set_title("Fraktal Kundschafter V 1.0.0");
    add_events(Gdk::KEY_PRESS_MASK);
    signal_key_press_event().connect(
        sigc::mem_fun(*this, &Main_window::on_main_window_key_press));

    _v_box.add1(_func_panel);
    _h_box.add1(_opt_panel);
    _h_box.add2(_display);
    _v_box.add2(_h_box);
    add(_v_box);
    show_all_children();
}

Main_window::~Main_window()
{
}

bool Main_window::on_main_window_key_press(GdkEventKey *event)
{
    std::cout << event->hardware_keycode << '\n';
    //D oder ctrl + D
    if (event->hardware_keycode == 40)
    {
        _opt_panel.request_calculation();
    }
    return true;
}