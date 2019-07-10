#ifndef BSP_MOTOR_HH
#define BSP_MOTOR_HH
sbit INA1 = P2^0;
sbit INA2 = P2^1;
extern unsigned char tflag;

void motor_on(void);
void motor_off(void);
#endif
//该预编译可以防止头文件被重复包含