#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N (5)
#define ROUND (4)
#define SLEEP_SCALE (10)

const int arr[N][ROUND * 2] = {
	{ 7, 8, 10, 4, 5, 6, 2, 4 }, { 3, 6, 2, 7, 10, 1, 3, 6 },
	{ 5, 2, 9, 2, 4, 6, 12, 4 }, { 5, 10, 6, 5, 8, 6, 2, 9 },
	{ 6, 1, 6, 6, 2, 5, 6, 2 },
};

int think[N][ROUND * 2];
int eat[N][ROUND * 2];

void philosopher_dining(long id)
{
	int left = id;
	int right = (id + 1) % N;
	int min = left < right ? left : right;
	int max = left < right ? right : left;
	for (int round = 0; round < ROUND; round++) {
		// thinking
		think[id][2 * round] = get_mtime();
		sleep(arr[id][2 * round] * SLEEP_SCALE);
		think[id][2 * round + 1] = get_mtime();
		// wait for forks
		mutex_lock(min);
		mutex_lock(max);
		// eating
		eat[id][2 * round] = get_mtime();
		sleep(arr[id][2 * round + 1] * SLEEP_SCALE);
		eat[id][2 * round + 1] = get_mtime();
		mutex_unlock(max);
		mutex_unlock(min);
	}
	exit(0);
}

int main()
{
	printf("Here comes %d philosophers!\n", N);
	int threads[N];
	int start = get_mtime();
	for (int i = 0; i < N; i++) {
		assert_eq(mutex_blocking_create(), i);
	}
	// Notice: Children threads creating must be after mutex creation
	for (int i = 0; i < N; i++) {
		threads[i] = thread_create(philosopher_dining, (void *)i);
		assert(threads[i] > 0);
	}
	puts("Phil threads created");
	for (int i = 0; i < N; i++) {
		waittid(threads[i]);
	}
	int time_cost = get_mtime() - start;
	printf("time cost = %d ms\n", time_cost);
	puts("'-' -> THINKING; 'x' -> EATING; ' ' -> WAITING ");
	for (int i = 0; i <= N; i++) {
		int id = i % N;
		printf("#%d:", id);
		for (int j = 0; j < time_cost / SLEEP_SCALE; j++) {
			int current = j * SLEEP_SCALE + start;
			int round;
			for (round = 0; round < ROUND; round++) {
				int start_thinking = think[id][2 * round];
				int stop_thinking = think[id][2 * round + 1];
				if (start_thinking <= current &&
				    current <= stop_thinking) {
					putchar('-');
					break;
				}
			}
			if (round < ROUND)
				continue;
			for (round = 0; round < ROUND; round++) {
				int start_eating = eat[id][2 * round];
				int stop_eating = eat[id][2 * round + 1];
				if (start_eating <= current &&
				    current <= stop_eating) {
					putchar('x');
					break;
				}
			}
			if (round < ROUND)
				continue;
			putchar(' ');
		}
		putchar('\n');
	}
	puts("philosopher dining problem with mutex passed!");
	return 0;
}
