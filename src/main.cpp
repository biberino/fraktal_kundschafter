#include <iostream>
#include <thread>
// #include <SDL2/SDL.h>
#include "main_window.hpp"
#include <gtkmm.h>
#include <locale>

#include "colors.hpp"
#include "fractal_functions.hpp"
#include "iterations.hpp"

#include "boost/compute.hpp"
namespace compute = boost::compute;

Combo_entries setup_combo_entries() {
  /** Fraktale **/

  Combo_entries retVal;
  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Die klassische Mandelbrotmenge", "z = z^2 + c", mandelbrot));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Mandelbrot konjugiert (Auge)", "z = z * (*z) + c", mandelbrot_konj));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Schädel", "z = z ^ (*z) + c +gen", mandelbrot_konj_plus_gen));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Kondensator", "z = ((z*c) / (z+c)) + gen", kondensator_plus_gen));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Kondensator", "z = ((z*z*c) / (z*z+c))", kondensator_4));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Kondensator", "z = ((z*(z*)*c) / (z*(z*)+c))", kondensator_5));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("EXP", "z = (exp(Z) + C)", e_1));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("EXP", "z = (exp(Z) + gen)", e_1_1));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("EXP 2", "z = (exp(Z)^exp(Z*) + gen)", e_2));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("EXP 3", "z = (exp(Z)^exp(Z*) + c)", e_3));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("EXP 4", "z = (exp(Z^Z*) + gen)", e_4));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("EXP 5", "z = (exp(Z^Z*) + c)", e_5));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = (Z^2+c) / (Z - C)", lifesmith_1));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "lifesmith", "z = (Z*(Z*)+c) / (Z - C)", lifesmith_1_1));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "lifesmith", "z = (Z*(Z*)+c) / (Z* - C)", lifesmith_1_2));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = Z^2 - Z + C", lifesmith_2));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = Z*(Z*) - Z + C", lifesmith_2_1));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = Z*(Z*) - Z* + C", lifesmith_2_2));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = Z * exp(-Z) + C", lifesmith_3));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = Z * exp(Z*) + C", lifesmith_3_1));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = Z^3 / (1 + CZ^2)", lifesmith_4));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "lifesmith", "z = Z^2sin(Re Z) + CZcos(Im Z) + C", lifesmith_5));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = exp(z^z* + gen)", schaedel_exp));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "lifesmith", "z = z^z* + gen + (z*c) / (z+c)", fractal_1));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = z^2 / 2z + gen", fractal_2));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = z^2 / 2z + c", fractal_3));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = ((z*c)^2 + 1) / (z+c)", fractal_4));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "lifesmith", "z = (sqrt((z*c)^2 + 1)) / (z+c)", fractal_5));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = (z* z*)^2 + c", fractal_6));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("lifesmith", "z = sqrt((z* z*)^2 + 1)+c", fractal_7));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z)*abs(c)*(sqrt((z+c)^2 + 1) / abs(z+c)) + gen",
      fractal_8));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z)*abs(c)*(sqrt((z+c)^2 + 1) / abs(z+c)) + c + gen",
      fractal_9));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "fractal_10",
      "z = abs(z*z)*abs(c)*(sqrt((z*z+c)^2 + 1) / abs(z*z+c)) + gen",
      fractal_10));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z*z)*abs(c)*(sqrt((z*z+c)^2 + 1) / abs(z*z+c)) + c + gen",
      fractal_11));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z*z*)*abs(c)*(sqrt((z*z*+c)^2 + 1) / abs(z*z*+c)) + gen",
      fractal_12));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm",
      "z = abs(z*z*)*abs(c)*(sqrt((z*z*+c)^2 + 1) / abs(z*z*+c)) + c + gen",
      fractal_13));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z^z*)*abs(c)*(sqrt((z^z*+c)^2 + 1) / abs(z^z*+c)) + gen",
      fractal_14));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm",
      "z = abs(z^z*)*abs(c)*(sqrt((z^z*+c)^2 + 1) / abs(z^z*+c)) + c + gen",
      fractal_15));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z^z)*abs(c)*(sqrt((z^z+c)^2 + 1) / abs(z^z+c)) + gen",
      fractal_16));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z^z)*abs(c)*(sqrt((z^z+c)^2 + 1) / abs(z^z+c)) + c + gen",
      fractal_17));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("hmm", "z = (z+c)(z*c) + gen", fractal_18));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Mediant", "z = z^2 med c", fractal_19));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Mediant", "z = z*z* med c", fractal_20));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Mediant", "z = (z*c) / (z med c) + gen", fractal_21));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z^z)*abs(c)*(sqrt((z^z+c)^2 + 1) / abs(z^z+c)) - c + gen",
      fractal_22));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm", "z = abs(z)*abs(c)*(sqrt((z+c)^2 + 1) / abs(z+c)) - c + gen",
      fractal_23));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "hmm",
      "z = abs(z^z*)*abs(c)*(sqrt((z^z*+c)^2 + 1) / abs(z^z*+c)) - c + gen",
      fractal_24));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Gerade durch Parabel", "z = (z+c)*gen-(z*c)", fractal_25));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Gerade durch Parabel", "z = (z*z+c)*gen-(z*z*c)", fractal_26));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Gerade durch Parabel", "z = (z*z*+c)*gen-(z*z* *c)", fractal_27));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Gerade durch Parabel", "z = (z^z*+c)*gen-(z^z* *c)", fractal_28));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Kondensator Potenz", "z = ((z^z* -1)  * c) / ((z^z* -1) +c) + gen",
      fractal_28));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Mandelbrot hoch 3", "z = z^3+c", mandelbrot_3));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Mandelbrot hoch 4", "z = z^4+c", mandelbrot_4));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Mandelbrot hoch 5", "z = z^5+c", mandelbrot_5));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Mandelbrot Auge", "z = z*z *(z*) + c", mandelbrot_konj_2));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Mandelbrot Auge", "z = z*(z*) *(z*) + c", mandelbrot_konj_3));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Mandelbrot Auge", "z = z*z *(z*) - c", mandelbrot_konj_4));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Mandelbrot Auge", "z = z*(z*) *(z*) -c", mandelbrot_konj_5));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Versuch", "z = (z*z)^(z*) + c + gen", versuch_1));

  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Binet mit hoch Z plus C",
                          "z = ((phi^z - (-1/phi)^z)/ sqrt(5))+c", binet));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Binet mit hoch C plus Z", "z = ((phi^c - (-1/phi)^c)/ sqrt(5))+z",
      binet_hoch_c));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Binet gemischt 1", "z = ((phi^z - (-1/phi)^c)/ sqrt(5))+c",
      binet_mixed_1));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Binet gemischt 2", "z = ((phi^c - (-1/phi)^z)/ sqrt(5))+c",
      binet_mixed_2));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "Fractal Arts 1", "z = (c+z*z*c)/(1-z*z*c)", fractal_arts1));
  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Z hoch C 1", "z = (z^c)/(z*c) + gen", z_power_c_1));

  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "test Spiegelung x Achse", "test Spiegelung x", x_gespiegelt));
  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "test Spiegelung x Achse 2", "test Spiegelung x", x_gespiegelt2));
  retVal.fractal_entries.push_back(Combo_entry_fractal(
      "test Spiegelung x Achse 3", "test Spiegelung x", x_gespiegelt3));
  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Burning Ship", "Burning Ship x", burning_ship));
  retVal.fractal_entries.push_back(
      Combo_entry_fractal("Burning Ship2", "Burning Ship x 2", burning_ship2));

  /** Iterationen **/

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Standard Iteration", normal_iter));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Standard Iteration ZWILLING", normal_iter_zw));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Standard Iteration ZWILLING ohne Punktverfolgung",
      normal_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Julia Iteration", julia_iter));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Julia Iteration Zwilling", julia_iter_zw));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Julia Iteration Zwilling keine Punktverfolgung",
      julia_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Julia Iteration Zwilling Test keine Punktverfolgung",
      julia_iter_test_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Hybrid Iteration Zwilling (Startwert + C sind vom Punkt abhängig), "
      "keine Punktverfolgung",
      hybrid_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Mal Geteilt Iteration Zwilling (Startwert + C sind vom Punkt abhängig), "
      "keine Punktverfolgung",
      mult_divide_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "??? Iteration Zwilling (Startwert + C sind vom Punkt abhängig), "
      "keine Punktverfolgung",
      test_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Zukunfts Iteration Zwilling (Startwert + C sind vom Punkt abhängig), "
      "keine Punktverfolgung",
      zukunfts_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Vertausch 1 Iteration Zwilling (Startwert + C sind vom Punkt abhängig), "
      "keine Punktverfolgung",
      vertausch_1_iter_zw_no_tracking));

  retVal.iter_entries.push_back(Combo_entry_iter(
      "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht "
      "in der Menge + Prüft auf Zyklen",
      "Standard Iteration ZWILLING ohne Punktverfolgung mit Alter Gen Param",
      normal_iter_zw_no_tracking_age));

  /**Farben **/

  retVal.color_entries.push_back(Combo_entry_color(
      "Färbt nach Mengenzugehörigkeit + anzahl Iterationen + Zyklen",
      "Standard Färbung", colorize));

  retVal.color_entries.push_back(Combo_entry_color(
      "Färbt nach Mengenzugehörigkeit", "Simple Färbung", colorize_simple));

  retVal.color_entries.push_back(
      Combo_entry_color("Färbt nach Abstand, linearer Gradient",
                        "Abstand linear", colorize_distance_linear_gradient));

  retVal.color_entries.push_back(Combo_entry_color(
      "Färbt nach Abstand, linearer Gradient+ Divergenz nach Tabelle",
      "Abstand linear + Divergenz nach Tabelle",
      colorize_inner_dist_outer_table));

  retVal.color_entries.push_back(Combo_entry_color(
      "Färbt nach Abstand, linearer Gradient+ Divergenz Gradient",
      "Abstand linear + Divergenz Gradient",
      colorize_inner_dist_outer_gradient));

  retVal.color_entries.push_back(Combo_entry_color(
      "Färbt nach Winkel, linearer Gradient+ Divergenz Gradient",
      "Winkel linear + Divergenz Gradient",
      colorize_inner_angle_outer_gradient));

  return retVal;
}

