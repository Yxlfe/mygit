#ifndef BSP_LED_HH
#define BSP_LED_HH


//3. 函数声明
void bsp_ledOn(void);
void bsp_ledOff(void);
void bsp_ledblink(unsigned char dir);//dir 方向
#endif
//该预编译可以防止头文件被重复包含