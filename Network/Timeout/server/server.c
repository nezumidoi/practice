#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SRV_PORT 9876

int main()
{
	int sock;
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	int ret;
	unsigned int cli_addr_len;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		fprintf(stderr, "socket() failed.\n");
		exit(1);
	}

	memset(&srv_addr, 0x00, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(SRV_PORT);

	ret = bind(sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		fprintf(stderr, "bind() failed.\n");
		exit(1);
	}

	for (;;) {
		ret  = recvfrom(sock, NULL, 0, 0, (struct sockaddr *)&cli_addr, &cli_addr_len);
		if (ret < 0) {
			fprintf(stderr, "recvfrom() failed.\n");
			exit(1);
		}

		printf("recieved packet from %s\n", inet_ntoa(cli_addr.sin_addr));

		ret = sendto(sock, NULL, 0, 0, (struct sockaddr *)&cli_addr, sizeof(cli_addr));
		if (ret < 0) {
			fprintf(stderr, "failed sendto().\n");
			return -1;
		}
	}

	close(sock);
}
