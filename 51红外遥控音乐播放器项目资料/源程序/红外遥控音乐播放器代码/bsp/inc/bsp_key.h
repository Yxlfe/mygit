#ifndef BSP_KEY_HH
#define BSP_KEY_HH

extern unsigned char modelset,modelalarm;
//3. ��������
unsigned char bsp_KeyScan(void);
void bsp_keyproc(unsigned char kvalue);
void  bsp_AddTime(void);
#endif
//��Ԥ������Է�ֹͷ�ļ����ظ�����