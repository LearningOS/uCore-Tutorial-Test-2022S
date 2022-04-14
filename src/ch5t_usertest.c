#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const char *TESTS[] = {
	"ch5t_stride0\0",	  "ch5t_stride1\0",   "ch5t_stride2\0",
    "ch5t_stride3\0",	  "ch5t_stride4\0",   "ch5t_stride5\0",
};

int pid[] = {0, 0, 0, 0, 0, 0};

int main()
{
    for(int i = 0; i < 6; i++) {
        pid[i] = spawn(TESTS[i]);
    }
    set_priority(4);
    int exit_pid = 0;
    for(int i = 0; i < 6; i++) {
        int wait_pid = waitpid(pid[i], &exit_pid);
        assert_eq(wait_pid, pid[i]);
    }
    puts("ch5t usertest passed!");
    return 0;
}
