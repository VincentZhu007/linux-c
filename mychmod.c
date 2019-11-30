/*
 * my chmod
 *
 * Written by Vincnet Zhu in Nov. 2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	int mod;
	int i, mods[3];
	char *path;

	if (argc > 3) {
		printf("Usage: mychmod mod path\n");
		exit(1);
	}
	
	/* 提取各位数字 */
	mod = atoi(argv[1]);
	if (mod > 777 || mod < 0) {
		fprintf(stderr, "mod number exceeded range.\n");
		exit(1);
	}

	for (i=0; i<3; i++) {
		mods[i] = mod % 10;
		mod = mod / 10;
	}

	/* 转化为8进制 */
	mod = mods[2]*8*8 + mods[1]*8 + mods[0];
	path = argv[2];
	if (chmod(path, mod) == -1) {
		perror("chmod");
		exit(1);
	}

	return 0;
}




