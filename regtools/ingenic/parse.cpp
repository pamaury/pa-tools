#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <regex>
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

/* map of (block,base address) */
std::map< std::string, soc_word_t > g_base_addr;
/* last block desc */
std::string g_block_desc;
/* last comment (can be multiline) */
std::vector< std::string > g_last_comment;
/* regex to match base register define:
 * #define HARB0_BASE   0xB3000000
 */
std::regex g_base_addr_regex(
    "^#define[[:space:]]+" /* #define and spaces */
    "([^[:space:]]*)_BASE" /* group 1: *_BASE */
    "[[:space:]]+" /* space */
    "(?:(0x[[:xdigit:]]+)" /* group 2: 0x* */
    "|([[:alnum:]]+)_BASE)" /* group 3: block */
    );
/* regex to match register in the current block:
 * #define RTC_RCR          (RTC_BASE + 0x00)
 * #define INTC_ISR(n)      (INTC_BASE + 0x00 + (n) * 0x20)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME: I know this regex is broken if ever the address contains '(n)'
 * and the comment section contains a parenthesis
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]_]+)" /* group 2: register name */
    "(?:|\\(([[:alpha:]]+)\\))" /* group 3: empty or variable (n) */
    "[[:space:]]+" /* space */
    "\\(([[:alnum:]]+)_BASE" /* group 4: block */
    "[[:space:]]*\\+[[:space:]]*" /* + */
    "(.*)\\)" /* group 5: address formula */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 6: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register width in the current block:
 * #define REG_INTC_ISR(n)		REG32(INTC_ISR((n)))
 * #define REG_RTC_RCR	REG32(RTC_RCR)
 */
std::regex g_block_reg_width_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "REG_[[:alnum:]_]+" /* register name */
    "(?:|\\([[:alpha:]]+\\))" /* empty or variable (n) */
    "[[:space:]]+" /* space */
    "REG([[:digit:]]+)" /* group 1: width */
    "\\(([[:alnum:]]+)_" /* group 2: block */
    "([[:alnum:]]+)" /* group 3: register */
    "(?:|\\([[:alpha:]]+\\))" /* empty or variable (n) */
    "\\)" /* end */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 4: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register field masks:
 * #define RTC_RGR_LOCK		(1 << 31)
 * #define RTC_RGR_ADJC_MASK	(0x3ff << RTC_RGR_ADJC_BIT)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_mask_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)" /* group 3: field name (plus _BIT or _MASK sometimes) */
    "[[:space:]]+" /* space */
    "\\([[:space:]]*([[:alnum:]_]+)[[:space:]]*" /* group 4: submask */
    "<<[[:space:]]*([[:alnum:]_]+)[[:space:]]*\\)" /* group 5: offset */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 6: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register field masks:
 * #define USB_CSR0_OUTPKTRDY	0x01
 * There sometimes is a comment on the same line that contains the description of the register
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_bit_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)" /* group 3: field name (plus _BIT or _MASK sometimes) */
    "[[:space:]]+" /* space */
    "[[:space:]]*(0x[[:xdigit:]]+)[[:space:]]*" /* group 4: mask */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match any define */
std::regex g_any_def_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]_]+)" /* group 1: define name */
    "(?:|\\([[:alpha:]]+\\))" /* empty or arguments */
    "[[:space:]]+" /* space */
    "([^/]*)" /* group 2: content */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 3: comment */
    "[[:space:]]*" /* space */
    );

struct block_addr_t
{
    static const int NO_INDEX = -1;
    int index;
    soc_addr_t addr;
    block_addr_t():index(NO_INDEX), addr(0) {}
    block_addr_t(int index, soc_addr_t addr):index(index), addr(addr) {}
};

struct field_t
{
    std::string desc;
    soc_word_t mask;
    int offset;

    int width() const
    {
        soc_word_t m = 1;
        int w = 1;
        while(m < mask)
        {
            w++;
            m = m << 1 | 1;
        }
        return w;
    }

    int last_bit() const
    {
        return offset + width() - 1;
    }
};

struct reg_t
{
    std::string desc;
    int width;
    static const int UNK_WIDTH = 0;
    int index_min;
    int index_max;
    std::string index_var; // empty is not indexed
    static const int UNK_INDEX = -1;
    std::string formula;
    std::map< std::string, field_t > field;
};

struct block_t
{
    std::string desc;
    std::vector< block_addr_t > addr;
    std::map< std::string, reg_t > regs;
};

