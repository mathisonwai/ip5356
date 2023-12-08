

#include "app_cfg.h"
#include "app_global.h"

#include "bsp_i2c.h"
#include "bsp_ip53xs.h"

#ifndef _IP53XS_H_
#define _IP53XS_H_

// #define CONST_BAT_VOLTAGE_SET_UV 3058 // 3120 //! 3.03 << -- 2.97 << -- 2.90V
// #define CONST_BAT_VOLTAGE_0 3180      //! 3.18 << -- 3.15 << --- 3.16
// #define CONST_BAT_VOLTAGE_CLR_UV 3380 //! 3.38 << -- 3.36 << -- 3.34 << -- 3.3452
// #define CONST_BAT_VOLTAGE_100 4180    //! 4.18 << -- 4.165 << --- 4.176
// #define CONST_BAT_VOLTAGE_FULL 4190   //! 4.19 << -- 4.176 << --- 4.19

#define CONST_FTLR_4V 7
#define CONST_AD_VOLTAGE_3V85 (14336)
#define CONST_AD_VOLTAGE_3V9 (14522)
#define CONST_AD_VOLTAGE_3V96 (14746)
#define CONST_AD_VOLTAGE_4V0 (14895)
#define CONST_AD_VOLTAGE_4V05 (15080)

// #define COSNT_AD_BAT_3V5 (0x32E8) //13032
#define CONST_FTLR_3V5 7             //! <<--31  4 sec 8
#define CONST_AD_VOLTAGE_LOW (12925) // 3.47
// #define CONST_AD_VOLTAGE_LOW_UP (13212) // 3.55
#define CONST_AD_VOLTAGE_LOW_UP (14336) // 3.85

#define CONST_AD_VOLTAGE_SET_UV 11425 //! 3.068
// #define CONST_AD_VOLTAGE_SET_UV 11388 //! 3.058
#define CONST_AD_VOLTAGE_0 11646      //! 3.155
#define CONST_AD_VOLTAGE_CLR_UV 12580 //! 3.38
#define CONST_AD_VOLTAGE_100 15546    //! 4.175
#define CONST_AD_VOLTAGE_FULL (15574) //! 4.1825

#define CONST_AD_VOL_EVERY_PERCENT 39 //!

// Lithium battery capacity
#define CONST_CAP_05K 5000UL
#define CONST_CAP_10K 10000UL
#define CONST_CAP_12K 12000UL
#define CONST_CAP_16K 16000UL
#define CONST_CAP_20K 20000UL
#define CONST_CAP_30K 30000UL
#define CONST_CAP_40K 40000UL

// RDC值过大，将RDC适当减小（推�?10%�?20%�?  //K.S reg0x4b �?0x59
#define CONST_RDC_10K 0x9B // 52mR/0.336 = 155
#define CONST_RDC_12K 0x95 //
#define CONST_RDC_16K 0x85 //
#define CONST_RDC_20K 0x77 // 40mR/0.336 = 119
#define CONST_RDC_30K 0x59 // 30mR/0.336 = 89
#define CONST_RDC_40K 0x40 //
//----------------------------------------------------------------

#define CONST_TMR_30K 600
#define CONST_TMR_20K 400
#define CONST_TMR_16K 320
#define CONST_TMR_12K 240
#define CONST_TMR_10K 200
#define CONST_TMR_05K 125

// 0x02<-- 10000mAh; 0x03 <-- 20000mAh; 0x04 <-- 30000mAh
#define CONST_TRC_30K 0x04
#define CONST_TRC_20K 0x03
#define CONST_TRC_16K 0x03
#define CONST_TRC_12K 0x02
#define CONST_TRC_10K 0x02
#define CONST_TRC_05K 0x02

