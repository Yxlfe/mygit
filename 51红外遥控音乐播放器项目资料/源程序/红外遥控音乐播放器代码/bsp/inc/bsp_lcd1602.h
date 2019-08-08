#ifndef BSP_LCD1602_HH
#define BSP_LCD1602_HH


//3. 函数声明
void bsp_LCDInit(void);
void bsp_LCDCommand(unsigned char cmd);
void bsp_LCDData(unsigned char dat);

void bsp_LCDDispChar(unsigned char x,unsigned char y, unsigned char s);
void bsp_LCDDispStr(unsigned char x,unsigned char y, unsigned char *s);

void bsp_LCDFillCGRAM(void);   //把设计的字符 送到液晶屏 便于显示
void bsp_LCDDispCGRAM(unsigned char x,unsigned char y, unsigned char index);

void setcursorlocation(unsigned char x,unsigned char y); //在坐标 xy 上 闪烁光标

void bsp_LcdClr(void);
//index 就是0-7  对应自己设计的8个特殊字符
#endif
//该预编