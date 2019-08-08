#include "bsp.h"
#define PCF8591ADDR 0X90
#define WR  0X00
#define RD  0X01
//����0 ˵������
//����1 ˵������

unsigned char bsp_InitAdc(void)
{
   //1.START
   i2c_Start();

   //2. ��ַ
   i2c_SendByte(PCF8591ADDR|WR);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //3. ���ƼĴ���
   i2c_SendByte(0x40);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}

   i2c_Stop(); //˵���������� ֹͣi2c
   return 1;
}
unsigned char bsp_SetDac(unsigned char davalue)//davalue ���� daת��ֵ
{
   //1. start
    i2c_Start();
   //2. ����ַ -wr
   i2c_SendByte(PCF8591ADDR|WR);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //3. �����ƼĴ���
   i2c_SendByte(0x40);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //4. ������Ҫת����Dֵ ����
   i2c_SendByte(davalue);
   if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
   //5. stop
   i2c_Stop(); //˵���������� ֹͣi2c
   return 1;

}
unsigned char bsp_ReadAdc(unsigned char ch)//ch ����ͨ��
{
    unsigned char re;
	//1. start
	  i2c_Start();
	//2.  ����ַ -ע���Ƕ�
	 i2c_SendByte(PCF8591ADDR|RD);
	 if(i2c_WaitAck()!=0){i2c_Stop();return 0;}
	//3. ��ȡ���� ����ֽ� nack
	  re= i2c_ReadByte(); //adоƬ �ڷ���һ���ֽ�
	  i2c_NAck();
	//4. stop
	  i2c_Stop();
	  
	  return re; 
}