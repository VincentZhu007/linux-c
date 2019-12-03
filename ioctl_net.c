/*
 * test ioctl on network.
 *
 * written by Vincent Zhu <VincentZhu007@gmail.com>
 * created on 12/3/2019.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if.h>

/*
 * print error message and line number
 */
#define my_err(msg,line) do {\
	fprintf(stderr, "line %d\n", line);\
	perror(msg);\
} while(0)

char		g_eth_name[16];
char		g_macaddr[6];
unsigned int	g_subnetmask;
unsigned int	g_ipaddr;
unsigned int	g_broadcast_ipaddr;

/* 初始化网络，获得当前网络设备的信息 */
void init_net(void)
{
	int i;
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1) {
		perror("socket");
	}
	strcpy(g_eth_name, "wlan0");
	strcpy(ifr.ifr_name, g_eth_name);
	printf("eth name: %s\n", g_eth_name);

	/* 获取并打印网卡地址 */
	if (ioctl(sock, SIOCGIFHWADDR, &ifr) < 0) {
		my_err("ioctl", __LINE__);
	}
	memcpy(g_macaddr, ifr.ifr_hwaddr.sa_data, 6);

	printf("local mac: ");
	for (i=0; i<5; i++) {
		printf("%.2x:", g_macaddr[i]);
	}
	printf("%.2x\n", g_macaddr[5]);

	/* 获取并打印IP地址 */
	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0) {
		my_err("ioctl", __LINE__);
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	g_ipaddr = sin.sin_addr.s_addr;
	printf("local eth0: %s\n", inet_ntoa(sin.sin_addr));

	/* 获取并打印广播地址 */
	if (ioctl(sock, SIOCGIFBRDADDR, &ifr) < 0) {
		my_err("ioctl", __LINE__);
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	g_broadcast_ipaddr = sin.sin_addr.s_addr;
	printf("broadcast: %s\n", inet_ntoa(sin.sin_addr));

	/* 获取并打印子网掩码 */
	if (ioctl(sock, SIOCGIFNETMASK, &ifr) < 0) {
		my_err("ioctl", __LINE__);
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	g_subnetmask = sin.sin_addr.s_addr;
	printf("subnetmask: %s\n", inet_ntoa(sin.sin_addr));

	close(sock);
}

int main(int argc, char *argv[])
{
	/* initialize... */
	init_net();

	/* do something */

	return 0;
}
