#include <iostream>
#include "result_store.hpp"

Result_store::Result_store()
{
}

Result_store::~Result_store()
{
}

void Result_store::reset(Resolution_info res)
{
    _res = res;
    _color_vec.clear();
}

void Result_store::put(std::vector<Color_info> *vec)
{
    std::unique_lock<std::mutex> lock(_mutex);

    for (auto el : *vec)
    {
        _color_vec.push_back(el);
        //std::cout << "Inserted:" << el.pixel.x << "|" << el.pixel.y << " --> " << el.color.dummy << '\n';
    }
}

std::vector<Color_info> *Result_store::get_vector()
{
    return &_color_vec;
}