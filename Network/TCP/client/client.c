#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SERV_ADDR "127.0.0.1"
#define SERV_PORT 9876

int main()
{
	int sock;
	struct sockaddr_in addr;
	int ret;
	char *message = "hello, TCP";

	/* create TCP socket */
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) {
		printf("fail to create socket.\n");
		exit(1);
	}

	/* struct address structure */
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(SERV_ADDR);
	addr.sin_port = htons(SERV_PORT);
	
	/* connect to server */
	ret = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	if (ret < 0) {
		printf("can't connect to the server.\n");
		exit(1);
	}


	/* send message */
	ret = send(sock, message, sizeof(message), 0);
	if (ret != strlen(message)) {
		printf("lost message.\n");
	}

	close(sock);

	return 0;
}
