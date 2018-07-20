#include "parameters_panel.hpp"
#include <iostream>

Parameters_panel::Parameters_panel(/* args */)
{
    _lbl_max_iter.set_text("Anzahl Iterationen:");
    _lbl_koppl.set_text("Verkopplungskonstante:");
    _lbl_width.set_text("Auflösung X:");
    _lbl_height.set_text("Auflösung Y:");

    attach(_lbl_max_iter, 0, 0, 1, 1);
    attach(_txt_max_iter, 0, 1, 1, 1);
    attach(_lbl_koppl, 1, 0, 1, 1);
    attach(_txt_koppl, 1, 1, 1, 1);

    attach(_lbl_width, 0, 2, 1, 1);
    attach(_txt_width, 0, 3, 1, 1);
    attach(_lbl_height, 1, 2, 1, 1);
    attach(_txt_height, 1, 3, 1, 1);

    /** DEFAULTS **/
    _txt_width.set_text("800");
    _txt_height.set_text("600");
    _txt_max_iter.set_text("50");
    _txt_koppl.set_text("0.1");

    show_all_children();
}

Parameters_panel::~Parameters_panel()
{
}

Parameters_Info Parameters_panel::get_data()
{
    Parameters_Info info;

    try
    {
        info.max_iter = std::stoi(_txt_max_iter.get_text());
        info.koppl = std::stod(_txt_koppl.get_text());
        info.res.x = std::stod(_txt_width.get_text());
        info.res.y = std::stod(_txt_height.get_text());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return info;
}
void Parameters_panel::set_data(Parameters_Info info)
{
    _txt_max_iter.set_text(std::to_string(info.max_iter));
    _txt_koppl.set_text(std::to_string(info.koppl));
    _txt_width.set_text(std::to_string(info.res.x));
    _txt_height.set_text(std::to_string(info.res.y));
}