#include "bsp.h"

#define  SIZEOFMENU  9
unsigned char Anum[4]={0};
unsigned char Bnum[4]={0};
unsigned char Asum=0;
unsigned char Bsum=0;
unsigned char a=0;
unsigned char b=0;
unsigned char CurMenuIndex =0; //指向当前菜单编号
unsigned char FirstLine[16]=" 123";
unsigned char SecondLine[16]=" 123";
unsigned char lcdflashflag =1;//菜单刷新命令
//unsigned char IRFLAG =0;   //红外操作的健值 


typedef struct keymenu
{  	
	unsigned char curindex;//当前的菜单编号
	unsigned char UPindex;//按下向上按键 进入的编号
	unsigned char DNindex;//按下向下按键 进入的编号
	unsigned char SUREindex;//按下回车按键 进入的编号
	unsigned char CANCELindex;//按下返回按键 进入的编号
	void (*operation)();

} MYMENU;

MYMENU code keytab[SIZEOFMENU] =
{
		 //当前，上，下，确定，返回
		 {0,0,1,2,0,dispmenu0},//模式选择界面1
		 {1,0,1,3,1,dispmenu1},//模式选择界面2
		 {2,2,4,5,0,dispmenu2},//播放模式选择界面1(选择特定曲目)
		 {3,3,3,3,1,dispmenu3},//输入选择音量大小数字界面
		 {4,2,4,6,0,dispmenu4},//播放模式选择界面2(全部循环播放)
		 {5,5,5,5,2,dispmenu5},//输入选择歌曲序号数字界面
		 {6,6,6,6,4,dispmenu6},//界面：Circle Playing!
};

//根据红外按键进行 菜单切换
void switch_menu(void)
{
  	switch(IRKEY)
	{
	   case PLAY://播放
	   {
	   	 Music_play();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case STOP://播放上一首
	   {
	   	 Music_stop();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case PAUSE://暂停
	   {
	   	 Music_pause();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case LEFT://播放上一首
	   {
	   	 Last_Play();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case RIGHT://播放下一首
	   {
	   	 Next_Play();
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 IRKEY=0X99;
		 break;
	   }

	   case  UP :  //向上
	   {
	   	CurMenuIndex = keytab[CurMenuIndex].UPindex;
	   	lcdflashflag = 1;
	   	bsp_LcdClr();
	   	IRKEY = 0x99;
	   	break;
	   }

	   case  DOWN :
	   {
	   	CurMenuIndex = keytab[CurMenuIndex].DNindex;
	   	lcdflashflag = 1;
	   	bsp_LcdClr();
	   	IRKEY = 0x99;
	   	break;
	   }

	   case  SURE :
	   {
	   	if(CurMenuIndex==4)
		{
			Cycle_play();		
		}
	   	else
	   		if(CurMenuIndex==5)
			{
				Asum = Anum[0] * 10 + Anum[1];
				Specify_Musi_Play(Asum);
				a = Asum = Anum[0] = Anum[1] = Anum[2]=0;	
			}
			else
				if(CurMenuIndex==3)
				{
					Bsum = Bnum[0] * 10 + Bnum[1];
					Specify_Volume(Bsum);
					b = Bsum = Bnum[0] = Bnum[1] = Bnum[2] = 0;	
				}
		CurMenuIndex = keytab[CurMenuIndex].SUREindex;
	   	lcdflashflag = 1;
	   	bsp_LcdClr();
	   	IRKEY = 0x99;
	   	break;
	   }

	   case  CANCEL :
	   {
	    if(CurMenuIndex==5)
		{
			a = Asum = Anum[0] = Anum[1] = Anum[2] = 0;	
		}
		else
			if(CurMenuIndex==3)
			{
				b = Bsum = Bnum[0] = Bnum[1] = Bnum[2] = 0;		
			}
	   	CurMenuIndex = keytab[CurMenuIndex].CANCELindex;
	   	lcdflashflag = 1;
	   	bsp_LcdClr();
	   	IRKEY = 0x99;
	   	break;
	   }
	
	   case ZERO://输入0
	   {
		if(CurMenuIndex==5)
	   	{
			Anum[a++]=0;
		 	if(a>2)
		 	{	
		 		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=0;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case ONE://输入1
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=1;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=1;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case TWO://输入2
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=2;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=2;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case THREE://输入3
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=3;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=3;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case FOUR://输入4
	   {
		if(CurMenuIndex==5)
	   	{
			Anum[a++]=4;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=4;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case FIVE://输入5
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=5;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=5;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case SIX://输入6
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=6;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=6;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case SEVEN://输入7
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=7;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=7;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case EIGHT://输入8
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=8;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=8;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	   case NINE://输入9
	   {
		if(CurMenuIndex==5)
	   	{
		 	Anum[a++]=9;
			if(a>2)
		 	{
		  		Anum[0] = Anum[1];
				Anum[1] = Anum[2];
		  		a=2;
		 	}
		}
		else
		 	if(CurMenuIndex==3)
		 	{
				Bnum[b++]=9;
				if(b>2)
				{
					Bnum[0] = Bnum[1];
					Bnum[1] = Bnum[2];
					b=2;
				}
		 	}
		lcdflashflag = 1;
	   	bsp_LcdClr();
		IRKEY=0X99;
		break;
	   }

	}
	
	keytab[CurMenuIndex].operation();	
}

void  dispmenu0(void) //0号界面
{
    strcpy(FirstLine , " PLAY MODEL ");
	strcpy(SecondLine ," SOUND SET ");
}

void  dispmenu1(void)
{
    strcpy(FirstLine , " PLAY MODEL ");
	strcpy(SecondLine ," SOUND SET ");
}

void  dispmenu2(void)
{
	strcpy(FirstLine , " Spe Play ");
	strcpy(SecondLine ," Cir Play ");
}

void  dispmenu3(void)
{
   	strcpy(FirstLine , " Input S Num: ");
	sprintf(SecondLine," %d%d",(unsigned int)Bnum[0],(unsigned int)Bnum[1]);
}

void  dispmenu4(void)
{
   	strcpy(FirstLine , " Spe Play ");
	strcpy(SecondLine ," Cir Play ");
}

void  dispmenu5(void)
{
   	strcpy(FirstLine , " Input M Num: ");
	sprintf(SecondLine," %d%d",(unsigned int)Anum[0],(unsigned int)Anum[1]);
}

void  dispmenu6(void)
{
   	strcpy(FirstLine , " All songs ");
	strcpy(SecondLine ," is  playing! ");
}

void  fresh(void)  //刷新函数
{	
	if(lcdflashflag ==1)
	{
	 	bsp_LCDDispStr(0,1, FirstLine);
		bsp_LCDDispStr(0,2, SecondLine);
		lcdflashflag =0;


		switch(CurMenuIndex)
		{
			case 0 :
			{
				setcursorlocation(15,1); //第一行加光标
				break;
			}

			case 1 :
			{
				setcursorlocation(15,2); //第二行
				break;
			}
			
			case 2 :
			{
				setcursorlocation(15,1); //第一行
				break;
			}
			
			case 4 :
			{
				setcursorlocation(15,2); //第二行
				break;
			}  
		}
	}
	
}