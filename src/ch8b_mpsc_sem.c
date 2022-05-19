#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define buffer_size (8)
#define producers (4)
#define number_per_producer (100)

int sem_mutex_id = 0;
int sem_empty_id = 1;
int sem_existed_id = 2;

int buffer[buffer_size];
int front = 0;
int tail = 0;
int threads[producers];

void producer(int id)
{
	for (int i = 0; i < number_per_producer; i++) {
		semaphore_down(sem_empty_id);
		semaphore_down(sem_mutex_id);
		buffer[front] = id;
		front = (front + 1) % buffer_size;
		semaphore_up(sem_mutex_id);
		semaphore_up(sem_empty_id);
	}
	exit(0);
}

void consumer()
{
	for (int i = 0; i < number_per_producer * producers; i++) {
		semaphore_down(sem_existed_id);
		semaphore_down(sem_mutex_id);
		printf("%d ", buffer[tail]);
		tail = (tail + 1) % buffer_size;
		semaphore_up(sem_mutex_id);
		semaphore_up(sem_existed_id);
	}
}

int main()
{
	assert_eq(semaphore_create(1), sem_mutex_id);
	assert_eq(semaphore_create(buffer_size), sem_mutex_id);
	assert_eq(semaphore_create(0), sem_mutex_id);
	for (int i = 0; i < producers; i++) {
		threads[i] = thread_create(producer, (void *)i);
		assert(threads[i] > 0);
	}
	return 0;
}