/* List of all devices */
std::map< std::string, block_t > g_dev;

struct define_t
{
    std::string value;
    std::string comment;

    define_t() {}
    define_t(const std::string& v, const std::string& c):value(v), comment(c) {}
};

/* list of all defines */
std::map< std::string, define_t > g_def;

template<typename T>
bool parse_unsigned(const std::string& val, T& out_val, int basis = 0)
{
    char *end = nullptr;
    out_val = strtoul(val.c_str(), &end, basis);
    return *end == 0;
}

void add_base(const std::string& block, const std::string& hex, const std::string& proxy_block)
{
    /* first group is block, second is address */
    debug("BASE base %s: %s%s", block.c_str(), hex.c_str(), proxy_block.c_str());
    /* two cases: either hex value or another base */
    if(hex.empty())
    {
        auto proxy = g_base_addr.find(proxy_block);
        if(proxy != g_base_addr.end())
        {
            g_base_addr[block] = proxy->second;
            debug(" (%#x)\n", proxy->second);
        }
        else
            debug(" (unknown) -> IGNORED\n");
    }
    else
    {
        soc_addr_t addr = strtoul(hex.c_str(), NULL, 0);
        if(parse_unsigned(hex, addr))
            g_base_addr[block] = addr;
        else
            debug(" (parse error) -> IGNORED");
        debug("\n");
    }
}

bool confirm_block(const std::string& block, const std::string& addr_block)
{
    /* ignore already confirmed blocks */
    if(g_dev.find(block) != g_dev.end())
        return true;
    /* ignore if addr block is unknown */
    if(g_base_addr.find(addr_block) == g_base_addr.end())
    {
        debug("REG block addr unknown -> IGNORED\n");
        return false;
    }
    /* create block: use latest block description gathered */
    block_t bl;
    bl.desc = g_block_desc;
    /* if block and addr block are the same, just register this address
     * otherwise it must be indexed */
    if(block != addr_block)
    {
        if(addr_block.size() != block.size() + 1 || !isdigit(addr_block.back()))
        {
            debug("REG block addr format unknown -> IGNORED\n");
            return false;
        }
        /* add all indexes we can find */
        for(auto x : g_base_addr)
        {
            if(x.first.substr(0, block.size()) != block || !isdigit(x.first.back()))
                continue;
            block_addr_t ba;
            ba.index = x.first.back() - '0';
            ba.addr = x.second;
            debug("BLOCK map %s to %s index %d\n", x.first.c_str(), block.c_str(), ba.index);
            bl.addr.push_back(ba);
        }
    }
    else
        bl.addr.push_back(block_addr_t(block_addr_t::NO_INDEX, g_base_addr[addr_block]));
    info("Create block %s with description '%s' at", block.c_str(), bl.desc.c_str());
    for(auto ba : bl.addr)
        if(ba.index == block_addr_t::NO_INDEX)
            info(" 0x%x", ba.addr);
        else
            info(" (%d,0x%x)", ba.index, ba.addr);
    info("\n");
    g_dev[block] = bl;
    return true;
}

void add_reg(const std::string& block, const std::string& reg,
    const std::string& index_var, const std::string& addr_block,
    const std::string& addr_formula, const std::string& comment)
{
    if(!confirm_block(block, addr_block))
        return;
    block_t& bl = g_dev[block];
    /* check if reg already exists */
    if(bl.regs.find(reg) != bl.regs.end())
    {
        debug("REG duplicate in %s -> IGNORED\n", block.c_str());
        return;
    }
    reg_t r;
    r.desc = trim(comment);
    r.width = reg_t::UNK_WIDTH;
    r.index_var = index_var;
    r.index_min = reg_t::UNK_INDEX;
    r.index_max = reg_t::UNK_INDEX;
    r.formula = addr_formula;
    info("Create register %s in %s with description '%s' at %s", reg.c_str(),
         block.c_str(), r.desc.c_str(), addr_formula.c_str());
    if(!index_var.empty())
    {
        info(" with index %s ranging from ", index_var.c_str());
        if(r.index_min == reg_t::UNK_INDEX)
            info("?");
        else
            info("%d", r.index_min);
        if(r.index_max == reg_t::UNK_INDEX)
            info(" to ?");
        else
            info(" to %d", r.index_max);
    }
    info("\n");
    bl.regs[reg] = r;
}

