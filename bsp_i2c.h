


#include "app_cfg.h"
#include "app_global.h"


#ifndef _BSP_I2C_H_
#define _BSP_I2C_H_

#define CONST_TIMER_GET_ACK                    250

void i2c_start(void);
void i2c_stop(void);
unsigned char i2c_chk_ack(void);
void i2c_send_ack(void);
void i2c_send_nack(void);
unsigned char i2c_writeByte(unsigned char sendByte);
unsigned char i2c_readByte(void);
#endif
