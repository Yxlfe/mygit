#include "bsp.h"

void bsp_init(void)//��������ĳ�ʼ������
{
    delay_ms(100);
	
	//��ʱ����ʼ��	  	
	bsp_InitTimer0();  //��¼ʱ�� ���ڼ�¼ �����źŵ�һλ������ʱ��
	bsp_InitSerial();//����ʱ�ӳ�ʼ��
	bsp_initInt0();	  //�����źŽ������ж�
	bsp_LCDInit();
}