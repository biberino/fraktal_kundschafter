#include <iostream>
#include <thread>
//#include <SDL2/SDL.h>
#include <gtkmm.h>
#include <locale>
#include "main_window.hpp"

#include "iterations.hpp"
#include "fractal_functions.hpp"
#include "colors.hpp"

Combo_entries setup_combo_entries()
{
    /** Fraktale **/

    Combo_entries retVal;
    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Die klassische Mandelbrotmenge",
        "z = z^2 + c",
        mandelbrot));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Mandelbrot konjugiert (Auge)",
        "z = z * (*z) + c",
        mandelbrot_konj));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Schädel",
        "z = z ^ (*z) + gen",
        mandelbrot_konj_plus_gen));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*c) / (z+c)) + gen",
        kondensator_plus_gen));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*z*c) / (z*z+c))",
        kondensator_4));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*(z*)*c) / (z*(z*)+c))",
        kondensator_5));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "EXP",
        "z = (exp(Z) + C)",
        e_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "EXP",
        "z = (exp(Z) + gen)",
        e_1_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "EXP 2",
        "z = (exp(Z)^exp(Z*) + gen)",
        e_2));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "EXP 3",
        "z = (exp(Z)^exp(Z*) + c)",
        e_3));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "EXP 4",
        "z = (exp(Z^Z*) + gen)",
        e_4));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "EXP 5",
        "z = (exp(Z^Z*) + c)",
        e_5));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = (Z^2+c) / (Z - C)",
        lifesmith_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = (Z*(Z*)+c) / (Z - C)",
        lifesmith_1_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = (Z*(Z*)+c) / (Z* - C)",
        lifesmith_1_2));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z^2 - Z + C",
        lifesmith_2));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z*(Z*) - Z + C",
        lifesmith_2_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z*(Z*) - Z* + C",
        lifesmith_2_2));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z * exp(-Z) + C",
        lifesmith_3));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z * exp(Z*) + C",
        lifesmith_3_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z^3 / (1 + CZ^2)",
        lifesmith_4));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = Z^2sin(Re Z) + CZcos(Im Z) + C",
        lifesmith_5));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = exp(z^z* + gen)",
        schaedel_exp));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = z^z* + gen + (z*c) / (z+c)",
        fractal_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = z^2 / 2z + gen",
        fractal_2));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = z^2 / 2z + c",
        fractal_3));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = ((z*c)^2 + 1) / (z+c)",
        fractal_4));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = (sqrt((z*c)^2 + 1)) / (z+c)",
        fractal_5));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = (z* z*)^2 + c",
        fractal_6));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "lifesmith",
        "z = sqrt((z* z*)^2 + 1)+c",
        fractal_7));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z)*abs(c)*(sqrt((z+c)^2 + 1) / abs(z+c)) + gen",
        fractal_8));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z)*abs(c)*(sqrt((z+c)^2 + 1) / abs(z+c)) + c + gen",
        fractal_9));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "fractal_10",
        "z = abs(z*z)*abs(c)*(sqrt((z*z+c)^2 + 1) / abs(z*z+c)) + gen",
        fractal_10));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z*z)*abs(c)*(sqrt((z*z+c)^2 + 1) / abs(z*z+c)) + c + gen",
        fractal_11));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z*z*)*abs(c)*(sqrt((z*z*+c)^2 + 1) / abs(z*z*+c)) + gen",
        fractal_12));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z*z*)*abs(c)*(sqrt((z*z*+c)^2 + 1) / abs(z*z*+c)) + c + gen",
        fractal_13));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z^z*)*abs(c)*(sqrt((z^z*+c)^2 + 1) / abs(z^z*+c)) + gen",
        fractal_14));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z^z*)*abs(c)*(sqrt((z^z*+c)^2 + 1) / abs(z^z*+c)) + c + gen",
        fractal_15));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z^z)*abs(c)*(sqrt((z^z+c)^2 + 1) / abs(z^z+c)) + gen",
        fractal_16));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = abs(z^z)*abs(c)*(sqrt((z^z+c)^2 + 1) / abs(z^z+c)) + c + gen",
        fractal_17));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "hmm",
        "z = (z+c)(z*c) + gen",
        fractal_18));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Mediant",
        "z = z^2 med c",
        fractal_19));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Mediant",
        "z = z*z* med c",
        fractal_20));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Mediant",
        "z = (z*c) / (z med c) + gen",
        fractal_21));
    /** Iterationen **/

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Standard Iteration",
        normal_iter));

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Standard Iteration ZWILLING",
        normal_iter_zw));

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Standard Iteration ZWILLING ohne Punktverfolgung",
        normal_iter_zw_no_tracking));

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Julia Iteration",
        julia_iter));

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Julia Iteration Zwilling",
        julia_iter_zw));

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Julia Iteration Zwilling keine Punktverfolgung",
        julia_iter_zw_no_tracking));

    retVal.iter_entries.push_back(Combo_entry_iter(
        "Prüft ob Punkt Teil der Menge + Prüft Anzahl Interationen falls nicht in der Menge + Prüft auf Zyklen",
        "Julia Iteration Zwilling Test keine Punktverfolgung",
        julia_iter_test_zw_no_tracking));

    /**Farben **/

    retVal.color_entries.push_back(Combo_entry_color(
        "Färbt nach Mengenzugehörigkeit + anzahl Iterationen + Zyklen",
        "Standard Färbung",
        colorize));

    retVal.color_entries.push_back(Combo_entry_color(
        "Färbt nach Mengenzugehörigkeit",
        "Simple Färbung",
        colorize_simple));

    retVal.color_entries.push_back(Combo_entry_color(
        "Färbt nach Abstand, linearer Gradient",
        "Abstand linear",
        colorize_distance_linear_gradient));

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

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "biber.fractale.cpp");
    Main_window main_window(setup_combo_entries());


    //FIX LOCALE WEGEN , und . !
    std::setlocale(LC_ALL, "C");

    return app->run(main_window);

    return 0;
}
