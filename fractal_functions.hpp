#ifndef FRAC_FUN_GUARD_1212
#define FRAC_FUN_GUARD_1212

#include <complex>

inline std::complex<float> mandelbrot(std::complex<float> z, std::complex<float> c)
{
    return ((z * z) + c);
}

inline std::complex<float> mandelbrot_konj(std::complex<float> z, std::complex<float> c)
{
    return ((z * std::conj(z) + c));
}

inline std::complex<float> kondensator_1(std::complex<float> z, std::complex<float> c)
{
    return (z * c) / (z + c);
}

inline std::complex<float> kondensator_3(std::complex<float> z, std::complex<float> c)
{
    std::complex<float> speedup = z * std::conj(z);
    return (speedup * c) / (speedup + c);
}

#endif // !FRAC_FUN_GUARD_!1212
