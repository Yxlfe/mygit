#include "Music_player_src_head.h"

void Sound_change(int sound_flag)
{
	char old_sound_str[4] = {0}; 
	int old_sound_int = 0;
	char now_sound_str[4] = {0};
	char cmd[64] = "amixer cset numid=17,iface=MIXER,name='PCM Playback Volume' ";
	My_system("amixer cget numid=17,iface=MIXER,name='PCM Playback Volume'");
	strcpy(old_sound_str,Sound_get());
	old_sound_int = atoi(old_sound_str);
	
	if((old_sound_int < 63) && (sound_flag == 1))
	{
		old_sound_int++;
		sprintf(now_sound_str,"%d",old_sound_int);
		strcat(cmd,now_sound_str);
		My_system(cmd);
	}
	else if((old_sound_int > 0) && (sound_flag == 0))
	{
		old_sound_int--;
		sprintf(now_sound_str,"%d",old_sound_int);
		strcat(cmd,now_sound_str);
		My_system(cmd);
	}
	else if(old_sound_int == 63)
	{
		cout << "音量已达到最大值!" << endl;
	}
	else if(old_sound_int == 0)
	{
		cout << "音量已达到最小值!" << endl;
	}
	
	cout << "now_sound_str: " << old_sound_int << endl;
}

char* Sound_get()
{
	char* dest = str_result;
	while(*dest != ',')
	{
		dest++;
	}
	dest++;
	return dest;
}

void My_system(const char * cmd) 
{ 
	FILE* fp; 
	int res = 0; 
	char buf[1024] = {0}; 
	int count = 0;
	if (cmd == NULL) 
	{
		cout  << "My_system cmd is NULL!" << endl;
	}  

	if ((fp = popen(cmd, "r") ) == NULL) 
	{ 
		perror("popen");
		cout <<"popen error: " << strerror(errno) << endl; 
	} 
	else
	{
		while(fgets(buf, sizeof(buf), fp)) 
		{ 
			++count;
			if(3 == count)
			{
				strcpy(str_result,buf);
			}
			cout << "Command: " << cmd << endl << "output: "  << buf << endl; 
		} 

		if ( (res = pclose(fp)) == -1) 
		{ 
			cout << "Close popen file pointer fp error!" << endl;
		} 
		else 
		{ 
			cout <<"Command: " << cmd << endl << "return: " << WEXITSTATUS(res) << endl;  
		}
 
	}
	
} 

void Ctrl_C(int temp)
{
	int ret = kill(pid1,SIGTRAP);
	if(ret == -1)
	{
		perror("kill_grandchild_end");
	}
	ret = kill(pid1,SIGKILL);
	if(ret == -1)
	{
		perror("kill_child_end");
	}
	
	semctl(semid,0,IPC_RMID);
	
	ret = pthread_cancel(tid_server_socket);
	if(ret != 0)
	{
		perror("pthread_cancel");
	}
	
	for(int i = 0; i < SIZE; i++)
	{
		if(fd[i] != 0)
		{
			cout << "fd[i]:" << fd[i] << endl;
			close(fd[i]);
		}
	}

	close(sockfd);

	if(shmctl(shmid,IPC_RMID,NULL)==-1)
	{
		perror("shmctl_father");
	}


	system("clear");
	cout << "Bye!" << endl;
	exit(1);

}


Menue :: Menue():m_flag(Music_list)
{

}

Share :: Share():m_end(0),m_start(0),m_local(0)
{

}

Menue& Menue :: operator=(const Menue& obj)
{
	this->m_flag = obj.m_flag;
	return *this;
}

void Shmaddr_set_start(int flag)
{
	Share memory;
	memory = *(Share*)shmaddr;
	memory.Set_member_start(flag);
	*(Share*)shmaddr = memory;
}

void Shmaddr_set_end(int flag)
{
	Share memory;
	memory = *(Share*)shmaddr;
	memory.Set_member_end(flag);
	*(Share*)shmaddr = memory;
}

void Shmaddr_set_local(int local)
{
	Share memory;
	memory = *(Share*)shmaddr;
	memory.Set_member_local(local);
	*(Share*)shmaddr = memory;
}

int Rand_get_num(int max)
{
	srand(unsigned(time(NULL)));
	return rand()%max;
}

