#ifndef __APP_DISP_H__
#define __APP_DISP_H__

#include "SYSCFG.h"

#ifdef DISP_GLOBALS
#define DISP_EXT
#else
#define DISP_EXT extern
#endif
#define CONST_UV_DISP_TIME (11)
#define SEG_A 0X01
#define SEG_B 0X02
#define SEG_C 0X04
#define SEG_D 0X08
#define SEG_E 0X10
#define SEG_F 0X20
#define SEG_G 0X40
#define SEG_K 0X80
#define SEG_OFF 0x00



DISP_EXT volatile unsigned char displayData;
DISP_EXT volatile unsigned char displayHundred;
DISP_EXT volatile unsigned char displayDecade;
DISP_EXT volatile unsigned char displayDigit;
#ifdef FUNC_RUN_HORSE
DISP_EXT volatile unsigned char displayLeft;
DISP_EXT volatile unsigned char displayRight;
#endif
DISP_EXT volatile unsigned char dispTimer;
DISP_EXT volatile unsigned char dispTimerFull;
#ifdef FUNC_RUN_HORSE
DISP_EXT volatile unsigned char displayTimerRunHorse;
#endif
DISP_EXT volatile unsigned char dispTimerUnderVoltage;

void app_display_all(void);

#endif