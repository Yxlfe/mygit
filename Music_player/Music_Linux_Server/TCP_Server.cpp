#include "TCP_Server_head.h"

Recv_info::Recv_info():m_flag(0)
{
	strcpy(m_name,"0");
}

Recv_info::~Recv_info()
{

}

Recv_info::Recv_info(const Recv_info& obj)
{
	strcpy(m_name,obj.m_name);
	m_flag = obj.m_flag;
}

char* Recv_info::Get_member_name()
{
	return m_name;
}

int Recv_info::Get_member_flag()
{
	return m_flag;
}

void Send_sql_history(int fd)
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret;
	char sql[128] = {0};
	SendInfo sendinfo;
	sendinfo.Set_member_flag(2);
	
	ret = sqlite3_open("music.db", &ppdb);
	if(ret != SQLITE_OK)
	{
		perror("sqlite_open");
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql, "create table if not exists music (name text, time text);");
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		cout << "sqlite3_exec error 1: " << sqlite3_errmsg(ppdb) << endl;
	}
	
	memset(sql, 0, sizeof(sql));
	sprintf(sql,"select * from music;");
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(ret != SQLITE_OK)
	{
		cout << "sqlite3_exec error 4: " << sqlite3_errmsg(ppdb) << endl;
	}
	else
	{
		for(int i = 1; i <= row ; i++)
		{
			usleep(100000);
			sendinfo.Set_member_name(result[i * column + 0]);
			sendinfo.Set_member_time(result[i * column + 1]);
			int ret_write = write(fd,(void*)(&sendinfo),sizeof(sendinfo));
			if(ret_write == -1)
			{
				perror("write info");
			}
		}
	}
	
	sqlite3_free_table(result);
	
	sqlite3_close(ppdb);

}

void Send_file_name(int fd)
{
	SendInfo sendinfo;
	sendinfo.Set_member_flag(1);
	
	for(list<char*>:: iterator it = File_name.begin(); it != File_name.end(); it++)
	{
		usleep(100000);
		sendinfo.Set_member_name(*it);
		int ret = write(fd,(void*)(&sendinfo),sizeof(sendinfo));
		if(ret == -1)
		{
			perror("write info");
		}
	}
}

Send_info::Send_info():m_flag(0)
{
	strcpy(m_name,"0");
	strcpy(m_time,"0");
}

Send_info::~Send_info()
{
	
}

Send_info::Send_info(const Send_info& obj)
{
	strcpy(m_name,obj.m_name);
	strcpy(m_time,obj.m_time);
	m_flag = obj.m_flag;
}

void Send_info::Set_member_name(char* name)
{
	strcpy(m_name,name);
}

void Send_info::Set_member_time(char* time)
{
	strcpy(m_time,time);
}

void Send_info::Set_member_flag(int flag)
{
	m_flag = flag;
}

void* TCP_connect(void* arg)
{	
	pthread_detach(pthread_self());
	int old;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old);
	int ret = 0;
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
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.128");
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
	
	Serveraccept();
	return NULL;
}

void TCP_socket_create()
{
	int ret = pthread_create(&tid_server_socket,NULL,TCP_connect,NULL);
	if(-1 == ret)
	{
		perror("pthread_create");
	}
}

void Music_choose_play(RecvInfo Info)
{
	char temp[32] = {0};
	strcpy(temp,Info.Get_member_name());
	Share memory;
	int local = 1;
	for(list<char*>:: iterator it = File_name.begin(); it != File_name.end(); it++)
	{
		if(strcmp(*it,temp) == 0)
		{
			break;
		}
		++local;
	}

	memory.Set_member_local(local);
	*(Share*)shmaddr = memory;

}


