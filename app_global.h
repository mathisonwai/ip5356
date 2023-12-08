

#ifndef __GLOBAL_H_
#define __GLOBAL_H_

#ifdef APP_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT extern
#endif

#include "app_cfg.h"

OS_CPU_EXT volatile bit bFlag_is_exception_full;
OS_CPU_EXT volatile bit bFlag_gSysTick_change; // vFlagbits.bit0
OS_CPU_EXT volatile bit bFlag_chg_or_dischg;    // 
OS_CPU_EXT volatile bit bFlag_charge_on;       // 充电
OS_CPU_EXT volatile bit bFlag_reg0xFD_bitx;
OS_CPU_EXT volatile bit bFlag_charge_qc;             //
OS_CPU_EXT volatile bit bFlag_in_small_current_mode; //
OS_CPU_EXT volatile bit bFlag_sink_pd;
OS_CPU_EXT volatile bit bFlag_derating_power_non_pd_9v; //
OS_CPU_EXT volatile bit bFlag_double_key;               //
OS_CPU_EXT volatile bit bFlag_discharge_qc;             //
OS_CPU_EXT volatile bit bFlag_discharge_pd;  
OS_CPU_EXT volatile bit bFlag_ovp_in_pd_9v;  
OS_CPU_EXT volatile bit bFlag_under_3v3;                // vFlagbits.bit3
OS_CPU_EXT volatile bit bFlag_Timeslice_16ms;           // vFlagbits.bit4
OS_CPU_EXT volatile bit bFlag_Timeslice_display;       // vFlagbits.bit5
OS_CPU_EXT volatile bit bFlag_led_blue_always_on; // vFlagbits.bit6
OS_CPU_EXT volatile bit bFlag_blink;              // vFlagbits.bit7

OS_CPU_EXT volatile bit bFlag_disable_send_cmd;  // vFlag2bits.bit2
OS_CPU_EXT volatile bit bFlag_p_ext_int_is_high; // vFlag2bits.bit3
OS_CPU_EXT volatile bit bFlag_isys_over_1A5;
OS_CPU_EXT volatile bit bFlag_init_ip5356;
OS_CPU_EXT volatile bit bFlag_plus_in_12v;


OS_CPU_EXT volatile bit bFlag_light_load;                // vFlag2bits.bit5
OS_CPU_EXT volatile bit bFlag_Bat_CC;                    // vFlag2bits.bit6
OS_CPU_EXT volatile bit bFlag_ad_voltage_battery_update; // vFlag2bits.bit7

OS_CPU_EXT volatile bit bFlag_is_breathing_mode; // vFlag3bits.bit0
OS_CPU_EXT volatile bit bFlag_temp_alarm;        // vFlag3bits.bit1
OS_CPU_EXT volatile bit bFlag_enable_charge;     // vFlag3bits.bit2
OS_CPU_EXT volatile bit bFlag_enable_discharge;  // vFlag3bits.bit3
OS_CPU_EXT volatile bit bFlag_temp_exception_over_chg;
OS_CPU_EXT volatile bit bFlag_temp_exception_chg; // bFlag_disable_ip53xx_quick_charge; // vFlag3bits.bit4
OS_CPU_EXT volatile bit bFlag_temp_exception_dischg;
OS_CPU_EXT volatile bit bFlag_ad_ntc_update;  // vFlag3bits.bit5
OS_CPU_EXT volatile bit bFlag_battery_is_low; // vFlag3bits.bit6
OS_CPU_EXT volatile bit bFlag_shutdown_eta;   // vFlag3bits.bit7
OS_CPU_EXT volatile bit bFlag_reverse;        // vFlag3bits.bit7
// bt status
OS_CPU_EXT volatile bit bFlag_charge_complete; // vFlag4bits.bit0
OS_CPU_EXT volatile bit bFlag_bt_standby;      // vFlag4bits.bit1
OS_CPU_EXT volatile bit bFlag_init_ip53xs;     // vFlag4bits.bit2
OS_CPU_EXT volatile bit bFlag_charge_ext;
// vFlag4bits.bit3
OS_CPU_EXT volatile bit bFlag_Timeslice_1ms;              // vFlag4bits.bit4
OS_CPU_EXT volatile bit bFlag_is_trickle_charge;    // vFlag4bits.bit5
OS_CPU_EXT volatile bit bFlag_charging_from_empty;  // vFlag4bits.bit6
OS_CPU_EXT volatile bit bFlag_Calc_Coulomb_Counter; // vFlag4bits.bit7
OS_CPU_EXT volatile bit bFlag_vsys_over_6v3;
OS_CPU_EXT volatile bit bFlag_vsys_over_12v8;
OS_CPU_EXT volatile bit bFlag_vsys_under_4v5;
OS_CPU_EXT volatile bit bFlag_in_scp_A3;
OS_CPU_EXT volatile bit bFlag_adjust_scp_ocp_5A;
OS_CPU_EXT volatile bit bFlag_adjust_scp_ocp_4A5;
OS_CPU_EXT volatile bit bFlag_typec_in;
OS_CPU_EXT volatile bit bFlag_usb_a1_in;
OS_CPU_EXT volatile bit bFlag_usb_a2_in;
OS_CPU_EXT volatile bit bFlag_all_led_is_off;