#define CONST_RDC CONST_RDC_10K
#define CONST_BAT_TYPE CONST_CAP_10K
#define CONST_TIMER CONST_TMR_10K
// #define CONST_TRICKLE 0x03//CONST_TRC_10K
//---------------------------------------------------------------
//! mAh --- 60 * 60 sec = 3600sec = 1hour
//#define CONST_BAT_CAP               (CONST_BAT_TYPE*3840UL) //3840UL/3600UL = 16/15 = 106.6666666667%
//#define CONST_BAT_CAP               (CONST_BAT_TYPE*3720UL) //
// #define CONST_BAT_CAP (CONST_BAT_TYPE * 3686UL) // 1.024%
#define CONST_BAT_CAP (CONST_BAT_TYPE * 3600UL) // 1.024%
//#define CONST_BAT_CAP               (CONST_BAT_TYPE*3600UL)
#define CONST_BAT_CAP_50PER (CONST_BAT_CAP / 2UL)
#define CONST_BAT_CAP_1PER (CONST_BAT_CAP / 100UL)

#define CNST_FILTER_COM 2

// 768mA - 0x300 --0B11 0000 0000        //if(I_BatInOutAverage >= 768)
// 767mA - 0x2FF --0B10 1111 1111        //if(I_BatInOutAverage < 768)
// 1024mA - 0x400 --0B100 0000 0000        //if(I_BatInOutAverage >= 1024)
// 1023mA - 0x3FF --0B11 1111 1111        //if(I_BatInOutAverage <= 1023)
//#define CONST_TRICKLE               0x04
//#define CONST_CHAGER_TIMER          511         //600



//!/! ------------------------------------------------------------------------
// ip5356  �?一�? I2C  开�?
#define DEVICE_ADDR_IP5356 (0XE8)

// 3.1 SYS_CTL0(boost �? charger 使能寄存�?)
// I2C 地址 0XE8 寄存器地址= 0x00
#define REG_SYS_CTL0 (0x00) //(boost �? charger 使能寄存�?)
//[7�?4]   RSERVED

//[3�?2] //EN_C2B_DET
// RESET -- 00
// 拔掉输入充电�?否自动转 boost 输出
// 1X：系统不�? boost 直接进入待机
// 01：输出有负载才自动开�? boost，没有负载就进入�?
// �?
// 00：无论输出是否有负载，自动开�? boost

// RESET  -- 1
#define b_EN_BOOST BIT1 // BOOST    输出使能
// RESET  -- 1
#define b_EN_CHARGER BIT0 // Charger  充电使能

#define REG_IP5356_0x01 (0x01) //默�?��? 0x33
#define REG_IP5356_0x02 (0x02) //默�?��? 0x71
#define REG_IP5356_0x04 (0x04) //默�?��? 0x7F
// 3.2 SYS_CTL1（轻载关机控制寄存器�?
// I2C 地址 0XE8 寄存器地址= 0x03
#define REG_SYS_CTL1 (0x03) //（轻载关机控制寄存器�? //默�?��? 0x64
//[7�?6]   RSERVED
//[5�?4]   SET ILOW TIME
// 轻载关机时间设置
// 00�?8S
// 01�?16S
// 10�?32S  < --- RESET
// 11�?64S
#define CONST_TIME_8S 0
#define CONST_TIME_16S 1
#define CONST_TIME_32S 2
#define CONST_TIME_64S 3
//[3]
#define b_En_Ipow_Low (BIT3)

//!----------------------------------
// 3.6 SYS_CTL2（轻载关机控制寄存器�?
// I2C 地址 0XE8 寄存器地址= 0x0F
// Bit(s) Name Description R/W RESET
//  IP5356 寄存器�?�明文档
// service@injoinic.com 5 / 32 V1.04
// 7:5 Reserved R/W XX
// 4 Wled_Act 按键开关照明灯方式选择
// 0：长�? 2S
// 1：连�?�?按两�?
// R/W 0
// 3 Lowcur_Off_Act 退出常开 N 小时按键方式选择
// 0：短�?
// 1：和进入常开 N 小时按键方式一�?
// R/W 0
// 2 Lowcur_On_Act 进入常开 N 小时按键方式选择
// 0：连�?�?按两�?
// 1：长�? 2S
// R/W 0
// 1 Dsb_Ahort 连续两�?�短按是否屏蔽短按使�?
// 0：不屏蔽�?�?
// 1：屏蔽短�?
// R/W 1
// 0 Reserved
#define REG_SYS_CTL2 (0x0F)

