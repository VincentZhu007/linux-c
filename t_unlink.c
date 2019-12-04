/*
 * test unlink.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/4/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

/*
 * 自定义错误处理
 */
#define my_err(msg,line) do {\
	fprintf(stderr, "[error line %d] ", line); \
	perror(msg);\
	exit(1);\
} while(0)

int main(int argc, char *argv[])
{
	int fd;
	char buf[32];

	if (argc != 2) {
		fprintf(stderr, "Usage: t_unlink <filename>\n");
		exit(1);
	}

	if ((fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) < 0) {
		my_err("open", __LINE__);
	}

	if (unlink(argv[1]) < 0) {
		my_err("unlink", __LINE__);
	}
	printf("file unlinked.\n");

	if (write(fd, "this is temp file.", 19) < 0) {
		my_err("write", __LINE__);
	}

	if (lseek(fd, 0, SEEK_SET) == -1) {
		my_err("lseek", __LINE__);
	}

	if (read(fd, buf, 19) < 0) {
		my_err("write", __LINE__);
	}
	printf("read from temp: %s\n", buf);

	return 0;
}
