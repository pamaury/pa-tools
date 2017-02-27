#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <sstream>
#include "soc_desc.hpp"

using soc_desc::soc_word_t;
using soc_desc::soc_addr_t;

int g_verbose = 1;
const int WARN = 1;
const int INFO = 2;
const int DEBUG = 3;

#define log(lvl, ...) do { if(g_verbose >= lvl) printf(__VA_ARGS__); }while(0)
#define info(...) log(INFO, __VA_ARGS__)
#define debug(...) log(DEBUG, __VA_ARGS__)
#define warn(...) log(WARN, __VA_ARGS__)

bool starts_with(const std::string& s, const std::string& pattern)
{
    return s.size() >= pattern.size() && s.substr(0, pattern.size()) == pattern;
}

bool ends_with(const std::string& s, const std::string& pattern)
{
    return s.size() >= pattern.size() && s.substr(s.size() - pattern.size(), pattern.size()) == pattern;
}

std::string trim(const std::string& str)
{
    const auto begin = str.find_first_not_of(" \t");
    if(begin == std::string::npos)
        return std::string();

    const auto end = str.find_last_not_of(" \t");

    return str.substr(begin, end - begin + 1);
}

template<typename T>
bool parse_unsigned(const std::string& val, T& out_val, int basis = 0)
{
    char *end = nullptr;
    out_val = strtoul(val.c_str(), &end, basis);
    return *end == 0;
}

enum token_type_t
{
    K_CLASS,
    K_EXPORT,
    K_GOTO,
    K_EXTERN,
    K_REGISTER,
    K_INT,
    K_THIS,
    K_ENUM,
    K_FOR,
    K_SIZEOF,
    K_CONST,
    T_LPAREN,
    T_RPAREN,
    T_COMMA,
    T_ID,
    T_STRING,
    T_UINT,
    T_LSHIFT,
    T_LT,
    T_GT,
    T_PARSE_ERR,
    T_EOF,
};

struct loc_t
{
    std::string file;
    int line;
    int pos;

    void init(const std::string& f)
    {
        file = f;
        line = 1;
        pos = 1;
    }

    void update(char c)
    {
        if(c == '\n')
        {
            line++;
            pos = 1;
        }
        else
            pos++;
    }
};

struct token_t
{
    loc_t loc;
    enum token_type_t type;
    std::string str;
    unsigned int uint;

    void subst(const token_t& tok, bool subst_loc)
    {
        type = tok.type;
        str = tok.str;
        uint = tok.uint;
        if(subst_loc)
            loc = tok.loc;
    }
};

/* current file */
std::ifstream g_file;
token_t g_cur_tok;

int cur_char()
{
    return g_file.peek();
}

bool next_char(char& c)
{
    if(!g_file.get(c))
        return false;
    g_cur_tok.loc.update(c);
    return true;
}

int next_char()
{
    int c = g_file.get();
    if(c != EOF)
        g_cur_tok.loc.update((char)c);
    return c;
}

token_t& cur_tok()
{
    return g_cur_tok;
}

enum token_type_t check_kw(const std::string& s)
{
    if(s == "class") return K_CLASS;
    if(s == "export") return K_EXPORT;
    if(s == "goto") return K_GOTO;
    if(s == "extern") return K_EXTERN;
    if(s == "register") return K_REGISTER;
    if(s == "for") return K_FOR;
    if(s == "int") return K_INT;
    if(s == "this") return K_THIS;
    if(s == "const") return K_CONST;
    if(s == "sizeof") return K_SIZEOF;
    if(s == "enum") return K_ENUM;
    return T_ID;
        
}

