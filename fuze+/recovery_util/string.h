#ifndef __string_h__
#define __string_h__

#include "stddef.h"

void memset(void *dst, int c, size_t n);
void memcpy(void *dst, const void *src, size_t n);
size_t strlen(const char *s);

#endif /* __string_h__ */
