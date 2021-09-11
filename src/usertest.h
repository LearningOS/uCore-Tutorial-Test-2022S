#ifndef USER_TEST
#define USER_TEST

int run_tests(char *tests[], int n)
{
	int success = 0;
	for (int i = 0; i < n; ++i) {
		char *test = tests[i];
		printf("Usertests: Running %s\n", test);
		int pid = fork();
		if (pid == 0) {
			exec(test, NULL);
			exit(-1);
		}
		int xstate = 0;
		int wait_pid = waitpid(pid, &xstate);
		assert(pid == wait_pid);
		success += (xstate == 0);
		printf("Usertests: Test %s in Process %d exited with code %d\n",
		       test, pid, xstate);
	}
	return success;
}

#endif // USER_TEST