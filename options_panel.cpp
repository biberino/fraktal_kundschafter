#include "options_panel.hpp"
#include <iostream>

Options_panel::Options_panel(void (*f)())
{
    _f = f;
    _button_draw.add_label("Zeichnen");

    _button_draw.signal_clicked()
        .connect(sigc::mem_fun(*this,
                               &Options_panel::on_button_draw_clicked));

    add(_button_draw);
    show_all_children();
}

Options_panel::~Options_panel()
{
}

void Options_panel::on_button_draw_clicked()
{
    std::cout << "CLICKED!!!" << '\n';
    _f();
}