OS_CPU_EXT volatile bit bFlag_disable_quick_discharge;
OS_CPU_EXT volatile bit bFlag_disable_quick_charge;
OS_CPU_EXT volatile bit bFlag_input_ovp;
OS_CPU_EXT volatile bit bFlag_ocp;
OS_CPU_EXT volatile bit bFlag_short_circuit;
OS_CPU_EXT volatile bit bFlag_disable_charge_on;
OS_CPU_EXT volatile bit bFlag_disable_discharge_on;
OS_CPU_EXT volatile bit bFlag_vol_bat_over_4v;
OS_CPU_EXT volatile bit bFlag_derating_power_temp_ex;
OS_CPU_EXT volatile bit bFlag_vol_bat_under_3v5;
OS_CPU_EXT volatile bit bFlag_under_3v5_derating_power;

OS_CPU_EXT volatile bit bFlag_change_total_i_limit;
OS_CPU_EXT volatile bit bFlag_multi_port;
OS_CPU_EXT volatile bit bFlag_trel_over_7v;
OS_CPU_EXT volatile bit bFlag_v_chg_5v;
OS_CPU_EXT volatile bit bFlag_v_chg_7v;
OS_CPU_EXT volatile bit bFlag_v_chg_9v;
OS_CPU_EXT volatile bit bFlag_v_chg_12v;
OS_CPU_EXT volatile bit bFlag_cc_src_sink_ok;
OS_CPU_EXT volatile bit bFlag_power_on;
OS_CPU_EXT volatile bit bFlag_init_battery_volume;
OS_CPU_EXT volatile bit bFlag_vsys_under_4v75;

OS_CPU_EXT volatile bit bFlag_input_voltage_5v;
OS_CPU_EXT volatile bit bFlag_bat_vol_alarm;

OS_CPU_EXT volatile bit bFlag_under_voltage;
OS_CPU_EXT volatile bit bFlag_bat_under_voltage;

OS_CPU_EXT volatile bit bFlag_Timeslice_1sec;


OS_CPU_EXT volatile bit bFlag_light_load_left;
OS_CPU_EXT volatile bit bFlag_light_load_right;


// sbit ;
// sbit ;

// extern U32_T sleep_cnt;
// extern volatile U32_T Key_Map;
// extern volatile U16_T sampling_data0[17];
// extern volatile U16_T baseline_data0[17];
// extern volatile U16_T offset_data0_abs[17];

// OS_CPU_EXT U32_T Key_Map_bk;
// // OS_CPU_EXT U8_T  buzz_f;
// // OS_CPU_EXT U32_T buzz_cnt;
// OS_CPU_EXT RING_QUEUE_T uart_queue;
OS_CPU_EXT volatile unsigned char underVoltageDispTimer;
OS_CPU_EXT volatile unsigned char isys_grade;
OS_CPU_EXT volatile unsigned char last_isys_grade;

