#ifndef _TCP_HEAD_H
#define _TCP_HEAD_H

#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sqlite3.h>
#include <list>
#define PORT 4444
#define SIZE 1024

using namespace std;

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
	Music_play_list,
	Music_choose
};

class Recv_info
{
	public:
		Recv_info();
		~Recv_info();
		Recv_info(const Recv_info& obj);
		char* Get_member_name();
		int Get_member_flag();

	private:
		char m_name[32];
		int m_flag;
};
typedef class Recv_info RecvInfo;

class Send_info
{
	public:
		Send_info();
		~Send_info();
		Send_info(const Send_info& obj);
		void Set_member_name(char* name);
		void Set_member_time(char* time);
		void Set_member_flag(int flag);

	private:
		char m_name[32];
		char m_time[32];
		int m_flag;
};
typedef class Send_info SendInfo;

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

int fd[SIZE]= {0};
fd_set readfd;

int clientcount;
int sockfd;

extern sqlite3* ppdb;//数据库标识符
extern int shmid;
extern void* shmaddr;
extern pid_t pid1;
extern void Shmaddr_set_local(int local);
extern void Shmaddr_set_start(int flag);
extern void Shmaddr_set_end(int flag);
extern void Sound_change(int sound_flag);

extern list<char*> File_name;

struct sockaddr_in server_addr;//存放服务器绑定需要的协议族、端口号、IP地址
struct sockaddr_in client_addr;//存放连接到服务器的客户端的协议族、端口号、IP地址
pthread_t tid_server_socket;

void Music_choose_play(RecvInfo Info);
void Send_sql_history(int fd);
void Send_file_name(int fd);
void* TCP_connect(void* arg);//创建TCP连接的线程回调函数
void TCP_socket_create();//创建TCP连接的线程
void recvhand(int* arg);//接收客户端发送的信息
void Serveraccept();//接受客户端建立连接的请求
#endif
