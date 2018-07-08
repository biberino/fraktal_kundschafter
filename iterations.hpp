#ifndef ITER_GUARD_FUNC
#define ITER_GUARD_FUNC

#include "types.hpp"
#include <complex>

int max_iter = 500;
float koppl = 0.5f;
float bailout_squared = 4.0f;

inline bool isComplexOK(std::complex<float> number)
{

    if (number.real() < std::numeric_limits<float>::max() && number.real() > (-1 * std::numeric_limits<float>::max()))
    {
        if (number.imag() < std::numeric_limits<float>::max() && number.imag() > (-1 * std::numeric_limits<float>::max()))
        {
            return true;
        }
    }
    return false;
}


Color normal_iter(std::complex<float> point)
{

    Color col;
    std::complex<float> z(0, 0);
    std::complex<float> c = point;
    for (size_t j = 0; j < max_iter; j++)
    {

        z = mandelbrot(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            col.r = j;
            col.g = j;
            col.b = j;

            return col;
        }
    }

    col.r = 0;
    col.g = 40;
    col.b = 125;

    return col;
}

#endif // !FRAC_FUN_GUARD_!1212