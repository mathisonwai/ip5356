/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"

#include "app_global.h"
#include "app_key.h"
static u8_t GetGpioKeyIndex(void)
{
    u8_t KeyIndex = 0xFF;

    if (P_KEY == 0)
    {
        KeyIndex = 0;
    }

    return KeyIndex;
}

//! Key support multi hit 多击
KEY_EVENT gpioKeyScan(void)
{
    static unsigned char PreKeyIndex = 0xFF;
    static unsigned char cnt_nkey_click = 0xFF;
    BYTE KeyIndex;

    // P_KEY_INPUT;
    // P_KEY_IN_PULLUP();
    // P_KEY_PULLUP(); //! 重要 因为按键 同时 接到5356 上
    // _dly_us(50);

    if (gpioKeyWaitTimer)
    {
        gpioKeyWaitTimer--;
    }

    KeyIndex = GetGpioKeyIndex();

    // P_KEY_IN_NOPULL();
    // P_KEY_NOPULL(); //! 重要 因为按键 同时 接到5356 上

    switch (gpioKeyState)
    {
    case GPIO_KEY_STATE_IDLE:
        if (KeyIndex == 0xFF)
        {
            if (!gpioKeyWaitTimer)
            {
                if (0xFF == cnt_nkey_click)
                {
                    // cnt_nkey_click = 0xFF;
                    return MSG_NONE;
                }
                else if (0x00 == cnt_nkey_click) //! 1 hit
                {
                    cnt_nkey_click = 0xFF;
                    gpioKeyState = GPIO_KEY_STATE_IDLE;
                    return MSG_NONE; // return GpioKeyEvent[PreKeyIndex][1]; //MSG_K1_SPR;
                }
                else if (0x01 == cnt_nkey_click) //! 2 hits
                {
                    cnt_nkey_click = 0xFF;
                    bFlag_double_key = 1;
                    // bFlag_in_small_current_mode ^= 1;
                    return MSG_NONE; // return GpioKeyEvent[PreKeyIndex][5]; //MSG_K2_SPR;  //2ji double key
                }
                else if (0x02 == cnt_nkey_click) //! 3 hits
                {
                    cnt_nkey_click = 0xFF;
                    return MSG_NONE; // return GpioKeyEvent[PreKeyIndex][6]; //MSG_K3_SPR;  // 3ji
                }
                else if (0x03 == cnt_nkey_click) //! 4 hits
                {
                    cnt_nkey_click = 0xFF;
                    return MSG_NONE; // return GpioKeyEvent[PreKeyIndex][7]; //MSG_K4_SPR;  //4ji
                }
                else // if(0x04 == cnt_nkey_click)//! 5 hits
                {
                    cnt_nkey_click = 0xFF;
                    return MSG_NONE; // return GpioKeyEvent[PreKeyIndex][7]; //MSG_K4_SPR;  //5ji
                }
            }
            else if (0xFF == cnt_nkey_click)
            {
                // cnt_nkey_click = 0xFF;
                return MSG_NONE;
            }
            else if (cnt_nkey_click > 0x03) // >=4
            {
                cnt_nkey_click = 0xFF;
                return MSG_NONE; // return MSG_K4_SPR; //5ji
            }
            else // if(0xFF == cnt_nkey_click)
            {
                // cnt_nkey_click = 0xFF;
                return MSG_NONE;
            }
        }

        PreKeyIndex = KeyIndex;
        gpioKeyWaitTimer = KEY_JTTER_TIMER; // gSysTick_current;
        // DBG(("GOTO JITTER!\n"));
        gpioKeyState = GPIO_KEY_STATE_JITTER;

    case GPIO_KEY_STATE_JITTER:
        if (PreKeyIndex != KeyIndex)
        {
            // DBG(("GOTO IDLE Because jitter!\n"));
            gpioKeyState = GPIO_KEY_STATE_IDLE;
        }
        else if (!gpioKeyWaitTimer) // if(gSysTick_current - gpioKeyWaitTimer > KEY_JTTER_TIMER)
        {
            // DBG(("GOTO PRESS_DOWN!\n"));
            gpioKeyWaitTimer = KEY_CP_TIMER; // gSysTick_current;
            gpioKeyState = GPIO_KEY_STATE_PRESS_DOWN;
        }

        break;

    case GPIO_KEY_STATE_PRESS_DOWN:
        if (PreKeyIndex != KeyIndex)
        {
            // DBG(("ADC KEY SP!*****\n"));
            gpioKeyState = GPIO_KEY_STATE_IDLE;

            // return GpioKeyEvent[PreKeyIndex][1]; //SPR(短按松开)
            cnt_nkey_click++;
            gpioKeyWaitTimer = KEY_NKEY_TIMER;
            delaySleepTimer = CNST_TIMER_DLY_SLP;

            if (bFlag_all_led_is_off)
            {
                bFlag_all_led_is_off = 0;

                if (displayData) //!电量不等于0
                {

                    forceDispTimer = 5; // 6 --5led  << -- 5 -- 4led 最后一个亮250ms               //跑马灯
                    bFlag_reverse = 0;
                    display_cycle = 125;                             //!跑马灯
                    ledDispTimer = CONST_TIMER_DISP_XSEC;            //!短按 亮5秒
                    display_timer_10minutes = CONST_TIMER_DISP_XSEC; //!短按 亮5秒 满电的时候灭灯
                }
                else
                {
                    ledDispTimer = CONST_TIMER_DISP_XSEC;            //!短按 亮5秒
                    display_timer_10minutes = CONST_TIMER_DISP_XSEC; //!短按 亮5秒 满电的时候灭灯
                }
            }
            // return MSG_MODE;//gpioKeyEvent[PreKeyIndex][1]; //SPR
        }
        else if (!gpioKeyWaitTimer) // if(gSysTick_current - gpioKeyWaitTimer > KEY_CP_TIMER)
        {
            // DBG(("ADC KEY CP!********\n"));
            gpioKeyState = GPIO_KEY_STATE_CP;
            cnt_nkey_click = 0xFF;

            return MSG_POWER_ON; // gpioKeyEvent[PreKeyIndex][2];  //CPS
        }

        break;

    case GPIO_KEY_STATE_CP:
        if (PreKeyIndex != KeyIndex)
        {
            // DBG(("ADC KEY CPR!*************\n"));
            gpioKeyState = GPIO_KEY_STATE_IDLE;
        }

        break;

    default:
        gpioKeyState = GPIO_KEY_STATE_IDLE;
        break;
    }

    return MSG_NONE;
}