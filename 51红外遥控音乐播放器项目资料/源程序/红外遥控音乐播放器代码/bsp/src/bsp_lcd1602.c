#include "bsp.h"
#define LCDPORT  P0
sbit  RS = P2^4;
sbit  RW = P2^5;
sbit  EN = P2^6;

void bsp_LCDInit(void)
{
	//延时15mS
	delay_ms(15);
	//写指令38H（不检测忙信号）
	bsp_LCDCommand(0x38);
	//延时5mS
	delay_ms(5);
	//写指令38H（不检测忙信号）
	bsp_LCDCommand(0x38);
	//延时5mS
	delay_ms(5);
	//写指令38H（不检测忙信号）
	bsp_LCDCommand(0x38);
	//以后每次写指令、读/写数据操作均需要检测忙信号
	delay_ms(5);
	bsp_LCDCommand(0x38);
	//写指令38H：显示模式设置
	delay_ms(5);
	bsp_LCDCommand(0x08);
	//写指令08H：显示关闭
	delay_ms(5);
	bsp_LCDCommand(0x01);
	//写指令01H：显示清屏
	delay_ms(5);
	bsp_LCDCommand(0x06);
	//写指令06H：显示光标移动设置
	delay_ms(5);
	bsp_LCDCommand(0x0c);
	//写指令0CH：显示开及光标设置

	 
}

void bsp_LCDCommand(unsigned char cmd)
{
  	delay_ms(5);
	RS = 0;
	RW = 0;
	LCDPORT= cmd;
	EN = 1;
	_nop_();   //1us
	EN = 0; 

}
void bsp_LCDData(unsigned char dat)
{
  	delay_ms(5);
	RS = 1;
	RW = 0;
	LCDPORT= dat;
	EN = 1;
	_nop_();
	EN = 0; 
}
//x代表横坐标  16个位置 从左到右 0-15
//y 行 1-第一行  2 第二行
//
/*void bsp_LCDDispChar(unsigned char x,unsigned char y, unsigned char s)
{
   if(y==1)	 //第一行
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   bsp_LCDData(s);	   //  bsp_LCDData(0)
}*/
void bsp_LCDDispStr(unsigned char x,unsigned char y, unsigned char *s)
{
   if(y==1)	 //第一行
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   while(*s)
   {
   	  bsp_LCDData(*s); //地址是自动+1
	  s++; 
   }  
}


/*void bsp_LCDFillCGRAM(void)   //把设计的字符 送到液晶屏 便于显示
{	 
	unsigned char i;
	 bsp_LCDCommand(0x40);//地址自动+1
	 for(i=0;i<64;i++)
	 {
	 	bsp_LCDData(mycgram[i]);
	 }
}*/

/*void bsp_LCDDispCGRAM(unsigned char x,unsigned char y, unsigned char index)
//index 就是0-7  对应自己设计的8个特殊字符
{
   	if(y==1)	 //第一行
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   bsp_LCDData(index);	   //  bsp_LCDData(0)
}*/

void setcursorlocation(unsigned char x,unsigned char y)
{
   if(y==1)	 //第一行
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   //	bsp_LCDCommand(0x0f);

   	bsp_LCDData(0x7f);
//	bsp_LCDData('a');
}

void bsp_LcdClr(void)
{
   bsp_LCDCommand(0x01);
}