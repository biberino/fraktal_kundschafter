#include <iostream>
#include <thread>
//#include <SDL2/SDL.h>
#include <gtkmm.h>

#include "types.hpp"
#include "workload_distributor.hpp"
#include "result_store.hpp"
#include "fractal_worker.hpp"
#include "fractal_functions.hpp"
#include "fractal_functions.hpp"
#include "iterations.hpp"

//Gtk components
#include "display.hpp"
#include "options_panel.hpp"

Workload_distributor work_dis;
Result_store store;
Display *dis;

void draw_store(Result_store *store, Display *display, Resolution_info res)
{
    display->set_data(res.x, res.y, store->get_data_pointer());
    display->queue_draw();
}

void calc_fractal()
{
    Resolution_info res;
    res.x = 800;
    res.y = 600;

    work_dis.reset(res);

    store.reset(res);

    Fractal_params fractal_params;
    fractal_params.store = &store;
    fractal_params.work_dis = &work_dis;
    fractal_params.axis.x_min = -2;
    fractal_params.axis.x_max = 1;
    fractal_params.axis.y_min = -1;
    fractal_params.axis.y_max = 1;
    fractal_params.iteration_function = normal_iter;
    fractal_params.res = res;
    fractal_params.work_size = 4000;

    max_iter = 150;
    koppl = 0.1f;
    bailout_squared = 4.0f;
    fractal_func = mandelbrot;
    julia_const = std::complex<float>(-1, 0);

    std::vector<std::thread> threads;
    std::vector<Fractal_worker> workers;

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        workers.push_back(Fractal_worker());
    }

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        workers[i].set_params(fractal_params);
        threads.push_back(std::thread(&Fractal_worker::start, &workers[i]));
    }

    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
    {
        threads[i].join();
        //store.put(&(workers[i]._col_info_vec));
    }
    draw_store(&store, dis, res);
}

int main(int argc, char *argv[])
{

    //display.show();

    //draw(&store);

    auto app = Gtk::Application::create(argc, argv, "biber.fractale.test");
    Gtk::Window window;
    window.set_default_size(800, 600);
    window.set_title("Fraktal Kundschafter");
    

    Display display;
    dis = &display;
    Options_panel opt_panel(calc_fractal);

    Gtk::Paned v_box(Gtk::ORIENTATION_HORIZONTAL);
    
    v_box.add1(opt_panel);
    v_box.add2(display);
    window.add(v_box);

    window.show_all_children();

    return app->run(window);

    return 0;
}
