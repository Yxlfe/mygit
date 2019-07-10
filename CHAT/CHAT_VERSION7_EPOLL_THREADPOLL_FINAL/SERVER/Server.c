#include "Server.h"

/*
作者:周超
日期:2018.9.18
描述:退出服务器
参数:代表kill信号的整数
返回值:无
*/
void Stopserver(int num)
{
	INFO Info;
	int ret;
	CLIENT *q = List;
	
	while(q->next != NULL)
	{
		q = q->next;
		Info.Flag = ServerClose;
		ret = send(q->fromsockfd,&Info,sizeof(Info),0);
		if(ret < 0)
		{
			perror("Send");
		}
	}
	
	system("clear");
	printf("\n\n\n\n");
	printf("\t\t\tServer has been closed!\n");
	sleep(2);
    threadpool_destroy(&pool);
	close(sockfd);
	close(epfd);
	exit(1);
}

/*
作者:周超
日期:2018.9.18
描述:数据库输入一个管理员帐户、密码和ID
参数:无
返回值:整型(成功或失败)
*/
int Sqlite3_admin()
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret;
	char sql[128] = {0};
	INFO Admin;
	strcpy(Admin.account,"1012786567");
	strcpy(Admin.password,"ZCYxlfezsy132051");
	strcpy(Admin.ID,"Admin");

	ret = sqlite3_open("client.db", &ppdb);
	if(ret != SQLITE_OK)
	{
		perror("sqlite_open");
		return FAILURE;
	}

	sprintf(sql, "create table if not exists client (account text, password text, ID text);");
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_exec error 1: %s\n", sqlite3_errmsg(ppdb));
		return FAILURE;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from client where account = '%s'and password = '%s';",Admin.account, Admin.password);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(row == 0)
	{
		memset(sql, 0, sizeof(sql));
		sprintf(sql, "insert into client (account, password, ID) values ('%s','%s','%s');", Admin.account, Admin.password, Admin.ID);
		ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
		if(ret != SQLITE_OK)
		{
			printf("sqlite3_exec error 2: %s\n", sqlite3_errmsg(ppdb));
			return FAILURE;
		}
	}

	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:初始化在线链表
参数:无
返回值:整型(成功或失败)
*/
int List_init()
{
	List = (CLIENT *) malloc(sizeof(CLIENT));
	if(NULL == List)
	{
		return FAILURE;
	}
	List->next = NULL;
	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:查询是否有人在线
参数:无
返回值:整型(有或没有)
*/
int Server_mgc()
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	int length = 0;
	CLIENT *q = List->next;
	while(q)
	{
		length++;
		q = q->next;
	}

	if(length == 1)
	{
		return FAILURE;
	}
	else
	{
		return SUCCESS;
	}
}

