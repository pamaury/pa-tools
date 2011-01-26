#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <time.h>
#include "rom.h"
#include "pe.h"

#define DO_UNCOMPRESS
#define ALLOW_NEGATIVE_PE_RVAs
/* Various PE parameters */
#define PE_SECTION_ALIGNMENT    0x1000
#define PE_FILE_ALIGNMENT       0x200
#define PE_STACK_COMMIT         0x1000
#define PE_HEAP_RESERVE         0x1000000
#define PE_HEAP_COMMIT          0x1000

#define BINFS_HDR_OFFSET    0x210
#define BINFS_ROM_OFFSET    0x248

struct binfs_header
{
    uint32_t xip_kernel_start;
    uint32_t xip_kernel_len;
    uint32_t nk_entry;
    uint32_t ignore[5];
    uint32_t xip_kernel_start2;
    uint32_t xip_kernel_len2;
    uint32_t chain_start;
    uint32_t chain_len;
    uint32_t xip_start;
    uint32_t xip_len;
};

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

/* #region mem_region */
#if 1

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

size_t g_sz; /* file size */
uint8_t *g_buf; /* file content */
#define PREFIX_SIZE     128
char out_prefix[PREFIX_SIZE];
struct mem_region_t *g_regions = NULL;
size_t g_nr_regions = 0;
char g_name_buffer[4096];

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
        if(regions->next && contains(regions,  regions->next))
        {
            //printf("%s!!nested!!\n", GREY);
            /* advance in the chain to keep all nested ones */
            regions->child = regions->next;
            while(regions->next && regions->next->next)
            {
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
            if(regions->next->next == NULL)
                regions->next = NULL;
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

/* #endregion */
#endif

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

int within_file(uint32_t off, uint32_t size)
{
    return (off + size) <= g_sz;
}

time_t parse_filetime(FILETIME *ft)
{
    uint64_t t = ft->dwLowDateTime | ((uint64_t)ft->dwHighDateTime << 32);
    return (t / 10000000) - 11644473600;
}

/* #region pe_generation */
#if 1

void write_mz_header(FILE *f)
{
    IMAGE_DOS_HEADER dos_hdr;
    memset(&dos_hdr, 0, sizeof(dos_hdr));

    dos_hdr.e_magic = IMAGE_DOS_SIGNATURE;
    dos_hdr.e_cblp = 0x90; // Bytes on last page of file
    dos_hdr.e_cp = 3; // Pages in file
    dos_hdr.e_cparhdr = 0x4; // Size of header in paragraphs
    dos_hdr.e_maxalloc = 0xffff; // Maximum extra paragraphs needed
    dos_hdr.e_sp = 0xb8; // Initial SP value
    dos_hdr.e_lfarlc = 0x40; // File address of relocation table
    dos_hdr.e_lfanew = 0xc0; // File address of new exe header
    
    uint8_t stupid_dos_code[] =
    {
        0x0e, 0x1f, 0xba, 0x0e, 0x00, 0xb4, 0x09, 0xcd, 0x21, 0xb8, 0x01, 0x4c, 0xcd, 0x21, 0x54, 0x68,
        0x69, 0x73, 0x20, 0x70, 0x72, 0x6f, 0x67, 0x72, 0x61, 0x6d, 0x20, 0x63, 0x61, 0x6e, 0x6e, 0x6f,
        0x74, 0x20, 0x62, 0x65, 0x20, 0x72, 0x75, 0x6e, 0x20, 0x69, 0x6e, 0x20, 0x44, 0x4f, 0x53, 0x20,
        0x6d, 0x6f, 0x64, 0x65, 0x2e, 0x0d, 0x0d, 0x0a, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    fwrite(&dos_hdr, sizeof(dos_hdr), 1, f);
    fwrite(&stupid_dos_code, sizeof(stupid_dos_code), 1, f);

    fseek(f, 0x40, SEEK_CUR);
}

uint32_t compute_segment_size(e32_rom *e32, o32_rom *o32, uint32_t flags)
{
    uint32_t size = 0;
    for(uint32_t i = 0; i < e32->e32_objcnt; i++)
        if(o32[i].o32_flags & flags)
            size += o32[i].o32_vsize;
    return size;
}

uint32_t find_first_segment(e32_rom *e32, o32_rom *o32, uint32_t flags)
{
    for(uint32_t i = 0; i < e32->e32_objcnt; i++)
        if(o32[i].o32_flags & flags)
            return o32[i].o32_rva;
    return 0;
}

uint32_t align(uint32_t addr, uint32_t alg)
{
    return ((addr + alg - 1) / alg) * alg;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

void write_nt_header(FILE *f, ROMHDR *romhdr, TOCentry *tocent, e32_rom *e32, o32_rom *o32)
{
    IMAGE_NT_HEADERS32 nt_hdr;
    memset(&nt_hdr, 0, sizeof(nt_hdr));
    
    nt_hdr.Signature = IMAGE_NT_SIGNATURE;
    nt_hdr.FileHeader.Machine = romhdr->usCPUType;
    nt_hdr.FileHeader.NumberOfSections = e32->e32_objcnt;
    nt_hdr.FileHeader.TimeDateStamp = parse_filetime(&tocent->ftTime);
    nt_hdr.FileHeader.PointerToSymbolTable = 0;
    nt_hdr.FileHeader.NumberOfSymbols = 0;
    nt_hdr.FileHeader.SizeOfOptionalHeader = sizeof(nt_hdr.OptionalHeader);
    nt_hdr.FileHeader.Characteristics = e32->e32_imageflags | IMAGE_FILE_RELOCS_STRIPPED;
    nt_hdr.OptionalHeader.Magic = IMAGE_NT_OPTIONAL_HDR32_MAGIC;
    nt_hdr.OptionalHeader.MajorLinkerVersion = 0;
    nt_hdr.OptionalHeader.MajorLinkerVersion = 0;
    nt_hdr.OptionalHeader.SizeOfCode = compute_segment_size(e32, o32, IMAGE_SCN_CNT_CODE);
    nt_hdr.OptionalHeader.SizeOfInitializedData = compute_segment_size(e32, o32, IMAGE_SCN_CNT_INITIALIZED_DATA);
    nt_hdr.OptionalHeader.SizeOfUninitializedData = compute_segment_size(e32, o32, IMAGE_SCN_CNT_UNINITIALIZED_DATA);
    nt_hdr.OptionalHeader.AddressOfEntryPoint = e32->e32_entryrva;
    nt_hdr.OptionalHeader.BaseOfCode = find_first_segment(e32, o32, IMAGE_SCN_CNT_CODE);
    nt_hdr.OptionalHeader.BaseOfData = find_first_segment(e32, o32, IMAGE_SCN_CNT_INITIALIZED_DATA);
    nt_hdr.OptionalHeader.ImageBase = e32->e32_vbase;
    nt_hdr.OptionalHeader.SectionAlignment = PE_SECTION_ALIGNMENT;
    nt_hdr.OptionalHeader.FileAlignment = PE_FILE_ALIGNMENT;
    nt_hdr.OptionalHeader.MajorOperatingSystemVersion = 4;
    nt_hdr.OptionalHeader.MinorOperatingSystemVersion = 0;
    nt_hdr.OptionalHeader.MajorImageVersion = 0;
    nt_hdr.OptionalHeader.MinorImageVersion = 0;
    nt_hdr.OptionalHeader.MajorSubsystemVersion = e32->e32_subsysmajor;
    nt_hdr.OptionalHeader.MinorSubsystemVersion = e32->e32_subsysminor;
    nt_hdr.OptionalHeader.Win32VersionValue = 0;
    nt_hdr.OptionalHeader.SizeOfImage = e32->e32_vsize;
    nt_hdr.OptionalHeader.SizeOfHeaders =
        align(sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS32) +
                e32->e32_objcnt * sizeof(IMAGE_SECTION_HEADER), PE_FILE_ALIGNMENT);
    nt_hdr.OptionalHeader.CheckSum = 0; // never used
    nt_hdr.OptionalHeader.Subsystem = e32->e32_subsys;
    nt_hdr.OptionalHeader.DllCharacteristics = 0;
    nt_hdr.OptionalHeader.SizeOfStackReserve = e32->e32_stackmax;
    nt_hdr.OptionalHeader.SizeOfStackCommit = PE_STACK_COMMIT;
    nt_hdr.OptionalHeader.SizeOfHeapReserve = PE_HEAP_RESERVE;
    nt_hdr.OptionalHeader.SizeOfHeapCommit = PE_HEAP_COMMIT;
    nt_hdr.OptionalHeader.LoaderFlags = 0;
    nt_hdr.OptionalHeader.NumberOfRvaAndSizes = IMAGE_NUMBEROF_DIRECTORY_ENTRIES;

    #define SetDirectoryEntry(dir, rva, size) \
        dir.VirtualAddress = rva; \
        dir.Size = size
    #define CopyDirectoryEntry(entry) \
        SetDirectoryEntry(nt_hdr.OptionalHeader.DataDirectory[entry], \
            e32->e32_unit[entry].rva, e32->e32_unit[entry].size)
    
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_EXPORT);
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_IMPORT);
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_RESOURCE);
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_EXCEPTION);
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_SECURITY);
    /* no base reloc */
    /* debug ? */
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_COPYRIGHT);
    CopyDirectoryEntry(IMAGE_DIRECTORY_ENTRY_GLOBALPTR);
    /* others don't apply... */
    /* ...except .NET */
    SetDirectoryEntry(nt_hdr.OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR],
        e32->e32_sect14rva, e32->e32_sect14size);

    fwrite(&nt_hdr, sizeof(nt_hdr), 1, f);
}

