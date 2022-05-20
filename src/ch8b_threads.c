#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOOP 1000
#define NTHREAD 3

void thread_a()
{
	for (int i = 0; i < LOOP; ++i) {
		putchar('a');
	}
	exit(1);
}

void thread_b()
{
	for (int i = 0; i < LOOP; ++i) {
		putchar('b');
	}
	exit(2);
}

void thread_c()
{
	for (int i = 0; i < LOOP; ++i) {
		putchar('c');
	}
	exit(3);
}

int main(void)
{
	int tids[NTHREAD];
	tids[0] = thread_create(thread_a, 0);
	tids[1] = thread_create(thread_b, 0);
	tids[2] = thread_create(thread_c, 0);
	for (int i = 0; i < NTHREAD; ++i) {
		int tid = tids[i];
		int exit_code = waittid(tid);
		printf("thread %d exited with code %d\n", tid, exit_code);
		assert_eq(tid, exit_code);
	}
	puts("threads test passed!");
	return 0;
}