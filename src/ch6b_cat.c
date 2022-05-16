#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char *filea = "filea\0";
	int fd = open(filea, O_RDONLY);
	if (fd < 0) {
		printf("Fail to open file %s\n", filea);
		return 0;
	}
	char buf[16];
	while (1) {
		int size = read(fd, buf, 16);
		if (size == 0)
			break;
		printf("%s", buf);
	}
	close(fd);
	return 0;
}
