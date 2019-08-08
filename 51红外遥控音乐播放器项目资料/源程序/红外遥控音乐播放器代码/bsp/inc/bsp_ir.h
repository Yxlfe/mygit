#ifndef BSP_IRIR_HH
#define BSP_IRIR_HH

#define  UP    10
#define  DOWN  11
#define  LEFT  12
#define  RIGHT 13

#define  SURE  14
#define  CANCEL 15
#define  PLAY  16
#define  STOP  17
#define  PAUSE 18

#define  ZERO  19
#define  ONE   20
#define  TWO   21
#define  THREE 22
#define  FOUR  23
#define  FIVE  24
#define  SIX   25
#define  SEVEN 26
#define  EIGHT 27
#define  NINE  28


extern unsigned char fIrRevOk ; //代表一次接收完成
extern unsigned char IR_CODE[4];
extern unsigned char IRKEY  ;
void bsp_IrDecode(void);//红外解码
void bsp_IrFunc(void);


#endif
//该预编译可以防止头文件被重复包含