#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SRV_ADDR "127.0.0.1"
#define SRV_PORT 9876

int main()
{
	int sock;
	struct sockaddr_in srv_addr;
	int ret;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		fprintf(stderr, "socket() failed.");
		exit(1);
	}

	memset(&srv_addr, 0x00, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr(SRV_ADDR);
	srv_addr.sin_port = htons(SRV_PORT);

	ret = sendto(sock, NULL, 0, 0, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		fprintf(stderr, "sendto() failed.");
		exit(1);
	}
	
	close(sock);

	return 0;
}