#define REG_SYS_CTL4 (0x31) //(按键关机)
// I2C 地址 0XE8 寄存器地址= 0x31
//[1:0]  Set_Key
#define b_Set_Key_1 BIT1
#define b_Set_Key_0 BIT0

#define REG_SYS_CTL5 (0x33)
#define b_en_Lowcur BIT5
//!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ip5356  �?一�? I2C 结束

//!---------------------------------------------------------------------------

//!>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>ip5356  �?二组 I2C  开�?
#define DEVICE_ADDR_IP5328 (0xEA)

// 4.1 BATVADC_DAT0（VBAT 电压寄存�?�? (备注�?//BATPIN 的真实电�?)
// I2C 地址 0XEA 寄存器地址= 0X50
#define REG_BATVADC_DAT0 (0x50) //�?8�?  5356

// 7:0 BATVADC[15:8] BATVADC 数据的高 8bit
//! VBAT=BATVADC*0.26855mv
// VBATPIN 的电�?

// 4.2 BATVADC_DAT1（VBAT 电压寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0X51
#define REG_BATVADC_DAT1 (0x51) // 5356

// -------------------------------------------------------------------------------------------
// 4.29 IBATIADC_DAT0（BAT �?电流寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0x6E
// 4.29 IBATIADC_DAT0（BAT �?电流寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0x6E
// Bit(s) Name Description R/W
// 7:0 IBATIADC[7:0] 电芯�?电流 IBATIADC 数据的低 8bit
#define REG_IBATIADC_DAT0 (0x6E) // 5356

// 4.30 IBATIADC_DAT1（BAT �?电流寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0x6F
// I2C 地址 0XEA 寄存器地址= 0x6F
// Bit(s) Name Description R/W
// 7:0 IBATIADC[15:8] 电芯�?电流 BATIADC 数据的高 8bit
//! IBAT=IBATVADC*1.6785mA
// 电流不区分�?�负方向

#define REG_IBATIADC_DAT1 (0x6F) // 5356

//! -------------------------------------
#define REG_IVSYS_DATA0 (0x70)
// 4.31 ISYS_IADC_DAT0（IVSYS �?电流寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0x70
// Bit(s) Name Description R/W
// 7:0 ISYSIADC[7:0] IVSYS �?电流 VSYSIADC 数据的低 8bit R

//! -----------------------------------------------
#define REG_IVSYS_DATA1 (0x71)
// 4.32 IVSYS_IADC_DAT1（IVSYS �?电流寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0x71
// Bit(s) Name Description R/W
// 7:0 IVSYSIADC[15:8
// ]
// IVSYS �?电流 VSYSIADC 数据的高 8bit
// IVSYS=ISYSVADC*0.671387mA
// 电流不区分�?�负方向
//! ---------------------------------------------------
//-------------------------------------------------------------------------------------------------
#define REG_VSYSVADC_DAT0 (0x52) //（VSYS 电压寄存�?�?
// 4.3 VSYSVADC_DAT0（VSYS 电压寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0X52
//  VSYS 电压数据的低 8bit
// VSYSPIN 的电�?

//----------------------------------------------------------------------------------------------------
#define REG_VSYSVADC_DAT1 (0x53) //（VSYS 电压寄存�?�?
//  VSYSVADC_DAT1（VSYS 电压寄存�?�?
// �? I2C 地址 0XEA 寄存器地址= 0X53
// VSYS 电压数据的高 8bit
// VSYSPIN 的电�?
// VSYS= VSYSVADC*1.611328mV