void set_width(const std::string& block, const std::string& reg,
    const std::string& width)
{
    if(g_dev.find(block) == g_dev.end())
    {
        debug("WIDTH block unknown -> IGNORED\n");
        return;
    }
    block_t& bl = g_dev[block];
    if(bl.regs.find(reg) == bl.regs.end())
    {
        debug("WIDTH register unknown -> IGNORED\n");
        return;
    }
    reg_t& r = bl.regs[reg];
    if(parse_unsigned(width, r.width))
        info("Set width of %s in %s to %d\n", reg.c_str(), block.c_str(), r.width);
    else
        debug("WIDTH parse error -> IGNORED\n");
}

void add_field_mask(const std::string& block, const std::string& reg,
    std::string field, std::string mask, std::string offset,
    std::string comment)
{
    mask = trim(mask);
    offset = trim(offset);
    comment = trim(comment);
    if(ends_with(field, "_MASK") && (ends_with(offset, "_BIT") || ends_with(offset, "_OFFSET")))
        field = field.substr(0, field.size() - 5);
    /* ignore if we can't find the block */
    if(g_dev.find(block) == g_dev.end())
    {
        debug("FMASK block unknown -> IGNORED\n");
        return;
    }
    /* ignore if we can't find the register */
    block_t& bl = g_dev[block];
    if(bl.regs.find(reg) == bl.regs.end())
    {
        debug("FMASK register unknown -> IGNORED\n");
        return;
    }
    /* if the mask is not a number, it must be a known define */
    if(g_def.find(offset) != g_def.end())
    {
        define_t& d = g_def[offset];
        offset = d.value;
        debug("FMASK substitute offset with '%s'\n", offset.c_str());
        /* use this comment if we don't have one */
        if(comment.empty())
        {
            debug("FMASK substitute comment with '%s'\n", d.comment.c_str());
            comment = d.comment;
        }
    }
    /* try to parse mask and offset */
    field_t f;
    f.desc = comment;
    if(!parse_unsigned(mask, f.mask))
    {
        debug("FMASK parse mask error -> IGNORED\n");
        return;
    }
    if(!parse_unsigned(offset, f.offset))
    {
        debug("FMASK parse offset error -> IGNORED\n");
        return;
    }
    bl.regs[reg].field[field] = f;
    info("Create field %s in reg %s of block %s with mask %#x shifted %d and comment '%s'\n",
        field.c_str(), reg.c_str(), block.c_str(), f.mask, f.offset,
        comment.c_str());
}

void add_field_bit(const std::string& block, const std::string& reg,
    const std::string& field, std::string mask,
    std::string comment)
{
    mask = trim(mask);
    comment = trim(comment);
    /* ignore if we can't find the block */
    if(g_dev.find(block) == g_dev.end())
    {
        debug("FBIT block unknown -> IGNORED\n");
        return;
    }
    /* ignore if we can't find the register */
    block_t& bl = g_dev[block];
    if(bl.regs.find(reg) == bl.regs.end())
    {
        debug("FBIT register unknown -> IGNORED\n");
        return;
    }
    /* parse mask */
    field_t f;
    f.desc = comment;
    if(!parse_unsigned(mask, f.mask))
    {
        debug("FBIT parse mask error -> IGNORED\n");
        return;
    }
    f.offset = -1;
    for(int i = 0; i < 32; i++)
        if(f.mask == (1ul << i))
            f.offset = i;
    if(f.offset == -1)
    {
        debug("FBIT invalid mask -> IGNORED\n");
        return;
    }
    f.mask = 1;
     bl.regs[reg].field[field] = f;
    info("Create field %s in reg %s of block %s with mask %#x shifted %d and comment '%s'\n",
        field.c_str(), reg.c_str(), block.c_str(), f.mask, f.offset,
        comment.c_str());
}

void guess_width(const std::string& bname, const std::string& rname, reg_t& reg)
{
    if(reg.width != reg_t::UNK_WIDTH)
        return;
    int last_bit = 0;
    for(auto field : reg.field)
        last_bit = std::max(last_bit, field.second.last_bit());
    if(last_bit == 7)
        reg.width = 8;
    else if(last_bit == 15)
        reg.width = 16;
    else if(last_bit == 31)
        reg.width = 32;
    if(reg.width != reg_t::UNK_WIDTH)
    {
        info("Register %s in %s has guessed width %d\n", rname.c_str(),
            bname.c_str(), reg.width);
    }
    else
    {
        debug("Cannot guess register width of %s in %s, from last bit %d\n",
            rname.c_str(), bname.c_str(), last_bit);
    }
}

