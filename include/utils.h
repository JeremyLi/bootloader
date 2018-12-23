#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdarg.h>


extern int __kprintf(const char *fmt, ...);

#define DBG(fmt, ...) __kprintf(fmt, ##__VA_ARGS__)

#endif
