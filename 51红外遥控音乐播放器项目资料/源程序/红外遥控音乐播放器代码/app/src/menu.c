#include "bsp.h"
#define  SIZEOFMENU  5
extern unsigned int temp;
unsigned char CurMenuIndex =1; //ָ��ǰ�˵����
unsigned char FirstLine[16]=" 123";
unsigned char SecondLine[16]=" 123";
unsigned char lcdflashflag =1;//�˵�ˢ������
//unsigned char IRFLAG =0;   //��������Ľ�ֵ 


typedef struct keymenu
{  	
	unsigned char curindex;//��ǰ�Ĳ˵����
	unsigned char keyDNindex;//�������°��� ����ı��
	unsigned char keyUPindex;//�������ϰ��� ����ı��
	void (*operation)();

} MYMENU;

MYMENU code keytab[SIZEOFMENU] =
{
		 //��ǰ���£���
		 {0,1,0,dispmenu0},
		 {1,1,0,dispmenu1},

};
//���ݺ��ⰴ������ �˵��л�
void switch_menu(void)
{
  	switch(IRKEY)
	{
	   case  START :  //����
	   CurMenuIndex = keytab[CurMenuIndex].keyUPindex;
	   lcdflashflag = 1;
	   bsp_LcdClr();
	   IRKEY = 0x99;
	   break;
	   case  STOP :
	   CurMenuIndex = keytab[CurMenuIndex].keyDNindex;
	   lcdflashflag = 1;
	   bsp_LcdClr();
	   IRKEY = 0x99;
	   break;
	}
	
	keytab[CurMenuIndex].operation();	
}

void  dispmenu0(void) //0�Ž���
{	
    strcpy(FirstLine , " Temperature ");
	sprintf(SecondLine," T= %4.2f ON",temp*0.0625);
	// �����˸����
//	setcursorlocation(15,1); //��һ��
}

void  dispmenu1(void)
{
    strcpy(FirstLine , " Temperature ");
    sprintf(SecondLine," T= %4.2f OFF",temp*0.0625);

	// �����˸����
	//setcursorlocation(15,2); //�ڶ���

}

void  fresh(void)  //ˢ�º���
{	
	if(lcdflashflag ==1)
	{
	 	bsp_LCDDispStr(0,1, FirstLine);
		bsp_LCDDispStr(0,2, SecondLine);
		lcdflashflag =0;


		switch(	CurMenuIndex)
		{
		case 0 :
		setcursorlocation(15,1); //��һ��
	    
		break;
		case 1:
		setcursorlocation(15,2); //��һ��
		break;  
		}
	}
	
}
