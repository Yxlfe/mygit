#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

#define PORT   8000
#define SIZE   1000

struct info
{
	int ToFd;
	char buf[32];
};
typedef struct info Info;

void *ClientHandler(void *arg)
{
	int ret;
	Info RecvBuf;
	int fd = *(int *)arg;

	pthread_detach(pthread_self());

	while (1)
	{
		ret = recv(fd, &RecvBuf, sizeof(RecvBuf), 0);
		if (-1 == ret)
		{
			perror("recv");
			exit(1);
		}

		if (!strcmp(RecvBuf.buf, "bye"))
		{
			close(fd);
			break;
		}
		
		ret = send(RecvBuf.ToFd, &RecvBuf, sizeof(RecvBuf), 0);
		if (-1 == ret)
		{
			perror("send");
		}

		memset(&RecvBuf, 0, sizeof(RecvBuf));
	}
	return NULL;
}

int main()
{
	int sockfd;
	int ret, fd[SIZE], i = 0;
	pthread_t tid;
	struct sockaddr_in server_addr;   //用于保存服务器信息
	struct sockaddr_in client_addr;   //用于保存客户端信息

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
		exit(1);
	}

	//设置socket属性，地址可以被重复绑定
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	//保存服务器信息
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0)
	{
		perror("bind");
		exit(1);
	}

	ret = listen(sockfd, 5);
	if (ret < 0)
	{
		perror("listen");
		exit(1);
	}

	int length = sizeof(client_addr);

	while (1)
	{
		printf("waitting for connect...\n");

		fd[i] = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t *)&length);  //接受连接
		if (-1 == fd[i])
		{
			perror("accept");
			exit(1);
		}
		printf("client connect success port : %d fd : %d\n", client_addr.sin_port, fd[i]);

		ret = pthread_create(&tid, NULL, ClientHandler, &fd[i]);
		if (ret != 0)
		{
			perror("pthread_create");
		}
		i++;
	}

	close(sockfd);

	return 0;
}
