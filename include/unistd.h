#ifndef __UNISTD_H__
#define __UNISTD_H__

#include "stddef.h"

int open(const char *, int);
ssize_t read(int, void *, size_t);
ssize_t write(int, const void *, size_t);
int close(int);
pid_t getpid();
pid_t getppid();
int sched_yield();
void exit(int);
int fork();
int exec(char *, char **);
int waitpid(int, int *);
int64 get_mtime();
int sys_get_time(TimeVal *ts,
		 int tz); // syscall ID: 169; tz 表示时区，这里无需考虑，始终为0;
// 返回值：正确返回 0，错误返回 -1。
int sys_task_info(TaskInfo *ti);
int sleep(unsigned long long);
int set_priority(int prio);
int mmap(void *start, unsigned long long len, int prot, int flag, int shmem_id);
int munmap(void *start, unsigned long long len);
int wait(int *);
int spawn(char *file);
int pipe(void *p);
int mailread(void *buf, int len);
int mailwrite(int pid, void *buf, int len);
int fstat(int fd, Stat *st);
int sys_linkat(int olddirfd, char *oldpath, int newdirfd, char *newpath,
	       unsigned int flags);
int sys_unlinkat(int dirfd, char *path, unsigned int flags);
int link(char *old_path, char *new_path);
int unlink(char *path);
int thread_create(void *entry, void *arg);
int gettid(void);
int waittid(int tid);

#endif // __UNISTD_H__