void parse_number(std::string s)
{
    long long int v = 0;
    int basis = 10;
    if(starts_with(s, "0x"))
    {
        s = s.substr(2);
        basis = 16;
    }
    for(auto c : s)
    {
        if(isdigit(c))
            v = v * basis + (c - '0');
        else if(basis == 16 && c >= 'a' && c <= 'f')
            v = v * basis + (c - 'a') + 10;
        else if(basis == 16 && c >= 'A' && c <= 'F')
            v = v * basis + (c - 'A') + 10;
        else if(c == '_')
            continue; /* ignore */
        else
        {
            g_cur_tok.str = "Bad number '" + s + "'";
            g_cur_tok.type = T_PARSE_ERR;
            return;
        }
        
    }
    g_cur_tok.uint = v;
    g_cur_tok.type = T_UINT;
}

void __next_tok()
{
    g_cur_tok.type = T_EOF;
    char c;
    while(true)
    {
        /* ignore spaces */
        while(true)
        {
            if(!next_char(c))
                return;
            if(!isspace(c) && !iscntrl(c))
                break;
        }
        /* maybe a comment ? */
        if(c == '/')
        {
            if(!next_char(c))
            {
                g_cur_tok.str = "Unexpected symbol at end of file: '/'";
                g_cur_tok.type = T_PARSE_ERR;
                return;
            }
            if(c == '/')
            {
                /* ignore until new line */
                while(next_char(c))
                    if(c == '\n')
                        break;
                continue; /* return to the beginning */
            }
            else if(c == '*')
            {
                /* ignore until end of comment */
                bool was_star = false;
                while(next_char(c))
                {
                    if(c == '/' && was_star)
                        break;
                    was_star = (c == '*');
                }
                continue; /* return to the beginning */
            }
            else
            {
                g_cur_tok.str = std::string("Unexpected symbol after '/': '") + c + "'";
                g_cur_tok.type = T_PARSE_ERR;
                return;
            }
        }
        /* identifier/keyword/number ? */
        if(isalnum(c) || c == '_')
        {
            /* parse identifier */
            std::stringstream ss;
            ss << c;
            while(true)
            {
                int cc = cur_char();
                if(isalnum(cc) || cc == '_')
                    ss << (char)next_char();
                else
                    break;
            }
            g_cur_tok.str = ss.str(); /* store how it was written */
            if(!isdigit(c))
                g_cur_tok.type = check_kw(g_cur_tok.str);
            else
                parse_number(ss.str());
            return;
        }
        /* string ? */
        if(c == '\"')
        {
            /* ignore until end of string */
            std::stringstream ss;
            while(true)
            {
                if(!next_char(c))
                {
                    g_cur_tok.str = "Unfinished string at end of file";
                    g_cur_tok.type = T_PARSE_ERR;
                    return;
                }
                if(c == '\"')
                    break;
                ss << c;
            }
            g_cur_tok.str = ss.str();
            g_cur_tok.type = T_STRING;
            return;
        }
        if(c == '(')
        {
            g_cur_tok.type = T_LPAREN;
            return;
        }
        if(c == ')')
        {
            g_cur_tok.type = T_RPAREN;
            return;
        }
        if(c == ',')
        {
            g_cur_tok.type = T_COMMA;
            return;
        }
        if(c == '<')
        {
            c = cur_char();
            if(c == '<')
            {
                g_cur_tok.type = T_LSHIFT;
                next_char();
                return;
            }
            else
            {
                g_cur_tok.type = T_LT;
                return;
            }
        }
        if(c == '>')
        {
            g_cur_tok.type = T_GT;
            return;
        }
        
        g_cur_tok.str = std::string("Unexpected symbol '") + c + "'";
        g_cur_tok.type = T_PARSE_ERR;
        return;
    }
}

