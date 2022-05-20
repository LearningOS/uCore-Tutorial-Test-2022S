#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// sem 0: used to sync child thread with main
// sem 1-3: representing some kind of resource

#define THREAD_N (4)
#define RES_TYPE (2)
int request[THREAD_N] = { 1, -1, 2, -1 };
const int alloc[THREAD_N] = { 2, 1, 1, 2 };
const int res_num[RES_TYPE] = { 2, 2 };

int semaphore_barrier_id;

void try_sem_down(int id, int sem_id)
{
	if (semaphore_down(sem_id) == -1) {
		assert_eq(semaphore_up(alloc[id]), 0);
		assert_eq(semaphore_up(semaphore_barrier_id), 0);
		exit(-1);
	}
}

void deadlock_test(long _tid)
{
	int id = _tid - 1;
	assert_eq(semaphore_down(alloc[id]), 0);
	assert_eq(semaphore_down(semaphore_barrier_id), 0);
	int sem_id = request[id];
	if (sem_id >= 0) {
		try_sem_down(id, sem_id);
		assert_eq(semaphore_up(sem_id), 0);
	}
	assert_eq(semaphore_down(semaphore_barrier_id), 0);
	assert_eq(semaphore_up(alloc[id]), 0);
	exit(0);
}

int main()
{
	assert((semaphore_barrier_id = semaphore_create(THREAD_N)) == 0);
	for (int i = 0; i < THREAD_N; i++) {
		semaphore_down(semaphore_barrier_id);
	}
	for (int i = 0; i < RES_TYPE; i++) {
		assert_eq(semaphore_create(res_num[i]), i + 1);
	}
	int threads[THREAD_N] = {};
	for (int i = 0; i < THREAD_N; i++) {
		threads[i] = thread_create(deadlock_test, (void *)i);
		assert(threads[i] == i + 1);
	}
	sleep(1000);
	for (int i = 0; i < THREAD_N; i++) {
		semaphore_up(semaphore_barrier_id);
	}
	for (int i = 0; i < THREAD_N; i++) {
		assert(waittid(threads[i]) == 0);
	}
	puts("deadlock test2 OK!");
	return 0;
}
