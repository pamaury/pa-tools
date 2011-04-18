#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
    printf("args[%d]:", argc);
    for(int i = 0; i < argc; i++)
        printf(" %s", argv[i]);
    printf("\n");

    srand(time(NULL));

    int fd = open("/dev/random", O_RDONLY);
    if(fd < 0)
    {
        perror("Unable to open /dev/random");
        return 1;
    }
    uint8_t data8;
    if(read(fd, &data8, sizeof data8) != sizeof data8)
    {
        perror("Unable to read from /dev/random");
        close(fd);
        return 1;
    }
    uint16_t data16;
    if(read(fd, &data16, sizeof data16) != sizeof data16)
    {
        perror("Unable to read from /dev/random");
        close(fd);
        return 1;
    }
    uint32_t data32;
    if(read(fd, &data32, sizeof data32) != sizeof data32)
    {
        perror("Unable to read from /dev/random");
        close(fd);
        return 1;
    }
    time_t tm = time(NULL);
    char buf[128];
    strftime(buf, 128, "%c", localtime(&tm));
    printf("%s %d %d %d %d\n", buf, data8, data16, data32, rand());
    close(fd);
    return 0;
}
