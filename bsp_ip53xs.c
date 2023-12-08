
/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/



#include "SYSCFG.h"
#include "app_cfg.h"
#include "app_global.h"


#include "bsp_i2c.h"
#include "bsp_ip53xs.h"
#include "app_bms_ip53xs.h"





BOOL ip53xs_writeByte(unsigned char deviceAddr, unsigned char regAddr, unsigned char sendByte)
{
	if (P_I2C_INT)
	{
		i2c_start();

		if (i2c_writeByte(deviceAddr | IIC_WRITE))
		{
			i2c_stop();
			return FALSE;
		}

		if (i2c_writeByte(regAddr))
		{
			i2c_stop();
			return FALSE;
		}

		if (i2c_writeByte(sendByte))
		{
			i2c_stop();
			return FALSE;
		}

		i2c_stop();
	}

	return TRUE;
}

unsigned char ip53xs_readByte(unsigned char deviceAddr, unsigned char regAddr) //(unsigned char regAddr)
{
	unsigned char readByte;
	if (P_I2C_INT)
	{
		i2c_start();

		if (i2c_writeByte(deviceAddr | IIC_WRITE))
		{
			i2c_stop();
			return FALSE;
		}

		if (i2c_writeByte(regAddr))
		{
			i2c_stop();
			return FALSE;
		}

		i2c_start();

		if (i2c_writeByte(deviceAddr | IIC_READ))
		{
			i2c_stop();
			return FALSE;
		}

		readByte = i2c_readByte();
		i2c_send_nack();
		i2c_stop();
	}

	return readByte;
}
