#include "bsp.h"

#define  SIZEOFMENU  9
unsigned char Anum[4]={0};
unsigned char Bnum[4]={0};
unsigned char Asum=0;
unsigned char Bsum=0;
unsigned char a=0;
unsigned char b=0;
unsigned char CurMenuIndex =0; //ָ��ǰ�˵����
unsigned char FirstLine[16]=" 123";
unsigned char SecondLine[16]=" 123";
unsigned char lcdflashflag =1;//�˵�ˢ������
//unsigned char IRFLAG =0;   //��������Ľ�ֵ 


typedef struct keymenu
{  	
	unsigned char curindex;//��ǰ�Ĳ˵����
	unsigned char UPindex;//�������ϰ��� ����ı��
	unsigned char DNindex;//�������°��� ����ı��
	unsigned char SUREindex;//���»س����� ����ı��
	unsigned char CANCELindex;//���·��ذ��� ����ı��
	void (*operation)();

} MYMENU;

MYMENU code keytab[SIZEOFMENU] =
{
		 //��ǰ���ϣ��£�ȷ��������
		 {0,0,1,2,0,dispmenu0},//ģʽѡ�����1
		 {1,0,1,3,1,dispmenu1},//ģʽѡ�����2
		 {2,2,4,5,0,dispmenu2},//����ģʽѡ�����1(ѡ���ض���Ŀ)
		 {3,3,3,3,1,dispmenu3},//����ѡ��������С���ֽ���
		 {4,2,4,6,0,dispmenu4},//����ģʽѡ�����2(ȫ��ѭ������)
		 {5,5,5,5,2,dispmenu5},//����ѡ�����������ֽ���
		 {6,6,6,6,4,dispmenu6},//���棺Circle Playing!
};

//���ݺ��ⰴ������ �˵��л�
void switch_menu(void)
{
  	switch(IRKEY)
	{
	   case PLAY://����
	   {
	   	 Music_play();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case STOP://������һ��
	   {
	   	 Music_stop();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case PAUSE://��ͣ
	   {
	   	 Music_pause();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case LEFT://������һ��
	   {
	   	 Last_Play();
		 IRKEY=0X99;
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 break;
	   }

	   case RIGHT://������һ��
	   {
	   	 Next_Play();
		 lcdflashflag = 1;
	   	 bsp_LcdClr();
		 IRKEY=0X99;
		 break;
	   }

	   case  UP :  //����
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
	
	   case ZERO://����0
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

	   case ONE://����1
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

	   case TWO://����2
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

	   case THREE://����3
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

	   case FOUR://����4
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

	   case FIVE://����5
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

	   case SIX://����6
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

	   case SEVEN://����7
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

	   case EIGHT://����8
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

	   case NINE://����9
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

void  dispmenu0(void) //0�Ž���
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

void  fresh(void)  //ˢ�º���
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
				setcursorlocation(15,1); //��һ�мӹ��
				break;
			}

			case 1 :
			{
				setcursorlocation(15,2); //�ڶ���
				break;
			}
			
			case 2 :
			{
				setcursorlocation(15,1); //��һ��
				break;
			}
			
			case 4 :
			{
				setcursorlocation(15,2); //�ڶ���
				break;
			}  
		}
	}
	
}