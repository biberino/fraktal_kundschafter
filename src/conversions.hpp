#ifndef __CONVERSIONS_HPP__
#define __CONVERSIONS_HPP__

#include "types.hpp"

complex_type Pixel_to_Koord(Pixel p, Axis_info axis, Resolution_info res);
Pixel Koord_to_Pixel(complex_type c, Axis_info axis, Resolution_info res);

#endif // __CONVERSIONS_HPP__
