#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "usertest.h"
/// 辅助测例，运行所有其他测例。

const char *TESTS[] = {
	"ch2b_hello_world\0", "ch2b_power\0",	  //"ch2b_write1\0",
	"ch3b_sleep\0",	      "ch3b_sleep1\0",	  "ch3b_yield0\0",
	"ch3b_yield1\0",      "ch3b_yield2\0",	  "ch5b_getpid\0",
	"ch5b_forktest0\0",   "ch5b_forktest1\0", "ch5b_forktest2\0",
	"ch4_mmap0\0",	      "ch4_mmap1\0",      "ch4_mmap2\0",
    "ch4_mmap3\0",	      "ch4_unmap0\0",
	"ch4_unmap1\0",	      "ch5_spawn0\0",	  "ch5_spawn1\0",
	"ch5_setprio\0",
};

int main()
{
	int pid[20] = {0};
	for (int i = 0; i < 20; i++) {
		printf("Usertests: Running %s\n", TESTS[i]);
		pid[i] = spawn(TESTS[i]);

	}
	int exit_pid = 0;
	for(int i = 0; i < 20; i++) {
        int wait_pid = waitpid(pid[i], &exit_pid);
        assert_eq(wait_pid, pid[i]);
    }
	int stride_pid = spawn("ch5t_usertest\0");
	int wait_pid = waitpid(stride_pid, &exit_pid);
	assert_eq(wait_pid, stride_pid);
    puts("ch5 Usertests passed!");
	return 0;
}
