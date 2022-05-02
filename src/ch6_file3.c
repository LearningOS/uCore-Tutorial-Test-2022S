#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/// 测试大量 open/unlink，输出 Test mass open/unlink OK! 就算正确。

void repeat(char *target, const char *template, int times)
{
	int len = strlen(template);
	for (int i = 0; i < times; i++)
		stpncpy(target + len * i, template, len);
}
char test_str[4096];
int main()
{
	char fname[] = "fname3-0";
	puts("build");
	repeat(test_str,
	       "some random long long long long long long long long string",
	       50);
	int len = strlen(test_str);
	puts("start iteration");
	for (int i = 0; i < 10; i++) {
		fname[7] = '0' + i; // change fname to "fname%d"
		int fd = open(fname, O_CREATE | O_WRONLY);
		assert(fd > 0);
		for (int j = 0; j < 50; j++) {
			write(fd, test_str, len);
		}
		close(fd);
		assert_eq(unlink(fname), 0);
		assert(open(fname, O_RDONLY) < 0);
		printf("test iteration %d\n", i);
	}
	puts("Test mass open/unlink OK!");
	return 0;
}
