#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define buffer_size (8)
#define producers (4)
#define number_per_producer (100)

int sem_mutex_id;
int sem_empty_id;
int sem_existed_id;

int buffer[buffer_size];
int front = 0;
int tail = 0;
int threads[producers + 1];

void producer(int id)
{
	printf("producer %d started task\n", id);
	for (int i = 0; i < number_per_producer; i++) {
		assert_eq(semaphore_down(sem_empty_id), 0);
		assert_eq(semaphore_down(sem_mutex_id), 0);
		buffer[front] = id;
		front = (front + 1) % buffer_size;
		assert_eq(semaphore_up(sem_mutex_id), 0);
		assert_eq(semaphore_up(sem_existed_id), 0);
	}
	printf("producer %d finished task\n", id);
	exit(0);
}

void consumer()
{
	puts("consumer started task");
	for (int i = 0; i < number_per_producer * producers; i++) {
		assert_eq(semaphore_down(sem_existed_id), 0);
		assert_eq(semaphore_down(sem_mutex_id), 0);
		printf("%d ", buffer[tail]);
		tail = (tail + 1) % buffer_size;
		assert_eq(semaphore_up(sem_mutex_id), 0);
		assert_eq(semaphore_up(sem_empty_id), 0);
	}
	puts("consumer finished task");
	exit(0);
}

int main()
{
	assert((sem_mutex_id = semaphore_create(1)) >= 0);
	assert((sem_empty_id = semaphore_create(buffer_size)) >= 0);
	assert((sem_existed_id = semaphore_create(0)) >= 0);
	for (int i = 0; i < producers; i++) {
		threads[i] = thread_create(producer, (void *)i);
		assert(threads[i] > 0);
	}
	threads[producers] = thread_create(consumer, 0);
	for (int i = 0; i <= producers; i++) {
		waittid(threads[i]);
	}
	puts("mpsc_sem passed!");
	return 0;
}
