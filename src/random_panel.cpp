
#include "iostream"
#include "random_panel.hpp"
#include "options_panel.hpp"

Random_panel::Random_panel(Options_panel *parent)
{

    _parent = parent;
    _lbl_random_info.set_markup("<b>Zufallsgenerator</b>");
    _lbl_random_info.set_size_request(-1, 50);
    _btn_draw.add_label("Zufälliges Fraktal zeichnen");

    _check_koppl.add_label("Koppl");
    _check_gen.add_label("Generischer Param");
    _check_start_real.add_label("Startwert Real");
    _check_start_imag.add_label("Startwert Imaginär");
    _check_formula.add_label("Formel zufällig");

    _check_koppl.set_size_request(-1, 30);
    _check_gen.set_size_request(-1, 30);
    _check_start_real.set_size_request(-1, 30);
    _check_start_imag.set_size_request(-1, 30);
    _check_formula.set_size_request(-1, 30);

    _lbl_koppl_stroke.set_text("-");
    _lbl_gen_stroke.set_text("-");
    _lbl_start_real_stroke.set_text("-");
    _lbl_start_imag_stroke.set_text("-");

    _lbl_koppl_stroke.set_size_request(10, 10);
    _lbl_gen_stroke.set_size_request(10, 10);
    _lbl_start_real_stroke.set_size_request(10, 10);
    _lbl_start_imag_stroke.set_size_request(10, 10);

    _txt_koppl_min.set_width_chars(5);
    _txt_koppl_max.set_width_chars(5);
    _txt_gen_min.set_width_chars(5);
    _txt_gen_max.set_width_chars(5);
    _txt_start_real_min.set_width_chars(5);
    _txt_start_real_max.set_width_chars(5);
    _txt_start_imag_min.set_width_chars(5);
    _txt_start_imag_max.set_width_chars(5);

    //default values
    _txt_koppl_min.set_text("0.0");
    _txt_gen_min.set_text("0.0");
    _txt_start_real_min.set_text("0.0");
    _txt_start_imag_min.set_text("0.0");

    _txt_koppl_max.set_text("1.0");
    _txt_gen_max.set_text("1.0");
    _txt_start_real_max.set_text("1.0");
    _txt_start_imag_max.set_text("1.0");

    attach(_lbl_random_info, 0, 0, 5, 1);

    attach(_check_koppl, 1, 2, 1, 1);
    attach(_txt_koppl_min, 2, 2, 1, 1);
    attach(_lbl_koppl_stroke, 3, 2, 1, 1);
    attach(_txt_koppl_max, 4, 2, 1, 1);

    attach(_check_gen, 1, 3, 1, 1);
    attach(_txt_gen_min, 2, 3, 1, 1);
    attach(_lbl_gen_stroke, 3, 3, 1, 1);
    attach(_txt_gen_max, 4, 3, 1, 1);

    attach(_check_start_real, 1, 4, 1, 1);
    attach(_txt_start_real_min, 2, 4, 1, 1);
    attach(_lbl_start_real_stroke, 3, 4, 1, 1);
    attach(_txt_start_real_max, 4, 4, 1, 1);

    attach(_check_start_imag, 1, 5, 1, 1);
    attach(_txt_start_imag_min, 2, 5, 1, 1);
    attach(_lbl_start_imag_stroke, 3, 5, 1, 1);
    attach(_txt_start_imag_max, 4, 5, 1, 1);

    attach(_check_formula, 1, 6, 1, 1);

    attach(_btn_draw, 0, 99, 5, 1);
    _btn_draw.signal_clicked().connect(sigc::mem_fun(*this,
                                                     &Random_panel::on_button_draw_clicked));
    show_all_children();
}

datatype Random_panel::random_between(datatype min, datatype max)
{
    datatype r = min + static_cast<datatype>((datatype)rand()) / (static_cast<datatype>((datatype)RAND_MAX / (max - min)));
    return r;
}

Random_panel::~Random_panel()
{
}

void Random_panel::on_button_draw_clicked()
{

    datatype koppl_min;
    datatype koppl_max;
    datatype gen_min;
    datatype gen_max;
    datatype start_real_min;
    datatype start_real_max;
    datatype start_imag_min;
    datatype start_imag_max;

    try
    {
        koppl_min = std::stod(_txt_koppl_min.get_text());
        koppl_max = std::stod(_txt_koppl_max.get_text());
        gen_min = std::stod(_txt_gen_min.get_text());
        gen_max = std::stod(_txt_gen_max.get_text());
        start_real_min = std::stod(_txt_start_real_min.get_text());
        start_real_max = std::stod(_txt_start_real_max.get_text());
        start_imag_min = std::stod(_txt_start_imag_min.get_text());
        start_imag_max = std::stod(_txt_start_imag_max.get_text());
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << '\n';
        return;
    }



    random_panel_change_data data;

    data.koppl = random_between(koppl_min, koppl_max);
    data.gen = random_between(gen_min, gen_max);
    data.start_real = random_between(start_real_min, start_real_max);
    data.start_imag = random_between(start_imag_min, start_imag_max);

    data.b_koppl = _check_koppl.get_active();
    data.b_gen = _check_gen.get_active();
    data.b_start_real = _check_start_real.get_active();
    data.b_start_imag = _check_start_imag.get_active();
    data.b_formula = _check_formula.get_active();
    
    _parent->request_param_change(data);
    _parent->request_calculation();
}
