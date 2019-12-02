/*
 * test fcnt access
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/2/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * print error message and line number
 */
#define my_err(msg,line) do{\
	fprintf(stderr, "line %d\n", line);\
	perror(msg);\
	exit(1);\
}while(0)

int main(int argc, char *argv[])
{
	int fd;
	char * path;
	int ret, access;

	if (argc != 2) {
		printf("Usage: fcntl_access filename\n");
		exit(1);
	}

	path = argv[1];
	if ((fd = creat(path, S_IRUSR | S_IWUSR)) ==  -1)
	//if ((fd = open(path, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) ==  -1)
		my_err("open", __LINE__);


	/* 设置文件打开方式 */
	if ((ret = fcntl(fd, F_SETFL, O_APPEND)) < 0)
		my_err("fcntl", __LINE__);

	/* 获取文件打开方式 */
	if ((ret = fcntl(fd, F_GETFL, 0)) == -1)
		my_err("fcntl", __LINE__);
	
	access = ret & O_ACCMODE;
	if (access == O_RDONLY)
		printf("%s access mode: read only", path);
	else if (access == O_WRONLY)
		printf("%s access mode: write only", path);
	else if (access == O_RDWR)
		printf("%s access mode: read and write", path);

	if (ret & O_APPEND)
		printf(", append");
	if (ret & O_NONBLOCK)
		printf(", nonblock");
	if (ret & O_SYNC)
		printf(", sync");
	printf("\n");
	
	close(fd);
	return 0;
}

