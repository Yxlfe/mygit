#ifndef BSP_TIMER_HH
#define BSP_TIMER_HH

void bsp_InitTimer0(void);
void bsp_InitTimer1(void);

void Delay240us(void);
void Delay480us(void);
void Delay60us(void);
void Delay16us(void);
#endif
//该预编译可以防止头文件被重复包含