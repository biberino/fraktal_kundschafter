#include <iostream>
#include "colors.hpp"
#include "iterations.hpp"
#include "options_panel.hpp"
#include "fractal_functions.hpp"



Options_panel::Options_panel(Calculation_handler *calc_handler, Display *display)
{
    _button_draw.add_label("Zeichnen");

    _button_draw.signal_clicked()
        .connect(sigc::mem_fun(*this,
                               &Options_panel::on_button_draw_clicked));

    add(_button_draw);
    show_all_children();
    _calc_handler = calc_handler;
    _display = display;
    set_default_params();
}

Options_panel::~Options_panel()
{
}

void Options_panel::set_default_params()
{
    _res.x = 800;
    _res.y = 600;
    _calc_params.x_min = -2;
    _calc_params.x_max = 1;
    _calc_params.y_min = -1;
    _calc_params.y_max = 1;
    _calc_params.iteration_function = normal_iter;
    _calc_params.color_function = colorize;
    _calc_params.fractal_function = mandelbrot;
    _calc_params.resolution = _res;
    _calc_params.work_size = 4000;
    _calc_params.max_iter = 150;
    _calc_params.koppl = 0.1f;
    _calc_params.bailout_squared = 4.0f;
    _calc_params.julia_const = std::complex<float>(-1, 0);
}

void Options_panel::on_button_draw_clicked()
{
    std::cout << "CLICKED!!!" << '\n';
    _calc_handler->set_params(_calc_params);
    _calc_handler->calculate(); //TODO: this blocks, maybe new thread + progressbar
    _display->set_data(_res.x, _res.y, _calc_handler->get_result_pointer());
    _display->queue_draw();
}