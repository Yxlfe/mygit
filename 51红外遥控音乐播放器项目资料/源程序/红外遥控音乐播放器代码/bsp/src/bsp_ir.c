#include "bsp.h"
unsigned char irtime =0 ;//��¼ 256us ���� 
unsigned char irdata[33]={0}; //����ԭʼ������-ʱ��-û�о������� ֻ��ʱ�䳤��
unsigned char startflag =0 ; //��ʾ�ǵ�һ�ν����ж� �ڶ��κ� ֵΪ1
unsigned char fIrRevOk =0; //����һ�ν������
unsigned char IR_CODE[4]={0};
unsigned char IRKEY   = 0x99;
void  ISR_INT0(void) interrupt 	0	  
{
   static unsigned char index =0; //static --ֻ��ʼ��һ�� ������ȫ�ֱ���
   if(startflag ==0)
   {
	  startflag =1 ;
	  irtime =0;
   }
   else //��N�� ���� 
   {
	  //�ж� ��û�г��������� --�ǳ���Ҫ -����
	  if((irtime>30)&&(irtime<60))
	  {
		 index =0;
	  }
	  irdata[index++] = irtime; //ʱ��
	  irtime =0;
	  if(index ==33) //һ�ν������
	  {
		index =0 ;
		irtime =0;
		startflag =0;
		fIrRevOk =1;
	  }
   }
}


void ISR_Timer0(void) interrupt  1	//T0 -65536*12/11.0592us --�Զ���irtime+1
{
	irtime++;
}
//idrdata[1] ~irdata[32]
void bsp_IrDecode(void)
{
	 unsigned char i,j,k;
	 unsigned char value=0;
	 k=1;
	 for(i=0;i<4;i++) //4���ֽ�
	 {
		for(j=0;j<8;j++)//8λ
		{
		   value >>= 1;
		   if( irdata[k]>7) //����=1
		   {
			  value |= 0x80;
		   }
		   k++;
		}

		IR_CODE[i] = value;
		value =0;
	 }
}

void bsp_IrFunc(void)
{
  	 if(fIrRevOk ==1)  //���յ�������33������ λ
	  {
		 fIrRevOk =0;
		 bsp_IrDecode(); //�������		 															   
	  }
	  switch(IR_CODE[2])
	  {
	  	case 0x40 : IRKEY = UP ;break;
		case 0x19 : IRKEY = DOWN ;break;
		case 0x7 : IRKEY = LEFT ;break;
		case 0x9 : IRKEY = RIGHT ;break;

		case 0x15 : IRKEY = SURE ;break;
		case 0x43 : IRKEY = CANCEL ;break;
	  	case 0x47 : IRKEY = PLAY ;break;
		case 0x45 : IRKEY = STOP ;break;
		case 0x0d : IRKEY = PAUSE ;break;

		case 0x16 : IRKEY = ZERO ;break;
		case 0x0c : IRKEY = ONE ;break;
		case 0x18 : IRKEY = TWO ;break;
		case 0x5e : IRKEY = THREE ;break;
		case 0x8  : IRKEY = FOUR ;break;
		case 0x1c : IRKEY = FIVE ;break;
		case 0x5a : IRKEY = SIX ;break;
		case 0x42 : IRKEY = SEVEN ;break;
		case 0x52 : IRKEY = EIGHT ;break;
		case 0x4a : IRKEY = NINE ;break;

		default : IRKEY = 0X99;break;
	  }
	  IR_CODE[2] =0x00;
}