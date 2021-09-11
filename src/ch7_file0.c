#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/// 测试文件基本读写，输出　Test file0 OK! 就算正确。

int main()
{
	char *test_str = "Hello, world!";
	char *fname = "fname";
	int fd = open(fname, O_CREATE | O_WRONLY);
	assert(fd > 0);
	write(fd, test_str, strlen(test_str));
	close(fd);

	fd = open(fname, O_RDONLY);
	assert(fd > 0);

	char buffer[100];
	memset(buffer, 0, sizeof(buffer));
	int read_len = read(fd, &buffer, sizeof(buffer));
	close(fd);

	assert_eq(strncmp(buffer, test_str, read_len), 0);
	puts("Test file0 OK!");
	return 0;
}