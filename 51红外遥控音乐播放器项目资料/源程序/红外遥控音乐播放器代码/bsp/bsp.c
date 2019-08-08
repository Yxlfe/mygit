#include "bsp.h"

void bsp_init(void)//所有外设的初始化函数
{
    delay_ms(100);
	
	//定时器初始化	  	
	bsp_InitTimer0();  //记录时间 用于记录 红外信号的一位持续的时间
	bsp_InitSerial();//串口时钟初始化
	bsp_initInt0();	  //红外信号进来的中断
	bsp_LCDInit();
}