/*
作者:周超
日期:2018.9.18
描述:接收客户端发送的信息
参数:代表服务器接收客户端发送消息通道的套接字
返回值:无
*/
void recvhand(int* arg)
{
	int ret;
	int fd = *arg;
	int choice = 0;
	RecvInfo Info;
	
	ret = read(fd,&Info, sizeof(Info));
	
	int flag = Info.Get_member_flag();
	
	if(-1 == ret)
	{
		perror("read");
	}
	else
		if(0 == ret)
		{
			close(fd);
			FD_CLR(fd, &readfd);
			*arg = 0;;
			clientcount--;
			cout << endl << "Client : " << fd <<" has disconnected!" << endl << endl;
			cout << "Now there are "<< clientcount << " client!" << endl << endl;
			
		}
		else
		{
			shmaddr = shmat(shmid,NULL,0);
			if(NULL == shmaddr)
			{
				perror("shmat");
				exit(1);
			}

			switch(flag)
			{
				case Music_list:
				{
					Send_file_name(fd);
					break;
				}

				case Start:
				{
					Shmaddr_set_start(1);
					Shmaddr_set_end(2);
					kill(pid1,SIGTRAP);
					sleep(1);
					kill(pid1,SIGILL);
					break;
				}
				
				case Stop:
				{
					Shmaddr_set_start(0);
					Shmaddr_set_end(0);
					kill(pid1,SIGTRAP);
					break;
				}

				case Continue:
				{
					kill(pid1,SIGABRT);
					break;
				}

				case Pause:
				{
					kill(pid1,SIGFPE);
					break;
				}

				case Last_music:
				{
					Shmaddr_set_start(2);
					kill(pid1,SIGTRAP);
					sleep(1);
					kill(pid1,SIGUSR1);
					break;
				}

				case Next_music:
				{
					Shmaddr_set_start(3);
					kill(pid1,SIGTRAP);
					sleep(1);
					kill(pid1,SIGUSR2);
					break;
				}

				case Sequential_Play:
				{
					Shmaddr_set_end(1);
					break;
				}

				case Rand_Play:
				{
					Shmaddr_set_end(3);
					break;
				}

				case Signel_Play:
				{
					Shmaddr_set_end(2);
					break;
				}
		
				case Sound_add:
				{
					Sound_change(1);
					break;
				}
		
				case Sound_reduce:
				{
					Sound_change(0);
					break;
				}
		
				case Music_play_list:
				{
					Send_sql_history(fd);
					break;
				}
				
				case Music_choose:
				{
					Music_choose_play(Info);
					
					Shmaddr_set_start(1);
					Shmaddr_set_end(2);
					kill(pid1,SIGTRAP);
					sleep(1);
					kill(pid1,SIGILL);
					break;
				}
				
				default:
					break;
			}

			if(-1 == (shmdt(shmaddr)))
			{
				perror("shmdt_grand");
				exit(1);
			}
		
		}
	return ;
}

/*
作者:周超
日期:2018.9.18
描述:接受客户端建立连接的请求
参数:代表服务器与客户端建立连接通道的套接字
返回值:监听套接字
*/
void Serveraccept()
{
	fd_set tmpfd;
	FD_ZERO(&readfd);
	FD_SET(sockfd,&readfd);		//把sockfd添加到集合
	int maxfd = sockfd;
	int length = sizeof(struct sockaddr_in);
	int i = 0;
	int count = 0;
	
	
	while(1)
    {
		tmpfd = readfd;		//	select每次回清空集合
		count = select(maxfd + 1, &tmpfd,NULL, NULL, NULL);
		if(-1 == count)
		{
			perror("select");
			exit(1);
		}

		if(FD_ISSET(sockfd,&tmpfd))
		{
			cout << "有客户端发起连接..." << endl;
			for (i = 0; i < SIZE; i++)
			{
				if (0 == fd[i])
				{
					break;
				}
			}

			if(i == SIZE)
			{
				cout << "超出客户端数目上限" << endl;
				break;
			}

			fd[i] = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t*)&length);
			if(-1 == fd[i])
			{
				perror("accept");
				exit(1);
			}
			
			clientcount++;
			cout << "Client IP: " << inet_ntoa(client_addr.sin_addr) << "PORT: " << ntohs(client_addr.sin_port)
				 << "connect from fd: " << fd[i] << endl;
			cout << "Now there are " << clientcount << " client!" << endl;
			
			if (fd[i] > maxfd)
			{
				maxfd = fd[i];
			}
			FD_SET(fd[i],&readfd);
		}
		else	//由客户端发消息
		{
			for (i = 0; i < SIZE; i++)
			{
				if(fd[i] == 0)
				{
					continue;
				}
				
				if(FD_ISSET(fd[i],&tmpfd))
				{
					cout << "One task!" << endl;
					recvhand(&fd[i]);
					if(--count <= 0)
					{
						break;
					}
				}
			}
		}
    }

}
