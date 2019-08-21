#include "functions_panel.hpp"

Functions_panel::Functions_panel(const Combo_entries &entries)
{
    _lbl_fractal.set_text("Fraktal:   ");
    _lbl_iterations.set_text("Iteration:   ");
    _lbl_color.set_text("Farbe:   ");

    attach(_lbl_fractal, 0, 0, 1, 1);
    attach(_lbl_iterations, 1, 0, 1, 1);
    attach(_lbl_color, 2, 0, 1, 1);

    attach(_combo_fractal, 0, 1, 1, 1);
    attach(_combo_iterations, 1, 1, 1, 1);
    attach(_combo_color, 2, 1, 1, 1);

    /** Combo Box Entries **/
    /**FRACTAL**/
    _refTreeModel_fractal = Gtk::ListStore::create(_col_fractal);
    _combo_fractal.set_model(_refTreeModel_fractal);

    bool default_set = false;
    int id_counter = 1;
    for (auto el : entries.fractal_entries)
    {
        Gtk::TreeModel::Row row = *(_refTreeModel_fractal->append());
        row[_col_fractal.m_col_id] = id_counter;
        row[_col_fractal.m_col_name] = el.formula;
        row[_col_fractal.m_col_extra] = el.description;
        vec_frac_callbacks.push_back(el.callback); // id -1
        if (!default_set)
        {
            _combo_fractal.set_active(row);
            default_set = true;
        }
        id_counter++;
    }

    _combo_fractal.pack_start(_col_fractal.m_col_id);
    _combo_fractal.pack_start(_col_fractal.m_col_name);
    _combo_fractal.pack_start(_col_fractal.m_col_extra);

    /**ITER **/
    _refTreeModel_iter = Gtk::ListStore::create(_col_iter);
    _combo_iterations.set_model(_refTreeModel_iter);

    default_set = false;
    id_counter = 1;
    for (auto el : entries.iter_entries)
    {
        Gtk::TreeModel::Row row = *(_refTreeModel_iter->append());
        row[_col_iter.m_col_id] = id_counter;
        row[_col_iter.m_col_name] = el.short_description;
        row[_col_iter.m_col_extra] = el.description;
        vec_iter_callbacks.push_back(el.callback); // id -1
        if (!default_set)
        {
            _combo_iterations.set_active(row);
            default_set = true;
        }
        id_counter++;
    }

    _combo_iterations.pack_start(_col_iter.m_col_id);
    _combo_iterations.pack_start(_col_iter.m_col_name);
    //_combo_iterations.pack_start(_col_iter.m_col_extra);

    /** COLOR**/

    _refTreeModel_color = Gtk::ListStore::create(_col_color);
    _combo_color.set_model(_refTreeModel_color);

    default_set = false;
    id_counter = 1;
    for (auto el : entries.color_entries)
    {
        Gtk::TreeModel::Row row = *(_refTreeModel_color->append());
        row[_col_color.m_col_id] = id_counter;
        row[_col_color.m_col_name] = el.short_description;
        row[_col_color.m_col_extra] = el.description;
        vec_color_callbacks.push_back(el.callback); // id -1
        if (!default_set)
        {
            _combo_color.set_active(row);
            default_set = true;
        }
        id_counter++;
    }

    _combo_color.pack_start(_col_color.m_col_id);
    _combo_color.pack_start(_col_color.m_col_name);
    //_combo_color.pack_start(_col_color.m_col_extra);

    show_all_children();
}

Functions_panel::~Functions_panel()
{
}

fractal_callback Functions_panel::get_fractal_callback()
{
    Gtk::TreeModel::iterator iter = _combo_fractal.get_active();
    if (iter)
    {
        Gtk::TreeModel::Row row = *iter;
        if (row)
        {
            //Get the data for the selected row, using our knowledge of the tree
            //model:
            int id = row[_col_fractal.m_col_id];

            return vec_frac_callbacks[id - 1];
        }
    }
}

fractal_callback Functions_panel::get_random_fractal_callback()
{
    int random_int = std::rand() % vec_frac_callbacks.size();
    _combo_fractal.set_active(random_int);
    return vec_frac_callbacks[random_int];
}

iter_callback Functions_panel::get_iter_callback()
{
    Gtk::TreeModel::iterator iter = _combo_iterations.get_active();
    if (iter)
    {
        Gtk::TreeModel::Row row = *iter;
        if (row)
        {
            //Get the data for the selected row, using our knowledge of the tree
            //model:
            int id = row[_col_iter.m_col_id];

            return vec_iter_callbacks[id - 1];
        }
    }
}
color_callback Functions_panel::get_color_callback()
{
    Gtk::TreeModel::iterator iter = _combo_color.get_active();
    if (iter)
    {
        Gtk::TreeModel::Row row = *iter;
        if (row)
        {
            //Get the data for the selected row, using our knowledge of the tree
            //model:
            int id = row[_col_color.m_col_id];

            return vec_color_callbacks[id - 1];
        }
    }
}