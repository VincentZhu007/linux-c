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
	int k=3;

	pid = fork();
	switch (pid) {
	case 0:
		while (k > 0) {
			printf("I am a child process, my pid is %d, "
			"my parent pid is %d.\n", getpid(), getppid());
			sleep(3);
			k--;
		}
		break;
	case -1:
		printf("Process creation failed.\n");
		exit(-1);
		break;
	default:
		printf("I am the parent process, my pid is %d, "
		       "my child pid is %d.\n", getpid(), pid);
		break;
	}

	return 0;
}
