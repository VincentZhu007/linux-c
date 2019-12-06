/*
 * test fork, another form.
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
	switch (pid) {
	case 0:
		printf("Child process is running, CurPid is %d, "
		       "ParentPid is %d.\n", pid, getppid());
		break;
	case -1:
		printf("Process creation failed.\n");
		exit(-1);
		break;
	default:
		printf("Parent process is running, ChildPid is %d, "
		       "ParentPid is %d.\n", pid, getpid());
		break;
	
	}

	return 0;
}
