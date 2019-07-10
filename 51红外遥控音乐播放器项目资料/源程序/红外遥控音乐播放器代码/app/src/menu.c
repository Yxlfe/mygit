#include "bsp.h"
#define  SIZEOFMENU  5
extern unsigned int temp;
unsigned char CurMenuIndex =1; //指向当前菜单编号
unsigned char FirstLine[16]=" 123";
unsigned char SecondLine[16]=" 123";
unsigned char lcdflashflag =1;//菜单刷新命令
//unsigned char IRFLAG =0;   //红外操作的健值 


typedef struct keymenu
{  	
	unsigned char curindex;//当前的菜单编号
	unsigned char keyDNindex;//按下向下按键 进入的编号
	unsigned char keyUPindex;//按下向上按键 进入的编号
	void (*operation)();

} MYMENU;

MYMENU code keytab[SIZEOFMENU] =
{
		 //当前，下，上
		 {0,1,0,dispmenu0},
		 {1,1,0,dispmenu1},

};
//根据红外按键进行 菜单切换
void switch_menu(void)
{
  	switch(IRKEY)
	{
	   case  START :  //向上
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

void  dispmenu0(void) //0号界面
{	
    strcpy(FirstLine , " Temperature ");
	sprintf(SecondLine," T= %4.2f ON",temp*0.0625);
	// 光标闪烁函数
//	setcursorlocation(15,1); //第一行
}

void  dispmenu1(void)
{
    strcpy(FirstLine , " Temperature ");
    sprintf(SecondLine," T= %4.2f OFF",temp*0.0625);

	// 光标闪烁函数
	//setcursorlocation(15,2); //第二行

}

void  fresh(void)  //刷新函数
{	
	if(lcdflashflag ==1)
	{
	 	bsp_LCDDispStr(0,1, FirstLine);
		bsp_LCDDispStr(0,2, SecondLine);
		lcdflashflag =0;


		switch(	CurMenuIndex)
		{
		case 0 :
		setcursorlocation(15,1); //第一行
	    
		break;
		case 1:
		setcursorlocation(15,2); //第一行
		break;  
		}
	}
	
}