void postprocess()
{
    for(auto bli : g_dev)
    {
        std::string blname = bli.first;
        block_t& bl = bli.second;
        for(auto ri : bl.regs)
        {
            std::string regname = ri.first;
            reg_t& r = ri.second;
            guess_width(blname, regname, r);
            /* check if register has width */
            if(r.width == reg_t::UNK_WIDTH)
            {
                warn("Register %s in %s has unknown width\n", regname.c_str(),
                     blname.c_str());
            }
            /* check if indexed register uses variable */
            if(!r.index_var.empty() && r.formula.find(r.index_var) == std::string::npos)
            {
                warn("Register %s in %s is indexed but does not depend on index\n",
                    regname.c_str(), blname.c_str());
            }
        }
    }
}

void add_def(const std::string& def, const std::string& value, const std::string& comment)
{
    g_def[trim(def)] = define_t(trim(value), trim(comment));
}

void push_comment(std::string line)
{
    line = trim(line);
    if(!line.empty())
        g_last_comment.push_back(line);
}

void add_comment(const std::string& line)
{
    if(starts_with(line, " *"))
        push_comment(line.substr(2));
    else
        push_comment(line);
}

bool parse(const char *filename)
{
    std::ifstream file(filename);
    if(!file)
        return false;
    std::smatch matches;
    std::string line;
    while(std::getline(file, line))
    {
        Lline:
        /* starts with doc comment => new block */
        if(starts_with(line, "/************************************"))
        {
            debug("BLOCK begin\n");
            /* next line is of the form ' * BLOCK (desc)' but desc does not always exists*/
            if(std::getline(file, line))
            {
                g_block_desc = trim(line.substr(2));
                debug("Begin block %s\n", g_block_desc.c_str());
            }
            else
                goto Lline;
        }
        /* comment */
        else if(starts_with(line, "/*"))
        {
            g_last_comment.clear();
            line = line.substr(2);
            do
            {
                /* end of comment ? */
                if(line.find("*/") != std::string::npos)
                {
                    line = line.substr(0, line.find("*/"));
                    add_comment(line);
                    for(size_t i = 0; i < g_last_comment.size(); i++)
                        debug("COMMENT[%zu]: '%s'\n", i, g_last_comment[i].c_str());
                    break;
                }
                else
                    add_comment(line);
            }while(std::getline(file, line));
        }
        else if(starts_with(line, "//"))
        {
            push_comment(line.substr(2));
        }
        else if(std::regex_search(line, matches, g_base_addr_regex))
        {
            debug("BASE match %s\n", line.c_str());
            add_base(matches.str(1), matches.str(2), matches.str(3));
        }
        /* NOTE: match instead of search because we really want to eat as much as
         * possible of the line (because of the comment section) */
        else if(std::regex_match(line, matches, g_block_reg_regex))
        {
            debug("REG match %s\n", line.c_str());
            add_reg(matches.str(1), matches.str(2), matches.str(3), matches.str(4),
                matches.str(5), matches.str(6));
        }
        /* NOTE: match instead of search because we really want to eat as much as
         * possible of the line (because of the comment section) */
        else if(std::regex_match(line, matches, g_block_reg_field_mask_regex))
        {
            debug("FMASK match %s\n", line.c_str());
            add_field_mask(matches.str(1), matches.str(2), matches.str(3), matches.str(4),
                matches.str(5), matches.str(6));
        }
        /* NOTE: match instead of search because we really want to eat as much as
         * possible of the line (because of the comment section) */
        else if(std::regex_match(line, matches, g_block_reg_field_bit_regex))
        {
            debug("FBIT match %s\n", line.c_str());
            add_field_bit(matches.str(1), matches.str(2), matches.str(3), matches.str(4),
                matches.str(5));
        }
        else if(std::regex_match(line, matches, g_block_reg_width_regex))
        {
            debug("WIDTH match %s\n", line.c_str());
            set_width(matches.str(2), matches.str(3), matches.str(1));
        }
        /* forget last comment if this was a define */
        if(std::regex_match(line, matches, g_any_def_regex))
        {
            add_def(matches.str(1), matches.str(2), matches.str(3));
            g_block_desc = "";
            g_last_comment.clear();
        }
    }
    postprocess();
    return true;
}

void usage()
{
    printf("usage: parse [options] <header file>\n");
    printf("options:\n");
    printf("  -?/--help   Dispaly this help\n");
    printf("  -v          Verbose\n");
    printf("  -o <file>   Output file\n");
    exit(1);
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
    return 0;
}