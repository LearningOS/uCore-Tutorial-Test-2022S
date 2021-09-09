#include <stdio.h>
#include <unistd.h>

int main()
{
	asm volatile("sret");
	return 0;
}