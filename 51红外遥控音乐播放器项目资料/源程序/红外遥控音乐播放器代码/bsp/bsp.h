#ifndef BSP_HH
#define BSP_HH


//1. ����ϵͳͷ�ļ�
#include "reg52.h"
#include "math.h"
#include "stdio.h"
#include "intrins.h"
#include "string.h"

//#include "menu.h"

//2. �������е�����ͷ�ļ�
#include "bsp_delay.h"
#include "bsp_int.h"
#include "bsp_timer.h"
#include "bsp_lcd1602.h"
//#include "bsp_iic.h"
//#include "bsp_eeprom_24xx.h"
//#include "bsp_pcf8591.h"
#include "bsp_serial.h"
#include "bsp_ir.h"
#include "bsp_music.h"



#define u8 unsigned char
#define u16 unsigned int


//3. ��������
void bsp_init(void);//��������ĳ�ʼ������
#endif
//��Ԥ������Է�ֹͷ�ļ����ظ�����
