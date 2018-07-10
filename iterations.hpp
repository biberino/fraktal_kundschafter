#ifndef ITER_GUARD_FUNC
#define ITER_GUARD_FUNC

#include "types.hpp"
#include "colors.hpp"
#include <complex>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <string>
#include <set>
#include <unordered_map>

int max_iter = 50;
float koppl = 0.1f;
float bailout_squared = 4.0f;
int float_compare_precision = 5;
std::complex<float> (*fractal_func)(std::complex<float>, std::complex<float>) = kondensator_3;
std::complex<float> julia_const(-1, 0);

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

inline std::string float_to_string(float f, int precision)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(precision) << f;
    return stream.str();
}

inline Color normal_iter(std::complex<float> point)
{

    std::complex<float> z(0, 0);
    std::complex<float> c = point;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = float_to_string(z.real(), float_compare_precision) +
                               " " +
                               float_to_string(z.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            if (jump_counter < MAX_COLORS)
            {
                Color temp = color_table[jump_counter];
                temp.b = ((float)j / (float)max_iter) * 255.0f;
                return temp;
            }
            unsigned char grauwert = ((float)j / (float)max_iter) * 255.0f;
            return Color(255, 255, 255);
        }

        hash_table[z_string] = j;

        z = fractal_func(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            unsigned char temp = (unsigned char)((float)j / (float)max_iter) * 255.0f;

            return Color(temp, temp, temp);
        }
    }

    return Color(0, 40, 125);
}

inline Color julia_iter(std::complex<float> point)
{

    std::complex<float> z = point;
    std::complex<float> c = julia_const;
    //für schnelle lookups
    std::unordered_map<std::string, int> hash_table;

    for (size_t j = 0; j < max_iter; j++)
    {

        std::string z_string = float_to_string(z.real(), float_compare_precision) +
                               " " +
                               float_to_string(z.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            if (jump_counter < MAX_COLORS)
            {
                Color temp = color_table[jump_counter];
                temp.b = ((float)j / (float)max_iter) * 255.0f;
                return temp;
            }
            unsigned char grauwert = ((float)j / (float)max_iter) * 255.0f;
            return Color(255, 255, 255);
        }

        hash_table[z_string] = j;

        z = fractal_func(z, c);

        if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared)
        {
            unsigned char temp = (unsigned char)((float)j / (float)max_iter) * 255.0f;

            return Color(temp, temp, temp);
        }
    }

    return Color(0, 40, 125);
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
                               " " +
                               float_to_string(z1.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            if (jump_counter < MAX_COLORS)
            {
                Color temp = color_table[jump_counter];
                temp.b = ((float)j / (float)max_iter) * 255.0f;
                return temp;
            }
            unsigned char grauwert = ((float)j / (float)max_iter) * 255.0f;
            return Color(255, 255, 255);
        }

        hash_table[z_string] = j;

        std::complex<float> buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) ||
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            unsigned char temp = (unsigned char)((float)j / (float)max_iter) * 255.0f;

            return Color(temp, temp, temp);
        }
    }

    return Color(0, 40, 125);
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
                               " " +
                               float_to_string(z1.imag(), float_compare_precision);

        if (hash_table.find(z_string) != hash_table.end())
        {
            //wert bereits in hash map
            int jump_counter = j - hash_table[z_string];
            //hier nach anzahl sprügne einfärben

            if (jump_counter < MAX_COLORS)
            {
                //Color temp = color_table[jump_counter];
                return Color(jump_counter * 20, (abs(z1+z2) / 4.0f)*255.0f, ((float)j / (float)max_iter) * 255.0f);
                //temp.b = ((float)j / (float)max_iter) * 255.0f;
                //return temp;
            }
            unsigned char grauwert = ((float)j / (float)max_iter) * 255.0f;
            return Color(255, 255, 255);
        }

        hash_table[z_string] = j;

        std::complex<float> buffer(z1);
        z1 = fractal_func(z1, c) + (z2 * koppl);

        z2 = fractal_func(z2, c) - (buffer * koppl);

        if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) > bailout_squared) ||
            (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) > bailout_squared))
        {
            unsigned char temp = (unsigned char)((float)j / (float)max_iter) * 255.0f;

            return Color(temp, temp, temp);
        }
    }

    return Color(250, 40, 125);
}

#endif // !FRAC_FUN_GUARD_!1212