//!------------------------------------------------------------
#define INPUT_IADC_DAT0 (0X54) //（输入电流寄存器�? �? 8bit
// 4.5 IVIN/IVBUS_IADC_DAT0（输入电流寄存器�?
// I2C 地址 0XEA 寄存器地址= 0X54
// Bit(s) Name Description R/W
// 7:0 IVIN/IVBUS
// ADC[7:0]
// 充电输入电流数据的低 8bit
// VIN 输入或�? VBUS 输入的电�?
// R

//-----------------------------------------------------------
#define INPUT_IADC_DAT1 (0X55) //（输入电流寄存器�? �? 8bit
// 4.6 IVIN/IVBUS_IADC_DAT0（输入电流寄存器�?
// �? I2C 地址 0XEA 寄存器地址= 0X55
// Bit(s) Name Description R/W
// 7:0 IVIN/IVBUSADC
// [15:8]
// 充电输入电流数据的高 8bit
// VIN 输入或�? VBUS 输入的电�?

//VOUT1 输出电流数据的低 8bit
#define REG_IVOUT1_IADC_DAT0 (0x56)
#define REG_IVOUT1_IADC_DAT1 (0x57)

#define REG_IVOUT2_IADC_DAT0 (0x58)
#define REG_IVOUT2_IADC_DAT1 (0x59)
//------------------------------------------------------------------------------------------------
#define REG_FORCE_STANDBY (0x86) //（软件关机）
// I2C 地址 0XEA 寄存器地址= 0X86
//[7]
#define b_Force_Standby (BIT7)
//[6:0]
// SOC_CAP_SET Reserved
//!-----------------------------------------------------------------------------
#define PD_STATE1 0XC2 //（系统状态指示寄存器�?
#define b_Src_pd_ok (BIT7)
// I2C 地址 0XEA 寄存器地址= 0XC2
// Bit(s) Name Description R/W
// 7 Src _Pd_Ok PD SRC 输出连接标志�?
// 1：有�?
// 0：无�?

//!------------------------------------------------------

// 4.45 SYS_STATE0（系统状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XC4
// Bit(s) Name Description R/W
// 7 VINOK VIN 电压有效标志
// 1：VIN 有电
// 0：VIN 没电
// R
// 5 VBUSOV VBUS 输入过压标志
// 1：VBUS 输入过压
// 0：VBUS 输入没有过压
// R
// 4 VBUSOK VBUS 电压有效标志，TYPEC 充电放电�? bit 都会有效
// 1：VBUS 有电
// 0：VBUS 没电

#define REG_SYS_STATE0 (0xC4) //（系统状态指示寄存器�?
// #define b_VINOK         (BIT7)  //!错�??
#define b_VBUSOK (BIT4)
//-------------------------------------------------------------------------------
// 4.46 SYS_STATE1（系统状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XC5

#define REG_SYS_STATE1 (0xC5)
// [7:3]  Reserved

// [2]
// 电芯电压 VBATLOW 标志
// 1：电�?低电有效
// 0：电�?电压没有低电
#define b_VBATLOW (BIT2)

// [1]
// VSYS 过压标志
// 1：VSYS 过压
// 0：VSYS 没有过压
#define b_VSYS_OV (BIT1)

// [0]
// VIN 输入过压标志
// 1：VIN 输入过压
// 0：VIN 输入没有过压
#define b_VIN_OV (BIT0)

//----------------------------------------------------------------------------
#define REG_SYS_STATE2 (0xCD) //（系统状态指示寄存器�?
#define b_Src_qc_ok (BIT6)
// 4.47 SYS_STATE2（系统状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XCD
// Bit(s) Name Description R/W
// 7
// 6 Src_qc_ok 输出�?充有效标志位
// 1：有�?
// 0：无�?
// QC5V �? PD5V 不算�?�? OK