int main(int argc, char *argv[]) {
  // TEST
  /**
  // get default device and setup context
  compute::device device = compute::system::default_device();
  compute::context context(device);
  compute::command_queue queue(context, device);

  using compute_type = int;
  // generate random data on the host
  std::vector<compute_type> host_vector(5);
  std::generate(host_vector.begin(), host_vector.end(), rand);
  for (auto number : host_vector) {
    // std::cout << number.real() << number.imag() << "  ";
  }
  std::cout << std::endl;
  // create a vector on the device
  compute::vector<compute_type> device_vector(host_vector.size(), context);

  // transfer data from the host to the device
  compute::copy(host_vector.begin(), host_vector.end(), device_vector.begin(),
                queue);

  BOOST_COMPUTE_FUNCTION(compute_type, add_complex,
                         (compute_type x, compute_type y), { return x + y; });

  // wie kann ich ne Funktion mit 2 Parametern ausweten???
  compute::transform(device_vector.begin(), device_vector.end(),
                     device_vector.begin(), add_complex, queue);

    // copy values back to the host
    compute::copy(device_vector.begin(), device_vector.end(),
  host_vector.begin(), queue);

    for (auto number : host_vector) {
      std::cout << number << "  ";
    }
    std::cout << std::endl;
  return 0;
  **/
  // ENDE TEST
  auto app = Gtk::Application::create(argc, argv, "biber.fractale.cpp");
  Main_window main_window(setup_combo_entries());

  // FIX LOCALE WEGEN , und . !
  std::setlocale(LC_ALL, "C");

  std::srand(std::time(nullptr));

  return app->run(main_window);

  return 0;
}
