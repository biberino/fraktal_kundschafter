#ifndef FRAC_FUN_GUARD_1212
#define FRAC_FUN_GUARD_1212

#include <complex>
#include "types.hpp"

inline complex_type mandelbrot(complex_type z, complex_type c, double gen)
{
    return ((z * z) + c);
}

inline complex_type mandelbrot_konj(complex_type z, complex_type c, double gen)
{
    return ((z * std::conj(z) + c));
}

inline complex_type mandelbrot_konj_plus_gen(complex_type z, complex_type c, double gen)
{
    return (std::pow(z, std::conj(z)) + complex_type(gen, 0));
}

inline complex_type mandelbrot_3(complex_type z, complex_type c, double gen)
{
    return ((z * z * z) + c);
}

inline complex_type kondensator_plus_gen(complex_type z, complex_type c, double gen)
{
    return ((z * c) / (z + c)) + complex_type(gen, 0);
}

inline complex_type kondensator_4(complex_type z, complex_type c, double gen)
{
    complex_type speedup = z * z;
    return (speedup * c) / (speedup + c);
}

inline complex_type kondensator_5(complex_type z, complex_type c, double gen)
{
    complex_type speedup = z * std::conj(z);
    return (speedup * c) / (speedup + c);
}

inline complex_type e_1(complex_type z, complex_type c, double gen)
{
    return (std::exp(z) + c);
}

inline complex_type e_1_1(complex_type z, complex_type c, double gen)
{
    return (std::exp(z) + complex_type(gen, 0));
}

inline complex_type e_2(complex_type z, complex_type c, double gen)
{
    return (std::pow(std::exp(z), std::exp(std::conj(z))) + complex_type(gen, 0));
}

inline complex_type e_3(complex_type z, complex_type c, double gen)
{
    return (std::pow(std::exp(z), std::exp(std::conj(z))) + c);
}

inline complex_type e_4(complex_type z, complex_type c, double gen)
{
    return (std::exp(std::pow(z, std::conj(z))) + complex_type(gen, 0));
}

inline complex_type e_5(complex_type z, complex_type c, double gen)
{
    return (std::exp(std::pow(z, std::conj(z))) + c);
}

/** credits to http://www.lifesmith.com/formulas.html **/

inline complex_type lifesmith_1(complex_type z, complex_type c, double gen)
{
    //(Z^2 + C) / (Z - C)
    return (z * z + c) / (z - c);
}

inline complex_type lifesmith_1_1(complex_type z, complex_type c, double gen)
{
    //(Z*Z* + C) / (Z - C)
    return (z * std::conj(z) + c) / (z - c);
}

inline complex_type lifesmith_1_2(complex_type z, complex_type c, double gen)
{
    //(Z*Z* + C) / (Z* - C)
    return (z * std::conj(z) + c) / (std::conj(z) - c);
}

inline complex_type lifesmith_2(complex_type z, complex_type c, double gen)
{
    //Z^2 - Z + C
    return (((z * z) - z) + c);
}

inline complex_type lifesmith_2_1(complex_type z, complex_type c, double gen)
{
    //Z*Z* - Z + C
    return (((z * std::conj(z)) - z) + c);
}

inline complex_type lifesmith_2_2(complex_type z, complex_type c, double gen)
{
    //Z*Z* - Z* + C
    return (((z * std::conj(z)) - (std::conj(z))) + c);
}

inline complex_type lifesmith_3(complex_type z, complex_type c, double gen)
{
    //Z * exp(-Z) + C
    return (((z * std::exp(-z)) + c));
}

inline complex_type lifesmith_3_1(complex_type z, complex_type c, double gen)
{
    //Z * exp(Z*) + C
    return (((z * std::exp(std::conj(z))) + c));
}

inline complex_type lifesmith_4(complex_type z, complex_type c, double gen)
{
    //Z^3 / (1 + CZ^2)
    return (pow(z, 3) / (complex_type(1, 0) + c * pow(z, 2)));
}

inline complex_type lifesmith_5(complex_type z, complex_type c, double gen)
{
    ////Z^2sin(Re Z) + CZcos(Im Z) + C
    return (pow(z, 2) * sin(z.real()) + c * cos(z.imag()) + c);
}

inline complex_type schaedel_exp(complex_type z, complex_type c, double gen)
{
    return std::exp(std::pow(z, std::conj(z)) + complex_type(gen, 0));
}

inline complex_type fractal_1(complex_type z, complex_type c, double gen)
{
    return (std::pow(z, std::conj(z)) + complex_type(gen, 0)) + ((z * c) / (z + c));
}

inline complex_type fractal_2(complex_type z, complex_type c, double gen)
{
    return (std::pow(z, 2) / (complex_type(2, 0) * z)) + complex_type(gen, 0);
}

inline complex_type fractal_3(complex_type z, complex_type c, double gen)
{
    return (std::pow(z, 2) / (complex_type(2, 0) * z)) + c;
}

#endif // !FRAC_FUN_GUARD_!1212
