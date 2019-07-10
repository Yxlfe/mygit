#include "Client.h"

extern pthread_mutex_t lock;
extern pthread_cond_t cond;
extern int skr;

/*
作者:周超
时间:2018.9.18
描述:接受信息
参数:代表客户端的套接字
返回值:无
*/
void *RecvThread(void *arg)
{
	pthread_detach(pthread_self());
	int fd = *(int *)arg;
	int ret,ret_write;

	int old;
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old);

	while (1)
	{
		memset(&Recv, 0, sizeof(Recv));
		
		ret = recv(fd, &Recv, sizeof(Recv), 0);
		if (ret < 0)
		{
			perror("recv");
			exit(1);
		}
		
		if(Recv.Flag == Register)
		{
			printf("Receive from Server : %s\n", Recv.text);
		}
		
		if(Recv.Flag == ChangePassword)
		{
			printf("Receive from Server : %s\n", Recv.text);
		}

		if(Recv.Flag ==  LoginSuccess)
		{
			strcpy(Login_Account.account,Recv.account);
			strcpy(Login_Account.ID,Recv.ID);
			printf("Receive from Server : %s (Waitting!)\n", Recv.text);
			sleep(2);
			FFlag = LoginSuccess;
		}
		
		if(Recv.Flag == LoginFailure)
		{
			printf("Receive from Server : %s (Waitting!)\n", Recv.text);
			sleep(2);
			FFlag = LoginFailure;
		}

		if(Recv.Flag == Traverse)
		{
			printf("Online Account : %s				ID : %s		\n",Recv.account,Recv.ID);
		}
		
		if(Recv.Flag == CanChat)
		{
			pthread_mutex_lock(&lock);
			FFlag = CanChat;
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == NotCanChat)
		{
			pthread_mutex_lock(&lock);
			printf("You have been forbiddened to Chat!(Waitting to exit!)\n");
			sleep(2);
			FFlag = NotCanChat;
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == OtherLogoff)
		{
			pthread_mutex_lock(&lock);
			printf("%s is OffLine!\n",Recv.ID);
			FFlag = OtherLogoff;
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == OtherLogin)
		{
			pthread_mutex_lock(&lock);
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == AllOtherLogoff)
		{
			pthread_mutex_lock(&lock);
			printf("All Receiver is OffLine!\n");
			FFlag = AllOtherLogoff;
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == AllOtherLogin)
		{
			pthread_mutex_lock(&lock);
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}


		if(Recv.Flag == PcSuccess)
		{
			printf("\t\t\t\t%s\t\t\t\tReceive from %s (Private) : %s \n", Recv.time, Recv.ID, Recv.text);
			fd1 = open("ChatMessage.txt",O_WRONLY|O_CREAT,S_IRWXU);
			if(fd1 == -1)
			{
				perror("open");
			}

			ret = lseek(fd1,0,SEEK_END);
			if(ret == -1)
			{
				perror("lseek");
			}
			
			ret = write(fd1,&Recv.time,strlen(Recv.time));
			if(ret == -1)
			{
				perror("write3");
			}
																
			ret = write(fd1,Login_Account.ID,strlen(Login_Account.ID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1," recv from (private) ",21);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1,Recv.ID,strlen(Recv.ID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1," : ",3);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1,Recv.text,strlen(Recv.text));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1,"\n\n",2);
			if(ret == -1)
			{
				perror("write");
			}

			close(fd1);
			
		}
		
		if(Recv.Flag == GcSuccess)
		{
			printf("\t\t\t\t%s\t\t\t\tReceive from %s (Group) : %s \n", Recv.time, Recv.ID, Recv.text);
			fd1 = open("ChatMessage.txt",O_WRONLY|O_CREAT,S_IRWXU);
			if(fd1 == -1)
			{
				perror("open");
			}

			ret = lseek(fd1,0,SEEK_END);
			if(ret == -1)
			{
				perror("lseek");
			}
			
			ret = write(fd1,&Recv.time,strlen(Recv.time));
			if(ret == -1)
			{
				perror("write4");
			}
																
			ret = write(fd1,Login_Account.ID,strlen(Login_Account.ID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1," recv from (group) ",19);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1,Recv.ID,strlen(Recv.ID));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1," : ",3);
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1,Recv.text,strlen(Recv.text));
			if(ret == -1)
			{
				perror("write");
			}
															
			ret = write(fd1,"\n\n",2);
			if(ret == -1)
			{
				perror("write");
			}

			close(fd1);
		}
		
		if(Recv.Flag == VIP)
		{
			FFlag = VIP;
		}
		
		if(Recv.Flag == NVIP)
		{
			printf("You are not Admin!(Waitting to exit!)\n");
			sleep(2);
			FFlag = NVIP;
		}
		
		if(Recv.Flag == ForbidSuccess)
		{
			pthread_mutex_lock(&lock);
			printf("Forbid %s to Chat Success!\n",Recv.ID);
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == CancelForbidSuccess)
		{
			pthread_mutex_lock(&lock);
			printf("Release the right of %s to Chat Success!\n",Recv.ID);
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == LogoffOther)
		{
			system("clear");
			printf("\n\n\n\n\t\t\tYou are forced to go offline!\n");
			sleep(2);
			exit(1);
		}
		
		if(Recv.Flag == LogoffOtherSuccess)
		{
			pthread_mutex_lock(&lock);
			printf("Logoff %s Success!\n",Recv.ID);
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == FileTransfer)
		{
			pthread_mutex_lock(&lock);
			printf("File is transferring!(Waitting)\n");
			skr=1;
			pthread_mutex_unlock(&lock);
			pthread_cond_signal(&cond);
		}
		
		if(Recv.Flag == RecvFileName)
		{
			fd4 = open(Recv.file,O_WRONLY|O_CREAT|O_EXCL,S_IRWXU);
			if(fd4 == -1)
			{
				perror("open");
			}
		}

		if(Recv.Flag == RecvFile)
		{
			printf("Recving File from %s!\n", Recv.ID);
			ret_write = write(fd4,Recv.text,strlen(Recv.text));
			if(ret_write == -1)
			{
				perror("write");
			}

			if(strlen(Recv.text) < sizeof(Recv.text) - 1)
			{
				printf("Recv File Finish!\n");
				close(fd4);
			}
			
		}
		
		if(Recv.Flag == ServerClose)
		{
			system("clear");
			printf("\n\n\n\n\t\t\tServer has been closed!\n");
			sleep(2);
			close(fd);
			exit(1);
		}
	}
	
	return NULL;
}

