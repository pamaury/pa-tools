#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    int fd = open("/dev/random", O_RDONLY);
    if(fd < 0)
    {
        perror("Unable to open /dev/random");
        return 1;
    }
    int data;
    if(read(fd, &data, sizeof data) != sizeof data)
    {
        perror("Unable to read from /dev/random");
        close(fd);
        return 1;
    }
    printf("%d\n", data);
    close(fd);
    return 0;
}
