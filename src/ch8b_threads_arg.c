#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LOOP 1000
#define NTHREAD 3

struct thread_arg {
	char c;
	int ret_code;
} args[NTHREAD] = {
	{ 'a', 1 },
	{ 'b', 2 },
	{ 'c', 3 },
};

void thread(struct thread_arg *arg)
{
	printf("thread %d arg: %p\n", gettid(), (uint64)arg);
	for (int i = 0; i < LOOP; ++i) {
		putchar(arg->c);
	}
	exit(arg->ret_code);
}

int main(void)
{
	int tids[NTHREAD];
	for (int i = 0; i < NTHREAD; ++i) {
		tids[i] = thread_create(thread, &args[i]);
	}
	for (int i = 0; i < NTHREAD; ++i) {
		int tid = tids[i];
		int exit_code = waittid(tid);
		printf("thread %d exited with code %d\n", tid, exit_code);
		assert_eq(tid, exit_code);
	}
	puts("threads with arg test passed!");
	return 0;
}