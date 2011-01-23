#ifndef __lsusb_gtk__
#define __lsusb_gtk__

#include <gtkmm/window.h>
#include <gtkmm/window.h>
#include <gtkmm/stock.h>
#include <gtkmm/uimanager.h>
#include <gtkmm/box.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>
#include <gtkmm/scrolledwindow.h>

class ListUsb : public Gtk::Window
{
    public:
    ListUsb();
    virtual ~ListUsb();

    protected:
    class ModelColumns : public Gtk::TreeModelColumnRecord
    {
        public:
        ModelColumns()
        {
            add(m_col_name);
            add(m_col_value);
            add(m_col_comment);
        }

        Gtk::TreeModelColumn<Glib::ustring> m_col_name;
        Gtk::TreeModelColumn<Glib::ustring> m_col_value;
        Gtk::TreeModelColumn<Glib::ustring> m_col_comment;
    };
    
    virtual void on_quit();
    virtual void on_refresh();
    
    void parse(const char *filename);
    
    Glib::RefPtr<Gtk::UIManager> m_refUIManager;
    Glib::RefPtr<Gtk::ActionGroup> m_refActionGroup;
    Gtk::VBox m_box;
    ModelColumns m_columns;
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::TreeView m_tree_view;
    Glib::RefPtr<Gtk::TreeStore> m_ref_tree_model;
};

#endif // __lsusb_gtk__