void Menue :: Signal_send()
{
	shmaddr = shmat(shmid,NULL,0);
	if(NULL == shmaddr)
	{
		perror("shmat");
		exit(1);
	}

	switch(m_flag)
	{
		case Music_list:
		{
			Show_Musiclist();
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
			Sqlite3_show();
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




Sql_recoder::Sql_recoder()
{
	strcpy(m_name,"0");
	strcpy(m_time,"0");
}

Sql_recoder::Sql_recoder(const Sql_recoder& obj)
{
	strcpy(m_name,obj.m_name);
	strcpy(m_time,obj.m_time);
	
}

void Sql_recoder::Set_member(char* name,char* time)
{
	strcpy(m_name,name);
	strcpy(m_time,time);
}
		

char* Sql_recoder::Get_member_name()
{
	return m_name;
}

char* Sql_recoder::Get_member_time()
{
	return m_time;
}

	

Share& Share :: operator= (const Share& obj)
{
	this->m_start = obj.m_start;
	this->m_end = obj.m_end;
	this->m_local = obj.m_local;
	return *this;
}


int Share :: Get_member_local()
{
	return m_local;
}

int Share :: Get_member_start()
{
	return m_start;
}

int Share :: Get_member_end()
{
	return m_end;
}


void Share :: Set_member_start(int start)
{
	m_start = start;
}

void Share :: Set_member_end(int end)
{
	m_end = end;
}

void Share :: Set_member_local(int local)
{
	m_local = local;
}

void IPC_init()
{
	if(key = ftok("/",'s') < 0)
	{
		perror("ftok");
		exit(1);
	}
	
	shmid = shmget(key,shmsize,IPC_CREAT|IPC_EXCL);
	if(-1 == shmid)
	{
		perror("shmget");
		exit(1);
	}
	
	semid = semget(key, 1, IPC_CREAT | IPC_EXCL);    //创建信号量
	if (-1 == semid)
	{
		perror("semget");
		exit(1);
	}

	union semun unsem;
	unsem.val = 1;    //初始化成二值信号量
	int ret = semctl(semid, 0, SETVAL, unsem);    //初始化信号量
	if (-1 == ret)
	{
		perror("semctl");
		exit(1);
	}
	
}

void Fork1()
{
	pid1 = fork();
	if(pid1 == -1)
	{
		perror("pid1 fork");
		exit(1);
	}
	else if(pid1 == 0)
		 {
			while(1)
			{
		 		Fork2();
		 	}
			exit(0);
		 }
		 else
		 {
		 	Menue_choose();
		 }

}

void Menue_choose()
{
	signal(SIGINT,Ctrl_C);//注册信号要放在子进程里，pid1 为子进程号

	while(1)
	{
		sem_p(semid);             //p操作  拔钥匙
		Show_Main_Menue();
		m_menue.Set_member();
		m_menue.Signal_send();
		sem_v(semid);           //v操作  加一操作  插钥匙
	}
	
	int status;
	waitpid(pid1,&status,0);
	if(WIFEXITED(status))
	{
		cout << "Child exit normal: " << WIFEXITED(status)<< endl;
	}
			

}

void Handel(int argc)
{
	if(SIGILL == argc)
	{
		int ret = kill(pid2,SIGILL);
		if(ret == -1)
		{
			perror("kill_grandchild_start");
		}
	}
	else if(SIGTRAP == argc)
	{
		int ret = kill(pid2,SIGTRAP);
		if(ret == -1)
		{
			perror("kill_grandchild_end");
		}
	}
	else if(SIGABRT == argc)
	{
		int ret = kill(pid2,SIGCONT);
		if(ret == -1)
		{
			perror("kill_grandchild_continue");
		}
	}
	else if(SIGFPE == argc)
	{
		int ret = kill(pid2,SIGSTOP);
		if(ret == -1)
		{
			perror("kill_grandchild_stop");
		}
	}	
	else if((SIGUSR1) == argc)
	{
		int ret = kill(pid2,SIGUSR1);
		if(ret == -1)
		{
			perror("kill_grandchild_last");
		}
	}
	else if(SIGUSR2 == argc)
	{
		int ret = kill(pid2,SIGUSR2);
		if(ret == -1)
		{
			perror("kill_grandchild_next");
		}
	}
}

char* Get_playing_music(int local)
{
	int i = 0;
	list<char*>:: iterator it = File_name.begin();
	while((it != File_name.end()) && (i < local-1))
	{
		it++;
		i++;
	}
	return (*it);
}


void Music_function(int argc)
{
	close(0);
	shmaddr = shmat(shmid,NULL,0);
	if(NULL == shmaddr)
	{
		perror("shmat");
		exit(1);
	}
	
	Sql_recoder recoder;
	char file_name[32] = {0};
	char madplay_name[20] = "/home/Mymusic/";
	int count = File_name.size();
	int local = 0;
	Share memory;
	memory = *(Share*)shmaddr;
	local = memory.Get_member_local();
	if(SIGILL == argc)
	{
		strcpy(file_name,Get_playing_music(local));
		strcat(madplay_name,file_name);
		time_t t = time(NULL);
		recoder.Set_member(file_name,ctime(&t));
		Sqlite3_insert(recoder);
	}
	else if(SIGUSR1 == argc)
	{
		--local;
		if(local == 0 || local == -1)
		{
			local = count;
		}
		strcpy(file_name,Get_playing_music(local));	
		strcat(madplay_name,file_name);
		time_t t = time(NULL);
		recoder.Set_member(file_name,ctime(&t));
		Sqlite3_insert(recoder);
	}
	else if(SIGUSR2 == argc)
	{
		++local;
		if(local == count+1)
		{
			local = 0;
		}
		else if(local == 1)
		{
			local = 2;
		}
		strcpy(file_name,Get_playing_music(local));	
		strcat(madplay_name,file_name);
		time_t t = time(NULL);
		recoder.Set_member(file_name,ctime(&t));
		Sqlite3_insert(recoder);
	}

	cout << "当前歌曲位置: " << local << endl;	
	cout << "当前播放模式start: " << memory.Get_member_start() << endl;	
	cout << "当前播放模式end: " << memory.Get_member_end() << endl;	
	memory.Set_member_local(local);
	*(Share*)shmaddr = memory;
	sem_v(semid);           //v操作  加一操作  插钥匙
	
	if(-1 == (shmdt(shmaddr)))
	{
		perror("shmdt_grand");
		exit(1);
	}
	cout << "Playing_file_name:" << file_name << endl;
	
	if(SIGTRAP == argc)
	{
		int ret = kill(getpid(),SIGKILL);
		if(ret == -1)
		{
			perror("kill_grandchild_end");
		}
	}
	
	execlp("madplay","madplay",madplay_name,(char*)0);
	
}

void Signal_grandchild_register()
{
	signal(SIGILL,Music_function);
	signal(SIGTRAP,Music_function);
	signal(SIGSTOP,SIG_DFL);
	signal(SIGCONT,SIG_DFL);
	signal(SIGUSR1,Music_function);
	signal(SIGUSR2,Music_function);
}

void Signal_child_register()
{
	signal(SIGILL,Handel);
	signal(SIGTRAP,Handel);
	signal(SIGABRT,Handel);
	signal(SIGFPE,Handel);
	signal(SIGUSR1,Handel);
	signal(SIGUSR2,Handel);
}


void Fork2()
{
	pid2 = fork();
	if(pid2 == -1)
	{
		perror("pid2 fork");	
	}
	else if(pid2 == 0)
		 {
			Signal_grandchild_register();
			shmaddr = shmat(shmid,NULL,0);
			if(NULL == shmaddr)
			{
				perror("shmat");
				exit(1);
			}
			Share memory;
			memory = *(Share*)shmaddr;
			
			int end = memory.Get_member_end();
			int start = memory.Get_member_start();
			cout << "start:" << start << endl;
			cout << "end:" << end << endl;
			if(4 == start && 1 == end)
			{
				int ret = kill(getpid(),SIGUSR2);
				if(ret == -1)
				{
					perror("kill_grandchild_sequence");
				}
			}
			else if((1 == start && 1 == end) || (2 == start && 1 == end) || (3 == start && 1 == end))
			{
				memory.Set_member_start(4);
			}

			if(4 == start && 2 == end)
			{
				int ret = kill(getpid(),SIGILL);
				if(ret == -1)
				{
					perror("kill_grandchild_circle");
				}
			}	
			else if((1 == start && 2 == end) || (2 == start && 2 == end) || (3 == start && 2 == end))
			{
				memory.Set_member_start(4);
			}
			
			if(4 == start && 3 == end)
			{
				int music_num = File_name.size() + 1;
				int rand_num = Rand_get_num(music_num);
				cout << "rand_num: " << rand_num << endl;
				memory.Set_member_local(rand_num);
				*(Share*)shmaddr = memory;
				int ret = kill(getpid(),SIGILL);
				if(ret == -1)
				{
					perror("kill_grandchild_random");
				}
			}	
			else if((1 == start && 3 == end) || (2 == start && 3 == end) || (3 == start && 3 == end))
			{
				memory.Set_member_start(4);
			}
			
			*(Share*)shmaddr = memory;

			if(-1 == (shmdt(shmaddr)))
			{
				perror("shmdt_grand");
				exit(1);
			}
			
		    sem_p(semid);             //p操作  拔钥匙
			
			exit(0);
			

		}
		else
		{
			Signal_child_register();
			int status;
			waitpid(pid2,&status,0);
			if(WIFEXITED(status))
			{
				cout << "Grandchild exit normal: " << WIFEXITED(status)<< endl;
			}
			
		}

}


void Show_Main_Menue()
{
	system("clear");
	cout << "1、歌曲列表" << endl;
	cout << "2、开始播放" << endl;
	cout << "3、结束播放" << endl;
	cout << "4、继续播放" << endl;
	cout << "5、暂停播放" << endl;
	cout << "6、上一首" << endl;
	cout << "7、下一首" << endl;
	cout << "8、顺序播放" << endl;
	cout << "9、随机播放" << endl;
	cout << "10、单曲循环" << endl;
	cout << "11、音量加" << endl;
	cout << "12、音量减" << endl;
	cout << "13、播放记录" << endl;
	cout << "请输入序号选择!" << endl;	
}

void Menue::Set_member()
{
	cin >> m_flag;
}

int Menue::Get_member()
{
	return m_flag;
}

void List_insert(char* name)
{
	File_name.push_back(name);

}

void Read_Filename()
{
	DIR *dir;
	struct dirent *ptr;
	dir = opendir(Music_path);
	if(dir == NULL)
	{
		perror("opendir");
		exit(1);
	}

	while((ptr = readdir(dir)) != NULL)
	{
		if(8 == ptr->d_type)
		{
			int flag = 0;
			int i = 0;
			while(ptr->d_name[i] != '\0')
			{
				if(ptr->d_name[i] == '.')
				{
					if(flag != 0)
					{
						flag = 0;
					}
					flag++;
				}
				else if(ptr->d_name[i] == 'm' && flag == 1)
					 {
					 	flag++;
					 }
					 else if(ptr->d_name[i] == 'p' && flag == 2)
					 	  {
						  	flag++;
						  }
					else if(ptr->d_name[i] == '3' && flag == 3)
						 {
							if(ptr->d_name[i+1] == '\0')
							{
								List_insert(ptr->d_name);
								break;
							}
							flag = 0;
						 }
						 else if(flag != 0)
							  {
							  	flag = 0;
							  }

				i++;
			}
		}
	}

	closedir(dir);
}

void Show_Musiclist()
{
	for(list<char*>:: iterator it = File_name.begin(); it != File_name.end(); it++)
	{
		cout << *it << " ";
		cout << endl;
	}
}

void sem_p(int semid)
{
	int ret;
	struct sembuf sbuf;

	sbuf.sem_num = 0;      //第一个 从0开始
	sbuf.sem_op = -1;      //p操作
	sbuf.sem_flg = SEM_UNDO;  

	ret = semop(semid, &sbuf, 1);
	if (-1 == ret)
	{
		perror("semop");
		return;
	}
}

void sem_v(int semid)
{
	int ret;
	struct sembuf sbuf;

	sbuf.sem_num = 0;      //第一个 从0开始
	sbuf.sem_op = 1;      //v操作
	sbuf.sem_flg = SEM_UNDO;  

	ret = semop(semid, &sbuf, 1);
	if (-1 == ret)
	{
		perror("semop");
		return;
	}
}


void Sqlite3_register()
{
	int ret;
	char sql[128] = {0};

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
	
	sqlite3_close(ppdb);
}

void Sqlite3_insert(Sql_recoder Recoder)
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret;
	char sql[128] = {0};
	char f_name[32];
	char f_time[32];
	strcpy(f_name,Recoder.Get_member_name());
	strcpy(f_time,Recoder.Get_member_time());
	cout << "register_music_name: " << f_name << endl;
	cout << "register_music_time: " << f_time << endl;

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
	sprintf(sql,"select * from music where name = '%s';",f_name);
	ret = sqlite3_get_table(ppdb,sql,&result,&row,&column,&errmsg);
	if(ret != SQLITE_OK)
	{
		cout << "sqlite3_exec error 4: " << sqlite3_errmsg(ppdb) << endl;
	}
	else if(row != 0)
		 {
			memset(sql, 0, sizeof(sql));
			sprintf(sql,"delete from music where name = '%s';",f_name);
			ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
			if(ret != SQLITE_OK)
			{
				cout << "sqlite3_exec error 3: " << sqlite3_errmsg(ppdb) << endl;
			}
		 }
	
	sqlite3_free_table(result);

	memset(sql, 0, sizeof(sql));
	sprintf(sql, "insert into music (name, time) values ('%s','%s');", f_name, f_time);
	ret = sqlite3_exec(ppdb, sql, NULL, NULL, NULL);
	if(ret != SQLITE_OK)
	{
		cout << "sqlite3_exec error 4: " << sqlite3_errmsg(ppdb) << endl;
	}

	sqlite3_close(ppdb);
	
}

void Sqlite3_show()
{
	int row,column;
	char *errmsg = NULL;
	char **result;
	int ret;
	char sql[128] = {0};
	
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
		for(int i = 0; i < row + 1; i++)
		{
			for(int j = 0; j < column; j++)
			{
				cout << result[i * column + j] << " ";
			}
			cout << endl;
		}
	}
	
	sqlite3_free_table(result);
	
	sqlite3_close(ppdb);
}
