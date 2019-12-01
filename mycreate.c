/*
 * test create
 * 
 * written by Vincent Zhu in Nov. 2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char *path;
	int fd = -1;

	if (argc != 2) {
		fprintf(stderr, "Usage: mycreate filename\n");
		exit(1);
	}

	path = argv[1];
	
	//if ((fd == open(path, O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1) {
	if ((fd == creat(path, S_IRUSR | S_IWUSR)) == -1) {
		perror("open");
		exit(1);
	}

	printf("create file %s successfully.\n", path);

	close(fd);

	return 0;
}