//---------------------------------------------------------------------------------
#define REG_SYS_STATE3 (0xD0) //（系统状态指示寄存器�?

#define b_VINOK (BIT7)
// I2C 地址 0XEA 寄存器地址= 0XD0

//----------------------------------------------------------------------------------------
#define REG_SYS_STATE4 (0xD4) //（系统状态指示寄存器�?
// 4.49 SYS_STATE4（系统状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XD4
// Bit(s) Name Description R/W
// 7:3 Reserved R
// 2:0 Chg_qc_state 充电输入�?充状�?
// 000：待机状�?
// 001：�?�于延时 0.5S 申�?�快充的状态中
// 010：未申�?�快�?
// 011：快充输�?
// 100：输入快充待申�?�状态，如涓流充�?
// 101：同充同放状�?

//---------------------------------------------------------------------------

// 4.52 CHG_STATE2（系统状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XE9
#define REG_CHG_STATE2 (0xE9) //（系统状态指示寄存器�?
//[7]
#define b_SINK_QC_OK BIT7 //输入�?充有效标志位（DM DP �?充和 PD�?充均有效)  1,  有效�?0，无�?
// [6�?4] 充电状�? chg_state
// 000 �?充电状�?
// 001 涓流充电
// 010 恒流充电
// 011 恒压充电
// 100 恒压�?开检测电�?电压
// 101 充满状�?
// 110 充电超时状�?

// [3]
#define b_Charge_en_state (BIT3)

//[2:0]  Reserved

//-----------------------------------------------------------------------------------------
// 4.53 MOS_STATE（输�? MOS 状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XEB
// Bit(s) Name Description R/W
// 7 At_same 同充同放标志�?
// 0：未在同充同�?
// 1：在同充同放
// R
// 6 Mos_vbus_state VBUS 口输�? MOS 状�?
// 0：关�?状�?
// 1：开�?状�?
// R
// 5 Mos_vout2_stat
// e
// Vout2 口输�? MOS 状�?
// 0：关�?状�?
// 1：开�?状�?
// R
// 4 Mos_vout1_stat
// e
// Vout1 口输�? MOS 状�?
// 0：关�?状�?
// 1：开�?状�?
// R
// 3 Src_qc_ok 输出�?充有效标志位
// 1：有�?
// 0：无�?
// QC5V �? PD5V 也算�?�? OK，建�?使用 0XCD bit6  //! �?0xCD BIT6
#define REG_MOS_STATE (0XEB) //（输�? MOS 状态指示寄存器�?
#define b_At_same (BIT7)
#define b_Mos_vbus_state (BIT6)
#define b_Mos_vout2_stat (BIT5)
#define b_Mos_vout1_stat (BIT4)

//-------------------------------------------------------------------------------
// 4.35 SOC_CAP_DATA（电�?电量数据寄存�?�?
// I2C 地址 0XEA 寄存器地址= 0X7B
// Bit(s) Name Description R/W
// 7:0 SOC_CAP 电芯百分比电量数�?(%)
#define REG_SOC_CAP_DATA (0x7B) //（电�?电量数据寄存�?�?

//-----------------------------------------------------------------------------------

// 4.54 ILOW_STATE（系统轻载状态指示寄存器�?
// I2C 地址 0XEA 寄存器地址= 0XF2
// Bit(s) Name Description R/W
// 7 Reserved R
// 6 Isys_low Isys 输出电流轻载标志�?
// 1：有�?
// 0：无�?
// R
// 5 Reserved R
// 4 Pow_low Isys 输出功率轻载标志�?
// 1：有�?
// 0：无�?
#define REG_ILOW_STATE (0xF2)
#define b_isys_low (BIT6)

// ip5356  �?二组 I2C 结束
#define CONST_VSYS_12V8 (7943) // 12 800 mv / 1.611328mV
#define CONST_VSYS_12V5 (7758) // 12 500 mv / 1.611328mV
#define CONST_VSYS_12V (7447)  // 12 000 mv / 1.611328mV

