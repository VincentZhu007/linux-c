/*
 * test write, read and lseek
 * 
 * written by Vincent Zhu in Nov. 2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024
/* 宏实现 */
#define MYERR(msg,line) do{\
	fprintf(stderr, "line %d\n", line);\
	perror(msg);\
	exit(1);\
}while(0)

/* 函数实现 */
void myerr(const char * msg, int line)
{
	fprintf(stderr, "line %d\n", line);
	perror(msg);
	exit(1);
}

/*
 * read from opening file
 */
void myread(int fd)
{
	int i, len;
	int count;
	char rd_buf[BUFFER_SIZE];

	if (lseek(fd, 0, SEEK_END) == -1) {
		MYERR("lseek", __LINE__);
	}
	
	if ((len = lseek(fd, 0, SEEK_CUR)) == -1) {
		MYERR("lseek", __LINE__);
	}

	if (lseek(fd, 0, SEEK_SET) == -1) {
		MYERR("lseek", __LINE__);
	}

	if ((count = read(fd, rd_buf, len)) == -1) {
		MYERR("read", __LINE__);
	}

	for (i=0; i<len; i++) {
		putchar(rd_buf[i]);
	}
	return;
}

int main(int argc, char *argv[])
{
	char *path;
	int fd;
	int count;
	char *wr_buf = "hello world\n";

	if (argc != 2) {
		fprintf(stderr, "Usage: mycreate filename\n");
		exit(1);
	}

	path = argv[1];
	
	if ((fd = open(path, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) == -1) {
		MYERR("open", __LINE__);
	}
	
	printf("write to %s.\n", path);
	if ((count = write(fd, wr_buf, strlen(wr_buf))) == -1) {
		MYERR("write", __LINE__);
	}

	/* 形成空洞 */
	if (lseek(fd, 10, SEEK_END) == -1) {
		MYERR("lseek", __LINE__);
	}

	if ((count = write(fd, wr_buf, strlen(wr_buf))) == -1) {
		MYERR("write", __LINE__);
	}

	printf("read from %s.\n", path);
	printf("---------------------------\n");
	myread(fd);
	printf("---------------------------\n");

	close(fd);
	return 0;
}

