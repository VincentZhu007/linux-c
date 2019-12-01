/*
 * test read
 * 
 * written by Vincent Zhu in Nov. 2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char *path;
	int fd = -1;
	int count = 0;
	int i, sum = 0;
	char buf[BUFFER_SIZE];

	if (argc != 2) {
		fprintf(stderr, "Usage: mycreate filename\n");
		exit(1);
	}

	path = argv[1];
	
	if ((fd = open(path, O_RDONLY)) == -1) {
		perror("open");
		exit(1);
	}
	
	printf("read from %s:\n", path);
	printf("---------------------------\n");
	do {
		count = read(fd, buf, BUFFER_SIZE);
		sum += count;
		for (i=0; i<count; i++)
			putchar(buf[i]);	
	} while (count > 0);	
	printf("---------------------------\n");
	printf("read char sum: %d\n", sum);


	close(fd);
	return 0;
}