//! PD 20W 输出 OVP 保护  (9.7V,10.7V) 标准�? 10.2V

#define CONST_VSYS_10V2 (6331) // 9 000 mv / 1.611328mV
#define CONST_VSYS_9V7 (6020)  // 9 700 mv / 1.611328mV
#define CONST_VSYS_9V (5586)   // 9 000 mv / 1.611328mV

#define CONST_VSYS_6V2 (3848)
#define CONST_VSYS_5V9 (3660)

#define CONST_VSYS_5V2 (3227)
#define CONST_VSYS_5V1 (3165)
#define CONST_VSYS_5V0 (3100) // 3103
#define CONST_VSYS_4V9 (3040)
#define CONST_VSYS_4V8 (2978)
#define CONST_VSYS_4V75 (2948)
#define CONST_VSYS_4V7 (2916)
#define CONST_VSYS_4V6 (2854)
#define CONST_VSYS_4V5 (2793)
#define CONST_VSYS_4V85 (3010)

#define CONST_VSYS_6V (3723)
#define CONST_VSYS_7V (4344)
#define CONST_VSYS_10V (6206)

#define CONST_IT_FILTER 32
#define CONST_FILTER 63   // 16sec
#define CONST_FILTER_2 15 // 8sec
#define CONST_FILTER_8 7  // 4sec

///!-------------------------------------------------------------------------------
// void get_ad_voltage_battery(void);
void is_vsys_under_4v75(void);
void get_0xea_0xa9(void);
void get_voltage_battery(void);
void get_FLAG0_status(void);
void get_FLAG1_status(void);
void get_system_voltage(void);

void get_system_current(void);

void is_ovp_pd_9v(void);
void is_ovp_qc_12v(void);
void is_ovp_6v3(void);
void is_scp_over_4v5(void);
void get_p_ext_int_status(void);

void is_chg_or_dischg(void);
void get_current_vout1(void);
void get_current_vout2(void);

unsigned char get_percentage_voltage_Battery(void); //! 5356 库伦�?
void init_Battery_Volume(void);

void get_quick_charge_states(void);
void get_pd_charge_states(void);
void get_light_load_status(void);
void get_small_current_mode_status(void);

void disable_quick_charge(void);
void enable_quick_charge(void);
void disable_DPDM_quick_charge(void);
void disable_quick_discharge(void);
void enable_quick_discharge(void);

void enable_charger_on(void);
void disable_charger_on(void);
void enable_discharger_on(void);
void disable_discharger_on(void);

void derating_power_bat_under_3v5(void);
void derating_power_temp_exception(void);
void derating_power_temp_exception_again(void);
void derating_power_scp_over_4v5(void);

void restore_power_no_in_scp_A3(void);
void restore_power_temp_normal(void);
void restore_total_current_limiting(void);
void is_ocp_short_circuit(void);
void is_under_voltage(void);
void ovp_input_proc(void);

void get_multi_port_status(void);
void vol_bat_is_over_4v(void);
void vol_bat_is_over_3v5(void);
void vol_bat_is_under_3v5(void);
void get_protocol_indication(void);

void get_type_c_state(void);
void set_force_standby_mode(void);
void get_v_chg_state(void);

void is_charge_complete(void);

void is_sink_pd_ok(void);
void derating_power_non_pd_9v(void);
void restore_power_non_pd_9v(void);
void restore_reg0xAC_in_scp(void);
void restore_reg0xAC_in_scp(void);
void in_scp_add_voltage_offset(void);
void derating_power_bat_under_3v5_no_reset(void);
// void init_battery_volume(void);
// void get_battery_volume(void);
void get_cc_status(void);
void get_dcp_status(void);
void ipc_proc(void);
void reset_ipc_default(void);
void disable_DP_quick_charge(void);
void enable_DP_quick_charge(void);
void init_ip53xs(void);
#endif