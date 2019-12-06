/*
 * test fork for more details.
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
	char *msg;
	int k = 0;

	pid = fork();
	switch (pid) {
	case 0:
		msg = "Child process is running.";
		k = 3;
		break;
	case -1:
		printf("Process creation failed.");
		exit(-1);
		break;
	default:
		msg = "Parent process is running.";
		k = 5;
		break;
	}

	while (k > 0) {
		puts(msg);
		sleep(1);
		k--;
	}

	return 0;
}
