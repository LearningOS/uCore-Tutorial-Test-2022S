#include "syscall.h"
#include <stddef.h>
#include <unistd.h>
#include <stdio.h>

void __write_buffer();
void __clear_buffer();

int open(const char *path, int flags)
{
	return syscall(SYS_openat, path, flags, O_RDWR);
}

int close(int fd)
{
	if (fd == 1) {
		__write_buffer();
		__clear_buffer();
	}
	return syscall(SYS_close, fd);
}

ssize_t read(int fd, void *buf, size_t len)
{
	return syscall(SYS_read, fd, buf, len);
}

ssize_t write(int fd, const void *buf, size_t len)
{
	return syscall(SYS_write, fd, buf, len);
}

int getpid()
{
	return syscall(SYS_getpid);
}

int getppid()
{
	return syscall(SYS_getppid);
}

int sched_yield()
{
	return syscall(SYS_sched_yield);
}

int fork()
{
	return syscall(SYS_clone);
}

void exit(int code)
{
	__write_buffer();
	__clear_buffer();
	syscall(SYS_exit, code);
}

int waitpid(int pid, int *code)
{
	return syscall(SYS_wait4, pid, code);
}

static char **null = { 0 };
int exec(const char *name, char **argv)
{
	return syscall(SYS_execve, name, argv == 0 ? null : argv);
}

int64 get_mtime()
{
	TimeVal time;
	int err = sys_get_time(&time, 0);
	if (err == 0) {
		return (time.sec * 1000 + time.usec / 1000);
	}
	// get_time should never failed.
	return -1;
}

int sys_get_time(TimeVal *ts, int tz)
{
	return syscall(SYS_gettimeofday, ts, tz);
}

int sleep(unsigned long long time)
{
	unsigned long long s = get_mtime();
	while (get_mtime() < s + time) {
		sched_yield();
	}
	return 0;
}

int sys_task_info(TaskInfo *ti)
{
	return syscall(SYS_task_info, ti);
}

int set_priority(int prio)
{
	return syscall(SYS_setpriority, prio);
}

int mmap(void *start, unsigned long long len, int prot, int flag, int sd)
{
	return syscall(SYS_mmap, start, len, prot, flag, sd);
}

int munmap(void *start, unsigned long long len)
{
	return syscall(SYS_munmap, start, len);
}

int wait(int *code)
{
	return waitpid(-1, code);
}

int spawn(const char *file)
{
	return syscall(SYS_spawn, file);
}

int pipe(void *p)
{
	return syscall(SYS_pipe2, p);
}

int mailread(void *buf, int len)
{
	return syscall(SYS_mailread, buf, len);
}

int mailwrite(int pid, void *buf, int len)
{
	return syscall(SYS_mailwrite, pid, buf, len);
}

int fstat(int fd, Stat *st)
{
	return syscall(SYS_fstat, fd, st);
}

int sys_linkat(int olddirfd, char *oldpath, int newdirfd, char *newpath,
	       unsigned int flags)
{
	return syscall(SYS_linkat, olddirfd, oldpath, newdirfd, newpath, flags);
}

int sys_unlinkat(int dirfd, char *path, unsigned int flags)
{
	return syscall(SYS_unlinkat, dirfd, path, flags);
}

int link(char *old_path, char *new_path)
{
	return sys_linkat(AT_FDCWD, old_path, AT_FDCWD, new_path, 0);
}

int unlink(char *path)
{
	return sys_unlinkat(AT_FDCWD, path, 0);
}

int thread_create(void *entry, void *arg)
{
	// on first thread create enable, here must be single thread
	if (!buffer_lock_enabled) {
		enable_thread_io_buffer();
	}
	return syscall(SYS_thread_create, (uint64)entry, (uint64)arg);
}

int gettid(void)
{
	return syscall(SYS_gettid);
}

int waittid(int tid)
{
	int ret = syscall(SYS_waittid, tid);
	while (ret == -2) {
		sched_yield();
		ret = syscall(SYS_waittid, tid);
	}
	return ret;
}

int mutex_create()
{
	return syscall(SYS_mutex_create, 0);
}

int mutex_blocking_create()
{
	return syscall(SYS_mutex_create, 1);
}

int mutex_lock(int mid)
{
	return syscall(SYS_mutex_lock, mid);
}

int mutex_unlock(int mid)
{
	return syscall(SYS_mutex_unlock, mid);
}

int semaphore_create(int res_count)
{
	return syscall(SYS_semaphore_create, res_count);
}

int semaphore_up(int sid)
{
	return syscall(SYS_semaphore_up, sid);
}

int semaphore_down(int sid)
{
	return syscall(SYS_semaphore_down, sid);
}

int condvar_create()
{
	return syscall(SYS_condvar_create);
}

int condvar_signal(int cid)
{
	return syscall(SYS_condvar_signal, cid);
}

int condvar_wait(int cid, int mid)
{
	return syscall(SYS_condvar_wait, cid, mid);
}

int enable_deadlock_detect(int enabled)
{
	return syscall(SYS_enable_deadlock_detect, enabled);
}
