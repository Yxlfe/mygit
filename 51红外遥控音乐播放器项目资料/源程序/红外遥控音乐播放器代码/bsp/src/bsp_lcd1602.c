#include "bsp.h"
#define LCDPORT  P0
sbit  RS = P2^4;
sbit  RW = P2^5;
sbit  EN = P2^6;

void bsp_LCDInit(void)
{
	//��ʱ15mS
	delay_ms(15);
	//дָ��38H�������æ�źţ�
	bsp_LCDCommand(0x38);
	//��ʱ5mS
	delay_ms(5);
	//дָ��38H�������æ�źţ�
	bsp_LCDCommand(0x38);
	//��ʱ5mS
	delay_ms(5);
	//дָ��38H�������æ�źţ�
	bsp_LCDCommand(0x38);
	//�Ժ�ÿ��дָ���/д���ݲ�������Ҫ���æ�ź�
	delay_ms(5);
	bsp_LCDCommand(0x38);
	//дָ��38H����ʾģʽ����
	delay_ms(5);
	bsp_LCDCommand(0x08);
	//дָ��08H����ʾ�ر�
	delay_ms(5);
	bsp_LCDCommand(0x01);
	//дָ��01H����ʾ����
	delay_ms(5);
	bsp_LCDCommand(0x06);
	//дָ��06H����ʾ����ƶ�����
	delay_ms(5);
	bsp_LCDCommand(0x0c);
	//дָ��0CH����ʾ�����������

	 
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
//x���������  16��λ�� ������ 0-15
//y �� 1-��һ��  2 �ڶ���
//
/*void bsp_LCDDispChar(unsigned char x,unsigned char y, unsigned char s)
{
   if(y==1)	 //��һ��
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   bsp_LCDData(s);	   //  bsp_LCDData(0)
}*/
void bsp_LCDDispStr(unsigned char x,unsigned char y, unsigned char *s)
{
   if(y==1)	 //��һ��
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   while(*s)
   {
   	  bsp_LCDData(*s); //��ַ���Զ�+1
	  s++; 
   }  
}


/*void bsp_LCDFillCGRAM(void)   //����Ƶ��ַ� �͵�Һ���� ������ʾ
{	 
	unsigned char i;
	 bsp_LCDCommand(0x40);//��ַ�Զ�+1
	 for(i=0;i<64;i++)
	 {
	 	bsp_LCDData(mycgram[i]);
	 }
}*/

/*void bsp_LCDDispCGRAM(unsigned char x,unsigned char y, unsigned char index)
//index ����0-7  ��Ӧ�Լ���Ƶ�8�������ַ�
{
   	if(y==1)	 //��һ��
   	  bsp_LCDCommand(0x80+x); 
   else
      bsp_LCDCommand(0xc0+x);
   bsp_LCDData(index);	   //  bsp_LCDData(0)
}*/

void setcursorlocation(unsigned char x,unsigned char y)
{
   if(y==1)	 //��һ��
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