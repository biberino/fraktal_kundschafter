#ifndef TYPED_GUARD_BLA
#define TYPED_GUARD_BLA

#include <complex>
#include <vector>
#include <string>

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
    double x_min;
    double x_max;

    double y_min;
    double y_max;
};

struct Parameters_Info
{
    int max_iter;
    float koppl;
    Resolution_info res;
};

using color_callback = Color (*)(int, bool, int, std::complex<float>, int);
using fractal_callback = std::complex<float> (*)(std::complex<float>, std::complex<float>);
using iter_callback = Color (*)(std::complex<float>, int,
                                fractal_callback, color_callback,
                                std::complex<float>,
                                float, float);

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
