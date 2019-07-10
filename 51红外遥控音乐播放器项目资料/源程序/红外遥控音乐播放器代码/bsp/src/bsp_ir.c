#include "bsp.h"
unsigned char irtime =0 ;//记录 256us 次数 
unsigned char irdata[33]={0}; //红外原始的数据-时长-没有经过译码 只是时间长度
unsigned char startflag =0 ; //表示是第一次进入中断 第二次后 值为1
unsigned char fIrRevOk =0; //代表一次接收完成
unsigned char IR_CODE[4]={0};
unsigned char IRKEY   = 0x99;
void  ISR_INT0(void) interrupt 	0	  
{
   static unsigned char index =0; //static --只初始化一次 类似于全局变量
   if(startflag ==0)
   {
	  startflag =1 ;
	  irtime =0;
   }
   else //第N次 进来 
   {
	  //判断 有没有出现引导码 --非常重要 -必须
	  if((irtime>30)&&(irtime<60))
	  {
		 index =0;
	  }
	  irdata[index++] = irtime; //时长
	  irtime =0;
	  if(index ==33) //一次接收完成
	  {
		index =0 ;
		irtime =0;
		startflag =0;
		fIrRevOk =1;
	  }
   }
}


void ISR_Timer0(void) interrupt  1	//T0 -65536*12/11.0592us --自动将irtime+1
{
	irtime++;
}
//idrdata[1] ~irdata[32]
void bsp_IrDecode(void)
{
	 unsigned char i,j,k;
	 unsigned char value=0;
	 k=1;
	 for(i=0;i<4;i++) //4个字节
	 {
		for(j=0;j<8;j++)//8位
		{
		   value >>= 1;
		   if( irdata[k]>7) //变量=1
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
  	 if(fIrRevOk ==1)  //接收到完整的33个数据 位
	  {
		 fIrRevOk =0;
		 bsp_IrDecode(); //红外解码		 															   
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