#include "range-panel.hpp"

Range_panel::Range_panel()
{
    //add(_grid_main);

    _lbl_x_min.set_text("X MIN:");
    _lbl_x_max.set_text("X MAX:");
    _lbl_y_min.set_text("Y MIN:");
    _lbl_y_max.set_text("Y MAX:");

    attach(_lbl_x_min, 0, 0, 1, 1);
    attach(_lbl_x_max, 0, 1, 1, 1);
    attach(_lbl_y_min, 0, 2, 1, 1);
    attach(_lbl_y_max, 0, 3, 1, 1);

    attach(_txt_x_min, 1, 0, 1, 1);
    attach(_txt_x_max, 1, 1, 1, 1);
    attach(_txt_y_min, 1, 2, 1, 1);
    attach(_txt_y_max, 1, 3, 1, 1);

    show_all_children();
}

Range_panel::~Range_panel()
{
}