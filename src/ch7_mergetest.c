#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usertest.h"

/// 辅助测例，运行所有其他测例。

char *TESTS[] = {
	"ch2b_hello_world\0", "ch2b_power\0",	  "ch2b_write1\0",
	"ch3b_sleep\0",	      "ch3b_sleep1\0",	  "ch3b_yield0\0",
	"ch3b_yield1\0",      "ch3b_yield2\0",	  "ch5b_gitpid\0",
	"ch5b_forktest0\0",   "ch5b_forktest1\0", "ch5b_forktest2\0",
	"ch4_mmap0\0",	      "ch4_mmap1\0",	  "ch4_mmap2\0",
	"ch4_mmap3\0",	      "ch4_unmap0\0",	  "ch4_unmap1\0",
	"ch5_spawn0\0",	      "ch5_spawn1\0",	  "ch6b_pipetest\0",
	"ch6_mail0\0",	      "ch6_mail1\0",	  "ch6_mail2\0",
	"ch6_mail3\0",	      "ch7b_filetest\0",  "ch7b_exec\0",
};

int main()
{
	int num_test = sizeof(TESTS) / sizeof(char *);
	int succ = run_tests(TESTS, num_test);
	assert_eq(succ, num_test);
	puts("ch7 Mergetests passed!");
	return 0;
}
