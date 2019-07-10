#ifndef BSP_INT_HH
#define BSP_INT_HH

extern unsigned char intvalue;
void bsp_initInt0(void); //初始化 INT0
void bsp_initInt1(void); //初始化 INT1 
#endif
//该预编译可以防止头文件被重复包含