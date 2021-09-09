#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	uint64 *start0 = (void *)0x10000000;
	uint64 *start1 = (void *)(0x10000000 + 0x1000);
	uint64 len = 0x1000;
	uint64 prot = 3;
	int xstate = 0;
	int shmem_id0 = mmap(start0, len, prot, MAP_SHARED, -1);
	assert(shmem_id0 >= 0);
	int pid = fork();
	if (pid == 0) {
		mmap(start1, len, prot, MAP_SHARED, shmem0_id);
		for (int try = 0; *start1 != 0xabab; try++) {
			sched_yield();
			if (try >= 3) {
				exit(-1);
			}
		}
		*start1 = 0xbaba;
		exit(0);
	} else {
		*start0 = 0xabab;
		munmap(start0, len);
		assert(wait(&xstate) == pid);
		assert(xstate == 0);
		assert(*start0 = 0xbaba);
	}
	puts("ch6_shmem1 OK!");
	return 0;
}