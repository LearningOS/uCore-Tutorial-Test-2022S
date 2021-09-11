#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/// 测试文件基本读写，输出　Test file0 OK! 就算正确。

int main()
{
	int a = 0;
	int b = 1;
	assert(a == b);
	return 0;
}