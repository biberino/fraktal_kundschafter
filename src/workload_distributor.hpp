#ifndef WORKL_DIST_GUARD
#define WORKL_DIST_GUARD

#include <vector>
#include <mutex>

#include "types.hpp"

class Workload_distributor
{
  private:
    Resolution_info _res;
    int _current_x = 0;
    int _current_y = 0;
    std::mutex _mutex;

  public:
    Workload_distributor();
    ~Workload_distributor();

    void reset(Resolution_info res);
    std::vector<Pixel> request_work(int work_size);
};

#endif // !WORKL_DIST_GUARD