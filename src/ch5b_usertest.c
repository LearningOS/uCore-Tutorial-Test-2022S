#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/// 辅助测例，运行所有其他测例。

char* TESTS[] = {
    "ch2b_hello_world\0", "ch2b_power\0",     "ch2b_write1\0",
    "ch3b_sleep\0",       "ch3b_sleep1\0",    "ch3b_yield0\0",
    "ch3b_yield1\0",      "ch3b_yield2\0",    "ch5b_forktest0\0",
    "ch5b_forktest1\0",   "ch5b_forktest2\0",
};

int main() {
    int num_test = sizeof(TESTS) / sizeof(char*);
    for (int i = 0; i < num_test; ++i) {
        char* test = TESTS[i];
        printf("Usertests: Running %s\n", test);
        int pid = fork();
        if (pid == 0) {
            exec(test, NULL);
            // unreachable()
        }
        int xstate = 0;
        int wait_pid = waitpid(pid, &xstate);
        assert(pid == wait_pid);
        printf("Usertests: Test %s in Process %d exited with code %d\n", test,
               pid, xstate);
    }
    puts("ch5 Usertests passed!");
    return 0;
}
