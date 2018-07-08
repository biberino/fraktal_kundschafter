#ifndef TYPED_GUARD_BLA
#define TYPED_GUARD_BLA

#include <complex>
#include <vector>

struct Resolution_info
{
    int x;
    int y;
};

struct Pixel
{
    int x;
    int y;
};

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct Color_info
{
    Pixel pixel;
    Color color;
};

struct Axis_info
{
    double x_min;
    double x_max;

    double y_min;
    double y_max;
};

#endif // !TYPED_GUARD_BLA