/*
作者:周超
时间:2018.9.18
描述:退出客户端
参数:代表kill信号的整数
返回值:无
*/
void Stopclient(int num)
{
	int ret;
	ret = pthread_cancel(tid_recv);
	if(ret != 0)
	{
		perror("pthread_cancel");
	}
	system("clear");
	printf("\n\n\n\n");
	printf("\t\t\tBYE!\n");
	sleep(2);
	exit(1);
}

/*
作者:周超
时间:2018.9.18
描述:即时获取输入的密码(字符)
参数:无
返回值:无
*/
int getch()
{
	int c = 0;
	struct termios org_opts, new_opts;
	int res = 0;
	//-----  store old settings -----------
	res = tcgetattr(STDIN_FILENO, &org_opts);
	assert(res == 0);
	//---- set new terminal parms --------
	memcpy(&new_opts, &org_opts, sizeof(new_opts));
	new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
	c = getchar();
	//------  restore old settings ---------
	res = tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
	assert(res == 0);
	return c;
}

/*
作者:周超
时间:2018.9.18
描述:即时转换输入的密码(字符)为*,结束输入后转化为字符串
参数:输入的密码
返回值:无
*/
void Password(char *pd)
{
    int i;
    for(i = 0; ; i++)
    {
		pd[i] = getch();
		if(pd[i] == '\n')
		{
	    	pd[i] = '\0';
	    	break;
		}
		if(pd[i] == 127) //删除
		{
	    	printf("\b \b");
	    	i = i - 2;
		}
		else
		{
			printf("*");
		}
		if(i<0)
		{
			pd[0]='\0';
		}
	}
}

/*
作者:周超
时间:2018.9.18
描述:修改密码输入帐户,旧密码和新密码
参数:无
返回值:无
*/
void ClientChangePassword()
{
	system("clear");
	memset(&Send,0,sizeof(Send));
	printf("Please input account!\n");
	scanf("%s",Send.account);
	printf("Please input oldpassword!\n");
	getchar();
	Password(Send.oldpassword);
	printf("\nPlease input password!\n");
	Password(Send.password);
	Send.Flag = ChangePassword;
}

/*
作者:周超
时间:2018.9.18
描述:注册输入帐户,密码和ID
参数:无
返回值:无
*/
void ClientRegister()
{
	system("clear");
	memset(&Send,0,sizeof(Send));
	printf("Please input account!\n");
	scanf("%s",Send.account);
	printf("Please input password!\n");
	getchar();
	Password(Send.password);
	printf("\nPlease input ID!\n");
	scanf("%s",Send.ID);
	Send.Flag = Register;
}

/*
作者:周超
时间:2018.9.18
描述:登录输入帐户和密码
参数:无
返回值:无
*/
void ClientLogin()
{
	system("clear");
	memset(&Send,0,sizeof(Send));
	printf("Please input account!\n");
	scanf("%s",Send.account);
	printf("Please input password!\n");
	getchar();
	Password(Send.password);
	printf("\n");
	Send.Flag = Login;
}


/*
作者:周超
时间:2018.9.18
描述:发送结构体(帐号,密码,ID,文本,文件名,标志位)
参数:代表客户端的套接字
返回值:整型(成功或失败)
*/
int SendClient(int sockfd)
{
	int ret;
	ret = send(sockfd,&Send,sizeof(Send),0);
	if(ret < 0)
	{
		perror("send");
		return FAILURE;
	}

	return SUCCESS;
}

/*
作者:周超
时间:2018.9.18
描述:欢迎界面
参数:无
返回值:无
*/
void Welcome()
{
	system("clear");
	printf("\n\n\n\n\n");
	printf("\t\t\t\tWelcome to Chat Room!\n");
	sleep(3);
}

/*
作者:周超
时间:2018.9.18
描述:注册、登录界面
参数:无
返回值:无
*/
void Loginmenue()
{
	system("clear");
	printf("\n\n\n\n\n");
	printf("\t\t1.Register				2.Login\n");
	printf("\t\t3.ChangePassword\n");
	printf("\t\tPlease input number(order)!\n");
}

/*
作者:周超
时间:2018.9.18
描述:用户功能界面
参数:无
返回值:无
*/
void menue()
{
	system("clear");
	printf("\t\tLogin_Account : %s\n",Login_Account.account);
	printf("\t\tLogin_ID : %s",Login_Account.ID);
	printf("\n\n\n\n\n");
	printf("\t\t4.Traverse				    5.Private Chat\n");
	printf("\t\t6.Group Chat				    7.Logoff Other\n");
	printf("\t\t8.Forbidden				    9.Cancel Forbidden\n");
	printf("\t\t10.File Transfer\n");
	printf("\t\tPlease input number(order)!\n");
}
