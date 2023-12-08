/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"
#define APP_GLOBALS
#include "app_global.h"
#include "bsp_adc.h"
#include "bsp_i2c.h"
#include "bsp_ip53xs.h"
#include "bsp_led.h"
#include "bsp_io_uart.h"
#include "app_bms_ip53xs.h"

#include "app_key.h"
#include "app_display.h"

/*
 *  INT-- ---------|1(PC0)           (PA7)20|---CLK
 *  SDA------------|2(PC1) 	     	 (PA6)19|----WAKE
 *  SCL------------|3(PB7)	   		 (PA5)18|----
 *  GND------------|4(GND)    	 	 (PA4)17|-------IS
 *  IDA-------------|5(PB6)          (PA3)16|-------SW1
 *
 *  VCC-- ---------|6(VDD)          (PA2)15|-------ICK
 *    ------------|7(PB5)       		 (PA1)14|----
 *  L5------------|8(PB4)         	 (PA0)13|----G1
 *  L4------------|9(PB3)    	         (PB0)12|------L1
 *  L3-----------|10(PB2)             (PB1)11|-----L2
 */

void main(void)
{
    init_gpio();
    init_timer4();
    init_system_parameter();
    P_IO_UART_TX_OUTPUT; // TEST

    T4UIF = 1;

    EPIF0 = 0xFF;

    INTCON |= 0B11000000;
    GIE = 1;

    P_I2C_INT_INPUT;
    bFlag_init_ip5356 = 1;
    bFlag_plus_in_12v = 1;

    while (TRUE)
    {

        if (bFlag_Timeslice_1ms)
        {
            bFlag_Timeslice_1ms = 0;
            if (bFlag_Timeslice_16ms)
            {
                bFlag_Timeslice_16ms = 0;
                if ((bFlag_p_ext_int_is_high) && (P_I2C_INT)) // 16ms
                {
                }
                get_p_ext_int_status();
                // gpioKeyScan();
                                 {
                    if (bFlag_plus_in_12v)
                    {
                        bFlag_plus_in_12v = 0;
                        P_IO_UART_TX = 1;
                    }
                    else
                    {
                        bFlag_plus_in_12v = 1;
                        P_IO_UART_TX = 0;
                    }
                }
#if 0
                switch (timer_get_ip53xs_status & 0x07) // 8*16 = 128
                {

                case 1:
                    if ((bFlag_p_ext_int_is_high) && (P_I2C_INT))
                    {

                        is_chg_or_dischg();
                        get_type_c_state();
                        if (0 == bFlag_charge_on)
                        {

                            get_light_load_status();

                            get_multi_port_status();
                            get_quick_charge_states();
                            get_pd_charge_states();

                            is_ovp_qc_12v();
                            if (bFlag_discharge_pd)
                            {
                                is_ovp_pd_9v();
                            }
                            is_ovp_6v3();
                            get_protocol_indication();
                        }

                        get_system_current();
                        get_system_voltage();
                    }
                    break;

                case 3:

                    if ((bFlag_p_ext_int_is_high) && (P_I2C_INT))
                    {
                        get_quick_charge_states();
                        get_small_current_mode_status();
                        is_sink_pd_ok();
                    }
                    break;

                case 5:

                    if ((bFlag_p_ext_int_is_high) && (P_I2C_INT))
                    {
                        if (0 == bFlag_charge_on)
                        {
                            get_current_vout1();
                            get_current_vout2();
                        }
                    }

                    break;

                case 6:
                    if (timer_dly_chk_ovp)
                    {
                        timer_dly_chk_ovp--;
                    }
                    break;

                case 7:
                    if ((bFlag_p_ext_int_is_high) && (P_I2C_INT))
                    {

                        get_voltage_battery();
                        displayData = get_percentage_voltage_Battery();
                    }
                    break;

                default:
                    break;
                }
#endif

                timer_get_ip53xs_status++;

                if (!(timer_get_ip53xs_status & 0x3F))
                {
                    bFlag_Timeslice_1sec = 1;
                }
                timer_display_slice_16ms++;

                if (timer_display_slice_16ms >= display_cycle)
                {
                    timer_display_slice_16ms = 0;
                    bFlag_Timeslice_display = 1;
                }
            }
            if (bFlag_Timeslice_display)
            {
                bFlag_Timeslice_display = 0;
                if (bFlag_blink)
                {
                    bFlag_blink = 0x00;
                }
                else
                {
                    bFlag_blink = 0x01;
                }
                if ((P_I2C_INT) && (bFlag_p_ext_int_is_high))
                {
                    init_ip53xs();
                }
                //             {
                //     if (bFlag_plus_in_12v)
                //     {
                //         bFlag_plus_in_12v = 0;
                //         P_IO_UART_TX = 1;
                //     }
                //     else
                //     {
                //         bFlag_plus_in_12v = 1;
                //         P_IO_UART_TX = 0;
                //     }
                // }
                app_display_all();
            }
            if (bFlag_Timeslice_1sec)
            {
                bFlag_Timeslice_1sec = 0;
                g_counter_1sec++;
                // if (0 == (g_counter_1sec & 0x07))
                // {
                //     if (bFlag_plus_in_12v)
                //     {
                //         bFlag_plus_in_12v = 0;
                //         P_IO_UART_TX = 1;
                //     }
                //     else
                //     {
                //         bFlag_plus_in_12v = 1;
                //         P_IO_UART_TX = 0;
                //     }
                // }
                // get_battery_volume();
                //! demo sleep_proc();
            }
        }
    }
}

void interrupt ISR(void)
{
    if (T4UIF)
    {

        // P_IO_UART_TX = ~P_IO_UART_TX;
        bFlag_gSysTick_change = 1;
        gSysTick++;
        bFlag_Timeslice_1ms = 1;

        if (!(gSysTick & 0x0F))
        {

            bFlag_Timeslice_16ms = 1;
        }
    }
    if (EPIF0)
    {
    }

    EPIF0 = 0xFF;
    T4UIF = 1;
}
