#ifndef __RANDOM_PANEL_HPP__
#define __RANDOM_PANEL_HPP__

#include <gtkmm.h>
#include "types.hpp"

//forward delcare
class Options_panel;

//The values the Random Fractal Generator is able to change
struct random_panel_change_data
{
    double koppl;
    double gen;
    double start_real;
    double start_imag;
    bool b_koppl;
    bool b_gen;
    bool b_start_real;
    bool b_start_imag;
    bool b_formula;
};

class Random_panel : public Gtk::Grid
{
private:
    //Gtk::Grid _grid_main;

    Options_panel *_parent;
    Gtk::Label _lbl_random_info;
    Gtk::Button _btn_draw;

    Gtk::CheckButton _check_koppl;
    Gtk::CheckButton _check_gen;
    Gtk::CheckButton _check_start_real;
    Gtk::CheckButton _check_start_imag;

    Gtk::CheckButton _check_formula;

    Gtk::Entry _txt_koppl_min;
    Gtk::Entry _txt_gen_min;
    Gtk::Entry _txt_start_real_min;
    Gtk::Entry _txt_start_imag_min;

    Gtk::Entry _txt_koppl_max;
    Gtk::Entry _txt_gen_max;
    Gtk::Entry _txt_start_real_max;
    Gtk::Entry _txt_start_imag_max;

    Gtk::Label _lbl_koppl_stroke;
    Gtk::Label _lbl_gen_stroke;
    Gtk::Label _lbl_start_real_stroke;
    Gtk::Label _lbl_start_imag_stroke;

    double random_between(double min, double max);

public:
    Random_panel(Options_panel *parent);
    ~Random_panel();

    void on_button_draw_clicked();
};

#endif // __RANDOM_PANEL_HPP__