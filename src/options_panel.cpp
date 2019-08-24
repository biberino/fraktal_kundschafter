#include <iostream>

#include "options_panel.hpp"
#include "conversions.hpp"

Options_panel::Options_panel(Display *display, Functions_panel *func_panel)
    : _sep_1(Gtk::Orientation::ORIENTATION_HORIZONTAL),
      _sep_2(Gtk::Orientation::ORIENTATION_HORIZONTAL),
      _random_panel(this)
{

    _dispatcher.connect(sigc::mem_fun(*this,
                                      &Options_panel::on_dispatcher_notify));

    _dispatcher_time.connect(sigc::mem_fun(*this,
                                           &Options_panel::on_dispatcher_time_notify));

    /** Beginn GUI **/
    _button_draw.add_label("Zeichnen");
    _button_zoom_out.add_label("Rauszoomen");
    _button_zoom_reset.add_label("Reset Zoom");

    _sep_1.set_size_request(10, 10);
    _sep_2.set_size_request(10, 10);

    _grid_main.attach(_range_panel, 0, 0, 2, 1);
    _grid_main.attach(_sep_1, 0, 1, 2, 1);
    _grid_main.attach(_params_panel, 0, 2, 2, 1);
    //_grid_main.attach(_func_panel, 0, 3, 2, 1);
    _grid_main.attach(_button_zoom_reset, 0, 4, 1, 1);
    _grid_main.attach(_button_zoom_out, 1, 4, 1, 1);
    _grid_main.attach(_button_draw, 0, 5, 2, 1);
    _grid_main.attach(_sep_2, 0, 6, 2, 1);
    _grid_main.attach(_progress_bar, 0, 7, 2, 1);
    _grid_main.attach(_info_panel, 0, 8, 2, 1);
    _grid_main.attach(_random_panel, 0, 9, 2, 1);

    add(_grid_main);
    show_all_children();

    set_size_request(350, 150);

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
    _func_panel = func_panel;
    _display = display;
    _calc_handler = new Calculation_handler(this);
}

Options_panel::~Options_panel()
{
    delete _calc_handler;
}

void Options_panel::read_params()
{
    Parameters_Info p = _params_panel.get_data();
    Axis_info a = _range_panel.get_data();

    _calc_params.iteration_function = _func_panel->get_iter_callback();
    _calc_params.color_function = _func_panel->get_color_callback();
    _calc_params.fractal_function = _func_panel->get_fractal_callback();

    _calc_params.bailout_squared = p.bailout * p.bailout;
    _calc_params.julia_const = p.startpoint;
    _calc_params.resolution = p.res;
    _calc_params.work_size = 4000;
    _calc_params.max_iter = p.max_iter;
    _calc_params.koppl = p.koppl;
    _calc_params.x_min = a.x_min;
    _calc_params.x_max = a.x_max;
    _calc_params.y_min = a.y_min;
    _calc_params.y_max = a.y_max;
    _calc_params.gen_param = p.gen_param;

    //zoom data verfügbar??

    if (_display->zoom_active())
    {
        double x_diff = a.x_max - a.x_min;
        double y_diff = a.y_max - a.y_min;

        Display::Rectangle zoom_rect = _display->get_zoom_rect();
        _display->remove_zoom();
        //oben links nach unten rechts!!
        _calc_params.x_min = zoom_rect.x1 * (x_diff / (double)_calc_params.resolution.x) + (double)a.x_min;
        _calc_params.y_max = ((-1.0f * zoom_rect.y1 + (double)_calc_params.resolution.y) * ((double)y_diff / (double)_calc_params.resolution.y) + (double)a.y_min);

        _calc_params.x_max = zoom_rect.x2 * (x_diff / (double)_calc_params.resolution.x) + (double)a.x_min;
        _calc_params.y_min = ((-1.0f * zoom_rect.y2 + (double)_calc_params.resolution.y) * ((double)y_diff / (double)_calc_params.resolution.y) + (double)a.y_min);

        //update range panel
        a.x_min = _calc_params.x_min;
        a.x_max = _calc_params.x_max;
        a.y_min = _calc_params.y_min;
        a.y_max = _calc_params.y_max;

        _range_panel.set_data(a);
    }
}

void Options_panel::request_param_change(random_panel_change_data random_data)
{
    Parameters_Info p = _params_panel.get_data();
    if (random_data.b_gen)
        p.gen_param = random_data.gen;
    if (random_data.b_koppl)
        p.koppl = random_data.koppl;
    if (random_data.b_start_real)
        p.startpoint.real(random_data.start_real);
    if (random_data.b_start_imag)
        p.startpoint.imag(random_data.start_imag);

    _params_panel.set_data(p);

    if (random_data.b_formula)
        _func_panel->get_random_fractal_callback(); //this sets the Combobox to a random
                                                    //Function. It also returns the Function
                                                    //but we can ignore this
}

/**
 * The Display has to delete the trail_buffer
 */
Point_trail * Options_panel::request_point_trail(Pixel p)
{
    read_params();
    Parameters_Info params = _params_panel.get_data();
    Axis_info a = _range_panel.get_data();

    complex_type point = Pixel_to_Koord(p, a, params.res);

    Point_trail *point_trail = new Point_trail;
    point_trail->points = new complex_type[params.max_iter];
    point_trail->valid_count = 0;

    _func_panel->get_iter_callback()(point,
                                     params.max_iter,
                                     _func_panel->get_fractal_callback(),
                                     _func_panel->get_color_callback(),
                                     params.startpoint,
                                     params.bailout * params.bailout,
                                     params.koppl,
                                     params.gen_param,
                                     point_trail);

    //trail_buffer now contains complex trail. We need to converts this for the display
    for (size_t i = 0; i < point_trail->valid_count; i++)
    {
        Pixel buffer;
        buffer = Koord_to_Pixel(point_trail->points[i], a, params.res);
        point_trail->points[i] = complex_type((double)buffer.x, (double)buffer.y);

    }

    return point_trail;
}

void Options_panel::on_button_draw_clicked()
{
    if (!_calc_in_progress)
    {
        _calc_in_progress = true;
        _time.start();
        _calc_thread = std::thread(&Options_panel::start_calculation, this);
        _calc_thread.detach();
    }
    else
    {
        _info_panel.append_message("-->  WARNUNG:   Berechnung bereits im Gange\n");
    }
}

void Options_panel::start_calculation()
{
    read_params();
    _calc_handler->set_params(_calc_params);
    _calc_handler->calculate(); //this blocks
    _display->set_data(_calc_params.resolution.x, _calc_params.resolution.y, _calc_handler->get_result_pointer());
    _display->remove_point_trail();
    _display->queue_draw();
    stop_time();
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

void Options_panel::on_dispatcher_notify()
{
    //Update GUI from GUI Thread
    _progress_bar.set_fraction(_calc_fraction);
}

void Options_panel::update_progress(double fraction)
{
    _calc_fraction = fraction;
    _dispatcher.emit();
}

void Options_panel::stop_time()
{
    _time_millis = _time.stop();
    _dispatcher_time.emit();
}

void Options_panel::on_dispatcher_time_notify()
{

    std::string buffer = "-->  FERTIG:    " + std::to_string((float)_time_millis / 1000.0f) + " Sekunden" + '\n';
    _info_panel.append_message(buffer);
    _calc_in_progress = false;
}

void Options_panel::request_calculation()
{
    on_button_draw_clicked();
}