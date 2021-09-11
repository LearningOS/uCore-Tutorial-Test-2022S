#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int NUM = 5;

int main()
{
	for (int i = 0; i < NUM; ++i) {
		int pid = fork();
		if (pid == 0) {
			exec("ch2b_hello_world", NULL);
			exit(0);
		}
	}
	int xstate = 0;
	for (int i = 0; i < NUM; ++i) {
		assert(wait(&xstate) > 0);
		assert_eq(xstate, 0);
	}
	assert(wait(&xstate) < 0);
	printf("forktest2 test passed!\n");
	return 0;
}
