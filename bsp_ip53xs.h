

#include "app_cfg.h"
#include "app_global.h"

#ifndef _BSP_IP53XS_H_
#define _BSP_IP53XS_H_

#define IIC_WRITE   (0) // 写操作
#define IIC_READ    (1)  // 读操作
BOOL ip53xs_writeByte(unsigned char deviceAddr, unsigned char regAddr, unsigned char sendByte);
unsigned char ip53xs_readByte(unsigned char deviceAddr, unsigned char regAddr);

#endif