void print_tok(token_t& t, int lvl = DEBUG)
{
    switch(t.type)
    {
        case K_CLASS: log(lvl, "class"); return;
        case K_EXPORT: log(lvl, "export"); return;
        case K_EXTERN: log(lvl, "extern"); return;
        case K_INT: log(lvl, "int"); return;
        case K_REGISTER: log(lvl, "register"); return;
        case K_GOTO: log(lvl, "goto"); return;
        case K_CONST: log(lvl, "const"); return;
        case K_THIS: log(lvl, "this"); return;
        case K_SIZEOF: log(lvl, "sizeof"); return;
        case K_FOR: log(lvl, "for"); return;
        case K_ENUM: log(lvl, "enum"); return;
        case T_STRING: log(lvl, "\"%s\"", t.str.c_str()); return;
        case T_UINT: log(lvl, "%uu", t.uint); return;
        case T_ID: log(lvl, "'%s'", t.str.c_str()); return;
        case T_LPAREN: log(lvl, "("); return;
        case T_RPAREN: log(lvl, ")"); return;
        case T_COMMA: log(lvl, ","); return;
        case T_LSHIFT: log(lvl, "<<"); return;
        case T_LT: log(lvl, "<"); return;
        case T_GT: log(lvl, ">"); return;
        case T_PARSE_ERR: log(lvl, "error: %s", t.str.c_str()); return;
        case T_EOF: log(lvl, "eof"); return;
        default: log(lvl, "?");
    }
}

void print_loc(const loc_t& l, int lvl = DEBUG)
{
    log(lvl, "%s:%d:%d", l.file.c_str(), l.line, l.pos);
}

token_t& next_tok()
{
    __next_tok();
    print_tok(cur_tok(), DEBUG);
    return cur_tok();
}

void start_tok(const std::string& file)
{
    g_cur_tok.loc.init(file);
    next_tok();
}

/* list of constants */
std::map< std::string, token_t > g_const;
/* soc */
soc_desc::soc_t g_soc;
/* current node/register */
soc_desc::soc_ref_t g_cur_soc;
soc_desc::node_ref_t g_cur_node;
soc_desc::register_ref_t g_cur_reg;
soc_desc::field_ref_t g_cur_field;

#define logl(lvl, loc, ...) do { if(g_verbose >= lvl) { print_loc(loc, lvl); printf(": "); printf(__VA_ARGS__); } }while(0)
#define infol(...) logl(INFO, __VA_ARGS__)
#define debugl(...) logl(DEBUG, __VA_ARGS__)
#define warnl(...) logl(WARN, __VA_ARGS__)

void set_soc_attr(const loc_t& loc, soc_desc::soc_t& soc, const std::string& attr,  const std::string& val)
{
    if(attr == "author")
        soc.author.push_back(val);
    else if(attr == "isa")
        soc.isa = val;
    else if(attr == "version")
        soc.version = val;
    else if(attr == "name")
        soc.name = val;
    else
        warnl(loc, "ignore soc attr %s = '%s'\n", attr.c_str(), val.c_str());
}

void set_node_attr(const loc_t& loc, soc_desc::node_t& node, const std::string& attr,  const std::string& val)
{
    warnl(loc, "ignore node attr %s = '%s'\n", attr.c_str(), val.c_str());
}

void set_reg_attr(const loc_t& loc, soc_desc::register_t& reg, const std::string& attr,  const std::string& val)
{
    warnl(loc, "ignore reg attr %s = '%s'\n", attr.c_str(), val.c_str());
}

/* substitute constants in the formula */
std::string formula_subst_const(const loc_t& loc, const std::string& formula, const std::string& var)
{
    std::ostringstream oss;
    bool in_number = false;
    for(size_t i = 0; i < formula.size(); i++)
    {
        if(isdigit(formula[i]))
            in_number = true;
        if(in_number && !isalnum(formula[i]))
            in_number = false;
        if(in_number || !isalpha(formula[i]))
        {
            oss << formula[i];
            continue;
        }
        size_t j = i;
        while(j < formula.size() && (isalnum(formula[j]) || formula[j] == '_'))
            j++;
        std::string id = formula.substr(i, j - i);
        if(id != var)
        {
            auto ci = g_const.find(id);
            if(ci == g_const.end())
            {
                warnl(loc, "formula '%s' uses unknown constant '%s'\n", formula.c_str(),
                    id.c_str());
            }
            else if(ci->second.type != T_UINT)
            {
                warnl(loc, "formula '%s' uses constant '%s' which is not a number\n", formula.c_str(),
                    id.c_str());
            }
            else
                id = ci->second.str; /* take raw representation of the number */
        }
        oss << id;
        i = j - 1;
    }
    return oss.str();
}

