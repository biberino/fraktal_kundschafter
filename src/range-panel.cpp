#include "range-panel.hpp"
#include <iostream>
#include <limits>
#include <iomanip> // setprecision
#include <sstream> // stringstream

Range_panel::Range_panel()
{
    //add(_grid_main);

    _lbl_x_min.set_text("X MIN:   ");
    _lbl_x_max.set_text("X MAX:   ");
    _lbl_y_min.set_text("Y MIN:   ");
    _lbl_y_max.set_text("Y MAX:   ");

    attach(_lbl_x_min, 0, 0, 1, 1);
    attach(_lbl_x_max, 0, 1, 1, 1);
    attach(_lbl_y_min, 0, 2, 1, 1);
    attach(_lbl_y_max, 0, 3, 1, 1);

    attach(_txt_x_min, 1, 0, 1, 1);
    attach(_txt_x_max, 1, 1, 1, 1);
    attach(_txt_y_min, 1, 2, 1, 1);
    attach(_txt_y_max, 1, 3, 1, 1);

    /**DEFAULT **/
    _txt_x_min.set_text("-2");
    _txt_x_max.set_text("1");
    _txt_y_min.set_text("-1");
    _txt_y_max.set_text("1");

    show_all_children();
}

Range_panel::~Range_panel()
{
}

Axis_info Range_panel::get_data()
{

    Axis_info axis;

    try
    {
        axis.x_min = std::stod(_txt_x_min.get_text());
        axis.x_max = std::stod(_txt_x_max.get_text());
        axis.y_min = std::stod(_txt_y_min.get_text());
        axis.y_max = std::stod(_txt_y_max.get_text());
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return axis;
}

void Range_panel::set_data(Axis_info axis)
{
    int max_digits = std::numeric_limits<datatype>::max_digits10;
    std::stringstream stream;
    stream << std::fixed << std::setprecision(max_digits) << axis.x_min;

    _txt_x_min.set_text(stream.str());

    stream.str("");
    stream << std::fixed << std::setprecision(max_digits) << axis.x_max;
    _txt_x_max.set_text(stream.str());

    stream.str("");
    stream << std::fixed << std::setprecision(max_digits) << axis.y_min;
    _txt_y_min.set_text(stream.str());
    stream.str("");

    stream << std::fixed << std::setprecision(max_digits) << axis.y_max;
    _txt_y_max.set_text(stream.str());

}