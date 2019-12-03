/*
 * test fcnt lock
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/3/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

/*
 * print error message and line number
 */
#define my_err(msg,line) do{\
	fprintf(stderr, "line %d\n", line);\
	perror(msg);\
	exit(1);\
}while(0)

/*
 * set or unset file lock
 */
int set_lock(int fd, struct flock *lock)
{
	if (fcntl(fd, F_SETLK, lock) == 0) { // 执行成功
		if (lock->l_type == F_RDLCK) {
			printf("set read lock, pid: %d\n", getpid());
			return 0;
		} else if (lock->l_type == F_WRLCK){
			printf("set write lock, pid: %d\n", getpid());
		} else if (lock->l_type == F_UNLCK){
			printf("release lock, pid: %d\n", getpid());
		}
	} else {
		perror("fcntl lock");
		return -1;
	}
	return 0;
}

/*
 * 测试锁，只有当测试发现参数lock指定的锁能被设置时，返回0.
 */
int test_lock(int fd, struct flock *lock)
{
	if (fcntl(fd, F_GETLK, lock) == 0) { // 执行成功
		if (lock->l_type == F_UNLCK) {
			printf("lock can be set in fd.\n");
			return 0;
		} else {
			if (lock->l_type == F_RDLCK) {
				printf("can't set lock, read lock has been set by:%d\n", lock->l_pid);
			} else if (lock->l_type == F_WRLCK) {
				printf("can't set lock, write lock has been set by:%d\n", lock->l_pid);
			}
			return -2;
		}
	} else {
		perror("get incompatible locks fail");
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	int fd;
	char * path;
	int ret;
	struct flock lock;
	char read_buf[32];

	if (argc != 2) {
		printf("Usage: fcntl_lock filename\n");
		exit(1);
	}

	path = argv[1];
	if ((fd = open(path, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR)) ==  -1)
		my_err("open", __LINE__);

	if (write(fd, "LINE READ", 10) != 10) {
		my_err("write", __LINE__);
	}

	/* 初始化lock结构 */
	memset(&lock, 0, sizeof(struct flock));
	lock.l_start = SEEK_SET;
	lock.l_whence = 0;
	lock.l_len = 0;

	/* 设置读锁 */
	lock.l_type = F_RDLCK;
	if (test_lock(fd, &lock) == 0) { // 测试是否可以设置锁
		lock.l_type = F_RDLCK;
		set_lock(fd, &lock);
	}

	/* 读数据 */
	lseek(fd, 0, SEEK_SET);
	if ((ret = read(fd, read_buf, 10)) < 0) {
		my_err("read", __LINE__);
	}
	read_buf[ret] = '\0';
	printf("%s\n", read_buf);

	/* 等待任意按钮 */
	getchar();

	/* 设置写锁 */
	lock.l_type = F_WRLCK;
	if (test_lock(fd, &lock) == 0) { // 测试可以设置锁
		lock.l_type = F_WRLCK;
		set_lock(fd, &lock);
	}

	/* 释放锁 */
	lock.l_type = F_UNLCK;
	set_lock(fd, &lock);
	close(fd);
	return 0;
}
