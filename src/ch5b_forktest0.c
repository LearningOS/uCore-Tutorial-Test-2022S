#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	assert(wait(0) < 0);
	printf("sys_wait without child process test passed!\n");
	printf("parent start, pid = %d!\n", getpid());
	int pid = fork();
	if (pid == 0) {
		// child process
		printf("hello child process!\n");
		exit(100);
	} else {
		// parent process
		int xstate = 0;
		printf("ready waiting on parent process!\n");
		assert_eq(pid, wait(&xstate));
		assert_eq(xstate, 100);
		printf("child process pid = %d, exit code = %d\n", pid, xstate);
	}
	printf("forktest0 pass.\n");
	return 0;
}