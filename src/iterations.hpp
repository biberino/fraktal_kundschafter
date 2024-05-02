#ifndef ITER_GUARD_FUNC
#define ITER_GUARD_FUNC

#include <complex>
#include <cstdint>
#include <iomanip> // setprecision
#include <iostream>
#include <set>
#include <sstream> // stringstream
#include <string.h>
#include <string>
#include <unordered_map>

#include "types.hpp"

std::string debug;
bool debug_active = true;

inline std::string datatype_to_string(datatype f) {
  uint64_t ui;
  memcpy(&ui, &f, sizeof(datatype));
  return std::to_string(ui & 0xFFFFFFFFFF000000);
}

/**
 *
 * point_path_buffer: indicates if the caller is interested in the point path.
 * If it is a nullptr, no points will be tracked. The caller needs to provide
 * the memory for the points, 0....max_iter
 */

inline Color normal_iter(complex_type point, int max_iter,
                         fractal_callback fractal_func,
                         color_callback color_func, complex_type julia_const,
                         datatype bailout_squared, datatype koppl,
                         datatype gen_param, Point_trail *point_path_buffer) {

  complex_type z = julia_const;
  complex_type c = point;
  // für schnelle lookups
  std::unordered_map<std::string, int> hash_table;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z);
      point_path_buffer->valid_count++;
    }

    std::string z_string =
        datatype_to_string(z.real()) + datatype_to_string(z.imag());

    if (hash_table.find(z_string) != hash_table.end()) {
      // wert bereits in hash map
      int jump_counter = j - hash_table[z_string];
      // hier nach anzahl sprügne einfärben

      return color_func(jump_counter, true, j, z, complex_type(0, 0), max_iter,
                        sqrt(bailout_squared));
    }

    hash_table[z_string] = j;

    z = fractal_func(z, c, gen_param);

    if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared) {
      return color_func(0, false, j, z, complex_type(0, 0), max_iter,
                        sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z, complex_type(0, 0), max_iter,
                    sqrt(bailout_squared));
}

inline Color julia_iter(complex_type point, int max_iter,
                        fractal_callback fractal_func,
                        color_callback color_func, complex_type julia_const,
                        datatype bailout_squared, datatype koppl,
                        datatype gen_param, Point_trail *point_path_buffer) {

  complex_type z = point;
  complex_type c = julia_const;
  // für schnelle lookups
  std::unordered_map<std::string, int> hash_table;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z);
      point_path_buffer->valid_count++;
    }

    std::string z_string =
        datatype_to_string(z.real()) + datatype_to_string(z.imag());

    if (hash_table.find(z_string) != hash_table.end()) {
      // wert bereits in hash map
      int jump_counter = j - hash_table[z_string];
      // hier nach anzahl sprügne einfärben

      return color_func(jump_counter, true, j, z, complex_type(0, 0), max_iter,
                        sqrt(bailout_squared));
    }

    hash_table[z_string] = j;

    z = fractal_func(z, c, gen_param);

    if (((z.real() * z.real()) + (z.imag() * z.imag())) > bailout_squared) {
      return color_func(0, false, j, z, complex_type(0, 0), max_iter,
                        sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z, complex_type(0, 0), max_iter,
                    sqrt(bailout_squared));
}