void set_node_range_addr(const loc_t& loc, soc_desc::node_t& node, const std::string& varname, soc_word_t start,
    soc_word_t end, const std::string& formula)
{
    if(node.instance.size() != 0)
    {
        warnl(loc, "Node already has an address\n");
        return;
    }
    node.instance.resize(1);
    node.instance[0].name = node.name;
    node.instance[0].id = 42;
    node.instance[0].type = soc_desc::instance_t::RANGE;
    node.instance[0].range.type = soc_desc::range_t::FORMULA;
    node.instance[0].range.first = start;
    node.instance[0].range.count = end - start + 1;
    node.instance[0].range.variable = varname;
    node.instance[0].range.formula = formula_subst_const(loc, formula, varname);
}

void set_reg_range_addr(const loc_t& loc, soc_desc::register_ref_t& reg, const std::string& varname,
    soc_word_t start, soc_word_t end, const std::string& formula)
{
    set_node_range_addr(loc, *reg.node().get(), varname, start, end, formula);
}

void set_node_addr(const loc_t& loc, soc_desc::node_t& node,  std::vector<soc_word_t>& list)
{
    if(list.size() == 1)
    {
        if(node.instance.size() != 0)
        {
            warnl(loc, "Node already has an address\n");
            return;
        }
        node.instance.resize(1);
        node.instance[0].name = node.name;
        node.instance[0].id = 42;
        node.instance[0].type = soc_desc::instance_t::SINGLE;
        node.instance[0].addr = list[0];
    }
    else if(list.size() == 2)
    {
        if(node.instance.size() != 0)
        {
            if(node.instance[0].type != soc_desc::instance_t::RANGE)
            {
                warnl(loc, "Node already has a non-range address\n");
                return;
            }
            if(node.instance[0].range.type != soc_desc::range_t::LIST)
            {
                warnl(loc, "Node already has a range non-list address\n");
                return;
            }
            if(list[0] != node.instance[0].range.first + node.instance[0].range.list.size())
            {
                warnl(loc, "Node addresses must be given with consecutive indexes\n");
                return;
            }
        }
        else
        {
            node.instance.resize(1);
            node.instance[0].name = node.name;
            node.instance[0].id = 42;
            node.instance[0].type = soc_desc::instance_t::RANGE;
            node.instance[0].range.type = soc_desc::range_t::LIST;
            node.instance[0].range.first = list[0];
        }
        node.instance[0].range.list.push_back(list[1]);
    }
    else
    {
        warnl(loc, "Expected goto statement with one or two number, got %zu\n", list.size());
    }
}

void set_reg_addr(const loc_t& loc, soc_desc::register_ref_t& reg,  std::vector<soc_word_t>& list)
{
    set_node_addr(loc, *reg.node().get(), list);
}

void set_field_addr(const loc_t& loc, soc_desc::field_t& field,  std::vector<soc_word_t>& list)
{
    if(list.size() == 1)
    {
        field.pos = list[0];
        field.width = 1;
    }
    else if(list.size() == 2)
    {
        if(list[0] < list[1])
        {
            warnl(loc, "Invalid field bitrange: %d:%d\n", list[0], list[1]);
            return;
        }
        field.pos = list[1];
        field.width = list[0] - list[1] + 1;
    }
    else
    {
        warnl(loc, "Expected goto statement with one or two number, got %zu\n", list.size());
    }
}

void check_const(token_t& tok, bool subst_loc = false)
{
    if(tok.type == T_ID && g_const.find(tok.str) != g_const.end())
        tok.subst(g_const[tok.str], subst_loc);
}

void process_shift(soc_word_t& mask, soc_word_t& shift)
{
    int cnt = 0;
    while(mask & 1)
    {
        cnt++;
        mask >>= 1;
    }
    mask = shift + cnt - 1;
}

