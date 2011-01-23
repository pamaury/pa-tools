#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

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

uint32_t checksum(uint8_t *data, int len)
{
    uint32_t result = 0;
    while(len-- > 0)
        result += *data++;
    return result;
}

int main(int argc, char **argv)
{
    if(argc != 3)
    {
        printf("usage: %s <binfs file> <cks file>\n", argv[0]);
        return 1;
    }
    size_t size;
    void *buf = load_file(argv[1], &size);
    if(buf == NULL)
        return 1;
    uint32_t ck = checksum(buf, size);
    free(buf);

    FILE *fout = fopen(argv[2], "wb");
    if(fout == NULL)
    {
        printf("Cannot open '%s' for writing\n", argv[2]);
        return 1;
    }
    fprintf(fout, "binSize : %ld\n", size);
    fprintf(fout, "checksum: 0x%X", ck);
    fclose(fout);
    return 0;
}
