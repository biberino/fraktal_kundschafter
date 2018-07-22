#ifndef COLORS_GUARD_123
#define COLORS_GUARD_123

#include "types.hpp"

const int MAX_COLORS = 14;
Color color_table[] = {
    Color(0x55E8F8),
    Color(0x03F472),
    Color(0xD6F403),
    Color(0xAF8B66),
    Color(0x86212E),
    Color(0xF74E63),
    Color(0xF74EC3),
    Color(0x5440D5),
    Color(0x585378),
    Color(0x476F9B),
    Color(0x386356),
    Color(0x7CC8B1),
    Color(0xD8D63F),
    Color(0x783D68)};

inline Color color_gradient_linear(double start, double end, double point)
{
    double distance = start + end;
    double section_length = distance / 5.0f;
    double section = (point - start) / section_length;
    int section_int = (int)section;
    double section_percentage = section - (double)section_int;

    if (section_int == 0)
    {
        //punkt in section 0
        return Color(255, section_percentage * 255.0f, 0);
    }

    if (section_int == 1)
    {
        return Color(255.0f - (section_percentage * 255.0f), 255, 0);
    }

    if (section_int == 2)
    {
        return Color(0, 255, section_percentage * 255.0f);
    }

    if (section_int == 3)
    {
        return Color(0, 255.0f - (section_percentage * 255.0f), 255);
    }

    //section 4
    return Color(section_percentage * 255.0f, 0, 255);
}

inline Color colorize(int jumps, bool in_set, int num_itertaions,
                      complex_type end_point1,
                      complex_type end_point2, int max_iter,
                      double bailout)
{

    if (!in_set)
    {
        unsigned char temp = (std::log(num_itertaions) / std::log(max_iter)) * 255.0f;

        return Color(temp, temp, temp);
    }

    if (jumps == 0)
    {
        double dist = abs(end_point1);
        //return Color(255, 0, 0); //test
        return Color((dist / 2.0f) * 255.0f, 40, 125);
    }

    if (jumps < MAX_COLORS)
    {
        Color temp = color_table[jumps];
        //temp.b = ((double)num_itertaions / (double)max_iter) * 255.0f;
        return temp;
    }
    unsigned char grauwert = ((double)num_itertaions / (double)max_iter) * 255.0f;
    return Color(0, 0, 255);
}

inline Color colorize_simple(int jumps, bool in_set, int num_itertaions,
                             complex_type end_point1,
                             complex_type end_point2, int max_iter,
                             double bailout)
{

    if (!in_set)
    {
        return Color(0, 0, 0);
    }

    return Color(0, 230, 105);
}

inline Color colorize_distance_linear_gradient(int jumps, bool in_set, int num_itertaions,
                                               complex_type end_point1,
                                               complex_type end_point2, int max_iter,
                                               double bailout)
{

    if (!in_set)
    {
        unsigned char temp = (std::log(num_itertaions) / std::log(max_iter)) * 255.0f;

        return Color(temp, temp, temp);
    }

    return color_gradient_linear(0.0f, 2.0f*bailout, abs(end_point1 + end_point2));
}


#endif // !COLORS_GUARD