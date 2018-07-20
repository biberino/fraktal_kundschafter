#include "functions_panel.hpp"

Functions_panel::Functions_panel(/* args */)
{
    _lbl_fractal.set_text("Fraktal:");
    _lbl_iterations.set_text("Iteration:");
    _lbl_color.set_text("Farbe:");

    attach(_lbl_fractal, 0, 0, 1, 1);
    attach(_lbl_iterations, 0, 1, 1, 1);
    attach(_lbl_color, 0, 2, 1, 1);

    attach(_combo_fractal, 1, 0, 1, 1);
    attach(_combo_iterations, 1, 1, 1, 1);
    attach(_combo_color, 1, 2, 1, 1);

    show_all_children();
}

Functions_panel::~Functions_panel()
{
}