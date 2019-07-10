#ifndef _SERVER_H
#define _SERVER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <pthread.h>
#include <signal.h>
#include <sqlite3.h>
#include <errno.h>
#include <sys/epoll.h>
#include "threadpool.h"
#define PORT 4444
#define MAXCLIENT 1000
#define FAILURE 10000
#define SUCCESS 10001
#define EPOLL_SIZE 1024 

struct sockaddr_in server_addr;//存放服务器绑定需要的协议族、端口号、IP地址
struct sockaddr_in client_addr;//存放连接到服务器的客户端的协议族、端口号、IP地址
struct epoll_event events[EPOLL_SIZE];//存放某一时刻内核事件表中就绪的事件

sqlite3 *ppdb;//数据库标识符

pthread_t tid;//接收线程的线程标识符

int clientcount;
int epfd;//epoll句柄，红黑树根结点
int pthread_exit_flag;//服务器退出时通知所有客户端处理线程退出的标志位
int fd3;//文件标识符
int sockfd;//代表服务器与客户端连接通道的套接字

//标志位(不同的功能和服务器反馈对应不同的标志位)
enum flag
{
	Register = 1,
	Login,
	ChangePassword,
	Traverse,
	Pc,
	Gc,
	LogoffOther,
	Forbidden,
	CancelForbidden,
	File,
	OtherLogoff,
	OtherLogin,
	AllOtherLogoff,
	AllOtherLogin,
	LoginSuccess,
	LoginFailure,
	MChat,
	CanChat,
	NotCanChat,
	PcSuccess,
	GcSuccess,
	MVIP,
	VIP,
	NVIP,
	ForbidSuccess,
	CancelForbidSuccess,
	LogoffOtherSuccess,
	SendFileName,
	FileTransfer,
	RecvFile,
	RecvFileName,
	ServerClose,
};
typedef enum flag FLAG;

//服务器与客户端之间用来传输信息的结构体类型
struct info
{
	char text[128];
	char account[128];
	char password[128];
	char oldpassword[128];
	char ID[128];
	char file[128];
	char time[128];
	FLAG Flag;
};
typedef struct info INFO;

//存储用户状态的结构体类型
struct con
{
	int ChatCon;
	int LoginCon;
	int VIPCon;
};
typedef struct con CON;

//存储在线用户信息的结构体类型(单链表的节点)
struct client
{
	CON Con;
	int fromsockfd;
	INFO Info;
	struct client *next;
};
typedef struct client CLIENT;

CLIENT *List;//存储登录用户信息的链表

void Stopserver(int num);//退出服务器
int Sqlite3_admin();//数据库输入一个管理员帐户、密码和ID
int List_init();//初始化在线链表
int List_insert(INFO Insert, int fd);//把登录的帐户信息插入在线链表
int List_travellogin(INFO Travel);//查询指定的帐户是否在线
int Server_mgc();//查询是否有人在线
int Server_gc(INFO Info, int fd);//群聊功能
int Server_mchat(INFO Info,int fd);//识别指定用户是否被禁言
int Server_pc(INFO Info,int fd);//私聊功能
int Server_register(INFO Info, int fd);//注册功能(查询数据库中的信息)
int Server_login(INFO Info, int fd);//登录功能(查询数据库中的信息)
int Server_changepassword(INFO Info, int fd);//修改密码功能
int Server_logoffself(int fd);//下线功能
int Server_logoffother(INFO Info,int fd);//将指定用户踢出聊天室(强制下线)
int Server_forbidden(INFO Info,int fd);//禁言功能
int Server_cancel_forbidden(INFO Info,int fd);//解禁功能
int Server_sendfilename(INFO Info, int fd);//发送文件名
int Server_file(INFO Info, int fd);//发送文件内容
int Server_mVIP(INFO Info,int fd);//识别指定用户是不是管理员用户
int Server_traverse(int fd);//查询所有在线用户的帐号和ID
void *recvhand(void *arg);//接收客户端发送的信息
void Serveraccept();//接受客户端建立连接的请求
void addfd(int epollfd, int fd);//添加新的客户端到内核事件列表
int setnonblocking(int sockfd);//设置文件流为非堵塞
#endif
