/*
 * test umask.
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
#include <string.h>

int main(int argc, char *argv[])
{
	/* 创建文件 */
	umask(0);	/* 不屏蔽任何权限设置 */
	if (creat("a1.txt", S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
		perror("creat");
		exit(1);
	}

	umask(S_IRWXO);	/* 屏蔽其它用户的权限 */
	if (creat("a2.txt", S_IRWXU | S_IRWXG | S_IRWXO) < 0) {
		perror("creat");
		exit(1);
	}

	return 0;
}
