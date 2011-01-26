#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <stdarg.h>
#include <time.h>
#include <dirent.h>
#include "pe.h"

#define ADD_PHYS_MAP

#if 1 /* ANSI colors */

#	define color(a) printf("%s",a)
char OFF[] 		= { 0x1b, 0x5b, 0x31, 0x3b, '0', '0', 0x6d, '\0' };

char GREY[] 	= { 0x1b, 0x5b, 0x31, 0x3b, '3', '0', 0x6d, '\0' };
char RED[] 		= { 0x1b, 0x5b, 0x31, 0x3b, '3', '1', 0x6d, '\0' };
char GREEN[] 	= { 0x1b, 0x5b, 0x31, 0x3b, '3', '2', 0x6d, '\0' };
char YELLOW[] 	= { 0x1b, 0x5b, 0x31, 0x3b, '3', '3', 0x6d, '\0' };
char BLUE[] 	= { 0x1b, 0x5b, 0x31, 0x3b, '3', '4', 0x6d, '\0' };

#else
	/* disable colors */
#	define color(a)
#endif

struct mem_region_t
{
    uint32_t start;
    uint32_t end;
    char *name;
    struct mem_region_t *next;
};

struct mem_region_tree_t
{
    uint32_t start;
    uint32_t end;
    char *name;
    struct mem_region_tree_t *next;
    struct mem_region_tree_t *child;
};

struct lookup_entry_t
{
    uint16_t ord;
    char *name;
    struct lookup_entry_t *next;
};

struct lookup_cache_t
{
    char *dll;
    struct lookup_entry_t *entries;
    struct lookup_cache_t *next;
};

size_t g_sz; /* file size */
uint8_t *g_buf; /* file content */
#define PREFIX_SIZE     4096
char g_ord_import_lookup_prefix[PREFIX_SIZE];
struct lookup_cache_t *g_lookup_cache = NULL;
struct mem_region_t *g_regions = NULL;
size_t g_nr_regions = 0;
char g_name_buffer[4096 * 2];

char *dup(char *str)
{
    size_t len = 1 + strlen(str);
    char *cpy = malloc(len * sizeof(char));
    memcpy(cpy, str, len);
    return cpy;
}

void add_memory_region(uint32_t start, uint32_t end, char *name)
{
    if(start == end)
        return;
    struct mem_region_t *region = malloc(sizeof(struct mem_region_t));
    region->start = start;
    region->end = end;
    region->name = dup(name);
    region->next = g_regions;
    g_regions = region;
    g_nr_regions++;
}

void add_memory_region_by_size(uint32_t start, uint32_t size, char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vsnprintf(g_name_buffer, sizeof(g_name_buffer), fmt, va);
    va_end(va);
    add_memory_region(start, start + size, g_name_buffer);
}

void add_memory_region_by_range(uint32_t start, uint32_t end, char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);
    vsnprintf(g_name_buffer, sizeof(g_name_buffer), fmt, va);
    va_end(va);
    add_memory_region(start, end, g_name_buffer);
}

int compare_mem_regions(const void *_a, const void *_b)
{
    const struct mem_region_tree_t *a = _a;
    const struct mem_region_tree_t *b = _b;
    if(a->start == b->start)
        return b->end - a->end;
    return a->start - b->start;
}

struct mem_region_tree_t *insert_gap(struct mem_region_tree_t *next, uint32_t start, uint32_t end)
{
    struct mem_region_tree_t *gap = malloc(sizeof(struct mem_region_tree_t));
    gap->start = start;
    gap->end = end;
    snprintf(g_name_buffer, sizeof(g_name_buffer), "%s<gap %#x bytes>", GREY, end - start);
    gap->name = dup(g_name_buffer);
    gap->next = next;
    gap->child = NULL;
    return gap;
}

bool contains(struct mem_region_tree_t *a, struct mem_region_tree_t *b)
{
    return a->start <= b->start && b->end <= a->end;
}