OS_CPU_EXT volatile unsigned char add_voltage_offset;
OS_CPU_EXT volatile unsigned char counter_isys_small;
OS_CPU_EXT volatile unsigned char counter_isys_big;
OS_CPU_EXT volatile unsigned char cc_dcp_mode;
OS_CPU_EXT volatile unsigned char last_cc_dcp_mode;
OS_CPU_EXT volatile unsigned char idexSum;
OS_CPU_EXT volatile unsigned char counter_dl;
OS_CPU_EXT volatile unsigned char counter_gl;
OS_CPU_EXT volatile unsigned char g_counter_cc;
OS_CPU_EXT volatile unsigned char g_counter_1sec;
OS_CPU_EXT volatile unsigned char timer_display_full;
OS_CPU_EXT volatile unsigned char indicator_light_mode;
OS_CPU_EXT volatile unsigned char displayDataLast;
OS_CPU_EXT volatile unsigned int display_cycle;

// OS_CPU_EXT GPIO_KEY_STATE gpioKeyState;

#ifdef BREATH_LED_MODE
OS_CPU_EXT volatile unsigned char led_lamp;
OS_CPU_EXT volatile unsigned char respiratory_rate; //呼吸次数
OS_CPU_EXT volatile unsigned char always_light_timer;
OS_CPU_EXT volatile unsigned char always_light_timer_shadow;
OS_CPU_EXT volatile unsigned char respiration_lamp_series;
OS_CPU_EXT volatile unsigned char respiration_lamp_timer;
#endif
OS_CPU_EXT volatile unsigned char restore_reg0x86;
OS_CPU_EXT volatile unsigned char restore_reg0xA6;
OS_CPU_EXT volatile unsigned char restore_reg0xAC;
OS_CPU_EXT volatile unsigned char restore_reg0xBB;
OS_CPU_EXT volatile unsigned char timer_display_slice_16ms;
// OS_CPU_EXT volatile unsigned char fastLedCnt;
// OS_CPU_EXT volatile unsigned int sys_value; // IP5328P 系统电压
OS_CPU_EXT volatile unsigned char gl_timer_out;
OS_CPU_EXT volatile unsigned char dl_timer_out;
OS_CPU_EXT volatile unsigned char under_voltage_timer_out;
// OS_CPU_EXT volatile unsigned char bOutPutUsb;    // 表示 �? USB  插入  2020/7/16
// OS_CPU_EXT volatile unsigned char bOutPutUsbEnd; // 表示 拔出USB 60s 无关�?结束
// OS_CPU_EXT volatile unsigned char bInPutUsb;     // 表示  插入  2020/7/16

OS_CPU_EXT volatile unsigned char battery_volume_voltage;
OS_CPU_EXT volatile unsigned char restore_power;
OS_CPU_EXT volatile unsigned char restore_reg0xb1;
OS_CPU_EXT volatile unsigned char restore_reg0xb5;
OS_CPU_EXT volatile unsigned char restore_reg0xb9;
OS_CPU_EXT volatile unsigned char restore_reg0x29;

OS_CPU_EXT volatile unsigned char default_power;
OS_CPU_EXT volatile unsigned int timer_derating_power;
OS_CPU_EXT volatile unsigned char derating_power_mode;
OS_CPU_EXT volatile unsigned char timer_dly_chk_vsys;

OS_CPU_EXT volatile unsigned char restore_chg_iset_vbus5v;
OS_CPU_EXT volatile unsigned char restore_chg_iset_vbus9v;
OS_CPU_EXT volatile unsigned char restore_chg_iset_vbus12v;

