#include "bsp.h"


void delay_us(unsigned char t) //2t+5 //t=1 ʵ��15us
{
		while(--t);
	
}

void delay_ms(unsigned char t) // ��t����tms t=1ʵ��1.1ms
{
		while(t--)
		{
			delay_us(245);
			delay_us(245);
		}
}


