#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const unsigned char LF = 0x0a;
const unsigned char CR = 0x0d;
const unsigned char DL = 0x7f;
const unsigned char BS = 0x08;

char line[100] = {};

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

char* argv[100];
char data[100][100];
char name[100];
void get_argv() 
{
	for(int i=0;i<100;i++) 
		argv[i] = NULL;
	int argc = -1;
	int st_pos[100];
	for(int i = 0;i < top;i ++){
		if(line[i] == ' ' || line[i] == '\0') {
				st_pos[++argc] = i;
			if(argc != 0) {
				argv[argc - 1] = data[argc - 1];
				int j;
				for(j=st_pos[argc-1]+1;j!=st_pos[argc];j++){
					argv[argc-1][j - st_pos[argc-1] - 1] = line[j];
				}
				argv[argc-1][j - st_pos[argc-1] - 1] = '\0';
			} else {
				int j;
				for(j = 0;j < st_pos[argc];j ++){
					name[j] = line[j];
				}
				name[j] = '\0';
			}
		}
	}
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
				int pid = fork();
				if (pid == 0) {
					get_argv();
					// child process
					if (exec(name, argv) < 0) {
						printf("no such program: %s\n",
						       line);
						exit(0);
					}
					panic("unreachable!");
				} else {
					int xstate = 0;
					int exit_pid = 0;
					exit_pid = waitpid(pid, &xstate);
					assert(pid == exit_pid);
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
			if(c == 'q')
				panic("exit!");
			break;
		}
	}
	return 0;
}
