#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <getopt.h>
#include <string>
#include <fstream>
#include <regex>
#include "soc_desc.hpp"

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
    const auto begin = str.find_first_not_of(" \t\n\r");
    if(begin == std::string::npos)
        return std::string();

    const auto end = str.find_last_not_of(" \t\n\r");

    return str.substr(begin, end - begin + 1);
}

/* regex to match oneline document line */
std::regex g_oneline_doc_regex(
    "[[:space:]]*/\\*(.*)\\*/[[:space:]]*" /* #define and spaces */
    );
/* regex to match oneline document line */
std::regex g_oneline_special_doc_regex(
    "[[:space:]]*/\\*(.*)"
    "\\(([[:alnum:]]+)\\)[[:space:]]*"
    "\\*/[[:space:]]*" /* #define and spaces */
    );
std::regex g_oneline_special_doc2_regex(
    "[[:space:]]*//(.*)"
    "\\(([[:alnum:]]+)\\)[[:space:]]*"
    );
/* regex to match range:
 * n is the DMA channel index (0 - 2) */
std::regex g_oneline_range_doc_regex(
    "[[:space:]]*/\\*[[:space:]]+"
    "(n|m)[[:space:]]+" /* group 1: variable */
    ".*" /* junk */
    "\\(([[:digit:]]+)[[:space:]]*-[[:space:]]*([[:digit:]]+)\\)" /* group 2/3: min/max */
    "[[:space:]]*"
    "\\*/[[:space:]]*" /* #define and spaces */
    );
/* regex to match base register define:
 * #define HARB0_BASE   0xB3000000
 */
std::regex g_base_addr_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([^[:space:]]*)_BASE" /* group 1: *_BASE */
    "[[:space:]]+" /* space */
    "(0x[[:xdigit:]]+)" /* group 2: 0x* */
    "[[:space:]]*"
    );
/* regex to match indexed base register define:
 * #define DMAC_BASE(m)	(0xB3420000 + (m)*100)
 */
std::regex g_base_addr_range_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([^[:space:]]*)" /* group 1: *_BASE */
    "_BASE\\(([[:alpha:]]+)\\)" /* group 2: variable */
    "[[:space:]]+" /* space */
    "\\((.*)\\)[[:space:]]*" /* group 3: formula */
    );
/* regex to match indexed base register define:
 * #define	I2C_BASE(0)	0xB0050000
 */
std::regex g_base_addr_indexed_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([^[:space:]]*)_BASE" /* group 1: *_BASE */
    "\\(([[:digit:]]+)\\)" /* group 2: index */
    "[[:space:]]+" /* space */
    "(0x[[:xdigit:]]+)" /* group 2: 0x* */
    "[[:space:]]*"
    );
/* regex to match any definition:
 * #define AIC_FR_OFFSET		(0x00)
 */
std::regex g_any_def_value_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]_]+)" /* group 1: name */
    "[[:space:]]+" /* space */
    "(?:|\\()"
    "((?:|0x)[[:xdigit:]]+)" /* group 2: value */
    "(?:|\\))"
    "[[:space:]]*"
    "(?:|(?:/\\*(.*)\\*/))" /* group 3: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match any bit definition with doc
 * #define AIC_FR_OFFSET		(0x00)
 */
std::regex g_any_def_value_bit_doc_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block */
    "([[:alnum:]]+)_" /* group 2: reg */
    "([[:alnum:]]+)_BIT" /* group 3: field */
    "[[:space:]]+" /* space */
    "(?:|\\()"
    "((?:|0x)[[:xdigit:]]+)" /* group 4: value */
    "(?:|\\))"
    "[[:space:]]*"
    "(?:/\\*(.*)\\*/)" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register in the current block:
 * #define RTC_RCR          (RTC_BASE + 0x00)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME: I know this regex is broken if ever the address contains '(n)'
 * and the comment section contains a parenthesis
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_simple_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]_]+)" /* group 2: register name */
    "[[:space:]]+" /* space */
    "\\([[:space:]]*([[:alnum:]]+)_BASE" /* group 3: block */
    "[[:space:]]*\\+[[:space:]]*" /* + */
    "(.*)\\)" /* group 4: address formula */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register in the current block:
 * #define INTC_ISR(n)      (INTC_BASE + 0x00 + (n) * 0x20)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME: I know this regex is broken if ever the address contains '(n)'
 * and the comment section contains a parenthesis
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_range_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]_]+)" /* group 2: register name */
    "\\(([[:alpha:]]+)\\)" /* group 3: variable (n) */
    "[[:space:]]+" /* space */
    "\\(([[:space:]]*[[:alnum:]]+)_BASE" /* group 4: block */
    "[[:space:]]*\\+[[:space:]]*" /* + */
    "(.*)\\)" /* group 5: address formula */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 6: comment */
    "[[:space:]]*" /* space */
    );
