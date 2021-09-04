#include <stdio.h>
#include <unistd.h>

int main()
{
	uint64 x;
	asm volatile("csrr %0, sstatus" : "=r"(x));
	return 0;
}