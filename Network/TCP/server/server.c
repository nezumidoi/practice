#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERV_PORT 9876

int main()
{
	int srv_sock;
	int cli_sock;
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;
	int ret;
	unsigned int len;

	srv_sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (srv_sock < 0) {
		printf("fail to create socket.\n");
		exit(1);
	}

	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(SERV_PORT);

	ret = bind(srv_sock, (struct sockaddr *)&srv_addr, sizeof(srv_addr));
	if (ret < 0) {
		printf("fail to bind.\n");
		exit(1);
	}

	ret = listen(srv_sock, 5);
	if (ret < 0) {
		printf("fail to listen socket.\n");
		exit(1);
	}

	for (;;) {
		len = sizeof(cli_addr);
		cli_sock = accept(srv_sock, (struct sockaddr *)&cli_addr, &len);
		if (cli_sock < 0) {
			printf("fail to accept.\n");
			exit(1);
		}

		printf("addr: %s\n", inet_ntoa(cli_addr.sin_addr));
	}





	return 0;
}
