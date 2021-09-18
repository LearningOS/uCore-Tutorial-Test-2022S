#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_ARG_NUM (32)
#define MAX_STR_LEN (200)

const unsigned char LF = 0x0a;
const unsigned char CR = 0x0d;
const unsigned char DL = 0x7f;
const unsigned char BS = 0x08;

char line[MAX_STR_LEN];
char *argv[MAX_ARG_NUM];

int top = 0;

void push(char c)
{
	line[top++] = c;
}

void pop()
{
	--top;
}

int is_empty()
{
	return top == 0;
}

void clear()
{
	top = 0;
}

void get_argv()
{
	int argc = 0;
	char *s = line;
	for (;;) {
		while (*s == ' ') {
			*(s++) = 0;
		}
		if (*s) {
			argv[argc++] = s;
		} else {
			argv[argc] = NULL;
			return;
		}
		while (*s && *s != ' ')
			s++;
	}
}

void parse_argv()
{
	if (strncmp(line, "quit", sizeof("quit")) == 0) {
		exit(0);
	}
	get_argv();
}

int main()
{
	printf("C user shell\n");
	printf(">> ");
	fflush(stdout);
	while (1) {
		char c = getchar();
		switch (c) {
		case LF:
		case CR:
			printf("\n");
			if (!is_empty()) {
				push('\0');
				parse_argv();
				int pid = fork();
				if (pid == 0) {
					// child process
					if (exec(argv[0], argv) < 0) {
						printf("no such program: %s\n",
						       line);
						exit(0);
					}
					panic("unreachable!");
				} else {
					int xstate = 0;
					int exit_pid = 0;
					exit_pid = waitpid(pid, &xstate);
					assert_eq(pid, exit_pid);
					printf("Shell: Process %d exited with code %d\n",
					       pid, xstate);
				}
				clear();
			}
			printf(">> ");
			fflush(stdout);
			break;
		case BS:
		case DL:
			if (!is_empty()) {
				putchar(BS);
				printf(" ");
				putchar(BS);
				fflush(stdout);
				pop();
			}
			break;
		default:
			putchar(c);
			fflush(stdout);
			push(c);
			break;
		}
	}
	return 0;
}
