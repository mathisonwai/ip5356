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


//! OK
void i2c_start(void)
{
	P_I2C_SDA_SET;
	P_I2C_SCL_SET;
	P_I2C_SDA_OUTPUT;
	P_I2C_SCL_OUTPUT;
	_dly_us(10);
	P_I2C_SDA_CLR;
	_dly_us(10);
	P_I2C_SCL_CLR;
}

//! OK
void i2c_stop(void)
{
	P_I2C_SCL_CLR;
	P_I2C_SDA_CLR;
	_dly_us(10);
	P_I2C_SCL_SET;
	_dly_us(10);
	P_I2C_SDA_SET;
}

//! ok
unsigned char i2c_chk_ack(void)
{
	// unsigned char ack;

	P_I2C_SCL_CLR; // slave send ACK

	P_I2C_SDA_INPUT;								// Allow slave to send ACK
	unsigned char getAckTime = CONST_TIMER_GET_ACK; //返回ACK信号延时等待时间
	_dly_us(0);
	P_I2C_SCL_SET;
	_dly_us(0);
	while (P_I2C_SDA)
	{
		--getAckTime;

		if (0 == getAckTime)
		{
			return 1;
		}
	}

	P_I2C_SCL_CLR;
	P_I2C_SDA_OUTPUT;
	return 0;
}
//! OK 产生ACK应答
void i2c_send_ack(void)
{
	P_I2C_SCL_CLR;
	P_I2C_SDA_CLR;
	_dly_us(10);
	P_I2C_SCL_SET;
	_dly_us(10);
	P_I2C_SCL_CLR;
	P_I2C_SDA_CLR;
}
//! OK
void i2c_send_nack(void)
{
	P_I2C_SCL_CLR;
	P_I2C_SDA_SET;
	_dly_us(10);
	P_I2C_SCL_SET;
	_dly_us(10);
	P_I2C_SCL_CLR;
	P_I2C_SDA_CLR;
}
//! OK
unsigned char i2c_writeByte(unsigned char sendByte)
{
	unsigned char i = 8;

	while (i--) // I2C_SDA脚从高位至低位发送数据
	{
		P_I2C_SCL_CLR; //拉低I2C_SCL,以允许I2C_SDA脚w位数据发生变化
		// NOP();
		// NOP();
		// NOP();
		// NOP();
		_dly_us(0);
		if (sendByte & 0x80) /* MSB output first */
		{
			P_I2C_SDA_SET;
		}
		else
		{
			P_I2C_SDA_CLR;
		}
		sendByte <<= 1;
		P_I2C_SCL_SET; //拉高I2C_SCL
		_dly_us(0);
		NOP();
		// NOP();
		// NOP();
		// NOP();
		// NOP();
	}

	return i2c_chk_ack();
}
// OK
unsigned char i2c_readByte(void)
{
	unsigned char i = 8;
	unsigned char readByte = 0;

	P_I2C_SCL_CLR;	 //拉低I2C_SCL
	P_I2C_SDA_INPUT; //设置I2C_SDA为输入

	while (i--)
	{
		// _dly_us(10);
		P_I2C_SCL_SET; //拉高I2C_SCL
		_dly_us(0);
		readByte <<= 1;

		if (P_I2C_SDA)
		{
			readByte |= 0x01;
		}

		P_I2C_SCL_CLR; //拉低I2C_SCL
		_dly_us(0);
	}

	// _dly_us(10);
	P_I2C_SDA_OUTPUT; //设置I2C_SDA为输出
	return readByte;  //返回数据
}
