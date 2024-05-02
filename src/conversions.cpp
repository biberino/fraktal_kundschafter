#include "conversions.hpp"

complex_type Pixel_to_Koord(Pixel p, Axis_info axis, Resolution_info res)
{
    datatype x_diff = axis.x_max - axis.x_min;
    datatype y_diff = axis.y_max - axis.y_min;

    datatype ca = (datatype)p.x * (x_diff / (datatype)res.x) + (datatype)axis.x_min;
    datatype cb = ((-1.0f * (datatype)p.y + (datatype)res.y) * ((datatype)y_diff / (datatype)res.y) + (datatype)axis.y_min);

    return complex_type(ca, cb);
}
Pixel Koord_to_Pixel(complex_type c, Axis_info axis, Resolution_info res)
{
    datatype x_diff = axis.x_max - axis.x_min;
    datatype y_diff = axis.y_max - axis.y_min;

    Pixel p;
    p.x = ((c.real() - (datatype)axis.x_min) / (x_diff / (datatype)res.x));
    p.y = (-1.0f * ((c.imag() - axis.y_min) * ((datatype)res.y / y_diff) - (datatype)res.y));
    return p;
}