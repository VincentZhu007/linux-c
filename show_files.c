/*
 * test opendir/readdir/closedir.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/4/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

int my_read(const char *path)
{
	DIR * dir;
	struct dirent * ptr;
	if ((dir = opendir(path)) == NULL) {
		perror("opendir");
		return -1;
	}
	while ((ptr = readdir(dir)) != NULL) {
		printf("file name: %s\n", ptr->d_name);
	}
	closedir(dir);

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "Usage: mycd <dirname>\n");
		exit(1);
	}

	if (my_read(argv[1]) == -1) {
		exit(1);
	}

	return 0;
}
