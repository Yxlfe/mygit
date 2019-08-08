#ifndef BSP_IIC_H_HH
#define BSP_IIC_H_HH

#define I2C_WR	0		/* д����bit */
#define I2C_RD	1		/* ������bit */


void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(unsigned char _ucByte);
unsigned char i2c_ReadByte(void);
unsigned char i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
unsigned char i2c_CheckDevice(unsigned char _Address);

#endif