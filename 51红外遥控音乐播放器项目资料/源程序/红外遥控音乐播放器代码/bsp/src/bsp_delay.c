#include "bsp.h"


void delay_us(unsigned char t) //2t+5 //t=1 Êµ²â15us
{
		while(--t);
	
}

void delay_ms(unsigned char t) // Ìît£¬¼´tms t=1Êµ²â1.1ms
{
		while(t--)
		{
			delay_us(245);
			delay_us(245);
		}
}