bool parse(const char *filename)
{
    g_file = std::ifstream(filename);
    if(!g_file)
        return false;
    /* init */
    g_cur_soc = soc_desc::soc_ref_t(&g_soc);
    g_cur_node.reset();
    g_cur_reg.reset();
    g_cur_field.reset();
    g_const.clear();
    std::map<std::string, std::pair<soc_word_t, soc_word_t>> ranges;
   /* parse */
    info("Processing file '%s'\n", filename);
    start_tok(filename);
    while(cur_tok().type != T_EOF)
    {
        std::string expected = "";
        switch(cur_tok().type)
        {
            case K_THIS:
                g_cur_node = g_cur_soc.root();
                g_cur_reg.reset();
                g_cur_field.reset();
                next_tok();
                break;
            case K_SIZEOF:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_UINT)
                {
                    expected = "number";
                    goto Lerr;
                }
                if(!g_cur_reg.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No register to set size to %u\n", cur_tok().uint);
                    return false;
                }
                g_cur_reg.get()->width = cur_tok().uint;
                next_tok();
                break;
            }
            case K_FOR:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID)
                {
                    expected = "identifier";
                    goto Lerr;
                }
                std::string name = cur_tok().str;
                if(next_tok().type != T_UINT)
                {
                    expected = "number";
                    goto Lerr;
                }
                soc_word_t min = cur_tok().uint;
                if(next_tok().type != T_UINT)
                {
                    expected = "number";
                    goto Lerr;
                }
                soc_word_t max = cur_tok().uint;
                if(min > max)
                {
                    warnl(loc, "Compile error\n");
                    info("Ranges with start greater than end\n");
                    return false;
                }
                ranges[name] = std::make_pair(min, max);
                next_tok();
                break;
            }
            case K_CONST:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID)
                {
                    expected = "identifier";
                    goto Lerr;
                }
                std::string name = cur_tok().str;
                if(g_const.find(name) != g_const.end())
                {
                    warnl(loc, "There is already a constant named '%s'\n", name.c_str());
                    return false;
                }
                next_tok();
                if(cur_tok().type == T_STRING || cur_tok().type == T_UINT || cur_tok().type == T_ID)
                {
                    g_const[name] = cur_tok();
                    check_const(g_const[name]);
                }
                else
                {
                    expected = "string, number or identifier";
                    goto Lerr;
                }
                next_tok();
                break;
            }
            case K_ENUM:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID && cur_tok().type != T_UINT && cur_tok().type != T_STRING)
                {
                    expected = "identifier, string or number";
                    goto Lerr;
                }
                std::string name = cur_tok().str; /* note: take raw string even for uint */
                if(next_tok().type != T_UINT)
                {
                    expected = "number";
                    goto Lerr;
                }
                if(!g_cur_field.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No context to create enum '%s'\n", cur_tok().str.c_str());
                    return false;
                }
                soc_desc::enum_ref_t e = g_cur_field.create_enum();
                e.get()->name = name;
                e.get()->value = cur_tok().uint;
                next_tok();
                break;
            }
            case K_EXPORT:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_STRING)
                {
                    expected = "string";
                    goto Lerr;
                }
                if(!g_cur_node.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No context to set title to '%s'\n", cur_tok().str.c_str());
                    return false;
                }
                if(g_cur_field.valid())
                    g_cur_field.get()->desc = cur_tok().str;
                else if(g_cur_reg.valid())
                    g_cur_reg.node().get()->title = cur_tok().str;
                else if(g_cur_node.is_root())
                    g_soc.title = cur_tok().str;
                else
                    g_cur_node.get()->title = cur_tok().str;
                next_tok();
                break;
            }
            case K_EXTERN:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID)
                {
                    expected = "identifier";
                    goto Lerr;
                }
                std::string attr = cur_tok().str;
                if(next_tok().type != T_STRING)
                {
                    expected = "string";
                    goto Lerr;
                }
                if(!g_cur_node.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No context to set attribute '%s' to '%s'\n", attr.c_str(), cur_tok().str.c_str());
                    return false;
                }
                if(g_cur_node.is_root())
                    set_soc_attr(loc, g_soc, attr, cur_tok().str);
                else if(g_cur_reg.valid())
                    set_reg_attr(loc, *g_cur_reg.get(), attr, cur_tok().str);
                else
                    set_node_attr(loc, *g_cur_node.get(), attr, cur_tok().str);
                next_tok();
                break;
            }
            case K_CLASS:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID)
                {
                    expected = "identifier";
                    goto Lerr;
                }
                std::string cl = cur_tok().str;
                if(!g_cur_node.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No context to create node '%s'\n", cur_tok().str.c_str());
                    return false;
                }
                /* create node if necessary */
                if(!g_cur_node.child(cl).valid())
                {
                    soc_desc::node_ref_t n = g_cur_node.create();
                    n.get()->name = cl;
                }
                g_cur_node = g_cur_node.child(cl);
                g_cur_reg.reset();
                g_cur_field.reset();
                next_tok();
                break;
            }
            case K_REGISTER:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID)
                {
                    expected = "identifier";
                    goto Lerr;
                }
                std::string reg = cur_tok().str;
                if(!g_cur_node.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No context to create register '%s'\n", cur_tok().str.c_str());
                    return false;
                }
                /* create node if necessary */
                if(!g_cur_node.child(reg).valid())
                {
                    soc_desc::node_ref_t n = g_cur_node.create();
                    n.get()->name = reg;
                    n.create_reg();
                }
                g_cur_reg = g_cur_node.child(reg).reg();
                g_cur_field.reset();
                next_tok();
                break;
            }
            case K_INT:
            {
                loc_t loc = cur_tok().loc;
                if(next_tok().type != T_ID && cur_tok().type != T_STRING)
                {
                    expected = "identifier or identifier";
                    goto Lerr;
                }
                std::string field = cur_tok().str; /* both id and string use .str */
                if(!g_cur_reg.valid())
                {
                    warnl(loc, "Compile error\n");
                    info("No context to create field '%s'\n", cur_tok().str.c_str());
                    return false;
                }
                /* create field if necessary */
                if(!g_cur_reg.field(field).valid())
                {
                    soc_desc::field_ref_t n = g_cur_reg.create_field();
                    n.get()->name = field;
                }
                g_cur_field = g_cur_reg.field(field);
                next_tok();
                break;
            }
            case K_GOTO:
            {
                loc_t loc = cur_tok().loc;
                /* range ? */
                if(next_tok().type == T_LT)
                {
                    if(next_tok().type != T_ID)
                    {
                        expected = "identifier";
                        goto Lerr;
                    }
                    auto range_it = ranges.find(cur_tok().str);
                    if(range_it == ranges.end())
                    {
                        warnl(cur_tok().loc, "Compile error\n");
                        info("There is no range named '%s'\n", cur_tok().str.c_str());
                        return false;
                    }
                    if(next_tok().type != T_GT)
                    {
                        expected = ">";
                        goto Lerr;
                    }
                    /* next must be a string */
                    if(next_tok().type != T_STRING)
                    {
                        expected = "string";
                        goto Lerr;
                    }
                    if(g_cur_field.valid())
                    {
                        warnl(loc, "Compile error\n");
                        info("Only nodes and registers can have rage addresses\n");
                        return false;
                    }
                    else if(g_cur_reg.valid())
                        set_reg_range_addr(loc, g_cur_reg, range_it->first,
                            range_it->second.first, range_it->second.second,
                            cur_tok().str);
                    else if(g_cur_node.valid() && !g_cur_node.is_root())
                        set_node_range_addr(loc, *g_cur_node.get(), range_it->first,
                            range_it->second.first, range_it->second.second,
                            cur_tok().str);
                    else
                    {
                        warnl(loc, "Compile error\n");
                        info("No context to set range address to '%s'\n", cur_tok().str.c_str());
                        return false;
                    }
                    next_tok();
                    break;
                }

                bool paren = false;
                if(cur_tok().type == T_LPAREN)
                {
                    paren = true;
                    next_tok();
                }
                check_const(cur_tok());
                if(cur_tok().type != T_UINT)
                {
                    expected = "number";
                    goto Lerr;
                }
                std::vector<soc_word_t> list;
                list.push_back(cur_tok().uint);
                next_tok();
                if(paren)
                {
                    /* special case of x << y */
                    if(cur_tok().type == T_LSHIFT)
                    {
                        check_const(next_tok());
                        if(cur_tok().type != T_UINT)
                        {
                            expected = "number or constant";
                            goto Lerr;
                        }
                        list.push_back(cur_tok().uint);
                        process_shift(list[0], list[1]);
                        next_tok();
                    }
                    while(cur_tok().type == T_COMMA)
                    {
                        next_tok();
                        check_const(cur_tok());
                        if(cur_tok().type != T_UINT)
                        {
                            expected = "number or constant";
                            goto Lerr;
                        }
                        list.push_back(cur_tok().uint);
                        next_tok();
                    }
                    if(cur_tok().type != T_RPAREN)
                    {
                        expected = ")";
                        goto Lerr;
                    }
                    next_tok();
                }
                if(g_cur_field.valid())
                    set_field_addr(loc, *g_cur_field.get(), list);
                else if(g_cur_reg.valid())
                    set_reg_addr(loc, g_cur_reg, list);
                else if(g_cur_node.valid() && !g_cur_node.is_root())
                    set_node_addr(loc, *g_cur_node.get(), list);
                else
                {
                    warnl(loc, "Compile error\n");
                    info("No context to set address to '%u'\n", list[0]);
                    return false;
                }
                break;
            }
            default:
                expected = "statement";
                goto Lerr;
        }
        continue;
    Lerr:
        warnl(cur_tok().loc, "Parse error\n");
        info("Expected %s, got ", expected.c_str());
        print_tok(cur_tok(), INFO);
        info("\n");
        return true;
    }

    return true;
}

