#ifndef __format_h__
#define __format_h__

#include <stdarg.h>

void vuprintf(int (*push)(void *userp, unsigned char data),
              void *userp, const char *fmt, va_list ap);

#endif /* __format_h__ */
