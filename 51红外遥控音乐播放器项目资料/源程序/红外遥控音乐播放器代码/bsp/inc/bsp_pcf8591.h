#ifndef BSP_PCF8591_HH
#define BSP_PCF8591_HH

unsigned char bsp_InitAdc(void);
unsigned char bsp_SetDac(unsigned char davalue);//davalue 代表 da转换值
unsigned char bsp_ReadAdc(unsigned char ch);//ch 代表通道

#endif
//该预编