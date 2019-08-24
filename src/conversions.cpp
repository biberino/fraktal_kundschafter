#include "conversions.hpp"

complex_type Pixel_to_Koord(Pixel p, Axis_info axis, Resolution_info res)
{
    double x_diff = axis.x_max - axis.x_min;
    double y_diff = axis.y_max - axis.y_min;

    double ca = (double)p.x * (x_diff / (double)res.x) + (double)axis.x_min;
    double cb = ((-1.0f * (double)p.y + (double)res.y) * ((double)y_diff / (double)res.y) + (double)axis.y_min);

    return complex_type(ca, cb);
}
Pixel Koord_to_Pixel(complex_type c, Axis_info axis, Resolution_info res)
{
    double x_diff = axis.x_max - axis.x_min;
    double y_diff = axis.y_max - axis.y_min;

    Pixel p;
    p.x = ((c.real() - (double)axis.x_min) / (x_diff / (double)res.x));
    p.y = (-1.0f * ((c.imag() - axis.y_min) * ((double)res.y / y_diff) - (double)res.y));
    return p;
}