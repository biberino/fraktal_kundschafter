#ifndef FRAC_FUN_GUARD_1212
#define FRAC_FUN_GUARD_1212

#include <complex>
#include "types.hpp"

inline complex_type mandelbrot(complex_type z, complex_type c)
{
    return ((z * z) + c);
}

inline complex_type mandelbrot_konj(complex_type z, complex_type c)
{
    return ((z * std::conj(z) + c));
}

inline complex_type mandelbrot_konj_minus_1(complex_type z, complex_type c)
{
    return (std::pow(z, std::conj(z)) - complex_type(1, 0));
}

inline complex_type mandelbrot_3(complex_type z, complex_type c)
{
    return ((z * z * z) + c);
}

inline complex_type kondensator_1(complex_type z, complex_type c)
{
    return (z * c) / (z + c);
}

inline complex_type kondensator_2(complex_type z, complex_type c)
{
    return ((z * c) / (z + c)) - complex_type(1, 0);
}

inline complex_type kondensator_3(complex_type z, complex_type c)
{
    return ((z * c) / (z + c)) + complex_type(1, 0);
}

inline complex_type kondensator_4(complex_type z, complex_type c)
{
    complex_type speedup = z * z;
    return (speedup * c) / (speedup + c);
}

inline complex_type kondensator_5(complex_type z, complex_type c)
{
    complex_type speedup = z * std::conj(z);
    return (speedup * c) / (speedup + c);
}

#endif // !FRAC_FUN_GUARD_!1212
