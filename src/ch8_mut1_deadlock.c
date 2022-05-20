#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
理想结果：检测出死锁，第二次 mutex_lock 失败，程序正常结束
*/

int main()
{
	enable_deadlock_detect(1);
	int mutex_id = mutex_create();
	assert_eq(mutex_lock(mutex_id), 0);
	assert_eq(mutex_lock(mutex_id), -0xdead);
	mutex_unlock(mutex_id);
	puts("deadlock test mutex 1 OK!");
	return 0;
}
