#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int mutex_id = mutex_create();
	assert_eq(mutex_lock(mutex_id), 0);
	assert_eq(mutex_lock(mutex_id), -1);
	mutex_unlock(mutex_id);
	puts("deadlock test1 OK!");
	return 0;
}
