#ifndef TYPED_GUARD_BLA
#define TYPED_GUARD_BLA

#include <complex>
#include <vector>
#include <string>
#include <boost/compute/types/complex.hpp>

using datatype = float;
using complex_type = std::complex<datatype>;

struct Resolution_info
{
    int x;
    int y;
};

struct Pixel
{
    int x;
    int y;
    Pixel(const complex_type &c)
    {
        x = (int)c.real();
        y = (int)c.imag();
    }
    Pixel()
    {
    }
};

struct Fraction
{
    long int z;
    long int n;
    Fraction(long int za, long int ne)
    {
        n = ne;
        z = za;
    }
};

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color(unsigned char rp, unsigned char gp, unsigned char bp)
    {
        r = rp;
        g = gp;
        b = bp;
    }
    Color() {}
    Color(int hex_value)
    {
        r = ((hex_value >> 16) & 0xFF); // Extract the RR byte
        g = ((hex_value >> 8) & 0xFF);  // Extract the GG byte
        b = ((hex_value)&0xFF);
    }
};

struct Color_info
{
    Pixel pixel;
    Color color;
};

struct Axis_info
{
    datatype x_min;
    datatype x_max;

    datatype y_min;
    datatype y_max;
};

struct Parameters_Info
{
    int max_iter;
    datatype koppl;
    Resolution_info res;
    datatype gen_param;
    datatype bailout;
    complex_type startpoint;
};

struct Point_trail
{
    complex_type *points;
    int valid_count;
};

using color_callback = Color (*)(int, bool, int, complex_type, complex_type, int, datatype);
using fractal_callback = complex_type (*)(complex_type, complex_type, datatype);
using iter_callback = Color (*)(complex_type, int,
                                fractal_callback, color_callback,
                                complex_type,
                                datatype, datatype, datatype,
                                Point_trail *);

struct Combo_entry_fractal
{
    std::string description;
    std::string formula;
    fractal_callback callback;
    Combo_entry_fractal(std::string d, std::string f,
                        fractal_callback c)
    {
        description = d;
        formula = f;
        callback = c;
    }
};

struct Combo_entry_iter
{
    std::string description;
    std::string short_description;
    iter_callback callback;
    Combo_entry_iter(std::string d, std::string f,
                     iter_callback c)
    {
        description = d;
        short_description = f;
        callback = c;
    }
};

struct Combo_entry_color
{
    std::string description;
    std::string short_description;
    color_callback callback;
    Combo_entry_color(std::string d, std::string f,
                      color_callback c)
    {
        description = d;
        short_description = f;
        callback = c;
    }
};

struct Combo_entries
{
    std::vector<Combo_entry_fractal> fractal_entries;
    std::vector<Combo_entry_iter> iter_entries;
    std::vector<Combo_entry_color> color_entries;
};

#endif // !TYPED_GUARD_BLA
