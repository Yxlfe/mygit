#ifndef BSP_PCF8591_HH
#define BSP_PCF8591_HH

unsigned char bsp_InitAdc(void);
unsigned char bsp_SetDac(unsigned char davalue);//davalue ���� daת��ֵ
unsigned char bsp_ReadAdc(unsigned char ch);//ch ����ͨ��

#endif
//��Ԥ��