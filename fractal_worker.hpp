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
  iter_callback iteration_function; // die Iteration >
  color_callback color_function;
  fractal_callback fractal_function;
  Workload_distributor *work_dis;
  Result_store *store;
  int max_iter;
  float koppl;
  float bailout_squared;
  std::complex<float> julia_const;
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