#ifndef BSP_SERIAL_HH
#define BSP_SERIAL_HH

void bsp_InitSerial(void);
void UART1_SendByte(unsigned char dat);

void Volume_add();//����+
void Volume_nec();//����-
void Music_play();//����
void Music_pause();//��ͣ
void Music_stop();//ֹͣ
void Last_Play();//������һ��
void Next_Play();//������һ��
void Specify_Musi_Play(unsigned char num);//�ض���Ŀ����
void Specify_Volume(unsigned  char num);//ָ������
void Cycle_play();//ȫ��ѭ������
#endif
//��Ԥ��