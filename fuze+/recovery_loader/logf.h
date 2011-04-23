#ifndef __logf_h__
#define __logf_h__

#include "stddef.h"

void logf(const char *fmt, ...);
size_t logf_readback(char *buf, size_t max_size);

#endif /* __logf_h__ */
