#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usertest.h"
/// 辅助测例，运行所有其他测例。

const char *TESTS[] = {
	"ch5_spawn0\0",	  "ch5_spawn1\0",   "ch5_setprio\0",
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
