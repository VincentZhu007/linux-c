/*
 * test getopt_long
 * written by Vincent Zhu in Nov. 2019.
 */

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

struct option options[] = {
	{"compile", no_argument, NULL, 'c'},
	{"debug", no_argument, NULL, 'g'},
	{"output", required_argument, NULL, 'o'}
};

void usage()
{
	fprintf(stdout,
		"Usage: tgetopt_long [options] argument\n"
		"  --compile|-f           compile\n"
		"  --debug|-g             debug\n"
		"  --output|-o file       specify output file\n");
}

int main(int argc, char *argv[])
{
	int c;
	int ind;
	while ((c = getopt_long(argc, argv, "cgo:",options, &ind)) != -1) {
		switch (c) {
		case 'c':
			fprintf(stdout, "option compile\n");
			break;
		case 'g':
			fprintf(stdout, "option debug\n");
			break;
		case 'o':
			fprintf(stdout, "option output:%s\n", optarg);
			break;
		case '?':
			usage();
			break;
		default:
			usage();
		}
	}
	for (ind = optind; ind < argc; ind++) {
		fprintf(stdout, "argument[%d] %s\n", ind-optind, argv[ind]);
	}		

	return 0;
}
