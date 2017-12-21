#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

#define LOOPBACK_ADDR "127.0.0.1"
#define SERV_PORT 9876
#define TIMEOUT_SECS 2
#define MAX_TRY_COUNT 10

static int try_count  = 0;

void handler(int sig)
{
	try_count++;
}

int main()
{
	int sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in from_addr;
	struct sigaction sa;
	int ret;
	unsigned int from_len;
	int err;

	sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock < 0) {
		fprintf(stderr, "failed socket().\n");
		return -1;
	}

	memset(&sa, 0x00, sizeof(sa));
	sa.sa_handler = handler;
	ret = sigaction(SIGALRM, &sa, 0);
	if (ret < 0) {
		fprintf(stderr, "failed sigaction().\n");
		return -1;
	}

	memset(&serv_addr, 0x00, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(LOOPBACK_ADDR);
	serv_addr.sin_port = htons(SERV_PORT);

	ret = sendto(sock, NULL, 0, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (ret < 0) {
		fprintf(stderr, "failed sendto().\n");
		return -1;
	}

	alarm(TIMEOUT_SECS);
	from_len = sizeof(from_addr);	
	
	/* wait to response */
	while (recvfrom(sock, NULL, 0, 0, (struct sockaddr *)&from_addr, &from_len)) {
		err = errno;

		if (try_count > MAX_TRY_COUNT) {
			printf("nothing response.\n");
			break;
		}

		if (err == EINTR) {
			printf("time out... %d times.\n", try_count);

			ret = sendto(sock, NULL, 0, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
			if (ret < 0) {
				fprintf(stderr, "failed sendto().\n");
			}

			alarm(TIMEOUT_SECS);
		}
		else {
			fprintf(stderr, "failed recvfrom().\n");
			return -1;
		}
	}

	alarm(0);

	close(sock);

	return 0;
}
