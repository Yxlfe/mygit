#include "bsp.h"

void main()
{
	bsp_init();//�����ʼ������
   	while(1)				 
	{
	  bsp_IrFunc();
	  switch_menu();
	  fresh(); 
	}
}