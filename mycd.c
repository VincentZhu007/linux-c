/*
 * test chdir.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/4/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

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
	char buf[PATH_MAX + 1];

	if (argc != 2) {
		fprintf(stderr, "Usage: mycd <dirname>\n");
		exit(1);
	}

	if (chdir(argv[1]) == -1) {
		my_err("chdir", __LINE__);
	}

	if (getcwd(buf, PATH_MAX + 1) == NULL) {
		my_err("getcwd", __LINE__);
	}
	printf("%s\n", buf);

	return 0;
}
