#include <iostream>
#include "colors.hpp"
#include "iterations.hpp"
#include "options_panel.hpp"
#include "fractal_functions.hpp"

Options_panel::Options_panel(Calculation_handler *calc_handler, Display *display)
    : _sep_1(Gtk::Orientation::ORIENTATION_HORIZONTAL)
{

    /** Beginn GUI **/
    _button_draw.add_label("Zeichnen");
    _button_zoom_out.add_label("Rauszoomen");
    _button_zoom_reset.add_label("Reset Zoom");

    _sep_1.set_size_request(10, 10);

    _grid_main.attach(_range_panel, 0, 0, 2, 1);
    _grid_main.attach(_sep_1, 0, 1, 2, 1);
    _grid_main.attach(_params_panel, 0, 2, 2, 1);
    _grid_main.attach(_func_panel, 0, 3, 2, 1);
    _grid_main.attach(_button_zoom_reset, 0, 4, 1, 1);
    _grid_main.attach(_button_zoom_out, 1, 4, 1, 1);
    _grid_main.attach(_button_draw, 0, 5, 2, 1);

    add(_grid_main);
    show_all_children();

    set_size_request(250, 150);

    //events
    _button_draw.signal_clicked()
        .connect(sigc::mem_fun(*this,
                               &Options_panel::on_button_draw_clicked));

    /** Ende GUI **/

    _calc_handler = calc_handler;
    _display = display;
}

Options_panel::~Options_panel()
{
}

void Options_panel::read_params()
{
    Parameters_Info p = _params_panel.get_data();
    Axis_info a = _range_panel.get_data();

    _calc_params.iteration_function = normal_iter;
    _calc_params.color_function = colorize;
    _calc_params.fractal_function = mandelbrot;

    _calc_params.bailout_squared = 4.0f;
    _calc_params.julia_const = std::complex<float>(-1, 0);
    _calc_params.resolution = p.res;
    _calc_params.work_size = 4000;
    _calc_params.max_iter = p.max_iter;
    _calc_params.koppl = p.koppl;
    _calc_params.x_min = a.x_min;
    _calc_params.x_max = a.x_max;
    _calc_params.y_min = a.y_min;
    _calc_params.y_max = a.y_max;
}

void Options_panel::on_button_draw_clicked()
{
    std::cout << "CLICKED!!!" << '\n';
    read_params();
    _calc_handler->set_params(_calc_params);
    _calc_handler->calculate(); //TODO: this blocks, maybe new thread + progressbar
    _display->set_data(_calc_params.resolution.x, _calc_params.resolution.y, _calc_handler->get_result_pointer());
    _display->queue_draw();
}