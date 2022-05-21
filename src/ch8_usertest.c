#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usertest.h"

/// 辅助测例，运行所有其他测例。

const char *TESTS[] = {
	"ch2b_hello_world\0",  "ch2b_power\0",	       "ch3b_sleep\0",
	"ch3b_sleep1\0",       "ch3b_yield0\0",	       "ch3b_yield1\0",
	"ch3b_yield2\0",       "ch5b_getpid\0",	       "ch5b_forktest0\0",
	"ch5b_forktest1\0",    "ch5b_forktest2\0",     "ch6b_filetest\0",
	"ch6b_exec\0",	       "ch8_sem1_deadlock\0",  "ch8_sem2_deadlock\0",
	"ch8_mut1_deadlock\0", "ch8b_mpsc_sem\0",      "ch8b_mut_race\0",
	"ch8b_sync_sem\0",     "ch8b_test_condvar\0",  "ch8b_threads_arg\0",
	"ch8b_threads\0",      "ch8b_spin_mut_race\0", "ch8b_mut_phi_din\0",
};

int main()
{
	int num_test = sizeof(TESTS) / sizeof(char *);
	int succ = run_tests(TESTS, num_test);
	assert_eq(succ, num_test);
	puts("ch8 Usertests passed!");
	return 0;
}
