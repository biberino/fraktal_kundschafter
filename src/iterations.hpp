#ifndef ITER_GUARD_FUNC
#define ITER_GUARD_FUNC


#include <complex>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <string>
#include <set>
#include <unordered_map>
#include <cstdint>
#include <string.h>

#include "types.hpp"



inline std::string float_to_string(float f)
{
    uint32_t ui;
    memcpy(&ui, &f, sizeof(float));
    return std::to_string(ui & 0xFFFFF000);

}

inline Color normal_iter(std::complex<float> point, int max_iter,
                         fractal_callback fractal_func, color_callback color_func,
                         std::complex<float> julia_const,
                         float bailout_squared, float koppl)
{

    std::complex<float> z(0, 0);
    std::complex<float> c = point;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = float_to_string(z.real()) +
                               float_to_string(z.imag());

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            return color_func(jump_counter, true, j, z, max_iter);
        }

        hash_table[z_string] = j;

        z = fractal_func(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            return color_func(0, false, j, z, max_iter);
        }
    }

    return color_func(0, true, max_iter, z, max_iter);
}

/**
inline Color julia_iter(std::complex<float> point)
{

    std::complex<float> z = point;
    std::complex<float> c = julia_const;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = float_to_string(z.real(), float_compare_precision) +
                               float_to_string(z.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            return colorize(jump_counter, true, j, z, max_iter);
        }

        hash_table[z_string] = j;

        z = fractal_func(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            return colorize(0, false, j, z, max_iter);
        }
    }

    return colorize(0, true, max_iter, z, max_iter);
}

inline Color normal_iter_zw(std::complex<float> point)
{

    std::complex<float> z1(0, 0);
    std::complex<float> z2(0, 0);

    std::complex<float> c = point;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = float_to_string(z1.real(), float_compare_precision) +
                               float_to_string(z1.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben
            return colorize(jump_counter, true, j, z1, max_iter);
        }

        hash_table[z_string] = j;

        std::complex<float> buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return colorize(0, false, j, z1, max_iter);
        }
    }

    return colorize(0, true, max_iter, z1, max_iter);
}

inline Color julia_iter_zw(std::complex<float> point)
{

    std::complex<float> z1(point);
    std::complex<float> z2(point);

    std::complex<float> c = julia_const;

    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = float_to_string(z1.real(), float_compare_precision) +
                               float_to_string(z1.imag(), float_compare_precision) +
                               float_to_string(z2.real(), float_compare_precision) +
                               float_to_string(z2.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            //Color temp = color_table[jump_counter];
            //return Color(jump_counter * 20, (abs(z1 + z2) / 4.0f) * 255.0f, ((float)j / (float)max_iter) * 255.0f);
            return colorize_zw(jump_counter, true, j, z1, z2, max_iter);
            //temp.b = ((float)j / (float)max_iter) * 255.0f;
            //return temp;
        }

        hash_table[z_string] = j;

        std::complex<float> buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return colorize_zw(0, false, j, z1, z2, max_iter);
        }
    }

    return colorize_zw(0, true, max_iter, z1, z2, max_iter);
}

**/

#endif // !FRAC_FUN_GUARD_!1212