/*
作者:周超
日期:2018.9.18
描述:把登录的帐户信息插入在线链表
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int List_insert(INFO Insert, int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	CLIENT *p = (CLIENT *)malloc(sizeof(CLIENT) * 1);
	if(NULL == p)
	{
		return FAILURE;
	}
	if(!strcmp(Insert.account,"1012786567"))
	{
		strcpy(p->Info.account, Insert.account);
		strcpy(p->Info.ID, Insert.ID);
		p->fromsockfd = fd;
		p->Con.ChatCon = 1;
		p->Con.LoginCon = 1;
		p->Con.VIPCon = 1;
	}
	else
	{
		strcpy(p->Info.account, Insert.account);
		strcpy(p->Info.ID, Insert.ID);
		p->fromsockfd = fd;
		p->Con.ChatCon = 1;
		p->Con.LoginCon = 1;
		p->Con.VIPCon = 0;
	}

	CLIENT *q = List;
	while(q->next != NULL)
	{
		q = q->next;
	}
	q->next = p;
	p->next = NULL;
	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:查询指定的帐户是否在线
参数:结构体(存放信息)
返回值:整型(是或否)
*/
int List_travellogin(INFO Travel)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	CLIENT *q = List;
	while(q->next != NULL)
	{
		q = q->next;
		if(!strcmp(q->Info.account,Travel.account))
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:群聊功能
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_gc(INFO Info, int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	int tosockfd,ret;
	char TOID[128] = {0};
	CLIENT *p = List;
	CLIENT *q = List;
	
	fd3 = open("ChatMessage.txt",O_WRONLY);
	if(fd3 == -1)
	{
		perror("open");
	}

	ret = lseek(fd3,0,SEEK_END);				
	if(ret == -1)
	{
		perror("lseek");
	}

	while(p->next != NULL)
	{
		p = p->next;
		if(fd == p->fromsockfd)
		{
			strcpy(Info.ID,p->Info.ID);
			break;
		}
	}

	while(q->next != NULL)
	{
		q = q->next;
		if(fd != q->fromsockfd)
		{
			strcpy(TOID, q->Info.ID);
			tosockfd = q->fromsockfd;
			Info.Flag = GcSuccess;
			send(tosockfd,&Info,sizeof(Info),0);
			
			ret = write(fd3,&Info.time,strlen(Info.time));
			if(ret == -1)
			{
				perror("write");
			}
																
			ret = write(fd3,Info.ID,strlen(Info.ID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3," (group) send to ",17);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3,&TOID,strlen(TOID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3," : ",3);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3,Info.text,strlen(Info.text));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3,"\n",1);
			if(ret == -1)
			{
				perror("write");
			}
		}
	}

	close(fd3);
	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:私聊功能
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_pc(INFO Info,int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}

	INFO REACTION_INFO;
	int tosockfd,ret;
	char TempID[128] = {0};
	char TOID[128] = {0};
	strcpy(TOID, Info.ID);
	CLIENT *p = List;
	CLIENT *q = List;
	
	fd3 = open("ChatMessage.txt",O_WRONLY);
	if(fd3 == -1)
	{
		perror("open");
	}

	ret = lseek(fd3,0,SEEK_END);				
	if(ret == -1)
	{
		perror("lseek");
	}
	
	while(p->next != NULL)
	{
		p = p->next;
		if(fd == p->fromsockfd)
		{
			strcpy(TempID,p->Info.ID);
			break;
		}
	}

	while(q->next != NULL)
	{
		q = q->next;
		if(!strcmp(q->Info.ID,Info.ID))
		{
			Info.Flag = PcSuccess;
			tosockfd = q->fromsockfd;
			strcpy(Info.ID,TempID);
			send(tosockfd,&Info,sizeof(Info),0);
			REACTION_INFO.Flag = OtherLogin;
			send(fd,&REACTION_INFO,sizeof(REACTION_INFO),0);
			
			ret = write(fd3,&Info.time,strlen(Info.time));
			if(ret == -1)
			{
				perror("write");
			}
																
			ret = write(fd3,Info.ID,strlen(Info.ID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3," send to ",9);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3,&TOID,strlen(TOID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3," : ",3);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3,Info.text,strlen(Info.text));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd3,"\n",1);
			if(ret == -1)
			{
				perror("write");
			}

			close(fd3);
			return SUCCESS;
		}
	}

	Info.Flag = OtherLogoff;
	send(fd,&Info,sizeof(Info),0);
	close(fd3);
	return FAILURE;
}

