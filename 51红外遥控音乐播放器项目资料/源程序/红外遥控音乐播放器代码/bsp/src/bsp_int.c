#include "bsp.h"
unsigned char intvalue=0;
void bsp_initInt0(void) //初始化 INT0
{
  //1. 确定触发电平
    IT0 = 1; //边沿触发
  //2. 打开中断开关
    EX0 = 1; 
	EA = 1;
}
