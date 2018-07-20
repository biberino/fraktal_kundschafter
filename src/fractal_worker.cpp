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

inline std::complex<float> Fractal_worker::XY_to_complex(Pixel pixel)
{
    float ca = (float)pixel.x * (_x_diff / (float)_params.res.x) + (float)_params.axis.x_min;
    float cb = ((-1.0f * (float)pixel.y + (float)_params.res.y) * ((float)_y_diff / (float)_params.res.y) + (float)_params.axis.y_min);

    return std::complex<float>(ca, cb);
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
                                                     _params.koppl);
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