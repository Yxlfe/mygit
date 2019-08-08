#ifndef _CLIENT_H
#define _CLIENT_H
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <semaphore.h>
#define FAILURE 10000
#define SUCCESS 10001
#define PORT 4444

//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
//pthread_mutex_t lock;
//pthread_cond_t cond;
//sem_t sem;


int sockfd;//代表服务器与客户端发送与接受数据通道的套接字

int fd1,fd2,fd4;//文件标识符

pthread_t tid_recv;//接收信息的线程标识符

struct sockaddr_in server_addr;//存放服务器绑定需要的协议族、端口号、IP地址

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

FLAG FFlag;

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

INFO Send;//保存发送信息
INFO Recv;//保存接受信息
INFO Login_Account;//保存登录帐户信息

void *RecvThread(void *arg);//接收信息
void Stopclient(int num);//退出客户端
int getch();//及时获取输入的密码(字符)
void Password(char *pd);//即时转换输入的密码(字符)为*,结束输入后转化为字符串
void ClientRegister();//注册输入帐户,密码和ID
void ClientLogin();//登录输入帐户和密码
void ClientChangePassword();//修改密码输入帐户，旧密码，新密码
int SendClient(int sockfd);//发送结构体(帐号,密码,ID,文本,文件名,标志位)
void Welcome();//欢迎界面
void Loginmenue();//注册、登录界面
void menue();//用户功能界面
#endif