/*
作者:周超
日期:2018.9.18
描述:下线功能
参数:代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_logoffself(int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	int tosockfd;
	CLIENT *q = List;
	CLIENT *p = List;

	close(fd);

	while(q->next != NULL)
	{
		p = q;
		q = q->next;
		if(q->fromsockfd == fd)
		{
			p->next = q->next;
			free(q);
			return SUCCESS;
		}
	}

	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:将指定用户踢出聊天室(强制下线)
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_logoffother(INFO Info,int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	int tosockfd;
	CLIENT *q = List;
	CLIENT *p = List;

	while(q->next != NULL)
	{
		p = q;
		q = q->next;
		if(!strcmp(q->Info.ID,Info.ID))
		{
			tosockfd = q->fromsockfd;
			Info.Flag = LogoffOther;
			send(tosockfd,&Info,sizeof(Info),0);
			Info.Flag = LogoffOtherSuccess;
			send(fd,&Info,sizeof(Info),0);
			p->next = q->next;
			free(q);
			return SUCCESS;
		}
	}

	Info.Flag = OtherLogoff;
	send(fd,&Info,sizeof(Info),0);
	return FAILURE;

}

/*
作者:周超
日期:2018.9.18
描述:禁言功能
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_forbidden(INFO Info,int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	CLIENT *q = List;

	while(q->next != NULL)
	{
		q = q->next;
		if(!strcmp(q->Info.ID,Info.ID))
		{
			q->Con.ChatCon = 0;
			Info.Flag = ForbidSuccess;
			send(fd,&Info,sizeof(Info),0);
			return SUCCESS;
		}
	}

	Info.Flag = OtherLogoff;
	send(fd,&Info,sizeof(Info),0);
	return FAILURE;

}

/*
作者:周超
日期:2019.3.15
描述:解禁功能
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_cancel_forbidden(INFO Info,int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	CLIENT *q = List;

	while(q->next != NULL)
	{
		q = q->next;
		if(!strcmp(q->Info.ID,Info.ID))
		{
			q->Con.ChatCon = 1;
			Info.Flag = CancelForbidSuccess;
			send(fd,&Info,sizeof(Info),0);
			return SUCCESS;
		}
	}

	Info.Flag = OtherLogoff;
	send(fd,&Info,sizeof(Info),0);
	return FAILURE;

}

/*
作者:周超
日期:2018.9.18
描述:发送文件名
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_sendfilename(INFO Info, int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}

	INFO REACTION_INFO;
	int tosockfd;
	CLIENT *q = List;
	
	while(q->next != NULL)
	{
		q = q->next;
		if(!strcmp(q->Info.ID,Info.ID))
		{
			tosockfd = q->fromsockfd;
			Info.Flag = RecvFileName;
			send(tosockfd,&Info,sizeof(Info),0);
			REACTION_INFO.Flag = OtherLogin;
			send(fd,&REACTION_INFO,sizeof(REACTION_INFO),0);
			return SUCCESS;
		}
	}
	
	Info.Flag = OtherLogoff;
	send(fd,&Info,sizeof(Info),0);
	return FAILURE;

}

/*
作者:周超
日期:2018.9.18
描述:发送文件内容
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_file(INFO Info, int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	int tosockfd;
	char TempID[128] = {0};
	CLIENT *p = List;
	CLIENT *q = List;
	
	while(p->next != NULL)
	{
		p = p->next;
		if(fd == p->fromsockfd)
		{
			strcpy(TempID,p->Info.ID);
			break;
		}
	}

	while(q->next != NULL)
	{
		q = q->next;
		if(!strcmp(q->Info.ID,Info.ID))
		{
			tosockfd = q->fromsockfd;
			strcpy(Info.ID,TempID);
			Info.Flag = RecvFile;
			send(tosockfd,&Info,sizeof(Info),0);
			Info.Flag = FileTransfer;
			send(fd,&Info,sizeof(Info),0);
			return SUCCESS;
		}
	}

	Info.Flag = OtherLogoff;
	send(fd,&Info,sizeof(Info),0);
	return FAILURE;
}

/*
作者:周超
日期:2018.9.18
描述:识别指定用户是不是管理员用户
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(是或不是)
*/
int Server_mVIP(INFO Info,int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	CLIENT *q = List;
	while(q->next != NULL)
	{
		q = q->next;
		if(q->fromsockfd == fd && q->Con.VIPCon == 1)
		{
			Info.Flag = VIP;
			send(fd,&Info,sizeof(Info),0);
			return SUCCESS;
		}
	}

	Info.Flag = NVIP;
	send(fd,&Info,sizeof(Info),0);
	
	return FAILURE;
}

