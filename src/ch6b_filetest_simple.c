#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char *s = "Hello, world!\n";
	char *filea = "filea\0";
	int fd = open(filea, O_CREATE | O_WRONLY);
	assert(fd > 0);
	write(fd, s, strlen(s));
	close(fd);
	fd = open(filea, O_RDONLY);
	assert(fd > 0);
	char buf[16];
	int read_len = read(fd, buf, 16);
	close(fd);
	assert(strcmp(s, buf) == 0);
	puts("file_test passed!");
	return 0;
}