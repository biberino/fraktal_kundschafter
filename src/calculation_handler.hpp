#ifndef CAL_GUARD_1212
#define CAL_GUARD_1212

#include "types.hpp"
#include "workload_distributor.hpp"
#include "result_store.hpp"
#include "fractal_worker.hpp"

struct calculation_params
{
    datatype x_min;
    datatype x_max;
    datatype y_min;
    datatype y_max;
    iter_callback iteration_function;
    Resolution_info resolution;
    int work_size;
    int max_iter;
    datatype koppl;
    datatype bailout_squared;
    fractal_callback fractal_function;
    color_callback color_function;
    complex_type julia_const;
    datatype gen_param;
};

class Options_panel;

class Calculation_handler
{
  private:
    calculation_params _params;
    Workload_distributor work_dis;
    Result_store store;

  public:
    Calculation_handler(Options_panel *caller);
    ~Calculation_handler();
    void set_params(calculation_params params);
    void calculate();
    unsigned char * get_result_pointer();
};



#endif // !CAL