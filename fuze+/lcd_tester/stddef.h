#ifndef __stddef_h__
#define __stddef_h__

#include "stdint.h"

typedef uint32_t size_t;
typedef int32_t ssize_t;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

#endif /* __stddef_h__ */