/*
作者:周超
日期:2018.9.18
描述:识别指定用户是否被禁言
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_mchat(INFO Info,int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	
	CLIENT *q = List;
	while(q->next != NULL)
	{
		q = q->next;
		if(q->fromsockfd == fd && q->Con.ChatCon == 1)
		{
			Info.Flag = CanChat;
			send(fd,&Info,sizeof(Info),0);
			return SUCCESS;
		}
	}
	Info.Flag = NotCanChat;
	send(fd,&Info,sizeof(Info),0);
	return FAILURE;
}

/*
作者:周超
日期:2018.9.18
描述:查询所有在线用户的帐号和ID
参数:代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_traverse(int fd)
{
	if(NULL == List)
	{
		return FAILURE;
	}
	CLIENT *q = List;
	while(q->next != NULL)
	{
		q = q->next;
		if(q->Con.LoginCon == 1)
		{
			q->Info.Flag = Traverse;
			send(fd,&q->Info,sizeof(q->Info),0);
		}
	}

	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:修改密码功能(查询数据库中的信息)
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_changepassword(INFO Info, int fd)
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret;
	char sql[128] = {0};

	ret = sqlite3_open("client.db", &ppdb);
	if(ret != SQLITE_OK)
	{
		perror("sqlite_open");
		return FAILURE;
	}

	sprintf(sql, "create table if not exists client (account text, password text, ID text);");
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_exec error 1: %s\n", sqlite3_errmsg(ppdb));
		return FAILURE;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from client where account = '%s';",Info.account);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(row == 0)
	{
		strcpy(Info.text,"Account has not been registed!");
		send(fd,&Info,sizeof(Info),0);
		sqlite3_free_table(result);
		return FAILURE;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from client where account = '%s' and password = '%s';",Info.account,Info.oldpassword);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(row == 0)
	{
		strcpy(Info.text,"Old password is wrong!");
		send(fd,&Info,sizeof(Info),0);
		sqlite3_free_table(result);
		sqlite3_close(ppdb);
		return FAILURE;
	}

	sqlite3_free_table(result);

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "update client set password = '%s' where account = '%s';", Info.password, Info.account);
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_exec error 2: %s\n", sqlite3_errmsg(ppdb));
		return FAILURE;
	}
	strcpy(Info.text,"Change password Success!");
	send(fd,&Info,sizeof(Info),0);
	sqlite3_close(ppdb);
	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:登录功能(查询数据库中的信息)
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_login(INFO Info, int fd)
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret,i,j;
	char sql[128] = {0};

	ret = sqlite3_open("client.db", &ppdb);
	if(ret != SQLITE_OK)
	{
		perror("sqlite_open");
		return FAILURE;
	}

	sprintf(sql, "create table if not exists client (account text, password text, ID text);");
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_exec error 3:%s\n", sqlite3_errmsg(ppdb));
		return FAILURE;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from client where account = '%s'and password = '%s';",Info.account, Info.password);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(row == 1)
	{
		strcpy(Info.ID,result[row + column + 1]);
		ret = List_travellogin(Info);
		if(ret == SUCCESS)
		{
			ret = List_insert(Info,fd);
			if(ret == FAILURE)
			{
				printf("List_insert Failure!\n");
			}
			else
			{
				Info.Flag = LoginSuccess;
				strcpy(Info.text,"Login Success!");
				send(fd,&Info,sizeof(Info),0);
				sqlite3_free_table(result);
				sqlite3_close(ppdb);
				return SUCCESS;
			}
		}
		else
		{
			Info.Flag = LoginFailure;
			strcpy(Info.text,"Login Faliure!(Account has been Login)");
			send(fd,&Info,sizeof(Info),0);
			sqlite3_free_table(result);
			sqlite3_close(ppdb);
			return FAILURE;
		}
	}
	Info.Flag = LoginFailure;
	strcpy(Info.text,"Login Faliure!(Account has not been Registed)");
	send(fd,&Info,sizeof(Info),0);
	sqlite3_free_table(result);
	sqlite3_close(ppdb);
	return FAILURE;
}

/*
作者:周超
日期:2018.9.18
描述:注册功能(查询数据库中的信息)
参数:结构体(存放信息)、代表服务器接收客户端发送消息通道的套接字
返回值:整型(成功或失败)
*/
int Server_register(INFO Info, int fd)
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret;
	char sql[128] = {0};

	ret = sqlite3_open("client.db", &ppdb);
	if(ret != SQLITE_OK)
	{
		perror("sqlite_open");
		return FAILURE;
	}

	sprintf(sql, "create table if not exists client (account text, password text, ID text);");
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_exec error 1: %s\n", sqlite3_errmsg(ppdb));
		return FAILURE;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from client where account = '%s';",Info.account);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(row != 0)
	{
		strcpy(Info.text,"Account has been registed!");
		send(fd,&Info,sizeof(Info),0);
		sqlite3_free_table(result);
		return FAILURE;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from client where ID = '%s';",Info.ID);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(row != 0)
	{
		strcpy(Info.text,"ID has been registed!");
		send(fd,&Info,sizeof(Info),0);
		sqlite3_free_table(result);
		sqlite3_close(ppdb);
		return FAILURE;
	}

	sqlite3_free_table(result);

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "insert into client (account, password, ID) values ('%s','%s','%s');", Info.account, Info.password, Info.ID);
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		printf("sqlite3_exec error 2: %s\n", sqlite3_errmsg(ppdb));
		return FAILURE;
	}
	strcpy(Info.text,"Register Success!");
	send(fd,&Info,sizeof(Info),0);
	sqlite3_close(ppdb);
	return SUCCESS;
}

