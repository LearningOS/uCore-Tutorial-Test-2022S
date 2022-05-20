#ifndef __STDLIB_H__
#define __STDLIB_H__

#include "stddef.h"
#include "stdio.h"

extern pid_t getpid();
extern char *basename(char *);

#define _STRINGIFY(s) #s
#define STRINGIFY(s) _STRINGIFY(s)

#define panic(fmt, ...)                                                        \
	do {                                                                   \
		int tid = getpid();                                            \
		printf("\x1b[%dm[%s %d][%s:%d]: " fmt "\x1b[0m\n", 31,         \
		       "PANIC", tid, basename(__FILE__), __LINE__,             \
		       ##__VA_ARGS__);                                         \
		exit(-1);                                                      \
	} while (0)

#ifndef assert
#define assert(f)                                                              \
	if (!(f))                                                              \
	panic("assert error: " STRINGIFY(f))
#endif

#ifndef assert_eq
#define assert_eq(a, b)                                                        \
	if (!((a) == (b)))                                                     \
		panic("assert_eq error: "                                      \
		      "%p != %p",                                              \
		      a, b);
#endif

void srand(int s);
uint32 rand();

#endif //__STDLIB_H__
