#include "logf.h"
#include "format.h"
#include "string.h"
#include "serial.h"

#define MAX_LOGF_SIZE   65536
static unsigned char logfbuffer[MAX_LOGF_SIZE];
static int logfread = 0;
static int logfwrite = 0;

static int logf_push(void *userp, unsigned char c)
{
    (void)userp;

    //serial_put(c);
    logfbuffer[logfwrite++] = c;
    if(logfwrite == MAX_LOGF_SIZE)
        logfwrite = 0;
    return true;
}

void logf(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vuprintf(logf_push, NULL, fmt, ap);
    va_end(ap);
}

size_t logf_readback(char *buf, size_t max_size)
{
    if(logfread == logfwrite)
        return 0;
    if(logfread < logfwrite)
        max_size = MIN(max_size, (size_t)(logfwrite - logfread));
    else
        max_size = MIN(max_size, (size_t)(MAX_LOGF_SIZE - logfread));
    memcpy(buf, &logfbuffer[logfread], max_size);
    logfread += max_size;
    if(logfread == MAX_LOGF_SIZE)
        logfread = 0;
    return max_size;
}
