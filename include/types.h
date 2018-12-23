#ifndef __TYPES_H__
#define __TYPES_H__

#include <stdint.h>



#define __OFFSET_OF(type, member) (uword)&(((type*)0)->member)
#define __CONTAINER_OF(ptr, type, member) ({ \
     const typeof( ((type *)0)->member ) *__mptr = (ptr); \
     (type *)( (char *)__mptr - offsetof(type, member) );})
// #define __HEAP_VAR_HEADER_OF(var) __CONTAINER_OF(var, __HeapVarDesc_t, content)
//#define __VAR_HEADER_OF(var) __CONTAINER_OF(var, __VarDesc_t, content)
#define		NULL	0

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

typedef u32 uword;
typedef i32 word;

#endif

