#include "Server.h"

int main()
{
	system("clear");
	signal(SIGINT,Stopserver);
	
	int ret;
	
	Sqlite3_admin();
	ret = List_init();

	if(ret == FAILURE)
	{
		printf("List_init Failure!\n");
	}
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
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.121");
	ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (ret < 0)
	{
		perror("bind");
		exit(1);
	}

	ret = listen(sockfd, 10);
	if (ret < 0)
	{
		perror("listen");
		exit(1);
	}
	
	//在内核中创建事件表
    epfd = epoll_create(EPOLL_SIZE);

    if(epfd < 0) 
	{ 
		perror("epfd error"); 
		exit(-1);
	}

    printf("epoll created, epollfd = %d\n", epfd);



    //往内核事件表里添加事件
	addfd(epfd, sockfd);
	printf("Add server = %d to epoll\n",sockfd);
	Serveraccept();
	return 0;
}
