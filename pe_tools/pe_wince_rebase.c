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

size_t g_sz; /* file size */
uint8_t *g_buf; /* file content */
uint32_t *g_sec2va_table = NULL;
uint32_t g_new_virtual_base;

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

void write_file(char *name, void *data, size_t size)
{
    FILE *f = fopen(name, "wb");
    if(f == NULL)
    {
        printf("Cannot open '%s' for writing !\n", name);
        return;
    }
    if(fwrite(data, size, 1, f) != 1)
    {
        printf("Cannot write '%s' !\n", name);
        return;
    }
    fclose(f);
}

enum statut_t
{
    MODIFIED = 1,
    UNMODIFIED = 0,
    ERROR = -1,
};

void __fix_rva(IMAGE_NT_HEADERS32 *nt_hdr, uint32_t *rva)
{
    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(nt_hdr + 1);
    for(size_t i = 0; i < nt_hdr->FileHeader.NumberOfSections; i++)
    {
        if(sections[i].VirtualAddress <= *rva &&
                *rva < (sections[i].VirtualAddress + sections[i].Misc.VirtualSize))
        {
            *rva = (*rva - sections[i].VirtualAddress) + (g_sec2va_table[i] - g_new_virtual_base);
            return;
        }
    }
    printf("!!Can't fix RVA: %#x!!\n", *rva);
    abort();
}

#define fix_rva(ptr) __fix_rva(nt_hdr, ptr)

uint32_t __rva_to_rphys(IMAGE_NT_HEADERS32 *nt_hdr, uint32_t rva)
{
    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(nt_hdr + 1);
    for(size_t i = 0; i < nt_hdr->FileHeader.NumberOfSections; i++)
    {
        if(sections[i].VirtualAddress <= rva &&
                rva < (sections[i].VirtualAddress + sections[i].Misc.VirtualSize))
            return sections[i].PointerToRawData + rva - sections[i].VirtualAddress;
    }
    printf("!!unknown RVA: %#x!!\n", rva);
    abort();
    return 0;
}

#define rva_to_rphys(rva) __rva_to_rphys(nt_hdr, rva)

