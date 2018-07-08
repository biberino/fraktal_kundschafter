#ifndef RESULT_STORE_GUARD
#define RESULT_STORE_GUARD

#include <vector>
#include <mutex>

#include "types.hpp"

class Result_store
{
private:
  std::vector<Color_info> _color_vec;
  Resolution_info _res;
  std::mutex _mutex;

public:
  Result_store();
  ~Result_store();
  void reset(Resolution_info res);
  void put(std::vector<Color_info> *vec);
  std::vector<Color_info> *get_vector();
};

#endif // !RESULT_STORE_GUARD
