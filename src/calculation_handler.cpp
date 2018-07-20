#include <thread>
#include "calculation_handler.hpp"

Calculation_handler::Calculation_handler()
{
}

Calculation_handler::~Calculation_handler()
{
}

void Calculation_handler::set_params(calculation_params params)
{
    _params = params;
}

void Calculation_handler::calculate()
{
    work_dis.reset(_params.resolution);
    store.reset(_params.resolution);

    Fractal_params fractal_params;
    fractal_params.store = &store;
    fractal_params.work_dis = &work_dis;
    fractal_params.axis.x_min = _params.x_min;
    fractal_params.axis.x_max = _params.x_max;
    fractal_params.axis.y_min = _params.y_min;
    fractal_params.axis.y_max = _params.y_max;
    fractal_params.iteration_function = _params.iteration_function;
    fractal_params.res = _params.resolution;
    fractal_params.work_size = _params.work_size;
    fractal_params.max_iter = _params.max_iter;
    fractal_params.color_function = _params.color_function;
    fractal_params.fractal_function = _params.fractal_function;
    fractal_params.bailout_squared = _params.bailout_squared;
    fractal_params.julia_const = _params.julia_const;

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
}

unsigned char *Calculation_handler::get_result_pointer()
{
    return store.get_data_pointer();
}