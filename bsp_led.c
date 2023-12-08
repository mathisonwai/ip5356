#include "SYSCFG.h"
#include "app_cfg.h"
#include "bsp_led.h"
#include "app_global.h"
#include "app_display.h"



void scan_io_led(void)
{
	static unsigned char scanComIndex = 0;

	P_LED_SEG1_INPUT;
	P_LED_SEG2_INPUT;
	P_LED_SEG3_INPUT;
	P_LED_SEG4_INPUT;
	P_LED_SEG5_INPUT;


	switch (scanComIndex)
	{
	case 17:
		if (displayHundred & SEG_A) // A4 快充
		{

			P_LED_SEG3_SET;
			P_LED_SEG3_OUTPUT;
			P_LED_SEG5_CLR;
			P_LED_SEG5_OUTPUT;
		}
		break;
	case 0:
		if (displayHundred & SEG_B) // B1
		{

			P_LED_SEG3_SET;
			P_LED_SEG3_OUTPUT;
			P_LED_SEG4_CLR;
			P_LED_SEG4_OUTPUT;
		}
		break;
	case 1:
		if (displayHundred & SEG_C) // C1
		{

			P_LED_SEG2_SET;
			P_LED_SEG2_OUTPUT;
			P_LED_SEG4_CLR;
			P_LED_SEG4_OUTPUT;
		}
		break;
	case 2:
		if (displayHundred & SEG_K) // A4 %
		{

			P_LED_SEG2_SET;
			P_LED_SEG2_OUTPUT;
			P_LED_SEG5_CLR;
			P_LED_SEG5_OUTPUT;
		}
		break;
	case 3:
		if (displayDecade & SEG_A) // A2
		{

			P_LED_SEG2_SET;
			P_LED_SEG2_OUTPUT;
			P_LED_SEG3_CLR;
			P_LED_SEG3_OUTPUT;
		}
		break;
	case 4:
		if (displayDecade & SEG_B) // B2
		{
	
			P_LED_SEG3_SET;
			P_LED_SEG3_OUTPUT;
			P_LED_SEG2_CLR;
			P_LED_SEG2_OUTPUT;
		}
		break;
	case 5:
		if (displayDecade & SEG_C) // C2
		{
	
			P_LED_SEG4_SET;
			P_LED_SEG4_OUTPUT;
			P_LED_SEG3_CLR;
			P_LED_SEG3_OUTPUT;
		}
		break;
	case 6:
		if (displayDecade & SEG_D) // D2
		{
	
			P_LED_SEG4_SET;
			P_LED_SEG4_OUTPUT;
			P_LED_SEG2_CLR;
			P_LED_SEG2_OUTPUT;
		}
		break;
	case 7:
		if (displayDecade & SEG_E) // E2
		{

			P_LED_SEG5_SET;
			P_LED_SEG5_OUTPUT;
			P_LED_SEG2_CLR;
			P_LED_SEG2_OUTPUT;
		}
		break;
	case 8:
		if (displayDecade & SEG_F) // F2
		{

			P_LED_SEG5_SET;
			P_LED_SEG5_OUTPUT;
			P_LED_SEG3_CLR;
			P_LED_SEG3_OUTPUT;
		}
		break;
	case 9:
		if (displayDecade & SEG_G) // G2
		{

			P_LED_SEG5_SET;
			P_LED_SEG5_OUTPUT;
			P_LED_SEG4_CLR;
			P_LED_SEG4_OUTPUT;
		}
		break;
	case 10:
		if (displayDigit & SEG_A) // A3  -- OK
		{

			P_LED_SEG1_SET;
			P_LED_SEG1_OUTPUT;
			P_LED_SEG2_CLR;
			P_LED_SEG2_OUTPUT;
		}
		break;
	case 11:
		if (displayDigit & SEG_B) // B3 --OK
		{

			P_LED_SEG2_SET;
			P_LED_SEG2_OUTPUT;
			P_LED_SEG1_CLR;
			P_LED_SEG1_OUTPUT;
		}
		break;
	case 12:
		if (displayDigit & SEG_C) // C3  -- OK
		{

			P_LED_SEG1_SET;
			P_LED_SEG1_OUTPUT;
			P_LED_SEG3_CLR;
			P_LED_SEG3_OUTPUT;
		}
		break;
	case 13:
		if (displayDigit & SEG_D) // D3 -- OK
		{

			P_LED_SEG3_SET;
			P_LED_SEG3_OUTPUT;
			P_LED_SEG1_CLR;
			P_LED_SEG1_OUTPUT;
		}
		break;
	case 14:
		if (displayDigit & SEG_F) // F3  -- ok
		{

			P_LED_SEG4_SET;
			P_LED_SEG4_OUTPUT;
			P_LED_SEG1_CLR;
			P_LED_SEG1_OUTPUT;
		}
		break;
	case 15:
		if (displayDigit & SEG_E) // E3  -- Ok
		{

			P_LED_SEG1_SET;
			P_LED_SEG1_OUTPUT;
			P_LED_SEG4_CLR;
			P_LED_SEG4_OUTPUT;
		}
		break;
	case 16:
		if (displayDigit & SEG_G) // G3  -- ok
		{

			P_LED_SEG5_SET;
			P_LED_SEG5_OUTPUT;
			P_LED_SEG1_CLR;
			P_LED_SEG1_OUTPUT;
		}
		break;

	default:
		break;
	}
	scanComIndex++;
	if (scanComIndex > 17)
	{
		scanComIndex = 0;
	}
}
