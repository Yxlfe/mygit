#ifndef BSP_KEY_HH
#define BSP_KEY_HH

extern unsigned char modelset,modelalarm;
//3. 函数声明
unsigned char bsp_KeyScan(void);
void bsp_keyproc(unsigned char kvalue);
void  bsp_AddTime(void);
#endif
//该预编译可以防止头文件被重复包含