inline Color normal_iter_zw(complex_type point, int max_iter,
                            fractal_callback fractal_func,
                            color_callback color_func, complex_type julia_const,
                            datatype bailout_squared, datatype koppl,
                            datatype gen_param,
                            Point_trail *point_path_buffer) {

  complex_type z1 = julia_const;
  complex_type z2 = julia_const;

  complex_type c = point;
  // für schnelle lookups
  std::unordered_map<std::string, int> hash_table;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }

    std::string z_string =
        datatype_to_string(z1.real()) + datatype_to_string(z1.imag()) +
        datatype_to_string(z2.real()) + datatype_to_string(z2.imag());

    if (hash_table.find(z_string) != hash_table.end()) {
      // wert bereits in hash map
      int jump_counter = j - hash_table[z_string];
      // hier nach anzahl sprügne einfärben
      return color_func(jump_counter, true, j, z1, z2, max_iter,
                        sqrt(bailout_squared));
    }

    hash_table[z_string] = j;

    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) + (z2 * koppl);

    z2 = fractal_func(z2, c, gen_param) - (buffer * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color normal_iter_zw_no_tracking(complex_type point, int max_iter,
                                        fractal_callback fractal_func,
                                        color_callback color_func,
                                        complex_type julia_const,
                                        datatype bailout_squared,
                                        datatype koppl, datatype gen_param,
                                        Point_trail *point_path_buffer) {

  complex_type z1 = julia_const;
  complex_type z2 = julia_const;

  complex_type c = point;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {
    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }

    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) + (z2 * koppl);

    z2 = fractal_func(z2, c, gen_param) - (buffer * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color julia_iter_zw(complex_type point, int max_iter,
                           fractal_callback fractal_func,
                           color_callback color_func, complex_type julia_const,
                           datatype bailout_squared, datatype koppl,
                           datatype gen_param, Point_trail *point_path_buffer) {

  complex_type z1(point);
  complex_type z2(point);

  complex_type c = julia_const;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  // für schnelle lookups
  std::unordered_map<std::string, int> hash_table;

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }

    std::string z_string =
        datatype_to_string(z1.real()) + datatype_to_string(z1.imag()) +
        datatype_to_string(z2.real()) + datatype_to_string(z2.imag());

    if (hash_table.find(z_string) != hash_table.end()) {
      // wert bereits in hash map
      int jump_counter = j - hash_table[z_string];
      // hier nach anzahl sprügne einfärben

      // Color temp = color_table[jump_counter];
      // return Color(jump_counter * 20, (abs(z1 + z2) / 4.0f) * 255.0f,
      // ((datatype)j / (datatype)max_iter) * 255.0f);
      return color_func(jump_counter, true, j, z1, z2, max_iter,
                        sqrt(bailout_squared));
      // temp.b = ((datatype)j / (datatype)max_iter) * 255.0f;
      // return temp;
    }

    hash_table[z_string] = j;

    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) + (z2 * koppl);

    z2 = fractal_func(z2, c, gen_param) - (buffer * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color julia_iter_zw_no_tracking(complex_type point, int max_iter,
                                       fractal_callback fractal_func,
                                       color_callback color_func,
                                       complex_type julia_const,
                                       datatype bailout_squared, datatype koppl,
                                       datatype gen_param,
                                       Point_trail *point_path_buffer) {

  complex_type z1(point);
  complex_type z2(point);

  complex_type c = julia_const;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }
    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) + (z2 * koppl);

    z2 = fractal_func(z2, c, gen_param) - (buffer * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color julia_iter_test_zw_no_tracking(complex_type point, int max_iter,
                                            fractal_callback fractal_func,
                                            color_callback color_func,
                                            complex_type julia_const,
                                            datatype bailout_squared,
                                            datatype koppl, datatype gen_param,
                                            Point_trail *point_path_buffer) {

  complex_type z1(point);
  complex_type z2(point);

  complex_type c = julia_const;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }
    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) - (koppl * z2);

    z2 = fractal_func(z2, c, gen_param) - (z1 * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color hybrid_iter_zw_no_tracking(complex_type point, int max_iter,
                                        fractal_callback fractal_func,
                                        color_callback color_func,
                                        complex_type julia_const,
                                        datatype bailout_squared,
                                        datatype koppl, datatype gen_param,
                                        Point_trail *point_path_buffer) {

  complex_type z1 = point;
  complex_type z2 = point;

  complex_type c = point;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {

    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }

    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) + (z2 * koppl);

    z2 = fractal_func(z2, c, gen_param) - (buffer * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color mult_divide_iter_zw_no_tracking(complex_type point, int max_iter,
                                             fractal_callback fractal_func,
                                             color_callback color_func,
                                             complex_type julia_const,
                                             datatype bailout_squared,
                                             datatype koppl, datatype gen_param,
                                             Point_trail *point_path_buffer) {

  complex_type z1 = julia_const;
  complex_type z2 = julia_const;

  complex_type c = point;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {
    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }

    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) * (z2 * koppl);

    z2 = fractal_func(z2, c, gen_param) / (buffer * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

inline Color test_iter_zw_no_tracking(complex_type point, int max_iter,
                                      fractal_callback fractal_func,
                                      color_callback color_func,
                                      complex_type julia_const,
                                      datatype bailout_squared, datatype koppl,
                                      datatype gen_param,
                                      Point_trail *point_path_buffer) {

  complex_type z1 = julia_const;
  complex_type z2 = julia_const;

  complex_type c = point;

  if (point_path_buffer) {
    point_path_buffer->valid_count = 0;
  }

  for (size_t j = 0; j < max_iter; j++) {
    // tracking
    if (point_path_buffer) {
      point_path_buffer->points[j] = complex_type(z1);
      point_path_buffer->valid_count++;
    }

    complex_type buffer(z1);
    z1 = fractal_func(z1, c, gen_param) + ((z2 * z2) * koppl);

    z2 = fractal_func(z2, c, gen_param) - ((buffer * buffer) * koppl);

    if ((((z1.real() * z1.real()) + (z1.imag() * z1.imag())) >
         bailout_squared) &&
        (((z2.real() * z2.real()) + (z2.imag() * z2.imag())) >
         bailout_squared)) {
      return color_func(0, false, j, z1, z2, max_iter, sqrt(bailout_squared));
    }
  }

  return color_func(0, true, max_iter, z1, z2, max_iter, sqrt(bailout_squared));
}

#endif // !FRAC_FUN_GUARD_!1212