std::regex g_block_reg_indexed_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]_]+)" /* group 2: register name */
    "\\(([[:digit:]]+)\\)" /* group 3: index */
    "[[:space:]]+" /* space */
    "\\([[:space:]]*([[:alnum:]]+)_BASE" /* group 3: block */
    "[[:space:]]*\\+[[:space:]]*" /* + */
    "(.*)\\)" /* group 4: address formula */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
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
    "(?:|\\((?:|\\()[[:alpha:]]+(?:|\\))\\))" /* empty or variable (n) */
    "\\)" /* end */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 4: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register def with BIT:
 * #define RTC_RGR_LOCK		BIT3
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_bitn_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)" /* group 3: field name */
    "[[:space:]]+" /* space */
    "BIT([[:digit:]]+)" /* group 4: position */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register def with BITS_H2L:
 * #define RTC_RGR_LOCK_MASK		BITS_H2L(x, RTC_RGR_LOCK_BIT)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_bits_h2l_regex(
    "#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)_MASK" /* group 3: field name */
    "[[:space:]]+" /* space */
    "BITS_H2L(\\([^\\)]+\\))" /* group 4: content */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register def with shift:
 *  #define BCH_INTES_ALL_FES	(1 << 4)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_bit_shift_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]_]+)__" /* group 2: register name */
    "([[:alnum:]_]+)" /* group 3: field name */
    "[[:space:]]+" /* space */
    "\\(1[[:space:]]*<<[[:space:]]*([[:digit:]_]+)[[:space:]]*\\)" /* group 4: bit */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register def with shift:
 *  #define BCH_INTES_ALL_FES	(1 << 4)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_bit_shift2_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)" /* group 3: field name */
    "[[:space:]]+" /* space */
    "\\(1[[:space:]]*<<[[:space:]]*([[:digit:]_]+)[[:space:]]*\\)" /* group 4: bit */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
/* regex to match register def with mask shift:
 *  #define	BCH_CR_BSEL_MASK         (0x3 << BCH_CR_BSEL_BIT)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_reg_field_mask_shift_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]_]+)__" /* group 2: register name */
    "([[:alnum:]_]+)_MASK" /* group 3: field name */
    "[[:space:]]+" /* space */
    "(\\([[:alnum:]]+[[:space:]]*<<[[:space:]]*[[:alnum:]_]+[[:space:]]*\\))" /* group 4: bit */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
    "[[:space:]]*" /* space */
    );
std::regex g_block_reg_field_mask_shift2_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)_MASK" /* group 3: field name */
    "[[:space:]]+" /* space */
    "(\\([[:alnum:]]+[[:space:]]*<<[[:space:]]*[[:alnum:]_]+[[:space:]]*\\))" /* group 4: bit */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 5: comment */
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
/* regex to match enum field with shift:
 * #define BCH_CR_BSEL_4          (0x0 << BCH_CR_BSEL_BIT)
 * There sometimes is a comment on the same line that contains the description of the register
 * FIXME I know this regex is broken if ever the bit/mask formula contains a '/'
 * NOTE this regex is a match and not a search
 */
std::regex g_block_enum_shift_bit_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]_]+)__" /* group 3: field name*/
    "([[:alnum:]_]+)" /* group 4: enum name*/
    "[[:space:]]+" /* space */
    "\\([[:space:]]*([[:alnum:]_]+)[[:space:]]*" /* group 5: submask */
    "<<[[:space:]]*([[:alnum:]_]+)_BIT[[:space:]]*\\)" /* group 6: offset */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 7: comment */
    "[[:space:]]*" /* space */
    );
