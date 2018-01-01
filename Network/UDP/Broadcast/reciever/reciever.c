#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAXRECVSTRING 255

int main()
{
	int sock;
	int ret;
	unsigned short multicastPort = 9999;
	struct sockaddr_in multicastAddr;
	char recvString[MAXRECVSTRING + 1];

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		fprintf(stderr, "failed socket.\n");
		exit(1);
	}

	/* set multicast group */
	memset(&multicastAddr, 0x00, sizeof(multicastAddr));
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	multicastAddr.sin_port = htons(multicastPort);

	ret = bind(sock, (struct sockaddr *)&multicastAddr, sizeof(multicastAddr));
	if (ret < 0) {
		fprintf(stderr, "failed bind. errno is %d\n", errno);
		exit(1);
	}
	
	recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0);

	printf("%s\n", recvString);
	close(sock);
	
	return 0;
}
