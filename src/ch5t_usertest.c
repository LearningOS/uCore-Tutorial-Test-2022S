#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usertest.h"
/// 辅助测例，运行所有其他测例。

const char *TESTS[] = {
	"ch5t_stride0\0",	  "ch5t_stride1\0",   "ch5t_stride2\0",
    "ch5t_stride3\0",	  "ch5t_stride4\0",   "ch5t_stride5\0",
};

const char *FAILS[] = {
};

int main()
{
	int nsucc = sizeof(TESTS) / sizeof(char *);
	int nfail = sizeof(FAILS) / sizeof(char *);
	test(TESTS, nsucc, FAILS, nfail, "ch5 Usertests passed!");
	return 0;
}