// OS_CPU_EXT volatile unsigned int delay_off_led_red_timer;
OS_CPU_EXT volatile unsigned int ack_status;
OS_CPU_EXT volatile unsigned int ad_ntc;
// OS_CPU_EXT volatile unsigned int ad_headset_left;
// OS_CPU_EXT volatile unsigned int ad_headset_right;
OS_CPU_EXT volatile unsigned int ad_voltage_battery;
OS_CPU_EXT volatile unsigned int ad_offset_by_power;
OS_CPU_EXT volatile unsigned char displayData;
// OS_CPU_EXT volatile unsigned char displayData;
OS_CPU_EXT volatile unsigned char timer_dly_chk_ovp;
// OS_CPU_EXT volatile unsigned char indicator_pao_ma;
// OS_CPU_EXT volatile unsigned char forceDispTimer;
OS_CPU_EXT volatile unsigned char compareTimer;
OS_CPU_EXT volatile unsigned int delaySleepTimer; //! 扩大 为了 2小时的�?�算时间
OS_CPU_EXT volatile unsigned char sendTimer;
OS_CPU_EXT volatile unsigned char display_timer_mask;
// OS_CPU_EXT volatile unsigned char underVoltageDispTimer;
OS_CPU_EXT volatile unsigned char forceDispTimer;
OS_CPU_EXT volatile unsigned char ledDispTimer;
OS_CPU_EXT volatile unsigned char timer_30_seconds;
OS_CPU_EXT volatile unsigned char timer_chg_minimum;
OS_CPU_EXT volatile unsigned char timer_dischg_minimum;
OS_CPU_EXT volatile unsigned char timer_led4_display;
OS_CPU_EXT volatile unsigned char gcounter;
OS_CPU_EXT volatile unsigned int display_timer_10minutes;
OS_CPU_EXT volatile unsigned int gSysTickCurrent;
OS_CPU_EXT volatile unsigned int gSysTick;

OS_CPU_EXT volatile unsigned int current_battery;
// OS_CPU_EXT volatile unsigned int voltage_battery;   //电池电压
OS_CPU_EXT volatile unsigned int ad_voltage_battery; //电池电压
OS_CPU_EXT volatile unsigned int i_charge;
OS_CPU_EXT volatile unsigned int i_discharge;
// OS_CPU_EXT volatile unsigned int i_charge_sum;//!库伦�?
// OS_CPU_EXT volatile unsigned int i_discharge_sum;//!库伦�?
// OS_CPU_EXT volatile unsigned int i_charge_average;//!库伦�?
// OS_CPU_EXT volatile unsigned int i_discharge_average;//!库伦�?
OS_CPU_EXT volatile unsigned int system_voltage;
OS_CPU_EXT volatile unsigned int system_current;
OS_CPU_EXT volatile unsigned int ad_current_vout;
OS_CPU_EXT volatile unsigned char timer_get_ip53xs_status;
// OS_CPU_EXT volatile unsigned char vsys_grade_dischg;
// OS_CPU_EXT volatile unsigned long gBatteryCapacity;//!库伦�?
// OS_CPU_EXT volatile unsigned long coulombSum;//!库伦�?
// OS_CPU_EXT volatile unsigned long battery_cap_every_1percent;//!库伦�?

// OS_CPU_EXT volatile unsigned int v_battery_average; //电池电压
// OS_CPU_EXT volatile unsigned int v_battery_sum;
OS_CPU_EXT volatile unsigned int v_input_output;    //�?/�? 电电�?
OS_CPU_EXT volatile unsigned int ad_i_input_output; //�?/�? 电流
OS_CPU_EXT volatile GPIO_KEY_STATE gpioKeyState;
OS_CPU_EXT volatile unsigned char gpioKeyWaitTimer;

// OS_CPU_EXT volatile unsigned int gCoulombSkipTimer;//!库伦�?
// OS_CPU_EXT volatile unsigned long gCoulombErrorBatteryCapacity;//!库伦�?

#define RX_BUF_SIZE 4
// OS_CPU_EXT volatile unsigned char RxQueueArray[RX_BUF_SIZE];
//-------------------------------------------------------------------------------------------------------------

// OS_CPU_EXT volatile unsigned char next_head;
// OS_CPU_EXT volatile unsigned int s_cmd_Queue[CMD_QUEUE_SIZE];
// OS_CPU_EXT RING_QUEUE_T cmd_queue;
// OS_CPU_EXT volatile unsigned int smartChargerWaitTimer;
// OS_CPU_EXT SMART_CHG_STATE smartChargerState;




void _dly_us(unsigned char Time);
void _dly_ms(unsigned char timer);
void init_gpio(void);
void init_wdt(void);
void init_timer4(void);
void init_system_parameter(void) ;
#endif