struct mem_region_tree_t *build_tree(struct mem_region_tree_t *regions,
    uint32_t start, uint32_t end)
{
    struct mem_region_tree_t *first = regions;
    if(start < regions->start)
        first = insert_gap(regions, start, regions->start);

    //printf("%s!!start=%#08x end=%#08x!!\n", GREY, start, end);
    while(regions)
    {
        //printf("%scur reg: %s\n", RED, regions->name);
        /* nested ? */
        if(regions->next && contains(regions, regions->next))
        {
            //printf("%s!!nested!!\n", GREY);
            /* advance in the chain to keep all nested ones */
            regions->child = regions->next;
            while(regions->next)
            {
                if(regions->next->next == NULL)
                {
                    regions->next = NULL;
                    break;
                }
                if(!contains(regions, regions->next->next))
                {
                    /* cut chain */
                    //printf("%s!!last of nested chain: %s%s!!\n", GREY, regions->next->name, GREY);
                    struct mem_region_tree_t *future_next = regions->next->next;
                    regions->next->next = NULL;
                    regions->next = future_next;
                    break;
                }
                else
                    regions->next = regions->next->next;
            }
            /* build recursively */
            regions->child = build_tree(regions->child, regions->start, regions->end);
        }
        /* go to next */
        uint32_t next_start = end;
        if(regions->next)
            next_start = regions->next->start;
        if(regions->end < next_start)
        {
            regions->next = insert_gap(regions->next, regions->end, next_start);
            regions = regions->next;
        }
        regions = regions->next;
    }
    //printf("%s!!done!!\n", GREY);

    return first;
}

struct mem_region_tree_t *build_memory_tree()
{
    if(g_nr_regions == 0)
        return NULL;
    struct mem_region_tree_t *sorted_regions = malloc(g_nr_regions * sizeof(struct mem_region_tree_t));
    struct mem_region_t *reg = g_regions;
    for(size_t i = 0; i < g_nr_regions; i++, reg = reg->next)
    {
        sorted_regions[i].start =  reg->start;
        sorted_regions[i].end =  reg->end;
        sorted_regions[i].name =  reg->name;
    }
    qsort(sorted_regions, g_nr_regions, sizeof(struct mem_region_tree_t), &compare_mem_regions);
    for(size_t i = 0; i < g_nr_regions; i++)
    {
        sorted_regions[i].next = &sorted_regions[i + 1];
        sorted_regions[i].child = NULL;
    }
    sorted_regions[g_nr_regions - 1].next = NULL;

    return build_tree(sorted_regions, sorted_regions[0].start,
        sorted_regions[g_nr_regions - 1].end);
}

typedef void (*tree_printer_t)(struct mem_region_tree_t *reg, void *data, size_t depth);

void print_memory_tree2(struct mem_region_tree_t *tree, tree_printer_t printer, void *data, size_t depth)
{
    while(tree)
    {
        printer(tree, data, depth);
        if(tree->child)
            print_memory_tree2(tree->child, printer, data, depth + 1);
        tree = tree->next;
    }
}

void print_memory_tree(struct mem_region_tree_t *tree, tree_printer_t printer, void *data)
{
    print_memory_tree2(tree, printer, data, 0);
}