enum statut_t rebase_import_directory(
    IMAGE_DOS_HEADER *dos_hdr,
    IMAGE_NT_HEADERS32 *nt_hdr,
    IMAGE_FILE_HEADER *file_hdr,
    IMAGE_OPTIONAL_HEADER32 *opt_hdr)
{
    (void) dos_hdr;
    (void) file_hdr;
    uint32_t offset = rva_to_rphys(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
    if(offset == 0)
        return ERROR;
    /* for each DLL */
    IMAGE_IMPORT_DESCRIPTOR *imports = (IMAGE_IMPORT_DESCRIPTOR *)(g_buf + offset);
    for(size_t i = 0; i < imports[i].Name; i++)
    {
        /* rebase DLL name and thunk pointers */
        fix_rva(&imports[i].Name);
        IMAGE_THUNK_DATA32 *iat_table = (IMAGE_THUNK_DATA32 *)(g_buf + rva_to_rphys(imports[i].FirstThunk));
        IMAGE_THUNK_DATA32 *int_table = (IMAGE_THUNK_DATA32 *)(g_buf + rva_to_rphys(imports[i].u.OriginalFirstThunk));
        if(imports[i].FirstThunk)
            fix_rva(&imports[i].FirstThunk);
        if(imports[i].u.OriginalFirstThunk)
            fix_rva(&imports[i].u.OriginalFirstThunk);
        if(imports[i].ForwarderChain)
            fix_rva(&imports[i].ForwarderChain);
        /* rebase each name */
        while(iat_table->u1.Ordinal)
        {
            //fix_rva(&iat_table->u1.Function);
            if(!IMAGE_SNAP_BY_ORDINAL32(int_table->u1.Ordinal))
                fix_rva(&int_table->u1.AddressOfData);
            *iat_table = *int_table;
            int_table++;
            iat_table++;
        }
    }
    return MODIFIED;
}

enum statut_t rebase_export_directory(
    IMAGE_DOS_HEADER *dos_hdr,
    IMAGE_NT_HEADERS32 *nt_hdr,
    IMAGE_FILE_HEADER *file_hdr,
    IMAGE_OPTIONAL_HEADER32 *opt_hdr)
{
    (void) dos_hdr;
    (void) file_hdr;
    uint32_t offset = rva_to_rphys(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
    if(offset == 0)
        return ERROR;
    
    IMAGE_EXPORT_DIRECTORY *exports = (IMAGE_EXPORT_DIRECTORY *)(g_buf + offset);
    fix_rva(&exports->Name);
    uint32_t *func_ptr = (uint32_t *)(g_buf + rva_to_rphys(exports->AddressOfFunctions));
    uint32_t *name_ptr = (uint32_t *)(g_buf + rva_to_rphys(exports->AddressOfNames));
    fix_rva(&exports->AddressOfFunctions);
    fix_rva(&exports->AddressOfNames);
    fix_rva(&exports->AddressOfNameOrdinals);
    
    for(size_t i = 0; i < exports->NumberOfFunctions; i++)
    {
        if(i < exports->NumberOfNames && name_ptr[i] != 0)
            fix_rva(&name_ptr[i]);
        fix_rva(&func_ptr[i]);
    }
    
    return MODIFIED;
}

enum statut_t rebase_exception_directory(
    IMAGE_DOS_HEADER *dos_hdr,
    IMAGE_NT_HEADERS32 *nt_hdr,
    IMAGE_FILE_HEADER *file_hdr,
    IMAGE_OPTIONAL_HEADER32 *opt_hdr)
{
    (void) dos_hdr;
    (void) file_hdr;
    uint32_t offset = rva_to_rphys(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress);
    if(offset == 0)
        return ERROR;

    /*
    IMAGE_RUNTIME_FUNCTION_ENTRY *functions = (IMAGE_RUNTIME_FUNCTION_ENTRY *)(g_buf + offset);
    while(functions->BeginAddress)
    {
        printf("Function: 0x%08x -> [0x%08x, 0x%08x]\n", functions->BeginAddress,
            functions->EndAddress, functions->PrologEndAddress);
        functions++;
    }
    */
    
    return MODIFIED;
}

enum statut_t rebase_executable(
    IMAGE_DOS_HEADER *dos_hdr,
    IMAGE_NT_HEADERS32 *nt_hdr,
    IMAGE_FILE_HEADER *file_hdr,
    IMAGE_OPTIONAL_HEADER32 *opt_hdr)
{
    /*
     * /!\ Watch out the order /!\
     */
    /* import directory */
    if(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress != 0)
        if(rebase_import_directory(dos_hdr, nt_hdr, file_hdr, opt_hdr) == ERROR)
            return ERROR;
    /* export directory */
    if(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress != 0)
        if(rebase_export_directory(dos_hdr, nt_hdr, file_hdr, opt_hdr) == ERROR)
            return ERROR;
    /* exception directory */
    if(opt_hdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION].VirtualAddress != 0)
        if(rebase_exception_directory(dos_hdr, nt_hdr, file_hdr, opt_hdr) == ERROR)
            return ERROR;
    /* rebase executable */
    fix_rva(&opt_hdr->AddressOfEntryPoint);
    fix_rva(&opt_hdr->BaseOfCode);
    fix_rva(&opt_hdr->BaseOfData);
    opt_hdr->ImageBase = g_new_virtual_base;
    /* rebase each directory */
    for(size_t i = 0; i < IMAGE_NUMBEROF_DIRECTORY_ENTRIES; i++)
        if(opt_hdr->DataDirectory[i].VirtualAddress != 0)
            fix_rva(&opt_hdr->DataDirectory[i].VirtualAddress);
    /* rebase each section (at the end because it's used for eeverything else */
    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(nt_hdr + 1);
    for(size_t i = 0; i < file_hdr->NumberOfSections; i++)
        sections[i].VirtualAddress = g_sec2va_table[i] - g_new_virtual_base;
    return MODIFIED;
}

enum statut_t read_sec2va_section(
    IMAGE_DOS_HEADER *dos_hdr,
    IMAGE_NT_HEADERS32 *nt_hdr,
    IMAGE_FILE_HEADER *file_hdr,
    IMAGE_OPTIONAL_HEADER32 *opt_hdr,
    IMAGE_SECTION_HEADER *sections)
{
    (void) dos_hdr;
    (void) nt_hdr;
    (void) opt_hdr;
    /* it must be the last section */
    IMAGE_SECTION_HEADER * sec = sections + (file_hdr->NumberOfSections - 1);
    /* check the name */
    if(strncmp(sec->Name, ".sec2va", IMAGE_SIZEOF_SHORT_NAME) != 0)
        return ERROR;
    /* check size */
    if(sec->SizeOfRawData != (file_hdr->NumberOfSections - 1) * sizeof(uint32_t))
        return ERROR;
    /* ok */
    file_hdr->NumberOfSections--;
    g_sec2va_table = (uint32_t *)(g_buf + sec->PointerToRawData);
    printf("Sec2VA table:\n");
    for(size_t i = 0; i < file_hdr->NumberOfSections; i++)
        printf("  [%u] %s -> 0x%08x\n", (unsigned)i, sections[i].Name, g_sec2va_table[i]);
    return MODIFIED;
}

enum statut_t rebase_wince()
{
    IMAGE_DOS_HEADER *dos_hdr = (IMAGE_DOS_HEADER *)g_buf;
    if(dos_hdr->e_magic != IMAGE_DOS_SIGNATURE)
        return false;
    IMAGE_NT_HEADERS32 *nt_hdr = (IMAGE_NT_HEADERS32 *)(g_buf + dos_hdr->e_lfanew);
    IMAGE_FILE_HEADER *file_hdr = &nt_hdr->FileHeader;
    IMAGE_OPTIONAL_HEADER32 *opt_hdr = &nt_hdr->OptionalHeader;
    if(nt_hdr->Signature != IMAGE_NT_SIGNATURE)
        return ERROR;
    if(file_hdr->SizeOfOptionalHeader != sizeof(IMAGE_OPTIONAL_HEADER32))
        return ERROR;
    if(opt_hdr->Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC)
        return ERROR;

    IMAGE_SECTION_HEADER *sections = (IMAGE_SECTION_HEADER *)(nt_hdr + 1);
    /* try to read the .sec2va table */
    if(read_sec2va_section(dos_hdr, nt_hdr, file_hdr, opt_hdr, sections) == ERROR)
        return ERROR;

    /* compute new virtual base */
    uint32_t old_smallest_va = 0xffffffff;
    for(size_t i = 0; i < file_hdr->NumberOfSections; i++)
    {
        uint32_t va = opt_hdr->ImageBase + sections[i].VirtualAddress;
        if(va < old_smallest_va)
            old_smallest_va = va;
    }
    uint32_t new_smallest_va = 0xffffffff;
    for(size_t i = 0; i < file_hdr->NumberOfSections; i++)
    {
        if(g_sec2va_table[i] < new_smallest_va)
            new_smallest_va = g_sec2va_table[i];
    }
    if(old_smallest_va == new_smallest_va)
        return UNMODIFIED;
    g_new_virtual_base = new_smallest_va - (old_smallest_va - opt_hdr->ImageBase);
    printf("Use new virtual base: 0x%08x (was 0x%08x)\n", g_new_virtual_base, opt_hdr->ImageBase);

    return rebase_executable(dos_hdr, nt_hdr, file_hdr, opt_hdr);
}

int main(int argc, char **argv)
{
    if(argc != 2 && argc != 3)
    {
        printf("usage: %s <in/out file> [<out file>]\n", argv[0]);
        return 1;
    }
    g_buf = load_file(argv[1], &g_sz);
    if(g_buf == NULL)
        return 1;

    switch(rebase_wince())
    {
        case UNMODIFIED: printf("Keep executable virtual base: don't rebase\n"); /* fallback */
        case MODIFIED: write_file(argc == 2 ? argv[1] : argv[2], g_buf, g_sz); break;
        case ERROR: printf("Ignore invalid PE file\n"); break;
    }
    free(g_buf);
    return 0;
}
