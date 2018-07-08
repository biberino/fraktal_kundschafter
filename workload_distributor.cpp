#include <iostream>

#include "workload_distributor.hpp"

Workload_distributor::Workload_distributor(/* args */)
{
}

Workload_distributor::~Workload_distributor()
{
}

void Workload_distributor::reset(Resolution_info res)
{
    _res = res;
    _current_x = 0;
    _current_y = 0;
}

std::vector<Pixel> Workload_distributor::request_work(int work_size)
{
    std::unique_lock<std::mutex> lock(_mutex);
    
    int work_assigned = 0;
    std::vector<Pixel> retVec;
    int x = _current_x;
    int y = _current_y;
    for (x = _current_x; x < _res.x; x++)
    {
        for (y = _current_y; y < _res.y; y++)
        {
            if (work_assigned >= work_size)
            {
                break;
            }

            Pixel pix;
            pix.x = x;
            pix.y = y;
            retVec.push_back(pix);
            work_assigned++;
            _current_y++;
        }
        if (work_assigned >= work_size)
        {
            break;
        }
        _current_x++;
        _current_y = 0;
    }
    return retVec;
}