void *load_file(char *name, size_t *size)
{
    FILE *f = fopen(name, "rb");
    if(f == NULL)
    {
        printf("Cannot open '%s' for reading !\n", name);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    *size = ftell(f);
    fseek(f, 0, SEEK_SET);
    void *buf = malloc(*size);
    if(buf != NULL)
        if(fread(buf, *size, 1, f) != 1)
        {
            printf("Cannot read '%s' !\n", name);
            free(buf);
            buf = NULL;
        }
    fclose(f);
    return buf;
}

void file_print(struct mem_region_tree_t *reg, void *data, size_t depth)
{
    FILE *f = data;
    for(size_t i = 0; i < depth; i++)
        g_name_buffer[2 * i]  = g_name_buffer[2 * i + 1] = ' ';
    g_name_buffer[2 * depth] = 0;
    fprintf(f, "%s0x%08x    %s0x%08x    %s%s\n", YELLOW, reg->start,
        YELLOW, reg->end, g_name_buffer, reg->name);
}

const char *get_machine_string(uint16_t machine)
{
    switch(machine)
    {
        case IMAGE_FILE_MACHINE_ARM: return "arm";
        case IMAGE_FILE_MACHINE_THUMB: return "thumb";
        case IMAGE_FILE_MACHINE_I386: return "x86";
        case IMAGE_FILE_MACHINE_AMD64: return "x64";
        default: return "unknown";
    }
}

const char *get_subsystem_string(uint16_t subsystem)
{
    switch(subsystem)
    {
        case IMAGE_SUBSYSTEM_NATIVE: return "native";
        case IMAGE_SUBSYSTEM_WINDOWS_GUI: return "windows gui";
        case IMAGE_SUBSYSTEM_WINDOWS_CUI: return "windows cui";
        case IMAGE_SUBSYSTEM_NATIVE_WINDOWS: return "native windows";
        case IMAGE_SUBSYSTEM_WINDOWS_CE_GUI: return "wince gui";
        case IMAGE_SUBSYSTEM_XBOX: return "xbox";
        default: return "unknown";
    }
}

const char *get_data_directory_string(size_t i)
{
    switch(i)
    {
        case IMAGE_DIRECTORY_ENTRY_EXPORT: return "export";
        case IMAGE_DIRECTORY_ENTRY_IMPORT: return "import";
        case IMAGE_DIRECTORY_ENTRY_RESOURCE: return "resource";
        case IMAGE_DIRECTORY_ENTRY_EXCEPTION: return "exception";
        case IMAGE_DIRECTORY_ENTRY_SECURITY: return "security";
        case IMAGE_DIRECTORY_ENTRY_BASERELOC: return "basereloc";
        case IMAGE_DIRECTORY_ENTRY_DEBUG: return "debug";
        case IMAGE_DIRECTORY_ENTRY_COPYRIGHT: return "copyright";
        case IMAGE_DIRECTORY_ENTRY_GLOBALPTR: return "globalptr";
        case IMAGE_DIRECTORY_ENTRY_TLS: return "TLS";
        case IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG: return "load config";
        case IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT: return "bound import";
        case IMAGE_DIRECTORY_ENTRY_IAT: return "IAT";
        case IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT: return "delay import";
        case IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR: return ".NET";
        default: return "unknown";
    }
}

uint32_t __rva_to_va(uint32_t rva, IMAGE_NT_HEADERS32 *nt_hdr)
{
    return rva + nt_hdr->OptionalHeader.ImageBase;
}

uint32_t __rva_to_rphys(uint32_t rva, IMAGE_NT_HEADERS32 *nt_hdr)
{
    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(nt_hdr + 1);
    for(size_t i = 0; i < nt_hdr->FileHeader.NumberOfSections; i++)
    {
        if(sections[i].VirtualAddress <= rva &&
                rva < (sections[i].VirtualAddress + sections[i].Misc.VirtualSize))
            return sections[i].PointerToRawData + rva - sections[i].VirtualAddress;
    }
    //printf("%s!!unknown RVA: %s%#x%s!!\n", GREY, YELLOW, rva, GREY);
    return 0;
}

struct lookup_cache_t *lookup_cache_file(char *dll)
{
    /* find the file */
    DIR *dir = opendir(g_ord_import_lookup_prefix);
    if(dir == NULL)
        return NULL;
    struct dirent *ent;
    while((ent = readdir(dir)))
    {
        if(strcasecmp(ent->d_name, dll) == 0)
            break;
    }
    closedir(dir);
    if(ent == NULL)
        return NULL;
    /* load it */
    size_t size;
    sprintf(g_name_buffer, "%s%s", g_ord_import_lookup_prefix, ent->d_name);
    void *data = load_file(g_name_buffer, &size);
    if(data == NULL)
        return NULL;
    /* check signatures */
    IMAGE_DOS_HEADER *dos_hdr = (IMAGE_DOS_HEADER *)data;
    if(dos_hdr->e_magic != IMAGE_DOS_SIGNATURE)
        goto Lerr;
    IMAGE_NT_HEADERS32 *nt_hdr = (IMAGE_NT_HEADERS32 *)(data + dos_hdr->e_lfanew);
    IMAGE_FILE_HEADER *file_hdr = &nt_hdr->FileHeader;
    IMAGE_OPTIONAL_HEADER32 *opt_hdr = &nt_hdr->OptionalHeader;
    if(nt_hdr->Signature != IMAGE_NT_SIGNATURE || 
            file_hdr->SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER32) ||
            opt_hdr->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
        goto Lerr;
    if(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress == 0)
        goto Lerr;
    uint32_t offset = __rva_to_rphys(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress,
        nt_hdr);
    if(offset == 0)
        goto Lerr;
    IMAGE_EXPORT_DIRECTORY *exports = (IMAGE_EXPORT_DIRECTORY *)(data + offset);
    uint32_t *name_ptr = (uint32_t *)(data + __rva_to_rphys(exports->AddressOfNames, nt_hdr));
    uint16_t *ord_ptr = (uint16_t *)(data + __rva_to_rphys(exports->AddressOfNameOrdinals, nt_hdr));
    /* only consider exports with a name */
    struct lookup_entry_t *entries = NULL;
    for(size_t i = 0; i < exports->NumberOfFunctions && i < exports->NumberOfNames; i++)
    {
        if(name_ptr[i] == 0 || __rva_to_rphys(name_ptr[i], nt_hdr) == 0)
            continue;
        char *name = (char *)(data +__rva_to_rphys(name_ptr[i], nt_hdr));
        struct lookup_entry_t *ent = malloc(sizeof(struct lookup_entry_t) + strlen(name) + 1);
        ent->name = (char *)(ent + 1);
        ent->ord = ord_ptr[i] + exports->Base;
        strcpy(ent->name, name);
        ent->next = entries;
        entries = ent;
    }
    struct lookup_cache_t *cache = malloc(sizeof(struct lookup_cache_t));
    cache->dll = dll; /* notice: no need to make a copy ! */
    cache->entries = entries;
    cache->next = NULL;
    return cache;
    
    Lerr:
    free(data);
    return NULL;
}

char *lookup_ordinal_import(char *dll, uint16_t ord)
{
    /* first look in the cache for the dll */
    struct lookup_cache_t *c = g_lookup_cache;
    while(c)
    {
        if(strcasecmp(c->dll, dll) == 0)
            break;
        c = c->next;
    }
    /* if not in the cache, load it */
    if(c == NULL)
    {
        c = lookup_cache_file(dll);
        /* can't load ? error */
        if(c == NULL)
            return NULL;
        /* add it to the cache */
        c->next = g_lookup_cache;
        g_lookup_cache = c;
    }
    /* lookup in the list */
    struct lookup_entry_t *e = c->entries;
    while(e)
    {
        if(e->ord == ord)
            return e->name;
        e = e->next;
    }
    /* not in the list */
    return NULL;
}

void pe_info()
{
    IMAGE_DOS_HEADER *dos_hdr = (IMAGE_DOS_HEADER *)g_buf;

    printf("%sDOS Header:\n", GREEN);
    printf("  %sSignature: %s%#x  %s%s\n", BLUE, YELLOW, dos_hdr->e_magic,
        RED, dos_hdr->e_magic == IMAGE_DOS_SIGNATURE ? "Ok" : "Failed");
    if(dos_hdr->e_magic != IMAGE_DOS_SIGNATURE)
        return;
    printf("  %sNew exe header: %s%#x\n", BLUE, YELLOW, dos_hdr->e_lfanew);

    IMAGE_NT_HEADERS32 *nt_hdr = (IMAGE_NT_HEADERS32 *)(g_buf + dos_hdr->e_lfanew);
    IMAGE_FILE_HEADER *file_hdr = &nt_hdr->FileHeader;
    IMAGE_OPTIONAL_HEADER32 *opt_hdr = &nt_hdr->OptionalHeader;
    printf("%sNT Headers:\n", GREEN);
    printf("  %sSignature: %s%#x  %s%s\n", BLUE, YELLOW, nt_hdr->Signature,
        RED, nt_hdr->Signature == IMAGE_NT_SIGNATURE ? "Ok" : "Failed");
    if(nt_hdr->Signature != IMAGE_NT_SIGNATURE)
        return;
    printf("  %sFile header:\n", GREEN);
    printf("    %sMachine: %s%#x  %s[%s]\n", BLUE, YELLOW, file_hdr->Machine, RED,
        get_machine_string(file_hdr->Machine));
    printf("    %sSections: %s%u\n", BLUE, YELLOW, file_hdr->NumberOfSections);
    printf("    %sOpt hdr size: %s%#x  %s%s\n", BLUE, YELLOW, file_hdr->SizeOfOptionalHeader,
        RED, file_hdr->SizeOfOptionalHeader == sizeof(IMAGE_OPTIONAL_HEADER32) ? "Ok" : "Failed");
    if(file_hdr->SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER32))
        return;
    printf("    %sCharacteristics: %s%#x%s ", BLUE, YELLOW, file_hdr->Characteristics, RED);
    if(file_hdr->Characteristics & IMAGE_FILE_RELOCS_STRIPPED)
        printf(" relocs_stripped");
    if(file_hdr->Characteristics & IMAGE_FILE_EXECUTABLE_IMAGE)
        printf(" exec");
    if(file_hdr->Characteristics & IMAGE_FILE_LINE_NUMS_STRIPPED)
        printf(" line_nums_stripped");
    if(file_hdr->Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE)
        printf(" large_addr_aware");
    if(file_hdr->Characteristics & IMAGE_FILE_SYSTEM)
        printf(" system");
    if(file_hdr->Characteristics & IMAGE_FILE_DLL)
        printf(" dll");
    printf("\n");
    printf("  %sOptional header:\n", GREEN);
    printf("    %sMagic: %s%#x  %s%s\n", BLUE, YELLOW, opt_hdr->Magic, RED,
        opt_hdr->Magic == IMAGE_NT_OPTIONAL_HDR32_MAGIC ? "Ok" : "Failed");
    if(opt_hdr->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
        return;
    printf("    %sEntry (RVA): %s%#x\n", BLUE, YELLOW, opt_hdr->AddressOfEntryPoint);
    printf("    %sCode base (RVA): %s%#x\n", BLUE, YELLOW, opt_hdr->BaseOfCode);
    printf("    %sData base (RVA): %s%#x\n", BLUE, YELLOW, opt_hdr->BaseOfData);
    printf("    %sImage base: %s%#x\n", BLUE, YELLOW, opt_hdr->ImageBase);
    printf("    %sImage size: %s%#x\n", BLUE, YELLOW, opt_hdr->SizeOfImage);
    printf("    %sSubsystem: %s%#x  %s[%s]\n", BLUE, YELLOW, opt_hdr->Subsystem,
        RED, get_subsystem_string(opt_hdr->Subsystem));
    for(size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
    {
        IMAGE_DATA_DIRECTORY *dir = &opt_hdr->DataDirectory[i];
        if(dir->Size == 0)
            continue;
        printf("    %sData directory %u: %s%s\n", GREEN, (unsigned)i, YELLOW,
            get_data_directory_string(i));
        printf("      %sAddress (RVA): %s%#x\n", BLUE, YELLOW, dir->VirtualAddress);
        printf("      %sSize: %s%#x\n", BLUE, YELLOW, dir->Size);
    }

    #define rva_to_va(rva) __rva_to_va(rva, nt_hdr)
    #define phys_to_rva(phys) (uint32_t)((void *)phys - (void *)g_buf)
    #define phys_to_va(phys) rva_to_va(phys_to_rva(phys))
    #define phys_to_rphys phys_to_rva
    #define rva_to_rphys(rva) __rva_to_rphys(rva, nt_hdr)
    

    #ifdef ADD_PHYS_MAP
    add_memory_region_by_size(0, g_sz, "%sphysical image address space", BLUE);
    add_memory_region_by_size(phys_to_rphys(dos_hdr), dos_hdr->e_lfanew, "%sDOS Header and code", BLUE);
    add_memory_region_by_size(phys_to_rphys(nt_hdr), sizeof(IMAGE_NT_HEADERS32), "%sNT Headers", BLUE);

    add_memory_region_by_size(opt_hdr->ImageBase, opt_hdr->SizeOfImage,
        "%svirtual image address space", RED);
    #endif
    add_memory_region_by_size(phys_to_va(dos_hdr), dos_hdr->e_lfanew, "%sDOS Header and code", RED);
    add_memory_region_by_size(phys_to_va(nt_hdr), sizeof(IMAGE_NT_HEADERS32), "%sNT Headers", RED);

    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(nt_hdr + 1);
    for(size_t i = 0; i < file_hdr->NumberOfSections; i++)
    {
        printf("%sSection %s%u%s:\n", GREEN, YELLOW, (unsigned)i, GREEN);
        printf("  %sName: %s%s\n", BLUE, YELLOW, sections[i].Name);
        printf("  %sAddress (RVA): %s%#x\n", BLUE, YELLOW, sections[i].VirtualAddress);
        printf("  %sSize: %s%#x\n", BLUE, YELLOW, sections[i].Misc.VirtualSize);
        printf("  %sRaw address: %s%#x\n", BLUE, YELLOW, sections[i].PointerToRawData);
        printf("  %sRaw data size: %s%#x\n", BLUE, YELLOW, sections[i].SizeOfRawData);
        printf("  %sCharacteristics: %s%#x %s", BLUE, YELLOW, sections[i].Characteristics, RED);
        if(sections[i].Characteristics & IMAGE_SCN_CNT_CODE)
            printf(" code");
        if(sections[i].Characteristics & IMAGE_SCN_CNT_INITIALIZED_DATA)
            printf(" data");
        if(sections[i].Characteristics & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
            printf(" bss");
        if(sections[i].Characteristics & IMAGE_SCN_COMPRESSED)
            printf(" compressed");
        printf("\n");

        add_memory_region_by_size(phys_to_va(&sections[i]), sizeof(IMAGE_SECTION_HEADER),
            "%sSection %s%s: %sheader", RED, YELLOW, sections[i].Name, GREEN);
        add_memory_region_by_size(rva_to_va(sections[i].VirtualAddress), sections[i].Misc.VirtualSize,
            "%sSection %s%s: %scontent", RED, YELLOW, sections[i].Name, GREEN);
        #ifdef ADD_PHYS_MAP
        add_memory_region_by_size(phys_to_rphys(&sections[i]), sizeof(IMAGE_SECTION_HEADER),
            "%sSection %s%s: %sheader", BLUE, YELLOW, sections[i].Name, GREEN);
        add_memory_region_by_size(sections[i].PointerToRawData, sections[i].SizeOfRawData,
            "%sSection %s%s: %scontent", BLUE, YELLOW, sections[i].Name, GREEN);
        #endif
    }

    for(size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
    {
        IMAGE_DATA_DIRECTORY *dir = &opt_hdr->DataDirectory[i];
        if(dir->Size == 0)
            continue;
        add_memory_region_by_size(rva_to_va(dir->VirtualAddress), dir->Size, "%sData directory: %s%s",
            RED, YELLOW, get_data_directory_string(i));
        #ifdef ADD_PHYS_MAP
        add_memory_region_by_size(rva_to_rphys(dir->VirtualAddress), dir->Size, "%sData directory: %s%s",
            BLUE, YELLOW, get_data_directory_string(i));
        #endif
    }

    // import directory
    if(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size != 0)
    {
        uint32_t offset = rva_to_rphys(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
        IMAGE_IMPORT_DESCRIPTOR *imports = (IMAGE_IMPORT_DESCRIPTOR *)(g_buf + offset);
        uint32_t max_nr_imports = opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size;
        max_nr_imports /= sizeof(IMAGE_IMPORT_DESCRIPTOR);
        
        printf("%sImports:\n", GREEN);
        for(size_t i = 0; i < max_nr_imports && imports[i].Name; i++)
        {
            char *dll_name = (char *)(g_buf + rva_to_rphys(imports[i].Name));
            #ifdef ADD_PHYS_MAP
            add_memory_region_by_size(rva_to_rphys(imports[i].Name),
                strlen(dll_name) + 1, "%sImport dll name: %s%s", BLUE, YELLOW, dll_name);
            #endif
            printf("  %sDLL %u: %s%s\n", GREEN, (unsigned)i, YELLOW, dll_name);
            printf("    %sIAT (RVA): %s0x%x\n", RED, YELLOW, imports[i].FirstThunk);
            printf("    %sINT (RVA): %s0x%x\n", RED, YELLOW, imports[i].u.OriginalFirstThunk);
            IMAGE_THUNK_DATA32 *function_name_list = (IMAGE_THUNK_DATA32 *)(g_buf + rva_to_rphys(imports[i].FirstThunk));
            if(imports[i].u.OriginalFirstThunk != 0)
                function_name_list = (IMAGE_THUNK_DATA32 *)(g_buf + rva_to_rphys(imports[i].u.OriginalFirstThunk));
            uint32_t j = 0;
            while(function_name_list->u1.Ordinal)
            {
                if(IMAGE_SNAP_BY_ORDINAL32(function_name_list->u1.Ordinal))
                {
                    uint16_t ordinal = IMAGE_ORDINAL32(function_name_list->u1.Ordinal);
                    char *name = lookup_ordinal_import(dll_name, ordinal);
                    if(name)
                        printf("    %s[%s%u%s]: ordinal=%s%u%s name=%s%s\n", BLUE, YELLOW, (unsigned)j, BLUE, YELLOW,
                            ordinal, BLUE, RED, name);
                    else
                        printf("    %s[%s%u%s]: ordinal=%s%u\n", BLUE, YELLOW, (unsigned)j, BLUE, YELLOW, ordinal);
                }
                else
                {
                    IMAGE_IMPORT_BY_NAME *name =
                        (IMAGE_IMPORT_BY_NAME *)(g_buf + rva_to_rphys(function_name_list->u1.AddressOfData));
                    printf("    %s[%s%u%s]: hint=%s%u %sname=%s%s\n", BLUE, YELLOW, (unsigned)j, BLUE, YELLOW,
                        name->Hint, BLUE, RED, name->Name);
                }
                function_name_list++;
                j++;
            }
            #ifdef ADD_PHYS_MAP
            add_memory_region_by_size(rva_to_rphys(imports[i].u.OriginalFirstThunk),
                j * sizeof(IMAGE_THUNK_DATA32), "%sImport table: %s%s: %sINT", BLUE, YELLOW,
                dll_name, RED);
            add_memory_region_by_size(rva_to_rphys(imports[i].FirstThunk),
                j * sizeof(IMAGE_THUNK_DATA32), "%sImport table: %s%s: %sIAT", BLUE, YELLOW,
                dll_name, RED);
            #endif
        }
    }

    // export directory
    if(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size != 0)
    {
        uint32_t offset = rva_to_rphys(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
        IMAGE_EXPORT_DIRECTORY *exports = (IMAGE_EXPORT_DIRECTORY *)(g_buf + offset);

        char *dll_name = (char *)(g_buf + rva_to_rphys(exports->Name));
        printf("%sExport: %s\n", GREEN, dll_name);
        #ifdef ADD_PHYS_MAP
        add_memory_region_by_size(rva_to_rphys(exports->Name), strlen(dll_name) + 1,
            "%sExport dll name: %s%s", BLUE, YELLOW, dll_name);
        #endif
        uint32_t *func_ptr = (uint32_t *)(g_buf + rva_to_rphys(exports->AddressOfFunctions));
        uint32_t *name_ptr = (uint32_t *)(g_buf + rva_to_rphys(exports->AddressOfNames));
        uint16_t *ord_ptr = (uint16_t *)(g_buf + rva_to_rphys(exports->AddressOfNameOrdinals));
        #ifdef ADD_PHYS_MAP
        add_memory_region_by_size(rva_to_rphys(exports->AddressOfFunctions),
            exports->NumberOfFunctions * sizeof(uint32_t),
            "%sExport table: %sfunction RVAs", BLUE, YELLOW);
        add_memory_region_by_size(rva_to_rphys(exports->AddressOfNames),
            exports->NumberOfNames * sizeof(uint32_t),
            "%sExport table: %sfunction names", BLUE, YELLOW);
        add_memory_region_by_size(rva_to_rphys(exports->AddressOfNameOrdinals),
            exports->NumberOfNames * sizeof(uint16_t),
            "%sExport table: %sfunction ordinals", BLUE, YELLOW);
        #endif

        //for(size_t i = 0; i < exports->NumberOfFunctions; i++)
        for(size_t i = 0; i < exports->NumberOfNames; i++)
        {
            char *name = "";
            if(i < exports->NumberOfNames && name_ptr[i] != 0 && rva_to_rphys(name_ptr[i]))
                name = (char *)(g_buf + rva_to_rphys(name_ptr[i]));
            printf("    %s[%s%u%s]: rva=%s%#x %sord=%s%u %sname=%s%s\n", BLUE, YELLOW, (unsigned)i, BLUE, YELLOW,
                        func_ptr[i], BLUE, YELLOW, ord_ptr[i] + exports->Base, BLUE, RED, name);
        }
    }

    // print memory map
    struct mem_region_tree_t *tree = build_memory_tree();
    fprintf(stdout, "%sstart addr     end addr     description\n", GREEN);
    fprintf(stdout, "%s----------    ----------    -----------\n", GREEN);
    print_memory_tree(tree, file_print, (void *)stdout);
}

int main(int argc, char **argv)
{
    if(argc != 2 && argc != 3)
    {
        printf("usage: %s <pe file> [<ordinal import lookup prefix>]\n", argv[0]);
        return 0;
    }

    if(argc == 3)
        snprintf(g_ord_import_lookup_prefix, PREFIX_SIZE, "%s", argv[2]);
    else
        strcpy(g_ord_import_lookup_prefix, "./");

    g_buf = load_file(argv[1], &g_sz);
    if(g_buf == NULL)
        return 1;

    pe_info();

    free(g_buf);
    
    return 0;
}
