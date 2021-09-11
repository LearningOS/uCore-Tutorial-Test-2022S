#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
理想结果：得到进程 pid，注意要关注 pid 是否符合内核逻辑，不要单纯以 Test OK!
作为判断。
*/

int main()
{
	int pid = getpid();
	int ppid = getppid();
	if (fork() == 0) {
		int cppid = getppid();
		assert_eq(cppid, pid);
		printf("Test getppid OK!\n");
		exit(0);
	}
	int xstate = 0;
	wait(&xstate);
	printf("Test getpid OK! pid = %d, ppid = %d\n", pid, ppid);
	return 0;
}