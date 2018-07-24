#ifndef CAL_GUARD_1212
#define CAL_GUARD_1212

#include <gtkmm/progressbar.h>
#include "types.hpp"
#include "workload_distributor.hpp"
#include "result_store.hpp"
#include "fractal_worker.hpp"

struct calculation_params
{
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    iter_callback iteration_function;
    Resolution_info resolution;
    int work_size;
    int max_iter;
    double koppl;
    double bailout_squared;
    fractal_callback fractal_function;
    color_callback color_function;
    complex_type julia_const;
    double gen_param;
};

class Calculation_handler
{
  private:
    calculation_params _params;
    Workload_distributor work_dis;
    Result_store store;

  public:
    Calculation_handler(Gtk::ProgressBar *progress);
    ~Calculation_handler();
    void set_params(calculation_params params);
    void calculate();
    unsigned char * get_result_pointer();
};



#endif // !CAL