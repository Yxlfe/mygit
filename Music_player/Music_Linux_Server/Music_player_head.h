#ifndef _HEAD_H
#define _HEAD_H
#include <iostream>
#include <signal.h>
using namespace std;

extern void IPC_init();
extern void Fork1();
extern void Read_Filename();
extern void Ctrl_C(int temp);
extern void Sqlite3_register();
extern void TCP_socket_create();//创建TCP连接的线程
#endif

