#ifndef COLORS_GUARD
#define COLORS_GUARD

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

inline Color colorize(int jumps, bool in_set, int num_itertaions,
                      std::complex<float> end_point, int max_iter)
{

    if (!in_set)
    {
        unsigned char temp = (std::log(num_itertaions) / std::log(max_iter)) * 255.0f;

        return Color(temp, temp, temp);
    }

    if (jumps == 0)
    {
        float dist = abs(end_point);
        //return Color(255, 0, 0); //test
        return Color((dist / 2.0f) * 255.0f, 40, 125);
    }

    if (jumps < MAX_COLORS)
    {
        Color temp = color_table[jumps];
        //temp.b = ((float)num_itertaions / (float)max_iter) * 255.0f;
        return temp;
    }
    unsigned char grauwert = ((float)num_itertaions / (float)max_iter) * 255.0f;
    return Color(0, 0, 255);
}

inline Color colorize_zw(int jumps, bool in_set, int num_itertaions,
                         std::complex<float> end_point_1,
                         std::complex<float> end_point_2, int max_iter)
{

    if (!in_set)
    {
        unsigned char temp = (std::log(num_itertaions) / std::log(max_iter)) * 255.0f;

        return Color(temp, temp, temp);
    }
    /**
    if (jumps == 0)
    {
        float dist = abs(end_point_1);
        //return Color(255, 0, 0); //test
        return Color((dist / 2.0f) * 255.0f, 40, 125);
    }
    **/

    return Color((abs(end_point_1) / 2.0f) * 255.0f, (abs(end_point_2) / 2.0f) * 255.0f, std::log((float)num_itertaions) / std::log((float)max_iter) * 255.0f);

    if (jumps < MAX_COLORS)
    {
        Color temp = color_table[jumps];
        //temp.b = ((float)num_itertaions / (float)max_iter) * 255.0f;
        return temp;
    }
    unsigned char grauwert = ((float)num_itertaions / (float)max_iter) * 255.0f;
    return Color(0, 0, 255);
}

#endif // !COLORS_GUARD