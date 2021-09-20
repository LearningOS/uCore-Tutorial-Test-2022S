#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

/*
理想结果：输出 Test 04_6 ummap2 OK!
*/

int main()
{
	uint64 start = 0x10000000;
	uint64 len = 4096;
	int prot = 3;
	assert_eq(0, mmap((void *)start, len, prot, MAP_ANONYMOUS, -1));
	assert_eq(munmap((void *)start, len + 1), -1);
	assert_eq(munmap((void *)(start + 1), len - 1), -1);
	puts("Test 04_5 ummap2 OK!");
	return 0;
}