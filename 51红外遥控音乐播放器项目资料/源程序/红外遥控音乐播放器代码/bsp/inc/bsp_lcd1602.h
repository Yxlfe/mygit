#ifndef BSP_LCD1602_HH
#define BSP_LCD1602_HH


//3. ��������
void bsp_LCDInit(void);
void bsp_LCDCommand(unsigned char cmd);
void bsp_LCDData(unsigned char dat);

void bsp_LCDDispChar(unsigned char x,unsigned char y, unsigned char s);
void bsp_LCDDispStr(unsigned char x,unsigned char y, unsigned char *s);

void bsp_LCDFillCGRAM(void);   //����Ƶ��ַ� �͵�Һ���� ������ʾ
void bsp_LCDDispCGRAM(unsigned char x,unsigned char y, unsigned char index);

void setcursorlocation(unsigned char x,unsigned char y); //������ xy �� ��˸���

void bsp_LcdClr(void);
//index ����0-7  ��Ӧ�Լ���Ƶ�8�������ַ�
#endif
//��Ԥ��