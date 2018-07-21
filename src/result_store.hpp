#ifndef RESULT_STORE_GUARD
#define RESULT_STORE_GUARD

#include <gtkmm/progressbar.h>
#include <vector>
#include <mutex>

#include "types.hpp"

class Result_store
{
private:
  //std::vector<Color_info> _color_vec;
  Resolution_info _res;
  std::mutex _mutex;
  unsigned char *_data = nullptr;
  Gtk::ProgressBar *_progress;
  int _num_points;
  int _num_points_calculated;

public:
  Result_store(Gtk::ProgressBar *progress);
  ~Result_store();
  void reset(Resolution_info res);
  void put(std::vector<Color_info> *vec);
  unsigned char * get_data_pointer();
  //std::vector<Color_info> *get_vector();
};

#endif // !RESULT_STORE_GUARD