/*
作者:周超
日期:2018.9.18
描述:接收客户端发送的信息
参数:代表服务器接收客户端发送消息通道的套接字
返回值:无
*/
void *recvhand(void *arg)
{
	INFO Info;
	//pthread_detach(pthread_self());
	int ret;
	int fd = *(int *)arg;
	

	memset(&Info, 0, sizeof(Info));
	ret = recv(fd,&Info, sizeof(Info), 0);
	if(-1 == ret)
	{
		perror("recv");
	}
	else
		if(0 == ret)
		{
			ret = Server_logoffself(fd);
			if(ret == FAILURE)
			{
				printf("Thread : %d : Server_logoffself Failure!\n",(int)pthread_self());
			}
			else
			{
				printf("Thread : %d : Server_logoffself Success!\n",(int)pthread_self());
			}
			close(fd);
			epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
			clientcount--;
			printf("\nClient : %d has disconnected!\n",fd);
			printf("Now there are %d client!\n\n",clientcount);
		}
		else
		{
			switch(Info.Flag)
			{
				case Register:
				{
					ret = Server_register(Info, fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_register Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_register Success!\n",(int)pthread_self());
					}
					break;
				}

				case Login:
				{
					ret = Server_login(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_login Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_login Success!\n",(int)pthread_self());
					}
					break;
				}

				case ChangePassword:
				{
					ret = Server_changepassword(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_changepassword Failure!\n",(int)pthread_self());
					}		
					else
					{
						printf("Thread : %d Server_changepassword Success!\n",(int)pthread_self());
					}
					break;
				}

				case Traverse:
				{
					ret = Server_traverse(fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_traverse Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_traverse Success!\n",(int)pthread_self());
					}
					break;
				}
			
				case MChat:
				{		
					ret = Server_mchat(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_mchat Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_mchat Success!\n",(int)pthread_self());
					}
					break;
				}
			
				case Pc:
				{
					ret = Server_pc(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_pc Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_pc Success!\n",(int)pthread_self());
					}
					break;
				}
			
				case Gc:
				{
					ret = Server_mgc();
					if(ret == FAILURE)
					{
						Info.Flag = AllOtherLogoff;
						send(fd,&Info,sizeof(Info),0);
						printf("Thread : %d Gc Failure!\n",(int)pthread_self());
					}
					else
					{
						Info.Flag = AllOtherLogin;
						send(fd,&Info,sizeof(Info),0);
						ret = Server_gc(Info,fd);
						if(ret == SUCCESS)
						{
							printf("Thread : %d Gc Success!\n",(int)pthread_self());
						}
						else
						{
							printf("Thread : %d Gc Failure!\n",(int)pthread_self());
						}
					}
					break;
				}
			
				case MVIP:
				{
					ret = Server_mVIP(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_mVIP Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_mVIP Success!\n",(int)pthread_self());
					}
					break;
				}
		
				case Forbidden:
				{
					ret = Server_forbidden(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_forbidden Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_forbidden Success!\n",(int)pthread_self());
					}
					break;
				}
			
				case CancelForbidden:
				{
					ret = Server_cancel_forbidden(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_cancel_forbidden Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_cancel_forbidden Success!\n",(int)pthread_self());
					}
					break;
				}
			
				case LogoffOther:
				{
					ret = Server_logoffother(Info,fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_logoffother Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_logoffother Success!\n",(int)pthread_self());
					}	
					break;
				}
			
				case File:
				{
					ret = Server_file(Info, fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_file Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_file Success!\n",(int)pthread_self());
					}
					break;
				}

				case SendFileName:
				{
					ret = Server_sendfilename(Info, fd);
					if(ret == FAILURE)
					{
						printf("Thread : %d Server_sendfilename Failure!\n",(int)pthread_self());
					}
					else
					{
						printf("Thread : %d Server_sendfilename Success!\n",(int)pthread_self());
					}
					break;
				}
			}
		}

	return NULL;
}

