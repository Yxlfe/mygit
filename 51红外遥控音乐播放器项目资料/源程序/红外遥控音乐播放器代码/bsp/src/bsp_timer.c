#include "bsp.h"								   
//sbit SPK= P0^7;
//#define FOSC  11059200	//11.0592M 12M �Լ����� 12000000
//#define TXMS 65536-FOSC/12/1000   //1MS ��ʱ�� ��ʼֵ
//unsigned int  count=0;
//unsigned char hour=10,min=1,sec=1; //����ֻ��һ�� 
//unsigned char ahour=10,amin=1,asec=55;
void bsp_InitTimer0(void)
{
	TMOD |= 0X02; //ģʽ2 �Զ���װ
	TH0 = 0;
	TL0 = 0;
	ET0 =1;
	TR0 =1;	

}
