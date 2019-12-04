/*
 * print file infomation.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/4/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	struct stat buf;

	if (argc != 2) {
		fprintf(stderr, "Usage: getinfo <filename>\n");
		exit(0);
	}

	/* 获取文件属性 */
	if (stat(argv[1], &buf) == -1) {
		perror("stat");
		exit(1);
	}

	/* 打印文件信息 */
	printf("device is: %d\n", (int)buf.st_dev);
	printf("inode is: %d\n", (int)buf.st_ino);
	printf("mode is: %o\n", buf.st_mode);
	printf("number of hard links is: %d\n", buf.st_nlink);
	printf("user ID of owner is: %d\n", buf.st_uid);
	printf("group ID of owner is: %d\n", buf.st_gid);
	printf("device type (if inode device) is: %d\n", (int)buf.st_rdev);

	printf("total size, in bytes is: %d\n", (int)buf.st_size);
	printf("block size for filesystem I/O is: %d\n", (int)buf.st_blksize);
	printf("number of blocks allocated is: %d\n", (int)buf.st_blocks);
	
	printf("time of last access is: %s", ctime(&buf.st_atime));
	printf("time of last modification is: %s", ctime(&buf.st_mtime));
	printf("time of last change is: %s", ctime(&buf.st_ctime));

	return 0;
}