/*
作者:周超
日期:2018.3.26
描述:设置IO为非阻塞模式
参数:代表服务器与客户端建立连接通道的套接字或者服务器监听套接字
返回值:整型
*/
int setnonblocking(int sockfd)
{
	int ret = 0;
    ret = fcntl(sockfd, F_SETFL, fcntl(sockfd, F_GETFD, 0)| O_NONBLOCK);
    return ret;
}

/*
作者:周超
日期:2019.3.26
描述:添加新的事件到内核事件列表中
参数:代表服务器与客户端建立连接通道的套接字或者服务器监听套接字
返回值:无
*/
void addfd(int epollfd, int fd)
{
	int ret = 0;
    struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN;
	ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev);
    ret = setnonblocking(fd);
	if(-1 == ret)
	{
		perror("setnonblocking!\n");
	}
    printf("\nfd added to epoll!\n");
}


/*
作者:周超
日期:2018.9.18
描述:接受客户端建立连接的请求
参数:代表服务器与客户端建立连接通道的套接字
返回值:无
*/
void Serveraccept()
{
	int len = sizeof(client_addr);
	int i = 0;
	int ret = 0;
	int epoll_events_count = 0;
	int clientfd = 0;

	//初始化线程池，最多10个线程
    threadpool_init(&pool, 10); 
	
	while(1)
    {
		
        //epoll_events_count表示就绪事件的数目
		epoll_events_count = epoll_wait(epfd, events, EPOLL_SIZE, -1);
        if(epoll_events_count < 0)
		{

            perror("epoll_wait failure");
            break;

        }
		
		printf("\nepoll_events_count = %d\n", epoll_events_count);

        //处理这epoll_events_count个就绪事件
        for(i = 0; i < epoll_events_count; i++)
        {

            //新用户连接
            if(events[i].data.fd == sockfd)
            {
                socklen_t client_addrLength = sizeof(struct sockaddr_in);
                clientfd = accept(sockfd, ( struct sockaddr* )&client_addr, &len);
                printf("client connection from: %s : % d(IP : port), clientfd = %d \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),clientfd);
                
				//把这个新的客户端添加到内核事件列表
				addfd(epfd, clientfd);
				clientcount++;
                // 服务端用list保存用户连接
                //clients_list.push_back(clientfd);

                printf("Add new clientfd = %d to epoll\n", clientfd);
				printf("Now there are %d client!\n\n",clientcount);

            }

            //客户端唤醒,处理用户发来的消息
            else
            {
				threadpool_add_task(&pool, recvhand, &events[i].data.fd);
            }

        }

    }

}
