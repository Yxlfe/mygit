#include "bsp.h"
unsigned char intvalue=0;
void bsp_initInt0(void) //��ʼ�� INT0
{
  //1. ȷ��������ƽ
    IT0 = 1; //���ش���
  //2. ���жϿ���
    EX0 = 1; 
	EA = 1;
}
