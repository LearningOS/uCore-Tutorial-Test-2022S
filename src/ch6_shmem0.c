#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	uint64 start0 = 0x10000000;
	uint64 start1 = 0x10000000 + 0x1000;
	uint64 len = 0x1000;
	uint64 prot = 3;
	int shmem_id0 = mmap(start0, len, prot, MAP_SHARED, -1);
	assert(shmem_id0 >= 0);
	int shmem_id1 = mmap(start1, len, prot, MAP_SHARED, shmem_id0);
	assert(shmem_id1 == shmem_id0);
	*(uint64 *)start0 = 0xabab;
	assert(*(uint64 *)start1 == 0xabab);
	munmap(start0, len);
	munmap(start1, len);
	puts("ch6_shmem0 OK!");
	return 0;
}