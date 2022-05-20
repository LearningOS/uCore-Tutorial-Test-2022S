#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int sem_sync_id;

void first()
{
	sleep(10);
	puts("First work and wakeup Second");
	semaphore_up(sem_sync_id);
	exit(0);
}

void second()
{
	puts("Second want to continue,but need to wait first");
	semaphore_down(sem_sync_id);
	puts("Second can work now");
	exit(0);
}

int main()
{
	assert((sem_sync_id = semaphore_create(0)) >= 0);
	init_thread_io_buffer();
	int threads[2];
	threads[0] = thread_create(first, 0);
	threads[1] = thread_create(second, 0);
	waittid(threads[0]);
	waittid(threads[1]);
	puts("sync_sem passed!");
	return 0;
}