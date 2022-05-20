#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Notice that chread_count must be no more than 15,
// becase 1(main thread) + 15 = 16 is NTHREAD
#define thread_count (15)
#define per_thread (100)
int mutex_id;

int a;

int threads[thread_count];

void fun(long i)
{
	int t = i + 1;
	for (int i = 0; i < per_thread; i++) {
		assert_eq(mutex_lock(mutex_id), 0);
		int old_a = a;
		for (int i = 0; i < 500; i++) {
			t = t * t % 10007;
		}
		a = old_a + 1;
		assert_eq(mutex_unlock(mutex_id), 0);
	}
	exit(t);
}

int main()
{
	int64 start = get_mtime();
	assert((mutex_id = mutex_blocking_create()) >= 0);
	for (int i = 0; i < thread_count; i++) {
		threads[i] = thread_create(fun, (void *)i);
		assert(threads[i] > 0);
	}
	for (int i = 0; i < thread_count; i++) {
		int rc = waittid(threads[i]);
		printf("thread %d return with code %d\n", threads[i], rc);
	}
	int64 stop = get_mtime();
	printf("time cost is %d ms\n", (int)(stop - start));
	assert_eq(a, per_thread * thread_count);
	puts("race adder blocking mutex passed!");
	return 0;
}