void usage()
{
    printf("usage: parse [options] <header files>\n");
    printf("options:\n");
    printf("  -?/--help   Dispaly this help\n");
    printf("  -v          Verbose\n");
    printf("  -o <file>   Output file\n");
    exit(1);
}

void print_context(const soc_desc::error_context_t& ctx)
{
    for(size_t j = 0; j < ctx.count(); j++)
    {
        soc_desc::error_t e = ctx.get(j);
        switch(e.level())
        {
            case soc_desc::error_t::INFO: printf("[INFO]"); break;
            case soc_desc::error_t::WARNING: printf("[WARN]"); break;
            case soc_desc::error_t::FATAL: printf("[FATAL]"); break;
            default: printf("[UNK]"); break;
        }
        if(e.location().size() != 0)
            printf(" %s:", e.location().c_str());
        printf(" %s\n", e.message().c_str());
    }
}

int main(int argc, char **argv)
{
    const char *outfile;
    if(argc <= 1)
        usage();

    while(1)
    {
        static struct option long_options[] =
        {
            {"help", no_argument, 0, '?'},
            {0, 0, 0, 0}
        };

        int c = getopt_long(argc, argv, "?vo:", long_options, NULL);
        if(c == -1)
            break;
        switch(c)
        {
            case -1:
                break;
            case '?':
                usage();
                break;
            case 'v':
                g_verbose++;
                break;
            case 'o':
                outfile = optarg;
                break;
            default:
                abort();
        }
    }
    if(argc == optind)
    {
        printf("You need at least one header file file\n");
        return 3;
    }
    if(outfile == 0)
        printf("Warning: no output file, dry run.\n");
    for(int i = optind; i < argc; i++)
        if(!parse(argv[i]))
            return 1;
    if(outfile)
    {
        soc_desc::error_context_t error_ctx;
        if(!soc_desc::produce_xml(outfile, g_soc, error_ctx))
        {
            printf("Cannot write output file:\n");
            print_context(error_ctx);
        }
    }
    return 0;
}