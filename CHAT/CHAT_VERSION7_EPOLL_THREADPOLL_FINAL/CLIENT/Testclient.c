#include "Client.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int skr=0;

int main()
{
	signal(SIGINT,Stopclient);
	int ret,choice,ret_read;
	time_t t;
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if (-1 == sockfd)
	{
		perror("socket");
	}

	//设置socket属性，地址可以被重复绑定
	int opt = 1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr("192.168.0.121");
	ret = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (-1 == ret)
	{
		perror("connect");
	}
	
	ret = pthread_create(&tid_recv, NULL, RecvThread, &sockfd);
	if (ret != 0)
	{
		perror("pthread_create");
	}


	Welcome();

	while(1)
	{
		Loginmenue();
		scanf("%d",&choice);
		FFlag = (FLAG)choice;
		switch(FFlag)
		{
			case Register :
				{
					ClientRegister();
					ret = SendClient(sockfd);
					if(ret == FAILURE)
					{
						printf("Register send Failure!\n");
					}
					break;
				}
			case ChangePassword :
				{
					ClientChangePassword();
					ret = SendClient(sockfd);
					if(ret == FAILURE)
					{
						printf("Register send Failure!\n");
					}
					break;
				}
			case Login:
				{
					ClientLogin();
					ret = SendClient(sockfd);
					if(ret == FAILURE)
					{
						printf("Login send Failure!\n");
					}
					while(1)
					{
						switch(FFlag)
						{
							case LoginSuccess:
								{
									while(1)
									{
										menue();
										scanf("%d",&choice);
										FFlag = (FLAG)choice;
										switch(FFlag)
										{
											case Traverse:
												{
													system("clear");
													Send.Flag = Traverse;
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("Traverse send Failure!\n");
													}
													getchar();
													printf("Please input any key to exit!\n");
													getchar();
													break;
												}
											case Pc:
												{
													system("clear");
													Send.Flag = MChat;
													
													pthread_mutex_lock(&lock);
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("SendMchat send Failure!\n");
													}
													
													while(!skr)
													{
														pthread_cond_wait(&cond,&lock);
													}
													skr = 0;
													pthread_mutex_unlock(&lock);
													
													while(1)
													{
														if(FFlag == CanChat)
														{
															while(1)
															{
																Send.Flag = MChat;
																
																pthread_mutex_lock(&lock);
																ret = SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("SendMchat send Failure!\n");
																}
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
																
																if(FFlag == NotCanChat)
																{
																	break;
																}


																printf("Please input the ID of Receiver(input EXIT or exit to exit!)\n");
																scanf("%s",Send.ID);
																if(!strcmp(Send.ID,"EXIT") || !strcmp(Send.ID,"exit"))
																{
																	FFlag = NotCanChat;
																	break;
																}
																printf("Please input:(input bye to exit!)\n");
																scanf("%s",Send.text);
																t = time(NULL);
																strcpy(Send.time,ctime(&t));
																Send.Flag = Pc;
																
																pthread_mutex_lock(&lock);
																ret = SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("SendPc send Failure!\n");
																}		
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
																
																if(!strcmp(Send.text,"bye"))
																{
																	FFlag = NotCanChat;
																	break;
																}
																
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
																
																ret = write(fd1,&Send.time,strlen(Send.time));
																if(ret == -1)
																{
																	perror("write1");
																}
																
																ret = write(fd1,Login_Account.ID,strlen(Login_Account.ID));
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1," send to ",9);
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1,Send.ID,strlen(Send.ID));
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1," : ",3);
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1,Send.text,strlen(Send.text));
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
														}
														
														if(FFlag == NotCanChat)
														{
															break;
														}
													}
													
													break;
												}
											case Gc:
												{
													system("clear");
													Send.Flag = MChat;
													
													pthread_mutex_lock(&lock);
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("SendMchat send Failure!\n");
													}
													
													while(!skr)
													{
														pthread_cond_wait(&cond,&lock);
													}
													skr = 0;
													pthread_mutex_unlock(&lock);
													
													while(1)
													{
														if(FFlag == CanChat)
														{
															while(1)
															{
																Send.Flag = MChat;
																
																pthread_mutex_lock(&lock);
																ret = SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("SendMchat send Failure!\n");
																}
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
		
																if(FFlag == NotCanChat)
																{
																	break;
																}
																printf("Please input:(input EXIT or exit to exit!)\n");
																scanf("%s",Send.text);
																t = time(NULL);
																strcpy(Send.time,ctime(&t));
																Send.Flag = Gc;
																if(!strcmp(Send.text,"EXIT") || !strcmp(Send.text,"exit"))
																{
																	FFlag = NotCanChat;
																	break;
																}
																
																pthread_mutex_lock(&lock);
																ret = SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("SendGc send Failure!\n");
																}
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
															
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
																
																ret = write(fd1,&Send.time,strlen(Send.time));
																if(ret == -1)
																{
																	perror("write2");
																}
																
																ret = write(fd1,Login_Account.ID,strlen(Login_Account.ID));
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1," send to ",9);
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1,"All Online Client",17);
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1," : ",3);
																if(ret == -1)
																{
																	perror("write");
																}
															
																ret = write(fd1,Send.text,strlen(Send.text));
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
														}
														
														if(FFlag == NotCanChat)
														{
															break;
														}

													}
													
													break;
												}
											case LogoffOther:
												{
													system("clear");
													Send.Flag = MVIP;
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("SendMVIP send Failure!\n");
													}
													
													while(1)
													{
														if(FFlag == VIP)
														{
															while(1)
															{
																printf("Please input the ID which you want to Logoff!(input EXIT or exit to exit)\n");
																Send.Flag = LogoffOther;
																scanf("%s",Send.ID);
																if(!strcmp(Send.ID,"exit") || !strcmp(Send.ID,"EXIT"))
																{
																	FFlag = NVIP;
																	break;
																}
																
																pthread_mutex_lock(&lock);
																SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("SendLogoffOther send Failure!\n");
																}	
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
															}
														}
														
														if(FFlag == NVIP)
														{
															break;
														}
													}
													break;
												}
											case Forbidden:
												{
													system("clear");
													Send.Flag = MVIP;
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("SendMVIP send Failure!\n");
													}
													
													while(1)
													{
														if(FFlag == VIP)
														{
															while(1)
															{
																printf("Please input the ID which you want to forbid to Chat!(input EXIT or exit to exit)\n");
																Send.Flag = Forbidden;
																scanf("%s",Send.ID);
																if(!strcmp(Send.ID,"exit") || !strcmp(Send.ID,"EXIT"))
																{
																	FFlag = NVIP;
																	break;
																}
																
																pthread_mutex_lock(&lock);
																SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("Sendforbidden send Failure!\n");
																}
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
															}
														}
														
														if(FFlag == NVIP)
														{
															break;
														}
													}
													
													break;
												}
											
											case CancelForbidden:
												{
													system("clear");
													Send.Flag = MVIP;
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("SendMVIP send Failure!\n");
													}
													
													while(1)
													{
														if(FFlag == VIP)
														{
															while(1)
															{
																printf("Please input the ID which you want to allow to Chat!(input EXIT or exit to exit)\n");
																Send.Flag = CancelForbidden;
																scanf("%s",Send.ID);
																if(!strcmp(Send.ID,"exit") || !strcmp(Send.ID,"EXIT"))
																{
																	FFlag = NVIP;
																	break;
																}
																
																pthread_mutex_lock(&lock);
																SendClient(sockfd);
																if(ret == FAILURE)
																{
																	printf("Sendcancelforbidden send Failure!\n");
																}
																
																while(!skr)
																{
																	pthread_cond_wait(&cond,&lock);
																}
																skr = 0;
																pthread_mutex_unlock(&lock);
															}
														}
														
														if(FFlag == NVIP)
														{
															break;
														}
													}
													
													break;
												}
											
											case File:
												{
													system("clear");
													printf("Please input ID:(input EXIT or exit to exit)\n");
													scanf("%s",Send.ID);
													if(!strcmp(Send.ID,"EXIT") || !strcmp(Send.ID,"exit"))
													{
														break;
													}
													printf("Please input File Name:(input EXIT or exit to exit)\n");
													scanf("%s",Send.file);
													if(!strcmp(Send.file,"EXIT") || !strcmp(Send.file,"exit"))
													{
														break;
													}
													Send.Flag = SendFileName;
													
													pthread_mutex_lock(&lock);
													ret = SendClient(sockfd);
													if(ret == FAILURE)
													{
														printf("SendMchat send Failure!\n");
													}
													
													while(!skr)
													{
														pthread_cond_wait(&cond,&lock);
													}
													skr = 0;
													pthread_mutex_unlock(&lock);
													
													if(FFlag == OtherLogoff)
													{
														printf("Wait a moment to exit!\n");
														sleep(2);
														break;
													}
													
													fd2 = open(Send.file,O_RDONLY);
													if(fd2 == -1)
													{
														perror("open");
													}

													while(1)
													{
														memset(Send.text,0,sizeof(Send.text));

														ret_read = read(fd2,Send.text,sizeof(Send.text) - 1);
														if(ret_read == -1)
														{
															perror("read");
														}
														
														Send.Flag = File;
														
														pthread_mutex_lock(&lock);
														ret = SendClient(sockfd);
														if(ret == FAILURE)
														{
															printf("SendMchat send Failure!\n");
														}
														
														while(!skr)
														{
															pthread_cond_wait(&cond,&lock);
														}
														skr = 0;
														pthread_mutex_unlock(&lock);
															
														if(FFlag == OtherLogoff)
														{
															printf("Wait a moment to exit!\n");
															sleep(2);
															break;
														}

														if(ret_read < sizeof(Send.text) - 1)
														{
															printf("Send File Finish!\n");
															close(fd2);
															sleep(2);
															break;
														}

													}
													
													break;
												}
										}
									}
									break;
								}
							case LoginFailure:
								{
									break;
								}
						}
						if(FFlag == LoginFailure)
						{
							break;
						}
					}
					break;
				}
		}
	}
}
