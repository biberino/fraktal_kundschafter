#include <iostream>

#include "options_panel.hpp"

Options_panel::Options_panel(Display *display, const Combo_entries &combo_entries)
    : _sep_1(Gtk::Orientation::ORIENTATION_HORIZONTAL),
      _func_panel(combo_entries)
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
    _grid_main.attach(_progress_bar, 0, 6, 2, 1);

    add(_grid_main);
    show_all_children();

    set_size_request(250, 150);

    //events
    _button_draw.signal_clicked()
        .connect(sigc::mem_fun(*this,
                               &Options_panel::on_button_draw_clicked));

    _button_zoom_reset.signal_clicked()
        .connect(sigc::mem_fun(*this,
                               &Options_panel::on_button_reset_zoom_click));

    _button_zoom_out.signal_clicked()
        .connect(sigc::mem_fun(*this,
                               &Options_panel::on_button_zoom_out_click));

    /** Ende GUI **/

    _display = display;
    _calc_handler = new Calculation_handler(&_progress_bar);
}

Options_panel::~Options_panel()
{
    delete _calc_handler;
}

void Options_panel::read_params()
{
    Parameters_Info p = _params_panel.get_data();
    Axis_info a = _range_panel.get_data();

    _calc_params.iteration_function = _func_panel.get_iter_callback();
    _calc_params.color_function = _func_panel.get_color_callback();
    _calc_params.fractal_function = _func_panel.get_fractal_callback();

    _calc_params.bailout_squared = 4.0f;
    _calc_params.julia_const = complex_type(-1, 0);
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
    _calc_thread = std::thread(&Options_panel::start_calculation, this);
    _calc_thread.detach();
}

void Options_panel::start_calculation()
{
    read_params();
    _calc_handler->set_params(_calc_params);
    _calc_handler->calculate(); //TODO: this blocks, maybe new thread + progressbar
    _display->set_data(_calc_params.resolution.x, _calc_params.resolution.y, _calc_handler->get_result_pointer());
    _display->queue_draw();
}

void Options_panel::on_button_zoom_out_click()
{
    Axis_info a = _range_panel.get_data();
    a.x_min *= 2;
    a.x_max *= 2;
    a.y_min *= 2;
    a.y_max *= 2;
    _range_panel.set_data(a);
}

void Options_panel::on_button_reset_zoom_click()
{
    Axis_info a;
    a.x_min = -2.0;
    a.x_max = 1.0;
    a.y_min = -1.0;
    a.y_max = 1.0;
    _range_panel.set_data(a);
}