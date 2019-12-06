/*
 * test fork.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/5/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	pid_t pid;

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	} else if (pid == 0) {
		printf("This is child %d whose parent is %d\n",
			getpid(), getppid());
	} else {
		printf("This is parent %d which forks child %d.\n",
			getpid(), pid);
	}

	return 0;
}
