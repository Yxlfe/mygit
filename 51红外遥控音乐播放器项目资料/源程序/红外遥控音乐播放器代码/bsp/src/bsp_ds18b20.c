#include "bsp.h"
sbit DQ =P1^0;


void Init_DS18B20(void)
{
//1.DQ拉低
	DQ = 0;
//2.延时480us
    Delay480us();
//3.DQ拉高 --主机释放
    DQ = 1;
//4.延时60us
    Delay60us();
//5.判断ds18b20的应答信号(DQ==0)
    if(DQ ==0)
	{
//6.延时 480us
     Delay480us();
//7. 释放总线 DQ=1
	 DQ = 1;
    }
 
}

/******************************************************************/
/*                    读一个字节  ， 低位开始                     */
/******************************************************************/
unsigned char ReadOneByte(void)
{
   unsigned char i;
   unsigned char value=0;
   for(i=0;i<8;i++)
   {
		//1. 读下一位(右移)，数据先读低位，注意和IIC的区别
		   value >>=1; //?参考iic 底层
		//2. DQ拉低
		   DQ = 0;
		//3. 保持1us
		  _nop_();
		  _nop_();
		//4. DQ拉高(释放)
		  DQ = 1;
		//5. 延时7us，到达采样点（小于15us）
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		
		//6. 读取DQ
		  if(DQ ==1)
		  {
		     value |= 0x80;//收最低位 放最高位
		  }
		//7. 延时60us
		   Delay60us();
   }
//8. 完成8位后，返回读取值
   return value;
}

/******************************************************************/
/*                 写一个字节    先写低位                         */
/******************************************************************/
void WriteOneByte(unsigned char dat)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
		//1. DQ拉低
			DQ =0;
			_nop_();
			_nop_();
			_nop_();
		//2. 写对应值(15us内),从机进行采样 --xian
		   if(dat&0x01)
		   {
			  DQ = 1;
		   }
		   else
		   {
			  DQ =0;
		   }
		//3. 延时60us
		   Delay60us();
		//4. DQ 拉高
		   DQ = 1;
		//5. 写下一位(右移)，数据先写低位，注意和IIC的区别
		   dat >>=1;

  }
      
}

/******************************************************************/
/*                   读取温度                                     */
/******************************************************************/
unsigned int ReadTemperature(void)
{
  	unsigned int a,b,t;
	Init_DS18B20();
	WriteOneByte(0xCC); 
	WriteOneByte(0x44); 
	delay_ms(100);
	Init_DS18B20();
	WriteOneByte(0xCC); 
	WriteOneByte(0xBE);
	a= ReadOneByte();//低字节
	b= ReadOneByte();//高字节
	b=b<<8;
	t= a+b;
	return t;
}

