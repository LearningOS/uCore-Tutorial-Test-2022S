#ifndef USER_TEST
#define USER_TEST

int run_tests(const char *tests[], int n)
{
	int success = 0;
	for (int i = 0; i < n; ++i) {
		const char *test = tests[i];
		printf("Usertests: Running %s\n", test);
		int pid = fork();
		if (pid == 0) {
			exec(test, NULL);
			exit(-1);
		}
		int xstate = 0;
		int wait_pid = waitpid(pid, &xstate);
		assert_eq(pid, wait_pid);
		success += (xstate == 0);
		printf("Usertests: Test %s in Process %d exited with code %d\n",
		       test, pid, xstate);
	}
	return success;
}

int test(const char *succs[], int nsucc, const char *fails[], int nfail,
	 const char *message)
{
	if (succs && nsucc > 0) {
		int succ_count = run_tests(succs, nsucc);
		assert_eq(succ_count, nsucc);
	}
	if (fails && nfail > 0) {
		int fail_count = run_tests(fails, nfail);
		assert_eq(fail_count, 0);
	}
	if (message)
		puts(message);
	return 0;
}

#endif // USER_TEST