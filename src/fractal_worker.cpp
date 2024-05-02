#include "fractal_worker.hpp"

Fractal_worker::Fractal_worker(/* args */)
{
}

Fractal_worker::~Fractal_worker()
{
}

void Fractal_worker::set_params(Fractal_params params)
{
    _params = params;
    _x_diff = params.axis.x_max - params.axis.x_min;
    _y_diff = params.axis.y_max - params.axis.y_min;
}

inline complex_type Fractal_worker::XY_to_complex(Pixel pixel)
{
    datatype ca = (datatype)pixel.x * (_x_diff / (datatype)_params.res.x) + (datatype)_params.axis.x_min;
    datatype cb = ((-1.0f * (datatype)pixel.y + (datatype)_params.res.y) * ((datatype)_y_diff / (datatype)_params.res.y) + (datatype)_params.axis.y_min);

    return complex_type(ca, cb);
}

void Fractal_worker::start()
{
    _col_info_vec.clear();
    while (1)
    {

        std::vector<Pixel> work = _params.work_dis->request_work(_params.work_size);

        if (work.size() == 0)
        {
            return;
        }

        std::vector<Color_info> colors;
        for (auto p : work)
        {
            Color_info color;
            color.pixel = p;
            color.color = _params.iteration_function(XY_to_complex(p),
                                                     _params.max_iter,
                                                     _params.fractal_function,
                                                     _params.color_function,
                                                     _params.julia_const,
                                                     _params.bailout_squared,
                                                     _params.koppl,
                                                     _params.gen_param,
                                                     nullptr);
            colors.push_back(color);
        }
        _params.store->put(&colors);

        /**
        for (auto p : work)
        {
            Color_info color;
            color.pixel = p;
            color.color = _params.iteration_function(XY_to_complex(p));
            _col_info_vec.push_back(color);
        }
        **/
    }
}