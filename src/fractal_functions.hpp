#ifndef FRAC_FUN_GUARD_1212
#define FRAC_FUN_GUARD_1212

#include <complex>
#include "types.hpp"
#include "mediant.hpp"

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
    return (std::pow(z, std::conj(z)) + c + complex_type(gen, 0));
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

inline complex_type fractal_4(complex_type z, complex_type c, double gen)
{
    return ((std::pow(z * c, 2) + complex_type(1, 0)) / (z + c));
}

inline complex_type fractal_5(complex_type z, complex_type c, double gen)
{
    return (std::sqrt(std::pow(z * c, 2) + complex_type(1, 0)) / (z + c));
}

inline complex_type fractal_6(complex_type z, complex_type c, double gen)
{
    return (std::pow(z * std::conj(z), 2) + c);
}

inline complex_type fractal_7(complex_type z, complex_type c, double gen)
{
    return (std::sqrt(std::pow(z * std::conj(z), 2) + complex_type(1, 0)) + c);
}

inline complex_type fractal_8(complex_type z, complex_type c, double gen)
{
    complex_type a = z;
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0);
}

inline complex_type fractal_9(complex_type z, complex_type c, double gen)
{
    complex_type a = z;
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) + c;
}

inline complex_type fractal_10(complex_type z, complex_type c, double gen)
{
    complex_type a = z * z;
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0);
}

inline complex_type fractal_11(complex_type z, complex_type c, double gen)
{
    complex_type a = z * z;
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) + c;
}

inline complex_type fractal_12(complex_type z, complex_type c, double gen)
{
    complex_type a = z * std::conj(z);
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0);
}

inline complex_type fractal_13(complex_type z, complex_type c, double gen)
{
    complex_type a = z * std::conj(z);
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) + c;
}

inline complex_type fractal_14(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, std::conj(z));
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0);
}

inline complex_type fractal_15(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, std::conj(z));
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) + c;
}

inline complex_type fractal_16(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, z);
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0);
}

inline complex_type fractal_17(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, z);
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) + c + gen;
}

// ^mehr von der sorte ausprobieren

inline complex_type fractal_18(complex_type z, complex_type c, double gen)
{
    return ((z + c) / (z * c) + complex_type(gen, 0));
}

inline complex_type fractal_19(complex_type z, complex_type c, double gen)
{
    return (calc_complex_mediant(std::pow(z, 2), c, 2147483647));
}

inline complex_type fractal_20(complex_type z, complex_type c, double gen)
{
    return (calc_complex_mediant(z * std::conj(z), c, 2147483647));
}

inline complex_type fractal_21(complex_type z, complex_type c, double gen)
{
    return ((z * c) / (calc_complex_mediant(z, c, 2147483647))) + complex_type(gen, 0);
}

inline complex_type fractal_22(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, z);
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) - c + gen;
}

inline complex_type fractal_23(complex_type z, complex_type c, double gen)
{
    complex_type a = z;
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) - c + gen;
}

inline complex_type fractal_24(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, std::conj(z));
    complex_type b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + complex_type(1, 0)) / (std::abs(a + b))))) + complex_type(gen, 0) - c + gen;
}

inline complex_type fractal_25(complex_type z, complex_type c, double gen)
{
    complex_type a = z;
    complex_type b = c;
    return ((a + b) * gen - (a * b));
}

inline complex_type fractal_26(complex_type z, complex_type c, double gen)
{
    complex_type a = z * z;
    complex_type b = c;
    return ((a + b) * gen - (a * b));
}

inline complex_type fractal_27(complex_type z, complex_type c, double gen)
{
    complex_type a = z * std::conj(z);
    complex_type b = c;
    return ((a + b) * gen - (a * b));
}

inline complex_type fractal_28(complex_type z, complex_type c, double gen)
{
    complex_type a = std::pow(z, std::conj(z));
    complex_type b = c;
    return ((a + b) * gen - (a * b));
}

inline complex_type fractal_29(complex_type z, complex_type c, double gen)
{
    return ((std::pow(z, std::conj(z)) - complex_type(1, 0)) * c) / ((std::pow(z, std::conj(z)) - complex_type(1, 0)) + c) + complex_type(gen, 0);
}

inline complex_type mandelbrot_4(complex_type z, complex_type c, double gen)
{
    return ((std::pow(z, 4)) + c);
}

inline complex_type mandelbrot_5(complex_type z, complex_type c, double gen)
{
    return ((std::pow(z, 5)) + c);
}

inline complex_type mandelbrot_konj_2(complex_type z, complex_type c, double gen)
{
    return ((z * z * std::conj(z) + c));
}

inline complex_type mandelbrot_konj_3(complex_type z, complex_type c, double gen)
{
    return ((z * std::conj(z) * std::conj(z) + c));
}

inline complex_type mandelbrot_konj_4(complex_type z, complex_type c, double gen)
{
    return ((z * z * std::conj(z) - c));
}

inline complex_type mandelbrot_konj_5(complex_type z, complex_type c, double gen)
{
    return ((z * std::conj(z) * std::conj(z) - c));
}

inline complex_type versuch_1(complex_type z, complex_type c, double gen)
{
    return (std::pow(z * z, std::conj(z)) + c + complex_type(gen, 0));
}

inline complex_type binet(complex_type z, complex_type c, double gen)
{
    const double golden_ration = 1.16180339887;
    return (((std::pow(golden_ration, z) - std::pow((-1 / golden_ration), z)) / std::sqrt(5)) + c);
}

inline complex_type binet_hoch_c(complex_type z, complex_type c, double gen)
{
    const double golden_ration = 1.16180339887;
    return (((std::pow(golden_ration, c) - std::pow((-1 / golden_ration), c)) / std::sqrt(5)) + z);
}

inline complex_type binet_mixed_1(complex_type z, complex_type c, double gen)
{
    const double golden_ration = 1.16180339887;
    return (((std::pow(golden_ration, z) - std::pow((-1 / golden_ration), c)) / std::sqrt(5)) + c);
}

inline complex_type binet_mixed_2(complex_type z, complex_type c, double gen)
{
    const double golden_ration = 1.16180339887;
    return (((std::pow(golden_ration, c) - std::pow((-1 / golden_ration), z)) / std::sqrt(5)) + c);
}



#endif // !FRAC_FUN_GUARD_!1212
