#ifndef MUSIC_SRC_H
#define MUSIC_SRC_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <list>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <signal.h>
#include <sqlite3.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#define SIZE 1024
using namespace std;

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO(Linux specific) */
};

enum Menue_Flag
{
	Music_list = 1,
	Start,
	Stop,
	Continue,
	Pause,
	Last_music,
	Next_music,
	Sequential_Play,
	Rand_Play,
	Signel_Play,
	Sound_add,
	Sound_reduce,
	Music_play_list
};
typedef Menue_Flag MFlag;

class Menue
{
	public:
		Menue();
		Menue& operator=(const Menue& obj);
		void Set_member();
		int Get_member();
		void Signal_send();
	private:
		int m_flag;
};

class Sql_recoder
{
	public:
		Sql_recoder();
		Sql_recoder(const Sql_recoder& obj);
		void Set_member(char* name,char* time);
		char* Get_member_name();
		char* Get_member_time();
	private:
		char m_name[32];
		char m_time[32];
};

class Share
{
	public:
		Share();
		Share& operator= (const Share& obj);
		int Get_member_local();
		int Get_member_end();
		int Get_member_start();
		void Set_member_start(int start);
		void Set_member_end(int end);
		void Set_member_local(int local);
	private:
		int m_end;
		int m_start;
		int m_local;

};

extern int fd[SIZE];
extern int sockfd;
extern pthread_t tid_server_socket;

sqlite3* ppdb;//数据库标识符
Menue m_menue;
key_t key;
pid_t pid1;
pid_t pid2;
pid_t pid3;
int shmid;
int semid;
const int shmsize = 4096;
void* shmaddr = NULL;

const char* Music_path = "/home/Mymusic";
list<char*> File_name;
char str_result[32] = {0}; 



void Sound_change(int sound_flag);
char* Sound_get();
void My_system(const char * cmd); 
int Rand_get_num(int max);
void Shmaddr_set_local(int local);
void Shmaddr_set_start(int flag);
void Shmaddr_set_end(int flag);
void Sqlite3_register();
void Sqlite3_insert(Sql_recoder Recoder);
void Sqlite3_show();
void Server_insert(Sql_recoder Recoder);
char* Get_playing_music(int local);
void Signal_grandchild_register();
void Signal_child_register();
void Music_function(int argc);
void Handel(int argc);
void Show_Main_Menue();
void Read_Filename();
void sem_p(int semid);
void sem_v(int semid);
void IPC_init();
void Fork1();
void Fork2();
void Menue_choose();
void Ctrl_C(int temp);
void Show_Musiclist();
void List_insert(char* name);
#endif
