#include "bsp.h"

void main()
{
	bsp_init();//外设初始化函数
   	while(1)				 
	{
	  bsp_IrFunc();
	  switch_menu();
	  fresh(); 
	}
}