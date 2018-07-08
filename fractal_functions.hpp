#ifndef FRAC_FUN_GUARD_1212
#define FRAC_FUN_GUARD_1212

#include <complex>

std::complex<float> mandelbrot(std::complex<float> z, std::complex<float> c)
{
    return ((z * z) + c);
}

#endif // !FRAC_FUN_GUARD_!1212
