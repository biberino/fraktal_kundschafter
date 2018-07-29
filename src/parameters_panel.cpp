#include "parameters_panel.hpp"
#include <iostream>

Parameters_panel::Parameters_panel(/* args */)
{
    _lbl_max_iter.set_text("Anzahl Iterationen:");
    _lbl_koppl.set_text("Verkopplungskonstante:");
    _lbl_width.set_text("Auflösung X:");
    _lbl_height.set_text("Auflösung Y:");
    _lbl_gen_param.set_text("Generischer Parameter:");
    _lbl_bailout.set_text("Fluchtradius");
    _lbl_startpoint_real.set_text("Startwert/Julia Realanteil:");
    _lbl_startpoint_imag.set_text("Startwert/Julia Imaginäranteil:");

    attach(_lbl_max_iter, 0, 0, 1, 1);
    attach(_txt_max_iter, 0, 1, 1, 1);
    attach(_lbl_koppl, 1, 0, 1, 1);
    attach(_txt_koppl, 1, 1, 1, 1);

    attach(_lbl_width, 0, 2, 1, 1);
    attach(_txt_width, 0, 3, 1, 1);
    attach(_lbl_height, 1, 2, 1, 1);
    attach(_txt_height, 1, 3, 1, 1);

    attach(_lbl_gen_param, 0, 4, 1, 1);
    attach(_txt_gen_param, 0, 5, 1, 1);

    attach(_lbl_bailout, 1, 4, 1, 1);
    attach(_txt_bailout, 1, 5, 1, 1);

    attach(_lbl_startpoint_real, 0, 6, 1, 1);
    attach(_txt_startpoint_real, 0, 7, 1, 1);

    attach(_lbl_startpoint_imag, 1, 6, 1, 1);
    attach(_txt_startpoint_imag, 1, 7, 1, 1);
    /** DEFAULTS **/
    _txt_width.set_text("1200");
    _txt_height.set_text("800");
    _txt_max_iter.set_text("50");
    _txt_koppl.set_text("0.1");
    _txt_gen_param.set_text("1.0");
    _txt_bailout.set_text("2.0");
    _txt_startpoint_real.set_text("0.0");
    _txt_startpoint_imag.set_text("0.0");

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
        info.gen_param = std::stof(_txt_gen_param.get_text());
        info.bailout = std::stof(_txt_bailout.get_text());
        info.startpoint = complex_type(std::stod(_txt_startpoint_real.get_text()),
                                       std::stod(_txt_startpoint_imag.get_text()));
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
    _txt_gen_param.set_text(std::to_string(info.gen_param));
    _txt_bailout.set_text(std::to_string(info.bailout));
    _txt_startpoint_real.set_text(std::to_string(info.startpoint.real()));
    _txt_startpoint_imag.set_text(std::to_string(info.startpoint.imag()));
}