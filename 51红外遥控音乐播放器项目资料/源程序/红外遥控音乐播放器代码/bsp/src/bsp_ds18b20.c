#include "bsp.h"
sbit DQ =P1^0;


void Init_DS18B20(void)
{
//1.DQ����
	DQ = 0;
//2.��ʱ480us
    Delay480us();
//3.DQ���� --�����ͷ�
    DQ = 1;
//4.��ʱ60us
    Delay60us();
//5.�ж�ds18b20��Ӧ���ź�(DQ==0)
    if(DQ ==0)
	{
//6.��ʱ 480us
     Delay480us();
//7. �ͷ����� DQ=1
	 DQ = 1;
    }
 
}

/******************************************************************/
/*                    ��һ���ֽ�  �� ��λ��ʼ                     */
/******************************************************************/
unsigned char ReadOneByte(void)
{
   unsigned char i;
   unsigned char value=0;
   for(i=0;i<8;i++)
   {
		//1. ����һλ(����)�������ȶ���λ��ע���IIC������
		   value >>=1; //?�ο�iic �ײ�
		//2. DQ����
		   DQ = 0;
		//3. ����1us
		  _nop_();
		  _nop_();
		//4. DQ����(�ͷ�)
		  DQ = 1;
		//5. ��ʱ7us����������㣨С��15us��
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		  _nop_();
		
		//6. ��ȡDQ
		  if(DQ ==1)
		  {
		     value |= 0x80;//�����λ �����λ
		  }
		//7. ��ʱ60us
		   Delay60us();
   }
//8. ���8λ�󣬷��ض�ȡֵ
   return value;
}

/******************************************************************/
/*                 дһ���ֽ�    ��д��λ                         */
/******************************************************************/
void WriteOneByte(unsigned char dat)
{
  unsigned char i;
  for(i=0;i<8;i++)
  {
		//1. DQ����
			DQ =0;
			_nop_();
			_nop_();
			_nop_();
		//2. д��Ӧֵ(15us��),�ӻ����в��� --xian
		   if(dat&0x01)
		   {
			  DQ = 1;
		   }
		   else
		   {
			  DQ =0;
		   }
		//3. ��ʱ60us
		   Delay60us();
		//4. DQ ����
		   DQ = 1;
		//5. д��һλ(����)��������д��λ��ע���IIC������
		   dat >>=1;

  }
      
}

/******************************************************************/
/*                   ��ȡ�¶�                                     */
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
	a= ReadOneByte();//���ֽ�
	b= ReadOneByte();//���ֽ�
	b=b<<8;
	t= a+b;
	return t;
}

