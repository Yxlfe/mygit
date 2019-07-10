#ifndef BSP_MKEY_HH
#define BSP_MKEY_HH


unsigned char bsp_MKeyScan(void);
unsigned char bsp_Mkeyproc(unsigned char scanvalue);

#endif
//该预编译可以防止头文件被重复包含