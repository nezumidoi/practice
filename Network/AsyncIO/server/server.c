#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <signal.h>

#define SRV_PORT 9876

int sock;

void handler(int sig)
{
	struct sockaddr_in cli_addr;
	int ret;
	unsigned int cli_len;

	cli_len = sizeof(cli_len);

	ret = recvfrom(sock, NULL, 0, 0, (struct sockaddr *)&cli_addr, &cli_len);
	if (ret < 0) {
		fprintf(stderr, "recvfrom() failed.\n");
		exit(5);
	}

	printf("reciving packet from: %s\n", inet_ntoa(cli_addr.sin_addr));
}

int main()
{
	struct sockaddr_in srv_addr;
	struct sigaction sa;

	int ret;

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

	/* setup handler */
	memset(&sa, 0x00, sizeof(sa));
	sa.sa_handler = handler;

	ret = sigfillset(&sa.sa_mask);
	if (ret < 0) {
		fprintf(stderr, "sigfillset() failed.\n");
		exit(1);
	}

	ret = sigaction(SIGIO, &sa, 0);
	if (ret < 0) {
		fprintf(stderr, "sigaction() failed.\n");
		exit(1);
	}

	ret = fcntl(sock, F_SETOWN, getpid());
	if (ret < 0) {
		fprintf(stderr, "fcntl() failed.\n");
		exit(1);
	}

	ret = fcntl(sock, F_SETFL, O_NONBLOCK | FASYNC);
	if (ret < 0) {
		fprintf(stderr, "fcntl() failed.\n");
		exit(1);
	}


	for (;;) {
		/* wait for reciving packet */
		sleep(5);
	}
}
