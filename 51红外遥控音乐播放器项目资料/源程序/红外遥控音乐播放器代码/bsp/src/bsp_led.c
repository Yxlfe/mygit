#include "bsp.h"
#define LEDPORT P1
unsigned temp ;
void bsp_ledOn(void)
{
	LEDPORT = 0xff;	//1111 1111
}
void bsp_ledOff(void)
{
	 LEDPORT = 0x00; //0000 0000
}
//流水灯 硬件电路 是 0 亮  1 灭
// 0111_1111 -> 1011_1111-> 1101 1111
// >>  << 操作
//dir :方向 0 ==》右移   非零 左移
void bsp_ledblink(unsigned char dir)//dir 方向
{
  	static unsigned char i=0;
	
	if(i==0)  //第一次
	{
	   if(dir ==0)
	   temp= 0x7f;// 0111 1111
	   else 
	   temp = 0xfe; // 1111 1110
	}
	if(i>0)
	{
	  if(dir ==0)
	  temp =temp>>1|0x80;    // 0011 1111 | 1000 0000
	  else
	  temp =temp<<1|0x01;	  // 1111 1100 | 0000 0001
	}
	i++;
	if(i==8) i=0;
	LEDPORT = temp;	//
}