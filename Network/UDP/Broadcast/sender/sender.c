#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char *broadcastIP = "255.255.255.255";
	unsigned short broadcastPort = 9999;
	char *sendString = "hello";
	int ret;
	int sock;
	int broadcastPermisson;
	struct sockaddr_in broadcastAddr;
	int sendStringLen;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		fprintf(stderr, "socket failed.\n");
		exit(1);
	}

	broadcastPermisson = 1;

	ret = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *)&broadcastPermisson, sizeof(broadcastPermisson));
	if (ret < 0) {
		fprintf(stderr, "sockopt failed.\n");
		exit(1);
	}

	memset(&broadcastAddr, 0x00, sizeof(broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);
	broadcastAddr.sin_port = htons(broadcastPort);

	sendStringLen = strlen(sendString);

	for (;;) {
		ret = sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *)&broadcastAddr, sizeof(broadcastAddr));
		printf("send message: %s\n", sendString);
		if (ret != sendStringLen) {
			fprintf(stderr, "sendto failed.\n");
			exit(1);
		}

		sleep(3);
	}

	return 0;
}
