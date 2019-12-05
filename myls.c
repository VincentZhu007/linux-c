/*
 * Implement my own ls, it supports -a and -l option.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/4/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <linux/limits.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


static int opt_all = 0;	 /* 显示所有文件，包括隐藏文件,.和.. */
static int opt_list = 0; /* 显示列表 */

int list_single(const char *path)
{
	struct stat buf;
	char ls_buf[PATH_MAX+20];
	char tmp [32];
	int i;
	int mask = 0400, ind=1;
	char table[3] = {'x', 'w', 'r'};
	char mon[][4] = {"Jan", "Feb", "Mar", "May", "Apr", "Jun",
			 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	struct tm *tptr;

	/* 默认:不显示隐藏文件 */
	if (opt_all == 0 && *path == '.') {
		return 0;
	}

	memset(ls_buf, 0, sizeof(ls_buf));
	/* 使用长列表形式显示文件信息 */
	if (opt_list == 1) {
		memset(&buf, 0, sizeof(struct stat));
		if (stat(path, &buf) == -1) {
			perror("stat");
			return -1;
		}

		/* 获取文件类型 */
		switch (buf.st_mode & S_IFMT) {
		case S_IFREG:  ls_buf[0] = '-'; break; 
		case S_IFDIR:  ls_buf[0] = 'd'; break;
		case S_IFCHR:  ls_buf[0] = 'c'; break;
		case S_IFBLK:  ls_buf[0] = 'b'; break;
		case S_IFIFO:  ls_buf[0] = 'p'; break;
		case S_IFLNK:  ls_buf[0] = 'l'; break;
		case S_IFSOCK: ls_buf[0] = 's'; break;
		default:       ls_buf[0] = '?'; break;
		}

		/* 文件访问权限 */
		for (i=8; i>=0; i--) {
			if (buf.st_mode & mask) {
				ls_buf[ind++] = table[i%3];
			} else {
				ls_buf[ind++] = '-';
			}
		}
		ls_buf[ind++] = '.';
		ls_buf[ind++] = ' ';

		/* 文件硬链接数目 */
		sprintf(tmp, "%2d ", (int)buf.st_nlink);
		strcat(ls_buf, tmp);
	
		/* 获取用户名和组名称 */
		struct passwd *pwd;
		if ((pwd = getpwuid(buf.st_uid)) == NULL) {
			perror("getpwuid");
			return -1;
		}
		strcat(ls_buf, pwd->pw_name);
		strcat(ls_buf, " ");

		struct group *grp;
		if ((grp = getgrgid(buf.st_gid)) == NULL) {
			perror("getgrgid");
			return -1;
		}
		strcat(ls_buf, grp->gr_name);
		strcat(ls_buf, " ");

		/* 文件大小 */
		sprintf(tmp, "%4d ", (int)buf.st_size);
		strcat(ls_buf, tmp);
		
		/* 修改时间mtime */
		tptr = localtime(&buf.st_mtime);
		strcat(ls_buf, mon[tptr->tm_mon]);
		sprintf(tmp, " %2d %02d:%02d ", tptr->tm_mday, tptr->tm_hour, tptr->tm_min);
		strcat(ls_buf, tmp);
	}
	/* 文件名 */
	strcat(ls_buf, path);

	printf("%s\n", ls_buf);
	return 0;
}

int list_dir(const char *path)
{
	DIR *dir;
	struct dirent *ptr;

	if ((dir = opendir(path)) == NULL) {
		perror("opendir");
		return -1;
	}

	/* 进入到path目录 */
	if (chdir(path) == -1) {
		perror("chdir");
		return -1;
	}

	while ((ptr = readdir(dir)) != NULL) {
		list_single(ptr->d_name);
	}

	closedir(dir);
	return 0;
}

void usage()
{
	printf("Usage: ls <path>\n"
	       "  -a   show all files\n"
	       "  -l   long list format\n");
}

int main(int argc, char *argv[])
{
	int c;
	int i;

	while((c = getopt(argc, argv, "al")) != -1) {
		switch(c) {
		case 'a':
			opt_all = 1;
			break;
		case 'l':
			opt_list = 1;
			break;
		case '?':
			usage();
			break;
		default:
			usage();
			break;
		}
	}

	if (optind >= argc) { /* 没有指定参数，默认显当前路径 */
		list_dir(".");
		return 0;
	}

	if (optind == argc - 1) {/* 只有一个路径 */
		list_dir(argv[optind]);
	} else {
		for (i = optind; i < argc-1; i++) {
			printf("%s:", argv[i]);
			list_dir(argv[i]);
			printf("\n");
		}
		printf("%s:", argv[i]);
		list_dir(argv[i]);
	}

	return 0;
}
