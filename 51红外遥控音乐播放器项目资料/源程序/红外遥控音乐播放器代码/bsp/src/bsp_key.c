#include "bsp.h"
sbit SET =P2^7;	    //修改时间按键
sbit ALARM =P2^6;	//修改闹钟时间按键
sbit ADD =P2^5;		//增加
sbit DEC =P2^4;		//减少
unsigned char modelalarm =0;//和设置时间的状态一致
// 1 2 3 对应 秒 分 时
// 设置时间时 不能设置闹钟 设置闹钟时 不能设置时间
unsigned char modelset =0; //该变量记录当前的状态 
//=0 正常走时  ==1  修改秒  ==2 修改分 ==3 修改小时
//如果有按键按下 那么io口会变成低电平 否则就是高电平
unsigned char bsp_KeyScan(void)
{
    if(SET ==0)
	{
	    delay_ms(5);
		while(!SET) bsp_segCCshow();//等待按键释放 ==》while(SET ==0);
		delay_ms(5);
		return 1;

	}
	else if(ALARM==0) 
	{
	  delay_ms(5);
	  while(!ALARM) bsp_segCCshow();//等待按键释放 ==》while(SET ==0);
	  delay_ms(5);
	  return 2;
	 }
	else if(ADD==0) 
	{ 
	    delay_ms(5);
		while(!ADD) bsp_segCCshow();
		delay_ms(5);
		return 3;
	}
	else if(DEC==0)  return 4;
	else  	return 0;
}
void bsp_keyproc(unsigned char kvalue)
{
    if(kvalue ==1) //设置时间处理
	{
	  if(modelalarm ==0) //当不处于设置闹钟状态
	  modelset ++;
	  if(modelset>3) modelset =0;
	  while(!SET);
	}
	else if(kvalue ==2)	//设置闹钟处理
	{
	  if(modelset ==0) //当不处于设置时间状态
	  modelalarm ++;
	  if(modelalarm>3) modelalarm =0;
	  while(!ALARM);
	}
	else if(kvalue ==3)
	{
	  
	 	bsp_AddTime();
		 while(!ADD);
	}
}
//修改时间
void  bsp_AddTime(void)
{
    if(modelalarm==0) //当前修改的是时间
	{
	  if(modelset ==1) //  秒
	  {
		 if(sec<59) sec++;
		 else
		  sec =0;
	  }

	  if(modelset ==2) // 分
	  {
		 if(min<59) min++;
		 else
		  min =0;
	  }

	  if(modelset ==3) // 时
	  {
		 if(hour<23) hour++;
		 else
		  hour =0;
	  }

	}
	else  //修改的是闹钟
	{
		if(modelalarm ==1) //  秒
	  {
		 if(asec<59) asec++;
		 else
		  asec =0;
	  }

	  if(modelalarm ==2) // 分
	  {
		 if(amin<59) amin++;
		 else
		  amin =0;
	  }

	  if(modelalarm ==3) // 时
	  {
		 if(ahour<23) ahour++;
		 else
		  ahour =0;
	  }
	}
}