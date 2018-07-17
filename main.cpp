#include <iostream>
#include <thread>
//#include <SDL2/SDL.h>
#include <gtkmm.h>

#include "calculation_handler.hpp"

//Gtk components
#include "display.hpp"
#include "options_panel.hpp"





int main(int argc, char *argv[])
{

    //display.show();

    //draw(&store);

    Calculation_handler calc_handler;

    auto app = Gtk::Application::create(argc, argv, "biber.fractale.test");
    Gtk::Window window;
    window.set_default_size(800, 600);
    window.set_title("Fraktal Kundschafter");

    Display display;
    Options_panel opt_panel(&calc_handler, &display);

    Gtk::Paned v_box(Gtk::ORIENTATION_HORIZONTAL);

    v_box.add1(opt_panel);
    v_box.add2(display);
    window.add(v_box);

    window.show_all_children();

    return app->run(window);

    return 0;
}
