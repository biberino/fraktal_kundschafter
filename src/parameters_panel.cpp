#include "parameters_panel.hpp"

Parameters_panel::Parameters_panel(/* args */)
{
    attach(_lbl_max_iter, 0, 0, 1, 1);
    attach(_txt_max_iter, 0, 1, 1, 1);
    attach(_lbl_koppl, 1, 0, 1, 1);
    attach(_txt_koppl, 1, 1, 1, 1);

    show_all_children();
}

Parameters_panel::~Parameters_panel()
{
}