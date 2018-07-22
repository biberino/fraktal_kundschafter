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
#include <iostream>

#include "types.hpp"

std::string debug;
bool debug_active = true;

inline std::string double_to_string(double f)
{
    uint64_t ui;
    memcpy(&ui, &f, sizeof(double));
    return std::to_string(ui & 0xFFFFFFFFFF000000);
}

inline Color normal_iter(complex_type point, int max_iter,
                         fractal_callback fractal_func, color_callback color_func,
                         complex_type julia_const,
                         double bailout_squared, double koppl)
{

    complex_type z(0, 0);
    complex_type c = point;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = double_to_string(z.real()) +
                               double_to_string(z.imag());

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            return color_func(jump_counter, true, j, z, complex_type(0, 0), max_iter, sqrt(bailout_squared));
        }

        hash_table[z_string] = j;

        z = fractal_func(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            return color_func(0, false, j, z, complex_type(0, 0), max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z, complex_type(0, 0), max_iter, sqrt(bailout_squared));
}

inline Color julia_iter(complex_type point, int max_iter,
                        fractal_callback fractal_func, color_callback color_func,
                        complex_type julia_const,
                        double bailout_squared, double koppl)
{

    complex_type z = point;
    complex_type c = julia_const;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = double_to_string(z.real()) +
                               double_to_string(z.imag());

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            return color_func(jump_counter, true, j, z, complex_type(0, 0), max_iter, sqrt(bailout_squared));
        }

        hash_table[z_string] = j;

        z = fractal_func(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            return color_func(0, false, j, z, complex_type(0, 0), max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z, complex_type(0, 0), max_iter, sqrt(bailout_squared));
}

inline Color normal_iter_zw(complex_type point, int max_iter,
                            fractal_callback fractal_func, color_callback color_func,
                            complex_type julia_const,
                            double bailout_squared, double koppl)
{
    if (debug_active)
    {
        std::cout << "ZWILLING" << max_iter << " " << koppl << " " << bailout_squared << '\n';
        debug_active = false;
    }

    complex_type z1(0, 0);
    complex_type z2(0, 0);

    complex_type c = point;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = double_to_string(z1.real()) +
                               double_to_string(z1.imag()) +
                               double_to_string(z2.real()) +
                               double_to_string(z2.imag());

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben
            return color_func(jump_counter, true, j, z1, z2, max_iter, sqrt(bailout_squared));
        }

        hash_table[z_string] = j;

        complex_type buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color normal_iter_zw_no_tracking(complex_type point, int max_iter,
                            fractal_callback fractal_func, color_callback color_func,
                            complex_type julia_const,
                            double bailout_squared, double koppl)
{


    complex_type z1(0, 0);
    complex_type z2(0, 0);

    complex_type c = point;
  

    for (size_t j = 0; j < max_iter; j++)
    {


        complex_type buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color julia_iter_zw(complex_type point, int max_iter,
                           fractal_callback fractal_func, color_callback color_func,
                           complex_type julia_const,
                           double bailout_squared, double koppl)
{

    complex_type z1(point);
    complex_type z2(point);

    complex_type c = julia_const;

    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = double_to_string(z1.real()) +
                               double_to_string(z1.imag()) +
                               double_to_string(z2.real()) +
                               double_to_string(z2.imag());

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            //Color temp = color_table[jump_counter];
            //return Color(jump_counter * 20, (abs(z1 + z2) / 4.0f) * 255.0f, ((double)j / (double)max_iter) * 255.0f);
            return color_func(jump_counter, true, j, z1, z2, max_iter, sqrt(bailout_squared));
            //temp.b = ((double)j / (double)max_iter) * 255.0f;
            //return temp;
        }

        hash_table[z_string] = j;

        complex_type buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color julia_iter_zw_no_tracking(complex_type point, int max_iter,
                                       fractal_callback fractal_func, color_callback color_func,
                                       complex_type julia_const,
                                       double bailout_squared, double koppl)
{

    complex_type z1(point);
    complex_type z2(point);

    complex_type c = julia_const;

    for (size_t j = 0; j < max_iter; j++)
    {

        complex_type buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color julia_iter_test_zw_no_tracking(complex_type point, int max_iter,
                                       fractal_callback fractal_func, color_callback color_func,
                                       complex_type julia_const,
                                       double bailout_squared, double koppl)
{

    complex_type z1(point);
    complex_type z2(point);

    complex_type c = julia_const;

    for (size_t j = 0; j < max_iter; j++)
    {

        complex_type buffer(z1);
        z1 = fractal_func(z1, c) - (koppl* z2);

        z2 = fractal_func(z2, c) - (z1 * koppl);


        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) &&
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
        }
    }

    return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

#endif // !FRAC_FUN_GUARD_!1212