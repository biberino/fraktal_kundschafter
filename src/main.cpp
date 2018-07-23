#include <iostream>
#include <thread>
//#include <SDL2/SDL.h>
#include <gtkmm.h>

#include "calculation_handler.hpp"

//Gtk components
#include "display.hpp"
#include "options_panel.hpp"
#include "functions_panel.hpp"

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
        "z = z ^ (*z) - 1",
        mandelbrot_konj_minus_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = (z*c) / (z+c)",
        kondensator_1));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*c) / (z+c)) -1",
        kondensator_2));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*c) / (z+c)) +1",
        kondensator_3));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*z*c) / (z*z+c))",
        kondensator_4));

    retVal.fractal_entries.push_back(Combo_entry_fractal(
        "Kondensator",
        "z = ((z*(z*)*c) / (z*(z*)+c))",
        kondensator_5));

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

    return retVal;
}

int main(int argc, char *argv[])
{

    //display.show();

    //draw(&store);

    auto app = Gtk::Application::create(argc, argv, "biber.fractale.test");
    Gtk::Window window;
    window.set_default_size(800, 600);
    window.set_title("Fraktal Kundschafter");

    Combo_entries entries = setup_combo_entries();

    Functions_panel func_panel(entries);
    Display display;

    Options_panel opt_panel(&display, &func_panel);

    Gtk::Paned v_box(Gtk::ORIENTATION_VERTICAL);

    v_box.add1(func_panel);

    Gtk::Paned h_box(Gtk::ORIENTATION_HORIZONTAL);

    h_box.add1(opt_panel);
    h_box.add2(display);

    v_box.add2(h_box);
    window.add(v_box);

    window.show_all_children();

    return app->run(window);

    return 0;
}
