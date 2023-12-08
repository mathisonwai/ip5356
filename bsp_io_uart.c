/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"

#include "app_global.h"

#include "bsp_io_uart.h"
void io_uart_tx(unsigned char sendByte)
{

    unsigned char bCount;

    bCount = 8;
    GIE = 0;
    P_IO_UART_TX_OUTPUT;
    P_IO_UART_TX_CLR; //输出高
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();

    while (bCount)
    {
        if (sendByte & 0x01)
        {
            P_IO_UART_TX_SET; //输出高
            NOP();
            NOP();
        }
        else
        {
            P_IO_UART_TX_CLR; //输出低
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
        }
        bCount--;
        sendByte >>= 1;
    }

    NOP();
    P_IO_UART_TX_SET; //输出高
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    NOP();
    GIE = 1;
}