#include "info_panel.hpp"

Info_panel::Info_panel(/* args */)
{
    _ref_text_buffer = Gtk::TextBuffer::create();
    _ref_text_buffer->set_text("INIT\n");
    _lbl_headline.set_text("INFO");
    _view.set_buffer(_ref_text_buffer);

    attach(_lbl_headline, 0, 0, 2, 1);
    attach(_view, 0, 1, 2, 1);

    show_all_children();
}

Info_panel::~Info_panel()
{
}

void Info_panel::clear()
{
    _ref_text_buffer->erase(_ref_text_buffer->begin(), _ref_text_buffer->end());
}
void Info_panel::append_message(const std::string& msg)
{
    _ref_text_buffer->place_cursor(_ref_text_buffer->end());
    _ref_text_buffer->insert_at_cursor(msg);
}