void write_section_header(FILE *f, o32_rom *o32, uint32_t raw_data_ptr)
{
    IMAGE_SECTION_HEADER sec_hdr;
    memset(&sec_hdr, 0, sizeof(IMAGE_SECTION_HEADER));

    if(o32->o32_flags & IMAGE_SCN_CNT_CODE)
        snprintf(sec_hdr.Name, IMAGE_SIZEOF_SHORT_NAME, ".text");
    else if(o32->o32_flags & IMAGE_SCN_CNT_INITIALIZED_DATA)
        snprintf(sec_hdr.Name, IMAGE_SIZEOF_SHORT_NAME, ".data");
    else if(o32->o32_flags & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
        snprintf(sec_hdr.Name, IMAGE_SIZEOF_SHORT_NAME, ".bss");
    else
        snprintf(sec_hdr.Name, IMAGE_SIZEOF_SHORT_NAME, ".misc");
    sec_hdr.Misc.VirtualSize = o32->o32_vsize;
    #ifdef ALLOW_NEGATIVE_PE_RVAs
    sec_hdr.VirtualAddress = o32->o32_realaddr;
    #else
    sec_hdr.VirtualAddress = o32->o32_rva;
    #endif
    sec_hdr.SizeOfRawData = min(o32->o32_psize, o32->o32_vsize); /* probably wrong, fixed later */
    sec_hdr.PointerToRawData = raw_data_ptr; /* probably wrong, fixed later */
    sec_hdr.PointerToRelocations = 0;
    sec_hdr.PointerToLinenumbers = 0;
    sec_hdr.NumberOfRelocations = 0;
    sec_hdr.NumberOfLinenumbers = 0;
    #ifdef DO_UNCOMPRESS
    sec_hdr.Characteristics = o32->o32_flags & ~IMAGE_SCN_COMPRESSED;
    #else
    sec_hdr.Characteristics = o32->o32_flags;
    #endif
    fwrite(&sec_hdr, sizeof(sec_hdr), 1, f);
}

void *cedecompress(void *in_buf, size_t in_size, size_t *out_size)
{
    char *tmpfilename = tmpnam(NULL);
    FILE *tmpfile = fopen(tmpfilename, "wb");
    if(tmpfile == NULL)
    {
        printf("%s[error creating temporary file]\n", GREY);
        return NULL;
    }
    fwrite(in_buf, in_size, 1, tmpfile);
    fclose(tmpfile);
    snprintf(g_name_buffer, sizeof(g_name_buffer), "./cedecompr.sh %s %s > /dev/null", tmpfilename, tmpfilename);
    //printf("%s{cmd: %s}\n", GREY, g_name_buffer);
    if(system(g_name_buffer) != 0)
    {
        remove(tmpfilename);
        printf("%s[error decompressing section]\n", GREY);
        return NULL;
    }
    void *tmpbuf = load_file(tmpfilename, out_size);
    remove(tmpfilename);
    if(tmpbuf == NULL)
        printf("%s[error loading temporary file]\n", GREY);
    return tmpbuf;
}

void write_section_data(FILE *f, o32_rom *o32, uint32_t virtual_base, uint32_t file_off)
{
    printf("  %sSection %sflags: %s%#x%s ", GREEN, BLUE, YELLOW, o32->o32_flags, RED);
    if(o32->o32_flags & IMAGE_SCN_CNT_CODE)
        printf(" code");
    if(o32->o32_flags & IMAGE_SCN_CNT_INITIALIZED_DATA)
        printf(" data");
    if(o32->o32_flags & IMAGE_SCN_CNT_UNINITIALIZED_DATA)
        printf(" bss");
    if(o32->o32_flags & IMAGE_SCN_COMPRESSED)
        printf(" compressed");
    printf("\n");
    printf("          %saddress: rva=%s%#x %sdata=%s%#x %sreal=%s%#x\n", BLUE, YELLOW,
        o32->o32_rva, BLUE, YELLOW, o32->o32_dataptr, BLUE, YELLOW, o32->o32_realaddr);
    printf("          %ssize: phys=%s%#x %svirt=%s%#x\n", BLUE, YELLOW, o32->o32_psize,
        BLUE, YELLOW, o32->o32_vsize);

    #ifdef DO_UNCOMPRESS
    if(o32->o32_flags & IMAGE_SCN_COMPRESSED)
    {
        size_t sz;
        void *tmpbuf = cedecompress(
            (void *)(g_buf + file_off + o32->o32_dataptr - virtual_base),
            min(o32->o32_psize, o32->o32_vsize),
            &sz);
        if(tmpbuf)
        {
            fwrite(tmpbuf, sz, 1, f);
            free(tmpbuf);
        }
    }
    else
    #endif
    fwrite((void *)(g_buf + file_off + o32->o32_dataptr - virtual_base),
        min(o32->o32_psize, o32->o32_vsize), 1, f);
}

void fixup_section(FILE *f, size_t section_idx, uint32_t section_headers_off,
    uint32_t raw_data_ptr, uint32_t raw_data_size)
{
    uint32_t fixup_off = section_headers_off +
        section_idx * sizeof(IMAGE_SECTION_HEADER);
    uint32_t pos = ftell(f); /* cast to 32bit ! */
    fseek(f, fixup_off + offsetof(IMAGE_SECTION_HEADER, PointerToRawData), SEEK_SET);
    fwrite(&raw_data_ptr, sizeof(raw_data_ptr), 1, f);
    fseek(f, fixup_off + offsetof(IMAGE_SECTION_HEADER, SizeOfRawData), SEEK_SET);
    fwrite(&raw_data_size, sizeof(raw_data_size), 1, f);
    fseek(f, pos, SEEK_SET);
}

/* #enregion */
#endif

uint32_t __phys_to_virt(void *ptr, struct binfs_header *binfs_hdr)
{
    return ptr - (void *)g_buf - BINFS_ROM_OFFSET + binfs_hdr->xip_kernel_start;
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

void dump_rom(uint8_t *buf, uint32_t file_off, uint32_t virtual_base, uint32_t phys_size)
{
    #define virt_to_phys(virt) ((uint32_t)(virt) - virtual_base + buf)
    #define phys_to_virt(ptr) ((uint8_t *)(ptr) - buf + virtual_base)
    #define phys_to_off(ptr) ((uint8_t *)(ptr) - buf + file_off)
    #define virt_to_off(virt) (virt - virtual_base + file_off)
    #define valid_virt(virt) ((uint32_t)virt >= virtual_base)

    add_memory_region_by_size(ROM_SIGNATURE_OFFSET + file_off, 3 * sizeof(uint32_t),
        "%sROM signature & pointer", RED);
    uint32_t sig = *(uint32_t *)(buf + ROM_SIGNATURE_OFFSET);
    uint32_t toc_ptr = *(uint32_t *)(buf + ROM_TOC_POINTER_OFFSET);
    uint32_t toc_off = *(uint32_t *)(buf + ROM_TOC_OFFSET_OFFSET);
    printf("%sROM:\n", GREEN);
    printf("  %sSignature: %s%#x", BLUE, YELLOW, sig);
    color(RED);
    if(sig == ROM_SIGNATURE)
        printf("  Ok\n");
    else
    {
        printf("  Failed\n");
        return;
    }

    add_memory_region_by_size(virt_to_off(toc_ptr), sizeof(ROMHDR), "%sROM Header", RED);

    printf("  %sTOC RVA: %s%#x\n", BLUE, YELLOW, toc_ptr);
    printf("  %sTOC offset: %s%#x\n", BLUE, YELLOW, toc_off);

    ROMHDR *romhdr = (ROMHDR *)virt_to_phys(toc_ptr);
    ROMPID *romext = (ROMPID *)virt_to_phys(romhdr->pExtensions);
    if(!valid_virt(romhdr->pExtensions))
        romext = NULL;
    printf("%sROM header:\n", GREEN);
    printf("  %sFirst DLL: %s%#x\n", BLUE, YELLOW, romhdr->dllfirst);
    printf("  %sLast DLL: %s%#x\n", BLUE, YELLOW, romhdr->dlllast);
    printf("  %sFirst phys: %s%#x\n", BLUE, YELLOW, romhdr->physfirst);
    printf("  %sLast phys: %s%#x\n", BLUE, YELLOW, romhdr->physlast);
    printf("  %sNr modules: %s%u\n", BLUE, YELLOW, romhdr->nummods);
    printf("  %sRAM start: %s%#x\n", BLUE, YELLOW, romhdr->ulRAMStart);
    printf("  %sRAM free: %s%#x\n", BLUE, YELLOW, romhdr->ulRAMFree);
    printf("  %sRAM end: %s%#x\n", BLUE, YELLOW, romhdr->ulRAMEnd);
    printf("  %sNr copy entries: %s%u\n", BLUE, YELLOW, romhdr->ulCopyEntries);
    printf("  %sCopy section off: %s%#x\n", BLUE, YELLOW, romhdr->ulCopyOffset);
    printf("  %sProfile section sz: %s%#x\n", BLUE, YELLOW, romhdr->ulProfileLen);
    printf("  %sProfile section off: %s%#x\n", BLUE, YELLOW, romhdr->ulProfileOffset);
    printf("  %sNr files: %s%u\n", BLUE, YELLOW, romhdr->numfiles);
    printf("  %sLernel flags: %s%#x\n", BLUE, YELLOW, romhdr->ulKernelFlags);
    printf("  %sFS RAM percent: %s%u%% %u%% %u%% %u%%\n", BLUE, YELLOW,
        ((romhdr->ulFSRamPercent & 0xff) * 100) / 255,
        (((romhdr->ulFSRamPercent >> 8) & 0xff) * 100) / 255,
        (((romhdr->ulFSRamPercent >> 16) & 0xff) * 100) / 255,
        (((romhdr->ulFSRamPercent >> 24) & 0xff) * 100) / 255);
    printf("  %sDev driver start: %s%#x\n", BLUE, YELLOW, romhdr->ulDrivglobStart);
    printf("  %sDev driver size: %s%#x\n", BLUE, YELLOW, romhdr->ulDrivglobLen);
    printf("  %sCPU type: %s%#x", BLUE, YELLOW, romhdr->usCPUType);
    if(romhdr->usCPUType == IMAGE_FILE_MACHINE_ARM)
        printf("  %s[ARM]\n", RED);
    else if(romhdr->usCPUType == IMAGE_FILE_MACHINE_THUMB)
        printf("  %s[Thumb]\n", RED);
    else
        printf("  %s[Unknown]\n", RED);
    printf("  %sMisc flags: %s%#x\n", BLUE, YELLOW, romhdr->usMiscFlags);
    printf("  %sROM extension addr: %s%#x\n", BLUE, YELLOW, romhdr->pExtensions);
    printf("  %sTracking mem start: %s%#x\n", BLUE, YELLOW, romhdr->ulTrackingStart);
    printf("  %sTracking mem size: %s%#x\n", BLUE, YELLOW, romhdr->ulTrackingLen);
    if(romhdr->pExtensions == 0)
        romext = NULL;

    XIPCHAIN_SUMMARY *xip_summary = NULL;
    uint32_t xip_summary_size = 0;
    while(romext)
    {
        add_memory_region_by_size(phys_to_off(romext), sizeof(ROMPID), "%sROM Extension", RED);
        printf("%sROM extension:\n", GREEN);
        printf("  %sName: %s%s\n", BLUE, YELLOW, romext->u.s.name);
        printf("  %sType: %s%#x\n", BLUE, YELLOW, romext->u.s.type);
        printf("  %sAddress: %s%#x\n", BLUE, YELLOW, romext->u.s.pdata);
        printf("  %sLength: %s%#x\n", BLUE, YELLOW, romext->u.s.length);

        char *chain_info = "chain information";
        if(memcmp(romext->u.s.name, chain_info, strlen(chain_info)) == 0)
        {
            xip_summary = (XIPCHAIN_SUMMARY *)virt_to_phys(romext->u.s.pdata);
            xip_summary_size = romext->u.s.length/* + 0x10*/;
            add_memory_region_by_size(virt_to_off(romext->u.s.pdata), romext->u.s.length,
                "%sROM Extension: %schain information", RED, BLUE);
        }
        
        if(romext->pNextExt == 0)
            romext = NULL;
        else
            romext = (ROMPID *)virt_to_phys(romext->pNextExt);
    }
    if(xip_summary)
    {
        printf("%sXIP chain summary:\n", GREEN);
        printf("  %sXIP address: %s%#x\n", BLUE, YELLOW, xip_summary->pvAddr);
        printf("  %sMax length: %s%#x\n", BLUE, YELLOW, xip_summary->dwMaxLength);
        printf("  %sOrder: %s%#x\n", BLUE, YELLOW, xip_summary->usOrder);
        printf("  %sFlags: %s%#x\n", BLUE, YELLOW, xip_summary->usFlags);

        uint32_t nr_regions = xip_summary_size / sizeof(XIPCHAIN_SUMMARY) - 1;
        XIPCHAIN_SUMMARY *xip_chain = xip_summary + 1; // don't read first header
        for(uint32_t i = 0; i < nr_regions; i++, xip_chain++)
        {
            printf("%sXIP chain %u:\n", GREEN, i);
            printf("  %sXIP address: %s%#x\n", BLUE, YELLOW, xip_chain->pvAddr);
            printf("  %sMax length: %s%#x\n", BLUE, YELLOW, xip_chain->dwMaxLength);
            printf("  %sOrder: %s%#x\n", BLUE, YELLOW, xip_chain->usOrder);
            printf("  %sFlags: %s%#x\n", BLUE, YELLOW, xip_chain->usFlags);
        }
    }

    TOCentry *toc_modules = (TOCentry *)(romhdr + 1);
    for(uint32_t i = 0; i < romhdr->nummods; i++)
    {
        printf("%sModule %u:\n", GREEN, i);
        printf("  %sFile attr: %s%#x\n", BLUE, YELLOW, toc_modules[i].dwFileAttributes);
        time_t time = parse_filetime(&toc_modules[i].ftTime);
        struct tm *tm = localtime(&time);
        printf("  %sDate time: %s%s", BLUE, YELLOW, asctime(tm));
        char *ptr = (char *)virt_to_phys(toc_modules[i].lpszFileName);
        printf("  %sFile size: %s%#x\n", BLUE, YELLOW, toc_modules[i].nFileSize);
        printf("  %sFile name: %s%#x (%s%s%s)\n", BLUE, YELLOW, toc_modules[i].lpszFileName, GREY, ptr, YELLOW);
        printf("  %sE32 offset: %s%#x\n", BLUE, YELLOW, toc_modules[i].ulE32Offset);
        printf("  %sO32 offset: %s%#x\n", BLUE, YELLOW, toc_modules[i].ulO32Offset);
        printf("  %sload offset: %s%#x\n", BLUE, YELLOW, toc_modules[i].ulLoadOffset);

        add_memory_region_by_size(phys_to_off(&toc_modules[i]), sizeof(TOCentry),
            "%sROM Header: %sTOC entry: %s%s", RED, YELLOW, BLUE, ptr);

        // recreate original file
        char *filename = malloc(strlen(ptr) + strlen(out_prefix) + 1);
        sprintf(filename, "%s%s", out_prefix, ptr);
        FILE *f = fopen(filename, "wb");
        free(filename);
        if(f == NULL)
            continue;
        write_mz_header(f);
        e32_rom *e32 = (e32_rom *)virt_to_phys(toc_modules[i].ulE32Offset);
        o32_rom *o32 = (o32_rom *)virt_to_phys(toc_modules[i].ulO32Offset);
        
        printf("  %sE32 Header:\n", GREEN);
        printf("    %sFlags: %s%#x\n", BLUE, YELLOW, e32->e32_imageflags);
        printf("    %sEntry (RVA): %s%#x\n", BLUE, YELLOW, e32->e32_entryrva);
        printf("    %sVirtual base: %s%#x\n", BLUE, YELLOW, e32->e32_vbase);
        printf("    %sVirtual size: %s%#x\n", BLUE, YELLOW, e32->e32_vsize);
        
        add_memory_region_by_size(phys_to_off(e32), sizeof(e32_rom), "%s%s: %sE32 Header",
            RED, ptr, BLUE);
        add_memory_region_by_size(phys_to_off(o32), e32->e32_objcnt * sizeof(o32_rom), "%s%s: %sO32 Headers",
            RED, ptr, BLUE);
        for(uint32_t i = 0; i < e32->e32_objcnt; i++)
            add_memory_region_by_size(virt_to_off(o32[i].o32_dataptr),
                min(o32[i].o32_psize, o32[i].o32_vsize),
                "%s%s: %ssection:%s%s%s%s%s",
                RED, ptr, YELLOW, BLUE,
                (o32[i].o32_flags & IMAGE_SCN_CNT_CODE) ? " code" : "",
                (o32[i].o32_flags & IMAGE_SCN_CNT_INITIALIZED_DATA) ? " data" : "",
                (o32[i].o32_flags & IMAGE_SCN_CNT_UNINITIALIZED_DATA) ? " bss" : "",
                (o32[i].o32_flags & IMAGE_SCN_COMPRESSED) ? " compressed" : "");

        write_nt_header(f, romhdr, &toc_modules[i], e32, o32);
        uint32_t section_headers_off = ftell(f);
        for(uint32_t i = 0; i < e32->e32_objcnt; i++)
            /* pointer to raw data offset will be fixed later on */
            write_section_header(f, &o32[i], 0);
        for(uint32_t i = 0; i < e32->e32_objcnt; i++)
        {
            fseek(f, align(ftell(f), PE_SECTION_ALIGNMENT), SEEK_SET);
            size_t pos = ftell(f);
            write_section_data(f, &o32[i], virtual_base, file_off);
            size_t pos_end = ftell(f);
            fixup_section(f, i, section_headers_off, pos, pos_end - pos);
        }
        fclose(f);
    }
    FILESentry *toc_files = (FILESentry *)&toc_modules[romhdr->nummods];
    for(uint32_t i = 0; i < romhdr->numfiles; i++)
    {
        printf("%sFile %u:\n", GREEN, i);
        printf("  %sFile attr: %s%#x\n", BLUE, YELLOW, toc_files[i].dwFileAttributes);
        time_t time = parse_filetime(&toc_files[i].ftTime);
        struct tm *tm = localtime(&time);
        printf("  %sDate time: %s%s", BLUE, YELLOW, asctime(tm));
        char *ptr = (char *)virt_to_phys(toc_files[i].lpszFileName);
        printf("  %sReal file size: %s%#x\n", BLUE, YELLOW, toc_files[i].nRealFileSize);
        printf("  %sCompressed size: %s%#x\n", BLUE, YELLOW, toc_files[i].nCompFileSize);
        printf("  %sFile name: %s%#x (%s%s%s)\n", BLUE, YELLOW, toc_files[i].lpszFileName, GREY, ptr, YELLOW);
        printf("  %sLoad offset: %s%#x\n", BLUE, YELLOW, toc_files[i].ulLoadOffset);

        add_memory_region_by_size(phys_to_off(&toc_files[i]), sizeof(TOCentry),
            "%sROM Header: %sfile entry: %s%s", RED, YELLOW, BLUE, ptr);
        add_memory_region_by_size(virt_to_off(toc_files[i].ulLoadOffset), toc_files[i].nCompFileSize,
            "%s%s: %scontent", RED, ptr, YELLOW);

        // recreate original file
        char *filename = malloc(strlen(ptr) + strlen(out_prefix) + 1);
        sprintf(filename, "%s%s", out_prefix, ptr);
        FILE *f = fopen(filename, "wb");
        free(filename);
        if(f == NULL)
            continue;
        if(toc_files[i].nRealFileSize != toc_files[i].nCompFileSize)
        {
            size_t sz;
            void *tmp_buf = cedecompress(virt_to_phys(toc_files[i].ulLoadOffset),
                toc_files[i].nRealFileSize, &sz);
            if(tmp_buf)
            {
                fwrite(tmp_buf, sz, 1, f);
                free(tmp_buf);
            }
        }
        else
            fwrite(virt_to_phys(toc_files[i].ulLoadOffset),
                toc_files[i].nRealFileSize, 1, f);
        fclose(f);
    }

    COPYentry *toc_copies = (COPYentry *)virt_to_phys(romhdr->ulCopyOffset);
    for(uint32_t i = 0; i < romhdr->ulCopyEntries; i++)
    {
        printf("%sCopy %u:\n", GREEN, i);
        printf("  %sSource: %s%#x\n", BLUE, YELLOW, toc_copies[i].ulSource);
        printf("  %sDestination: %s%#x\n", BLUE, YELLOW, toc_copies[i].ulDest);
        printf("  %sCopy size: %s%#x\n", BLUE, YELLOW, toc_copies[i].ulCopyLen);
        printf("  %sDest size: %s%#x\n", BLUE, YELLOW, toc_copies[i].ulDestLen);
    }
}

void rom_info()
{
    struct binfs_header *binfs_hdr = (struct binfs_header *)(g_buf + BINFS_HDR_OFFSET);
    
    printf("%sBINFS header:\n", GREEN);
    printf("  %sXIP kernel start: %s%#x\n", BLUE, YELLOW, binfs_hdr->xip_kernel_start);
    printf("  %sXIP kernel size: %s%#x\n", BLUE, YELLOW, binfs_hdr->xip_kernel_len);
    printf("  %sNK entry: %s%#x\n", BLUE, YELLOW, binfs_hdr->nk_entry);
    printf("  %sXIP kernel start: %s%#x\n", BLUE, YELLOW, binfs_hdr->xip_kernel_start2);
    printf("  %sXIP kernel size: %s%#x\n", BLUE, YELLOW, binfs_hdr->xip_kernel_len2);
    printf("  %sChain start: %s%#x\n", BLUE, YELLOW, binfs_hdr->chain_start);
    printf("  %sChain size: %s%#x\n", BLUE, YELLOW, binfs_hdr->chain_len);
    printf("  %sXIP start: %s%#x\n", BLUE, YELLOW, binfs_hdr->xip_start);
    printf("  %sXIP size: %s%#x\n", BLUE, YELLOW, binfs_hdr->xip_len);
    add_memory_region_by_size(BINFS_HDR_OFFSET,
        sizeof(struct binfs_header), "%sBINFS header", RED);

    dump_rom(g_buf + BINFS_ROM_OFFSET, BINFS_ROM_OFFSET, binfs_hdr->xip_kernel_start, binfs_hdr->xip_kernel_len);

    XIPCHAIN_INFO *xip_info = (XIPCHAIN_INFO *)(g_buf + BINFS_ROM_OFFSET + binfs_hdr->xip_kernel_len);
    XIPCHAIN_ENTRY *xip_entry = &xip_info->xipEntryStart;
    size_t nr_xip_entries = 0;
    printf("%sXIP chain info:\n", GREEN);
    if(xip_info->cXIPs > 10)
    {
        printf("  %sNr XIPs: %s%u  %ssuspicious\n", BLUE, YELLOW, xip_info->cXIPs, RED);
    }
    else
    {
        printf("  %sNr XIPs: %s%u\n", BLUE, YELLOW, xip_info->cXIPs);
        nr_xip_entries = xip_info->cXIPs;
    }
    for(uint32_t i = 0; i < nr_xip_entries; i++)
    {
        printf("%sXIP entry %u:\n", GREEN, i);
        printf("  %sAddress: %s%#x\n", BLUE, YELLOW, xip_entry[i].pvAddr);
        printf("  %sLength: %s%#x\n", BLUE, YELLOW, xip_entry[i].dwLength);
        printf("  %sMax length: %s%#x\n", BLUE, YELLOW, xip_entry[i].dwMaxLength);
        printf("  %sOrder: %s%#x\n", BLUE, YELLOW, xip_entry[i].usOrder);
        printf("  %sFlags: %s%#x\n", BLUE, YELLOW, xip_entry[i].usFlags);
        printf("  %sVersion: %s%#x\n", BLUE, YELLOW, xip_entry[i].dwVersion);
        printf("  %sName: %s%s\n", BLUE, YELLOW, xip_entry[i].szName);
        printf("  %sAlgo flags: %s%#x\n", BLUE, YELLOW, xip_entry[i].dwAlgoFlags);
        printf("  %sKey len: %s%#x\n", BLUE, YELLOW, xip_entry[i].dwKeyLen);
    }

    dump_rom(g_buf + BINFS_ROM_OFFSET + binfs_hdr->xip_kernel_len + binfs_hdr->chain_len,
        BINFS_ROM_OFFSET + binfs_hdr->xip_kernel_len + binfs_hdr->chain_len,
        xip_entry[1].pvAddr, xip_entry[1].dwLength);

    char *str = "memory_map.txt";
    char *filename = malloc(strlen(str) + strlen(out_prefix) + 1);
    sprintf(filename, "%s%s", out_prefix, str);
    FILE *f = fopen(filename, "wb");
    free(filename);
    if(f != NULL)
    {
        struct mem_region_tree_t *tree = build_memory_tree();

        fprintf(f, "%sstart addr     end addr     description\n", GREEN);
        fprintf(f, "%s----------    ----------    -----------\n", GREEN);
        print_memory_tree(tree, file_print, (void *)f);
        fclose(f);
    }
}

int main(int argc, char **argv)
{
    if(argc != 2 && argc != 3)
    {
        printf("usage: %s <rom file> [<out prefix>]\n", argv[0]);
        return 0;
    }

    if(argc == 3)
        snprintf(out_prefix, PREFIX_SIZE, "%s", argv[2]);
    else
        strcpy(out_prefix, "");

    g_buf = load_file(argv[1], &g_sz);
    if(g_buf == NULL)
        return 1;

    rom_info();

    free(g_buf);
    
    return 0;
}