std::regex g_block_enum_shift_bit2_regex(
    "[[:space:]]*#define[[:space:]]+" /* #define and spaces */
    "([[:alnum:]]+)_" /* group 1: block name */
    "([[:alnum:]]+)_" /* group 2: register name */
    "([[:alnum:]]+)_" /* group 3: field name*/
    "([[:alnum:]_]+)" /* group 4: enum name*/
    "[[:space:]]+" /* space */
    "\\([[:space:]]*([[:alnum:]_]+)[[:space:]]*" /* group 5: submask */
    "<<[[:space:]]*([[:alnum:]_]+)_BIT[[:space:]]*\\)" /* group 6: offset */
    "[[:space:]]*" /* space */
    "(?:|(?:/\\*(.*)\\*/))" /* group 7: comment */
    "[[:space:]]*" /* space */
    );

void normalize_unix(std::string& line)
{
    if(line.size() >= 1 && line.back() == '\r')
        line.pop_back();
}

std::string escape_id(const std::string& id)
{
    if(isdigit(id.front()))
        return "\"" + id + "\"";
    return id;
}

bool preprocess(const char *filename, const char *outdir)
{
    std::ofstream fout;
    if(outdir)
    {
        std::string outfile = filename;
        if(outfile.find('/') != std::string::npos)
            outfile = outfile.substr(outfile.rfind('/') + 1);
        outfile = std::string(outdir) + "/" + outfile;
        fout = std::ofstream(outfile.c_str());
        if(!fout)
            printf("Cannot open '%s' for writing\n", outfile.c_str());
    }
    std::ifstream file(filename);
    if(!file)
        return false;
    std::smatch matches;
    std::string line;
    std::string lastline;

    fout << "/**\n";
    fout << " * WARNING\n";
    fout << " * This file was autogenerated by jz_preprocess from " << filename << "\n";
    fout << " */\n";

    while(std::getline(file, line))
    {
        normalize_unix(line);
        /* comment */
        if(trim(line).empty())
            fout << "\n";
        if(std::regex_match(line, matches, g_oneline_special_doc_regex) ||
                std::regex_match(line, matches, g_oneline_special_doc2_regex))
            fout << "register " << matches.str(2) << " export \"" << trim(matches.str(1)) << "\"\n";
        else if(std::regex_match(line, matches, g_oneline_range_doc_regex))
            fout << "for " << matches.str(1) << " " << matches.str(2) << " " << matches.str(3) << "\n";
        else if(starts_with(line, "/*"))
        {
            do
            {
                normalize_unix(line);
                fout << line << "\n";
                /* end of comment ? */
                if(line.find("*/") != std::string::npos)
                    break;
            }while(std::getline(file, line));
        }
        else if(starts_with(line, "//"))
        {
            fout << line << "\n";
        }
        /* try to match some patterns */
        else if(std::regex_match(line, matches, g_base_addr_regex))
        {
            fout << "this class " << matches.str(1) << " goto " << matches.str(2);
            if(std::regex_match(lastline, matches, g_oneline_doc_regex))
                fout << " export \"" << trim(matches.str(1)) << "\"";
            fout << "\n";
        }
        else if(std::regex_match(line, matches, g_base_addr_range_regex))
        {
            fout << "this class " << matches.str(1) << " goto<" << matches.str(2) << "> "
                << "\"" << matches.str(3) << "\"";
            if(std::regex_match(lastline, matches, g_oneline_doc_regex))
                fout << " export \"" << trim(matches.str(1)) << "\"";
            fout << "\n";
        }
        else if(std::regex_match(line, matches, g_base_addr_indexed_regex))
        {
            fout << "this class " << matches.str(1) << " goto (" << matches.str(2) << ", "
                << matches.str(3) << ")";
            if(std::regex_match(lastline, matches, g_oneline_doc_regex))
                fout << " export \"" << trim(matches.str(1)) << "\"";
            fout << "\n";
        }
        else if(std::regex_match(line, matches, g_block_reg_simple_regex))
        {
            fout << "register " << matches.str(2) << " goto " << matches.str(4)
                << " export \"" << trim(matches.str(5)) << "\"\n";
        }
        else if(std::regex_match(line, matches, g_block_reg_indexed_regex))
        {
            fout << "register " << matches.str(2) << " goto (" << matches.str(3) 
                << "," << matches.str(5) << ")"
                << " export \"" << trim(matches.str(6)) << "\"\n";
        }
        else if(std::regex_match(line, matches, g_block_reg_range_regex))
        {
            fout << "register " << matches.str(2) << " goto<" << matches.str(3)
                << "> \"" << matches.str(5) << "\""
                << " export \"" << trim(matches.str(6)) << "\"\n";
        }
        else if(std::regex_match(line, matches, g_block_reg_width_regex))
        {
            fout << "register " << matches.str(3) << " sizeof " << matches.str(1) << "\n";
        }
        else if(std::regex_match(line, matches, g_block_reg_field_bitn_regex))
        {
            fout << "register " << matches.str(2) << " int " << escape_id(matches.str(3))
                << " goto " << matches.str(4);
            if(!matches.str(5).empty())
                fout << " export \"" << trim(matches.str(5)) << "\"";
            fout << "\n";
        }
        else if(std::regex_match(line, matches, g_any_def_value_regex))
        {
            fout << "const " << matches.str(1) << " " << matches.str(2) << "\n";
            /* check doc */
            if(std::regex_match(line, matches, g_any_def_value_bit_doc_regex))
            {
                fout << "register " << matches.str(2) << " int " << escape_id(matches.str(3))
                    << " export \"" << trim(matches.str(5)) << "\"\n";
            }
        }
        else if(std::regex_match(line, matches, g_block_reg_field_bits_h2l_regex))
        {
            fout << "register " << matches.str(2) << " int " << escape_id(matches.str(3))
                << " goto " << matches.str(4);
            if(!matches.str(5).empty())
                fout << " export \"" << trim(matches.str(5)) << "\"";
            fout << "\n";
        }
        /* watch the order of the matches ! */
        else if(std::regex_match(line, matches, g_block_reg_field_bit_shift_regex) ||
                std::regex_match(line, matches, g_block_reg_field_bit_shift2_regex))
        {
            fout << "register " << matches.str(2) << " int " << escape_id(matches.str(3))
                << " goto " << matches.str(4);
            if(!matches.str(5).empty())
                fout << " export \"" << trim(matches.str(5)) << "\"";
            fout << "\n";
        }
        /* watch the order of the matches ! */
        else if(std::regex_match(line, matches, g_block_reg_field_mask_shift_regex) ||
            std::regex_match(line, matches, g_block_reg_field_mask_shift2_regex))
        {
            fout << "register " << matches.str(2) << " int " << escape_id(matches.str(3))
                << " goto " << matches.str(4);
            if(!matches.str(5).empty())
                fout << " export \"" << trim(matches.str(5)) << "\"";
            fout << "\n";
        }
        /* watch the order of the matches ! */
        else if(std::regex_match(line, matches, g_block_enum_shift_bit_regex) ||
                std::regex_match(line, matches, g_block_enum_shift_bit2_regex))
        {
            fout << "register " << matches.str(2) << " int " << escape_id(matches.str(3))
                << " enum "<< escape_id(matches.str(4)) << " " << matches.str(5);
            if(!matches.str(7).empty())
                fout << " export \"" << trim(matches.str(7)) << "\"";
            fout << "\n";
        }
        else
        {
            fout << "// " << line << "\n";
        }
        lastline = line;
    }
    return true;
}

void usage()
{
    printf("usage: parse [options] <infile>\n");
    printf("options:\n");
    printf("  -?/--help   Dispaly this help\n");
    printf("  -o <file>   Output directory\n");
    exit(1);
}

int main(int argc, char **argv)
{
    const char *outdir;
    if(argc <= 1)
        usage();

    while(1)
    {
        static struct option long_options[] =
        {
            {"help", no_argument, 0, '?'},
            {0, 0, 0, 0}
        };

        int c = getopt_long(argc, argv, "?o:", long_options, NULL);
        if(c == -1)
            break;
        switch(c)
        {
            case -1:
                break;
            case '?':
                usage();
                break;
            case 'o':
                outdir = optarg;
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
    if(outdir == 0)
        printf("Warning: no output directory, dry run.\n");
    for(int i = optind; i < argc; i++)
        if(!preprocess(argv[i], outdir))
            return 1;
    return 0;
}
