#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Notice that chread_count must be no more than 15,
// becase 1(main thread) + 15 = 16 is NTHREAD
#define thread_count (15)
#define per_thread (100)
const int mid = 0;

int a;

int threads[thread_count];

void fun()
{
	int t = 2;
	for (int i = 0; i < per_thread; i++) {
		mutex_lock(mid);
		// Force to extend the time of a++
		int old_a = a;
		for (int i = 0; i < 500; i++) {
			t = t * t / 10007;
		}
		a = old_a + 1;
		// A time cost a++ ends
		mutex_unlock(mid);
	}
	exit(t);
}

int main()
{
	int64 start = get_mtime();
	assert_eq(mutex_blocking_create(), mid);
	for (int i = 0; i < thread_count; i++) {
		threads[i] = thread_create(fun, 0);
		assert(threads[i] > 0);
	}
	for (int i = 0; i < thread_count; i++) {
		waittid(threads[i]);
	}
	int64 stop = get_mtime();
	printf("time cost is %d ms\n", (int)(stop - start));
	assert_eq(a, per_thread * thread_count);
	return 0;
}
