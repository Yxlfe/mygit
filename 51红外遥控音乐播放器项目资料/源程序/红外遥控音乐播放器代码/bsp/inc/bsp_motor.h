#ifndef BSP_MOTOR_HH
#define BSP_MOTOR_HH
sbit INA1 = P2^0;
sbit INA2 = P2^1;
extern unsigned char tflag;

void motor_on(void);
void motor_off(void);
#endif
//��Ԥ������Է�ֹͷ�ļ����ظ�����