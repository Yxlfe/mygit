#ifndef BSP_SERIAL_HH
#define BSP_SERIAL_HH

void bsp_InitSerial(void);
void UART1_SendByte(unsigned char dat);

void Volume_add();//音量+
void Volume_nec();//音量-
void Music_play();//播放
void Music_pause();//暂停
void Music_stop();//停止
void Last_Play();//播放上一首
void Next_Play();//播放下一首
void Specify_Musi_Play(unsigned char num);//特定曲目播放
void Specify_Volume(unsigned  char num);//指定音量
void Cycle_play();//全部循环播放
#endif
//该预编