#include <gtkmm/main.h>
#include "lsusb_gtk.hpp"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <cassert>

ListUsb::ListUsb()
{
    set_title("lsusb");
    maximize();
    
    add(m_box);
    m_scrolled_window.add(m_tree_view);
    m_scrolled_window.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);

    m_refActionGroup=Gtk::ActionGroup::create();
    m_refActionGroup->add(Gtk::Action::create("Quit", Gtk::Stock::QUIT),
          sigc::mem_fun(*this, &ListUsb::on_quit));
    m_refActionGroup->add(Gtk::Action::create("Refresh", Gtk::Stock::REFRESH),
          sigc::mem_fun(*this, &ListUsb::on_refresh));
  
    m_refUIManager=Gtk::UIManager::create();
    m_refUIManager->insert_action_group(m_refActionGroup);

    add_accel_group(m_refUIManager->get_accel_group());

    Glib::ustring ui_info = 
        "<ui>"
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='Refresh'/>"
        "    <toolitem action='Quit'/>"
        "  </toolbar>"
        "</ui>";

    #ifdef GLIBMM_EXCEPTIONS_ENABLED
    try
    {
        m_refUIManager->add_ui_from_string(ui_info);
    }
    catch(const Glib::Error& ex)
    {
        fprintf(stderr,"building menus failed: %s",ex.what().c_str());
    }
    #else
    std::auto_ptr<Glib::Error> ex;
    m_refUIManager->add_ui_from_string(ui_info,ex);
    if(ex.get())
    {
        fprintf(stderr,"building menus failed: %s",ex->what());
    }
    #endif //GLIBMM_EXCEPTIONS_ENABLED

    Gtk::Widget* pToolbar = m_refUIManager->get_widget("/ToolBar") ;
    if(pToolbar)
        m_box.pack_start(*pToolbar,Gtk::PACK_SHRINK);
    m_box.pack_start(m_scrolled_window);

    m_ref_tree_model=Gtk::TreeStore::create(m_columns);
    m_tree_view.set_model(m_ref_tree_model);
    
    //Add the TreeView's view columns:
    Gtk::TreeViewColumn col_name("Name",m_columns.m_col_name);
    Gtk::TreeViewColumn col_value("Value",m_columns.m_col_value);
    Gtk::TreeViewColumn col_comment("Comment",m_columns.m_col_comment);
    
    col_name.set_resizable();
    col_value.set_resizable();
    col_comment.set_resizable();
    
    m_tree_view.append_column(col_name);
    m_tree_view.append_column(col_value);
    m_tree_view.append_column(col_comment);

    show_all_children();
    
    on_refresh();
}

ListUsb::~ListUsb()
{
}

void ListUsb::on_quit()
{
    hide();
}

void ListUsb::on_refresh()
{
    const char *filename="temp.txt";
    const char *command="lsusb -v > temp.txt";
    
    m_ref_tree_model->clear();
    
    int ret=system(command);
    
    if(ret==0)
        parse(filename);
    
    ::remove(filename);
}

size_t get_left_padding(const std::string& str)
{
    size_t i=0;
    while(i<str.size() && str[i]==' ')
        i++;
    return i;
}

std::string trim(const std::string& str)
{
    size_t left=0;
    while(left<str.size() && str[left]==' ')
        left++;
    if(left==str.size())
        return std::string();
    // we can safely assume that str.size()>0
    size_t right=str.size()-1;
    // we can safely assume that right>0 at any time
    while(str[right]==' ')
        right--;
    
    assert(left<str.size() && right<str.size() && left<=right);
    return str.substr(left,right-left+1);
}

void ListUsb::parse(const char *filename)
{
    std::ifstream f(filename);
    std::string str;
    std::vector<Gtk::TreeStore::iterator> stack;
    
    const size_t indent_step=2;
    std::vector<size_t> possible_value_last_pos;
    
    // order is important !
    possible_value_last_pos.push_back(22);// for hubs
    possible_value_last_pos.push_back(24);// usual value
    
    while(getline(f,str))
    {
        // ignore empty line
        if(str.size()==0)
            continue;
        // get padding
        size_t indent=get_left_padding(str);
        // trim left
        str.erase(0,indent);
        
        // ignore ill-formed lined
        if(indent%indent_step!=0)
            continue;
        indent/=indent_step;
        
        std::string name;
        std::string value;
        std::string comment;
        bool ok_value=false;
        
        // default behaviour
        name=str;
        // special cases for descriptive lines
        // and also for device announcement lines
        if(str[str.size()-1]==':' || str.substr(0,3)=="Bus")
            goto Ladd;
        
        for(size_t pvlp=0;pvlp<possible_value_last_pos.size();pvlp++)
        {
            size_t value_last_pos=possible_value_last_pos[pvlp];
            size_t value_first_pos=possible_value_last_pos[pvlp];
            // try to see if there is a value
            if(str.size()<=value_last_pos || !isxdigit(str[value_last_pos]))
                continue;
            
            // it's possible so read back the value: accept hex digits, 'x' and '.'
            bool ok=true;
            
            while(value_first_pos>0)
            {
                char c=str[value_first_pos];
                if(c==' ')
                    break;
                else if(isxdigit(c) || c=='.' || c=='x')
                    value_first_pos--;
                else
                {
                    ok=false;
                    break;
                }
            }
            
            if(!ok)
                continue;
            
            // we've got a value, try to read forward to pick a value unit (e.g mA)
            while(value_last_pos<str.size() && str[value_last_pos]!=' ')
                value_last_pos++;
            
            name=trim(str.substr(0,value_first_pos));
            value=str.substr(value_first_pos,value_last_pos+1-value_first_pos);
            
            if((value_last_pos+1)<str.size())
                comment=trim(str.substr(value_last_pos+1));
            
            ok_value=true;
            break;
        }
        
        if(!ok_value)
            goto Ladd;
        
        Ladd:
        // try to find a parent
        // special case for device line
        if(indent!=0 || str.substr(0,3)!="Bus")
            indent++;
        
        Gtk::TreeStore::iterator it;
        
        if(indent==0)
        {
            it=m_ref_tree_model->append();
        }
        else
        {
            size_t par_level=indent-1;
            if(par_level>=stack.size())
                continue;// ignore line
            it=m_ref_tree_model->append(stack[par_level]->children());
        }
        
        // add to stack
        if(indent==stack.size())
            stack.push_back(it);
        else
            stack[indent]=it;
        
        Gtk::TreeModel::Row row=*it;
        row[m_columns.m_col_name]=name;
        row[m_columns.m_col_value]=value;
        row[m_columns.m_col_comment]=comment;
    }
    
    f.close();
}

int main(int argc,char **argv)
{
  Gtk::Main kit(argc,argv);

  ListUsb lsusb;
  Gtk::Main::run(lsusb);

  return 0;
}

