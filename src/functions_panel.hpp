#ifndef FUNCTIONS_PANEL_GUARD
#define FUNCTIONS_PANEL_GUARD
#include <gtkmm.h>
#include "types.hpp"

class Functions_panel : public Gtk::Grid
{
private:
protected:
  //Tree model columns:
  class ModelColumns : public Gtk::TreeModel::ColumnRecord
  {
  public:
    ModelColumns()
    {
      add(m_col_id);
      add(m_col_name);
      add(m_col_extra);
    }

    Gtk::TreeModelColumn<int> m_col_id;
    Gtk::TreeModelColumn<Glib::ustring> m_col_name;
    Gtk::TreeModelColumn<Glib::ustring> m_col_extra;
  };

  Gtk::Label _lbl_fractal;
  Gtk::Label _lbl_iterations;
  Gtk::Label _lbl_color;

  Gtk::ComboBox _combo_fractal;
  Gtk::ComboBox _combo_iterations;
  Gtk::ComboBox _combo_color;

  ModelColumns _col_fractal;
  ModelColumns _col_iter;
  ModelColumns _col_color;

  //Gtk::CellRendererText m_cell;
  Glib::RefPtr<Gtk::ListStore> _refTreeModel_fractal;
  Glib::RefPtr<Gtk::ListStore> _refTreeModel_iter;
  Glib::RefPtr<Gtk::ListStore> _refTreeModel_color;

  std::vector<fractal_callback> vec_frac_callbacks;
  std::vector<iter_callback> vec_iter_callbacks;
  std::vector<color_callback> vec_color_callbacks;

public:
  Functions_panel(const Combo_entries &entries);
  ~Functions_panel();

  fractal_callback get_fractal_callback();
  fractal_callback get_random_fractal_callback();
  iter_callback get_iter_callback();
  color_callback get_color_callback();
};

#endif // !FUNCTIONS_PANEL_GUARD