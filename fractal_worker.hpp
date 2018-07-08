#ifndef FRACTAL_WORKER_GUARD
#define FRACTAL_WORKER_GUARD

#include <complex>

#include "types.hpp"
#include "workload_distributor.hpp"
#include "result_store.hpp"

struct Fractal_params
{
  Axis_info axis;
  Resolution_info res;
  int work_size;
  Color (*iteration_function)(std::complex<float>); // die Iteration >
  Workload_distributor *work_dis;
  Result_store *store;
};

class Fractal_worker
{
private:
  Fractal_params _params;
  float _x_diff;
  float _y_diff;

public:
  std::vector<Color_info> _col_info_vec;
  Fractal_worker();
  ~Fractal_worker();
  void set_params(Fractal_params params);
  inline std::complex<float> XY_to_complex(Pixel pixel);
  void start();
};

#endif // !FRACTAL_WORKER_GUARD