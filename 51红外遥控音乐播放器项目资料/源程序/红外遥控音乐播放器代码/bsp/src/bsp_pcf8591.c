#include "bsp.h"
#define PCF8591ADDR 0X90
#define WR  0X00
#define RD  0X01
//返回0 说明出错
//返回1 说明正常

unsigned char bsp_InitAdc(void)
{
   //1.START
   i2c_Start();

   //2. 地址
   i2c_SendByte(PCF8591ADDR|WR);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //3. 控制寄存器
   i2c_SendByte(0x40);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}

   i2c_Stop(); //说明是正常的 停止i2c
   return 1;
}
unsigned char bsp_SetDac(unsigned char davalue)//davalue 代表 da转换值
{
   //1. start
    i2c_Start();
   //2. 发地址 -wr
   i2c_SendByte(PCF8591ADDR|WR);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //3. 发控制寄存器
   i2c_SendByte(0x40);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //4. 发送需要转换的D值 数据
   i2c_SendByte(davalue);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //5. stop
   i2c_Stop(); //说明是正常的 停止i2c
   return 1;

}
unsigned char bsp_ReadAdc(unsigned char ch)//ch 代表通道
{
    unsigned char re;
	//1. start
	  i2c_Start();
	//2.  发地址 -注意是读
	 i2c_SendByte(PCF8591ADDR|RD);
	 if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
	//3. 读取数据 最后字节 nack
	  re= i2c_ReadByte(); //ad芯片 在发送一个字节
	  i2c_NAck();
	//4. stop
	  i2c_Stop();
	  
	  return re; 
}