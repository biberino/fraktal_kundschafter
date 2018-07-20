#include <iostream>
#include "result_store.hpp"

Result_store::Result_store()
{
}

Result_store::~Result_store()
{
    std::cout << "DESTRUCTOR" << '\n';
    if (_data != nullptr)
    {
        delete[] _data;
    }
}

void Result_store::reset(Resolution_info res)
{
    std::cout << "RESET:" << res.x << "  " << res.y << '\n';
    _res = res;
    //_color_vec.clear();
    if (_data != nullptr)
    {
        delete[] _data;
    }
    _data = new unsigned char[res.x * res.y * 3];
}

void Result_store::put(std::vector<Color_info> *vec)
{
    std::unique_lock<std::mutex> lock(_mutex);

    for (auto el : *vec)
    {
        _data[_res.x * el.pixel.y * 3 + el.pixel.x * 3] = el.color.r;
        _data[(_res.x * el.pixel.y * 3 + el.pixel.x * 3) + 1] = el.color.g;
        _data[(_res.x * el.pixel.y * 3 + el.pixel.x * 3) + 2] = el.color.b;
        // _color_vec.push_back(el);
        //std::cout << "Inserted:" << el.pixel.x << "|" << el.pixel.y << " --> " << el.color.dummy << '\n';
    }
}

unsigned char *Result_store::get_data_pointer()
{
    return _data;
}

/**
std::vector<Color_info> *Result_store::get_vector()
{
    return &_color_vec;
}
**/