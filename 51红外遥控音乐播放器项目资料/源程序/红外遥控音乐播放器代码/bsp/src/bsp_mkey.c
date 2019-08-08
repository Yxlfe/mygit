#include "bsp.h"
#define  MKEYPORT   P0

unsigned char bsp_MKeyScan(void)
{
	unsigned char kvalue =0xff;
	MKEYPORT = 0xf0;  //1111 0000
	if(	  MKEYPORT != 0xf0)	//确定 矩阵键盘有按键按下
	{
	   //1. 第一行
		MKEYPORT = 0xfe; //1111 1110
		if(	 MKEYPORT != 0xfe)//按键 在第一行
		{
			kvalue = MKEYPORT;
			//消抖  延时 死等释放按键
			while(MKEYPORT !=0xfe);
			delay_ms(5);
		}
	   //1. 第二行
		MKEYPORT = 0xfd; //1111 1110
		if(	 MKEYPORT != 0xfd)//按键 在第一行
		{
			kvalue = MKEYPORT;
			//消抖  延时 死等释放按键
			while(MKEYPORT !=0xfd);
			delay_ms(5);
		}
		//1. 第三行
		MKEYPORT = 0xfb; //1111 1110
		if(	 MKEYPORT != 0xfb)//按键 在第一行
		{
			kvalue = MKEYPORT;
			//消抖  延时 死等释放按键
			while(MKEYPORT !=0xfb);
			delay_ms(5);
		}
		//1. 第一行
		MKEYPORT = 0xf7; //1111 1110
		if(	 MKEYPORT != 0xf7)//按键 在第一行
		{
			kvalue = MKEYPORT;
			//消抖  延时 死等释放按键
			while(MKEYPORT !=0xf7);
				delay_ms(5);
		}
	}
      return kvalue;
}
unsigned char  bsp_Mkeyproc(unsigned char scanvalue)
{
	  unsigned char keyre=0x99;
	  switch(scanvalue)
	  {
		case 0x7e : keyre = 1;break;
		case 0xbe : keyre = 2;break;
		case 0xde : keyre = 3;break;
		case 0xee : keyre = 10;break;  //10 +

		case 0x7d : keyre = 4;break;
		case 0xbd : keyre = 5;break;
		case 0xdd : keyre = 6;break;
		case 0xed : keyre = 11;break;	  //11 -

		case 0x7b : keyre = 7;break;
		case 0xbb : keyre = 8;break;
		case 0xdb : keyre = 9;break;
		case 0xeb : keyre = 12;break;	 //12 *

		case 0x77 : keyre = 0;break;
		case 0xb7 : keyre = 15;break;	// 15 rst
		case 0xd7 : keyre = 14;break;	// 14  =
		case 0xe7 : keyre = 13;break;   //13 /
		default: keyre =0x99;break;
	  }
	  return  keyre;

}