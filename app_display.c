/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"
#include "app_global.h"
#define DISP_GLOBALS
#include "app_display.h"

const unsigned char DispTable[] =
	{
		SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,		   // 0
		SEG_B | SEG_C,										   // 1
		SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,				   // 2
		SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,				   // 3
		SEG_B | SEG_C | SEG_F | SEG_G,						   // 4
		SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,				   // 5
		SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,		   // 6
		SEG_A | SEG_B | SEG_C,								   // 7
		SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G, // 8
		SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,		   // 9
		SEG_G,												   // -
		0x00,												   // null
};
#ifdef FUNC_RUN_HORSE
void displayRunHorse(void)
{
	++displayTimerRunHorse;

	if (displayTimerRunHorse > 3)
	{
		displayTimerRunHorse = 0;
		displayLeft = 0x10;
		displayRight = 0x10;
	}

	if (false == bFlag_light_load_left)
	{
		displayLeft &= 0x0F;
		displayLeft |= (1 << displayTimerRunHorse);
		displayLeft |= BIT4; // icon left
	}
	else
	{
		displayLeft = SEG_OFF;
	}

	if (false == bFlag_light_load_right)
	{
		displayRight &= 0x0F;
		displayRight |= (1 << displayTimerRunHorse);
		displayRight |= BIT4; // icon right
	}
	else
	{
		displayRight = SEG_OFF;
	}
}
#endif
void app_display_all(void)
{
	unsigned char i, j;

	if (forceDispTimer)
	{
		forceDispTimer--;

		if (0 == forceDispTimer)
		{
			displayHundred = SEG_K; //%
			displayDecade = SEG_OFF;
			displayDigit = SEG_OFF;
#ifdef FUNC_RUN_HORSE
			displayTimerRunHorse = 3;
			displayLeft = SEG_OFF;
			displayRight = SEG_OFF;
#endif
			display_cycle = 31;
		}
		else
		{
			displayHundred = SEG_K; //%

			// if (bFlag_discharge_qc)
			// {
			displayHundred |= SEG_A; // quick
									 // }
			displayHundred |= DispTable[1];
			displayDecade = DispTable[8];
			displayDigit = DispTable[8];

#ifdef FUNC_RUN_HORSE
			displayLeft = 0x1F;
			displayRight = 0x1F;
#endif
		}
	}
	else if (bFlag_charge_on) // <-- 充电显示部分
	{
		dispTimerUnderVoltage = 0;

		if (displayData < 100)
		{
			// dispTimerFull = LED_DISP_TIME;
#ifdef FUNC_RUN_HORSE
			displayRunHorse();
#endif
			if (bFlag_blink)
			{
				// displayHundred = 0x00;
				displayHundred = SEG_K; //%
				if (bFlag_charge_qc)
				{
					displayHundred |= SEG_A; // quick
				}
				//{displayData = get_percentage_voltage_Battery();
				i = displayData / 10;
				j = displayData % 10;
#ifdef DISP_ZERO_IN_DEC
				displayDecade = DispTable[i];
#else //十位不显
				if (i)
				{
					displayDecade = DispTable[i];
				}
				else
				{
					displayDecade = SEG_OFF;
				}

#endif

				displayDigit = DispTable[j];
				//}
			}
			else
			{
				displayDigit = SEG_OFF;
				dispTimer = CONST_DISP_TIME; // <-- 拨出显示
			}
		}
		else // <-- 充满
		{
			if (dispTimerFull)
			{
				dispTimerFull--;
#ifdef FUNC_RUN_HORSE
				displayRunHorse();
#endif
				displayHundred = SEG_K; //%
				if (bFlag_charge_qc)
				{
					displayHundred |= SEG_A; // quick
				}
				displayHundred |= DispTable[1];
				displayDecade = DispTable[0];
				displayDigit = DispTable[0];
				dispTimer = CONST_DISP_TIME; // <-- 拨出显示
			}
			else
			{
				displayHundred = SEG_OFF;
				displayDecade = SEG_OFF;
				displayDigit = SEG_OFF;
#ifdef FUNC_RUN_HORSE
				displayLeft = SEG_OFF;
				displayRight = SEG_OFF;
				displayTimerRunHorse = 3;
#endif
			}
		}
	}
	else // <-- 以下为放电部分显
	{
		if (dispTimerUnderVoltage) // <-- LED欠压关机显示
		{
			dispTimerUnderVoltage--;
			dispTimer = 0;
			displayHundred = SEG_K;
			if (bFlag_discharge_qc)
			{
				displayHundred |= SEG_A; // quick
			}
			// if(bFlag_Power_On)
			//{
			// gBatteryCapacity = (unsigned long)0;        // 这里有风险吗
			// bFlag_Chargering_From_Empty = 1;
			// }

			if (dispTimerUnderVoltage % 2)
			{
				i = displayData / 10;
				j = displayData % 10;
#ifdef DISP_ZERO_IN_DEC
				displayDecade = DispTable[i];
#else
				if (i)
				{
					displayDecade = DispTable[i];
				}
				else
				{
					displayDecade = SEG_OFF; //十位不显
				}

#endif

				displayDigit = DispTable[j];
			}
			else
			{
				if (0 == displayData)
				{
					displayDigit = SEG_OFF;
				}
			}

			if (0 == dispTimerUnderVoltage)
			{
				if (displayData)
				{
					displayData--;
					dispTimerUnderVoltage = (CONST_UV_DISP_TIME - 1);
				}
				else if (0 == displayData)
				{
					//#ifdef USING_IP5306
					// shutdown_ip5306();
					//#endif
				}
			}
		}
		else if (dispTimer) // else if((func_mode) || (dispTimer))
		{

			dispTimer--;
#ifdef FUNC_RUN_HORSE
			displayRunHorse();
#endif
			displayHundred = SEG_K; //%
			if (bFlag_discharge_qc)
			{
				displayHundred |= SEG_A; // quick
			}
			if (displayData < 100)
			{
				// displayHundred = SEG_OFF;

				if (bFlag_blink)
				{
					i = displayData / 10;
					j = displayData % 10;
#ifdef DISP_ZERO_IN_DEC
					displayDecade = DispTable[i];
#else
					if (i)
					{
						displayDecade = DispTable[i];
					}
					else
					{
						displayDecade = SEG_OFF;
					}

#endif

					displayDigit = DispTable[j];
				}
				else
				{

					if (0 == displayData)
					{
						displayDigit = SEG_OFF;
					}
				}
			}
			else
			{
				displayHundred |= DispTable[1];
				displayDecade = DispTable[0];
				displayDigit = DispTable[0];
			}
		}
		else
		{
			displayHundred = SEG_OFF;
			displayDecade = SEG_OFF;
			displayDigit = SEG_OFF;
#ifdef FUNC_RUN_HORSE
			displayLeft = SEG_OFF;
			displayRight = SEG_OFF;
			displayTimerRunHorse = 3;
#endif
		}
	}
}
