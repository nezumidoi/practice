#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
	char *multicastIP= "224.0.0.0";
	unsigned short multicastPort= 9999;
	char *sendString = "hello";
	int ret;
	int sock;
	struct sockaddr_in multicastAddr;
	int sendStringLen;
	unsigned char multicastTTL;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		fprintf(stderr, "socket failed.\n");
		exit(1);
	}

	ret = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&multicastTTL, sizeof(multicastTTL));
	if (ret < 0) {
		fprintf(stderr, "sockopt failed.\n");
		exit(1);
	}

	memset(&multicastAddr, 0x00, sizeof(multicastAddr));
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = inet_addr(multicastIP);
	multicastAddr.sin_port = htons(multicastPort);

	sendStringLen = strlen(sendString);

	for (;;) {
		ret = sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *)&multicastAddr, sizeof(multicastAddr));
		printf("send message: %s\n", sendString);
		if (ret != sendStringLen) {
			fprintf(stderr, "sendto failed.\n");
			exit(1);
		}

		sleep(3);
	}

	return 0;
}
