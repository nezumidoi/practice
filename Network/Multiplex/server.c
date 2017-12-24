#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>

#define SRV_PORT 9876
#define MAX_PORT_NUM 10
#define TIMEOUT 2

int running = 1;

int create_socket(int port)
{
	int sock;
	int ret;
	struct sockaddr_in srv_addr;

	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		fprintf(stderr, "socket() failed.\n");
		exit(1);
	}

	memset(&srv_addr, 0x00, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(port);

	ret = bind(sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		fprintf(stderr, "bind() failed.\n");
		exit(1);
	}

	ret = listen(sock, 5);
	if (ret < 0) {
		fprintf(stderr, "listen() failed.\n");
		exit(1);
	}

	return sock;
}

int main()
{
	int sockets[MAX_PORT_NUM];
	int ret;
	int port_number;
	int max_descripter = -1;
	unsigned int port_list[MAX_PORT_NUM] = {9000,9001,9002,9003,9004,9005,9006,9007,9008,9009};
	fd_set sock_set;
	struct timeval timeout;


	for (int i = 0; i < MAX_PORT_NUM; i++) {
		port_number	= port_list[i];

		sockets[i] = create_socket(port_number);

		if (sockets[i] > max_descripter) {
			max_descripter = sockets[i];
		}
	}

	while(running) {
		FD_ZERO(&sock_set);
		FD_SET(STDIN_FILENO, &sock_set);

		for (int i = 0; i < MAX_PORT_NUM; i++) {
			FD_SET(sockets[i], &sock_set);
		}

		timeout.tv_sec = TIMEOUT;
		timeout.tv_usec = 0;

		ret = select(max_descripter + 1, &sock_set, NULL, NULL, &timeout);
		if (ret == 0) {
			printf("timeout...\n");
		}
		else {
			if (FD_ISSET(STDIN_FILENO, &sock_set)) {
				printf("interupt.\n");
				getchar();
				running = 0;
			}

			for (int i = 0; i < MAX_PORT_NUM; i++) {
				if (FD_ISSET(sockets[i], &sock_set)) {
					printf("request on port %d\n", port_list[i]);
				}
			}
		}
	}

	for (int i = 0; i < MAX_PORT_NUM; i++) {
		close(sockets[i]);
	}
}
