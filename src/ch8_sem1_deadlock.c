#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// sem 0: used to sync child thread with main
// sem 1-3: representing some kind of resource

#define THREAD_N (3)
#define RES_TYPE (3)
const int request[THREAD_N] = { 1, 3, 2 };
const int res_num[RES_TYPE] = { 1, 2, 1 };

int semaphore_barrier_id;

void sem_dealloc();
void try_sem_down(int tid, int sem_id)
{
	if (semaphore_down(sem_id) == -1) {
		sem_dealloc(tid);
		exit(-1);
	}
}

void sem_alloc(int tid)
{
	semaphore_down(semaphore_barrier_id);
	switch (tid) {
	case 1:
		assert_eq(semaphore_down(2), 0);
		break;
	case 2:
		assert_eq(semaphore_down(1), 0);
		assert_eq(semaphore_down(2), 0);
		break;
	case 3:
		assert_eq(semaphore_down(3), 0);
		break;
	default:
		exit(1);
	}
}

void sem_dealloc(int tid)
{
	switch (tid) {
	case 1:
		assert_eq(semaphore_up(2), 0);
		break;
	case 2:
		assert_eq(semaphore_up(1), 0);
		assert_eq(semaphore_up(2), 0);
		break;
	case 3:
		assert_eq(semaphore_up(3), 0);
		break;
	default:
		exit(1);
	}
	semaphore_up(semaphore_barrier_id);
}

void deadlock_test(long _tid)
{
	int tid = _tid;
	sem_alloc(tid);
	int sem_id = request[tid - 1];
	try_sem_down(tid, sem_id);
	semaphore_up(sem_id);
	sem_dealloc(tid);
	exit(0);
}

int main()
{
	assert((semaphore_barrier_id = semaphore_create(THREAD_N)) >= 0);
	for (int i = 0; i < THREAD_N; i++) {
		semaphore_down(semaphore_barrier_id);
	}
	for (int i = 0; i < RES_TYPE; i++) {
		semaphore_create(res_num[i]);
	}
	int threads[THREAD_N] = {};
	for (int i = 0; i < THREAD_N; i++) {
		threads[i] = thread_create(deadlock_test, (void *)i);
	}
	sleep(1000);
	for (int i = 0; i < THREAD_N; i++) {
		semaphore_up(semaphore_barrier_id);
	}
	for (int i = 0; i < THREAD_N; i++) {
		waittid(threads[i]);
	}
	puts("deadlock test2 OK!");
	return 0;
}
