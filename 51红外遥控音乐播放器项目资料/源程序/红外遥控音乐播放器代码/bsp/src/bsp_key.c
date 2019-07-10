#include "bsp.h"
sbit SET =P2^7;	    //�޸�ʱ�䰴��
sbit ALARM =P2^6;	//�޸�����ʱ�䰴��
sbit ADD =P2^5;		//����
sbit DEC =P2^4;		//����
unsigned char modelalarm =0;//������ʱ���״̬һ��
// 1 2 3 ��Ӧ �� �� ʱ
// ����ʱ��ʱ ������������ ��������ʱ ��������ʱ��
unsigned char modelset =0; //�ñ�����¼��ǰ��״̬ 
//=0 ������ʱ  ==1  �޸���  ==2 �޸ķ� ==3 �޸�Сʱ
//����а������� ��ôio�ڻ��ɵ͵�ƽ ������Ǹߵ�ƽ
unsigned char bsp_KeyScan(void)
{
    if(SET ==0)
	{
	    delay_ms(5);
		while(!SET) bsp_segCCshow();//�ȴ������ͷ� ==��while(SET ==0);
		delay_ms(5);
		return 1;

	}
	else if(ALARM==0) 
	{
	  delay_ms(5);
	  while(!ALARM) bsp_segCCshow();//�ȴ������ͷ� ==��while(SET ==0);
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
    if(kvalue ==1) //����ʱ�䴦��
	{
	  if(modelalarm ==0) //����������������״̬
	  modelset ++;
	  if(modelset>3) modelset =0;
	  while(!SET);
	}
	else if(kvalue ==2)	//�������Ӵ���
	{
	  if(modelset ==0) //������������ʱ��״̬
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
//�޸�ʱ��
void  bsp_AddTime(void)
{
    if(modelalarm==0) //��ǰ�޸ĵ���ʱ��
	{
	  if(modelset ==1) //  ��
	  {
		 if(sec<59) sec++;
		 else
		  sec =0;
	  }

	  if(modelset ==2) // ��
	  {
		 if(min<59) min++;
		 else
		  min =0;
	  }

	  if(modelset ==3) // ʱ
	  {
		 if(hour<23) hour++;
		 else
		  hour =0;
	  }

	}
	else  //�޸ĵ�������
	{
		if(modelalarm ==1) //  ��
	  {
		 if(asec<59) asec++;
		 else
		  asec =0;
	  }

	  if(modelalarm ==2) // ��
	  {
		 if(amin<59) amin++;
		 else
		  amin =0;
	  }

	  if(modelalarm ==3) // ʱ
	  {
		 if(ahour<23) ahour++;
		 else
		  ahour =0;
	  }
	}
}