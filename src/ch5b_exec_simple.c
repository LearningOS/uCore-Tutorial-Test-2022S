#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	puts("execute hello");
	exec("ch2b_hello_world", NULL);
	return 0;
}