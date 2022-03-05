#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <syscall.h>
// Seems that can't include <syscall.h>, so define SYSCALL id here
#define SYSCALL_WRITE 64
#define SYSCALL_EXIT 93
#define SYSCALL_YIELD 124
#define SYSCALL_GETTIMEOFDAY 169
#define SYSCALL_TASK_INFO 410

int main()
{
	TaskInfo info;
	get_time();
	get_time();
	get_time();
	// 注意本次 task info 调用也计入内
	assert(task_info(&info) == 0);
	assert(3 == info.syscall_times[SYSCALL_GETTIMEOFDAY]);
	assert(1 == info.syscall_times[SYSCALL_TASK_INFO]);
	assert(0 == info.syscall_times[SYSCALL_WRITE]);
	assert(0 == info.syscall_times[SYSCALL_YIELD]);
	assert(0 == info.syscall_times[SYSCALL_EXIT]);

	puts("hello world!");
	// 想想为什么 write 调用是两次
	assert(task_info(&info) == 0);
	assert(3 == info.syscall_times[SYSCALL_GETTIMEOFDAY]);
	assert(2 == info.syscall_times[SYSCALL_TASK_INFO]);
	assert(2 == info.syscall_times[SYSCALL_WRITE]);
	assert(0 == info.syscall_times[SYSCALL_YIELD]);
	assert(0 == info.syscall_times[SYSCALL_EXIT]);
	return 0;
}