#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char DATA_STRING[] = "string from data section\n";

/// 正确输出：
/// string from data section
/// strinstring from stack section
/// strin
/// Test write1 OK!

int main()
{
	int str_len = strlen(DATA_STRING);
	assert_eq(write(1234, DATA_STRING, str_len), -1);
	assert_eq(write(stdout, DATA_STRING, str_len), str_len);
	assert_eq(write(stdout, DATA_STRING, 5), 5);
	char *stack_string = "string from stack section\n";
	str_len = strlen(stack_string);
	assert_eq(write(stdout, stack_string, str_len), str_len);
	assert_eq(write(stdout, stack_string, 5), 5);
	puts("\nTest write1 OK!");
	return 0;
}
