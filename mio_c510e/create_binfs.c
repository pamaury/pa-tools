#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>
#include "rom.h"

#define ADD_XIPCHAIN

#define BINFS_HDR_OFFSET    0x210

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

/* globals */
uint32_t g_start_address = 0x30000000;

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

void write_file(char *name, void *buf, size_t size)
{
    FILE *f = fopen(name, "wb");
    if(f == NULL)
    {
        printf("Cannot open '%s' for writing !\n", name);
        return;
    }
    if(fwrite(buf, size, 1, f) != 1)
    {
        printf("Cannot write '%s' !\n", name);
    }
    fclose(f);
}

#ifdef ADD_XIPCHAIN
uint32_t extract_virtual_size(void *fw, size_t fw_size)
{
    uint32_t sig = *(uint32_t *)(fw + ROM_SIGNATURE_OFFSET);
    if(sig != ROM_SIGNATURE)
    {
        printf("Wrong ROM signature !\n");
        return 0;
    }
    uint32_t toc_ptr = *(uint32_t *)(fw + ROM_TOC_POINTER_OFFSET);
    ROMHDR *romhdr = (ROMHDR *)(fw + toc_ptr - g_start_address);
    return romhdr->physlast - romhdr->physfirst;
}
#endif

void *build_image(void *fw, size_t fw_size, void *hdr, size_t hdr_size, size_t *binfs_size)
{
    #ifdef ADD_XIPCHAIN
    *binfs_size = fw_size + hdr_size + sizeof(XIPCHAIN_INFO);
    #else
    *binfs_size = fw_size + hdr_size;
    #endif
    void *binfs = malloc(*binfs_size);
    if(binfs == NULL)
        return NULL;
    memcpy(binfs, hdr, hdr_size);
    memcpy(binfs + hdr_size, fw, fw_size);

    #ifdef ADD_XIPCHAIN
    uint32_t fw_virt_size = extract_virtual_size(fw, fw_size);

    struct binfs_header *mod = (struct binfs_header *)(binfs + BINFS_HDR_OFFSET);
    mod->xip_kernel_start = g_start_address;
    mod->xip_kernel_len = fw_virt_size;
    mod->nk_entry = g_start_address;
    mod->xip_kernel_start2 = mod->xip_kernel_start;
    mod->xip_kernel_len2 = mod->xip_kernel_len;
    mod->chain_start = g_start_address + fw_virt_size;
    mod->chain_len = sizeof(XIPCHAIN_INFO);
    mod->xip_start = g_start_address;
    mod->xip_len = fw_virt_size;
    XIPCHAIN_INFO *xipchain = (XIPCHAIN_INFO *)(binfs + hdr_size + fw_size);
    memset(xipchain, 0, sizeof(XIPCHAIN_INFO));
    xipchain->cXIPs = 1;
    xipchain->xipEntryStart.pvAddr = g_start_address;
    xipchain->xipEntryStart.dwLength = fw_size;
    xipchain->xipEntryStart.dwMaxLength = fw_size;
    xipchain->xipEntryStart.usOrder = 1;
    xipchain->xipEntryStart.usFlags = ROMXIP_OK_TO_LOAD;
    xipchain->xipEntryStart.dwVersion = 0;
    strcpy(xipchain->xipEntryStart.szName, "XIPKERNEL");
    xipchain->xipEntryStart.dwAlgoFlags = 0;
    xipchain->xipEntryStart.dwKeyLen = 0;
    #endif
    
    return binfs;
}

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        printf("usage: %s <firmware file> <binfs header file> <out binfs file>\n", argv[0]);
        return 1;
    }
    char *firmware = argv[1];
    char *header = argv[2];
    char *binfs = argv[3];

    size_t fw_size;
    void *fw_buf = load_file(firmware, &fw_size);
    if(fw_buf == NULL)
        return 1;

    size_t hdr_size;
    void *hdr_buf = load_file(header, &hdr_size);
    if(hdr_buf == NULL)
    {
        free(fw_buf);
        return 1;
    }

    size_t binfs_size;
    void *binfs_buf = build_image(fw_buf, fw_size, hdr_buf, hdr_size, &binfs_size);
    
    free(fw_buf);
    free(hdr_buf);

    write_file(binfs, binfs_buf, binfs_size);
    free(binfs_buf);
    
    return 0;
}
