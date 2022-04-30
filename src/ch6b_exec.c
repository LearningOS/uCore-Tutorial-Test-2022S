#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char *_argv[] = {
		"(*o*)", "(>.<)", "(O.O)", "(QwQ)", "orz", "没有了呀"
	};
	exec("ch6b_args", _argv);
	return 0;
}