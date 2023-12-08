/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"
#include "app_global.h"
// #include "app_display.h"
#include "bsp_i2c.h"
#include "bsp_ip53xs.h"
#include "app_bms_ip53xs.h"
#include "bsp_io_uart.h"
// #include "app_key.h"

/*

输入协议兼容性 IPC
Input protocol compatibility

IP5356输入协议兼容性：未针对适配器协议来抽电流，导致无CV输出的适配器过流保护；--->需要IP5356提供协议标志，MCU配合调整；
流程：
! IPC.1
上电初始化时，0xE8 0x25[5]=1   //开启C口的输入DCP使能
上电先读取5V充电电流参数0XE8 0x29[6:0]，并记录当前值。
! IPC.2
判断到C口处于5V充电状态时（0XEA 0XC4[4]=1 && 0XEA 0XD0[7]=1，0XEA 0XE8[5:4]=00），
void get_input_status(void)

!IPC.3
通过0XEA 0xDF[2:0]先判断输入CC模式，再判断0XEA 0x2D[7:0] DCP模式状态，

根据CC状态和DCP状态来设定输入电流。设定规则如下：

CC模式
001:defalult：   表示输入设备为USB模式的CC上拉。5V输入电流最大值限制为默认值，具体看DCP模式
011:1.5A：     表示输入设备为的1.5A模式的CC上拉。5V输入电流限制最大为1.5A，再看DCP模式
111:3A：      表示输入设备为的3A模式的CC上拉。5V输入电流最大值限制为默认值，具体看DCP模式

DCP模式
苹果2.4A模式：  表示输入设备DPDM为苹果2.4模式。5V输入电流限制在2.4A
苹果2.10A模式：  表示输入设备DPDM为苹果2.0A模式。5V输入电流限制在2.0A
苹果1.0A模式：  表示输入设备DPDM为苹果1.0A模式。5V输入电流限制在1.0A
浮空模式：   表示输入设备DPDM为浮空模式。5V输入电流按照可以按照默认值设置，
三星模式、DCP模式、CDP模式、SDP模式：   其他模式，5V输入电流限制2A

要调节充电电流时，请在默认值的基础上进行减档，默认值校准为2.8A。比如：
调节到2.4A，0XE8 0x29[6:0]默认值基础上减16档，减小400ma   25ma/step
调节到2.0A，0XE8 0x29[6:0] 默认值基础上减32档，减小800ma

当退出充电模式，电流阈值需要恢复默认值。当DCP模式、CC模式有变化时，需要实时调整充电电流参数。


*/
#if 0
static void init_ip53xs_2(void)
{
    unsigned char reg_ip53xs;

#ifdef IPC_FUNC
    // ! IPC.1.0
    // 上电先读取5V充电电流参数0XE8 0x29[6:0]，并记录当前值。
    reg_ip53xs = ip53xs_readByte(0xE8, 0x29); //
    restore_reg0x29 = reg_ip53xs;
#endif
    reg_ip53xs = ip53xs_readByte(0xE8, 0xA6); // Device 0xE8 reg 0xA6
    restore_reg0xA6 = reg_ip53xs;

    reg_ip53xs = ip53xs_readByte(0xE8, 0xAC); // Device 0xE8 reg 0xAC
    restore_reg0xAC = reg_ip53xs;

    reg_ip53xs = ip53xs_readByte(0xE8, 0xBB); // Device 0xE8 reg 0xBB
    restore_reg0xBB = reg_ip53xs;

    reg_ip53xs = ip53xs_readByte(0xE8, 0XB1); // Device 0xE8 reg 0xB1
    restore_reg0xb1 = reg_ip53xs;

    reg_ip53xs = ip53xs_readByte(0xE8, 0XB5); // Device 0xE8 reg 0xB5
    restore_reg0xb5 = reg_ip53xs;

    reg_ip53xs = ip53xs_readByte(0xE8, 0XB9); // Device 0xE8 reg 0xB9
    restore_reg0xb9 = reg_ip53xs;

    // 1、MCU在初始化IP5356寄存器时候需要先将ISYSLOW轻载关机功能关闭（En_Isys_Low I2C地址 0XE8 寄存器地址 0X03  bit2 写 0）
    reg_ip53xs = ip53xs_readByte(0xE8, REG_SYS_CTL1); // Device 0xE8 0X03
    // reg_ip53xs &= 0x3F;
    // reg_ip53xs |= (CONST_TIME_64S << 4);        //CONST_TIME_64S
    reg_ip53xs &= (~(BIT2));                          //! Q26 Q32 10/14
    ip53xs_writeByte(0xE8, REG_SYS_CTL1, reg_ip53xs); //
#ifdef IPC_FUNC
    // ! IPC.1.1
    // 上电初始化时，0xE8 0x25[5]=1   //开启C口的输入DCP使能
    reg_ip53xs = ip53xs_readByte(0xE8, 0x25); // 0x29 导致9V充电 直接上3A
    reg_ip53xs |= BIT5;
    ip53xs_writeByte(0xE8, 0x25, reg_ip53xs);
#endif

    // restore_chg_iset_vbus5v =

    //! 4.25 CHG_ CTL9（VBUS 9V 充电电流控制寄存器）
    // I2C 地址 0XE8 寄存器地址= 0x6F
    // Bit(s) Name Description R/W RESET
    // 7 Reserved R/W XX
    // 6:0 Chg_Iset_Vbus9v 9V VBUS 输入电流设置
    // I=25mA*N
    // 校准值为 2A 左右，如需要调整时可在校准值上增加或
    // 者减小相应档位
    // reg_ip53xs = ip53xs_readByte(0xE8, 0x6F); // Device 0xE8 reg 0x6F
    //     restore_chg_iset_vbus9v = reg_ip53xs;

    //     restore_chg_iset_vbus12v =

    // ip53xs_writeByte(0xE8, 0xA6, reg_ip53xs);

    //! new ic derating_power_scp_under_4v5();

    //! I2C 地址 0XE8 寄存器地址= 0XBB

    derating_power_non_pd_9v();
    bFlag_sink_pd = 0;

    // REG_SYS_CTL2
    reg_ip53xs = ip53xs_readByte(0xE8, REG_SYS_CTL2); // Device 0xE8
    reg_ip53xs &= 0xE1;
    reg_ip53xs |= (BIT1);
    ip53xs_writeByte(0xE8, REG_SYS_CTL2, reg_ip53xs); //

    //! disable常开模式 再enble常开模式  解决小电流模式下过流 通过插拔恢复 之后还在小电流模式
    reg_ip53xs = ip53xs_readByte(0xE8, REG_SYS_CTL5); // Device 0xE8
    reg_ip53xs &= 0xDF;                               // bit5 写0
    ip53xs_writeByte(0xE8, REG_SYS_CTL5, reg_ip53xs); //
    _dly_ms(10);
    reg_ip53xs = ip53xs_readByte(0xE8, REG_SYS_CTL5); // Device 0xE8
    reg_ip53xs &= 0xDF;
    reg_ip53xs |= (BIT5);                             // bit5 写1
    ip53xs_writeByte(0xE8, REG_SYS_CTL5, reg_ip53xs); //

    // //! 放初始化代码中做
    reg_ip53xs = ip53xs_readByte(0xE8, 0x31); // Device 0xE8
    reg_ip53xs &= 0xFC;                       //! 00：disable 按键关机使能
    ip53xs_writeByte(0xE8, 0x31, reg_ip53xs); //

    reg_ip53xs = ip53xs_readByte(0xE8, 0x33); // Device 0xE8
    reg_ip53xs |= BIT5;                       //! bit5 写 1
    ip53xs_writeByte(0xE8, 0x33, reg_ip53xs); //

    // 3.3 CHG_CTL0 （12V 输入充电欠压环路电压控制寄存器）
    // I2C 地址 0XE8 寄存器地址= 0x0B
    reg_ip53xs = ip53xs_readByte(0xE8, 0x0B); // Device 0xE8 reg 0x0B
    reg_ip53xs &= 0xF8;                       //
    ip53xs_writeByte(0xE8, 0x0B, reg_ip53xs); //

    // 3.4 CHG_CTL1 （9V 输入充电欠压环路电压控制寄存器）
    // I2C 地址 0XE8 寄存器地址= 0x0C
    reg_ip53xs = ip53xs_readByte(0xE8, 0x0C); // Device 0xE8 reg 0x0C
    reg_ip53xs &= 0xC7;                       // 0b 1100 0111                     //
    ip53xs_writeByte(0xE8, 0x0C, reg_ip53xs); //

    // 0xEA 0X34[5:4]=11   初始化配置这个寄存器试试看

    // reg_ip53xs = ip53xs_readByte(0xEA, 0x34); // Device 0xEA reg 0x34
    // reg_ip53xs &= 0xCF;                       // 0b 1100 1111                     //
    // // reg_ip53xs |= BIT5;
    // // reg_ip53xs |= BIT4;
    // reg_ip53xs |= 0x30;  //! 0b 0011 0000
    // ip53xs_writeByte(0xEA, 0x34, reg_ip53xs); //

    reg_ip53xs = ip53xs_readByte(0xEA, 0xFC); // Device 0xEA  0xFC

    // if ((BIT0 == (reg_ip53xs & BIT0)) || (BIT2 == (reg_ip53xs & BIT2)))
    // {
    //! 写1清0
    ip53xs_writeByte(0xEA, 0xFC, reg_ip53xs);
    // }
    //! 写1清0
    reg_ip53xs = ip53xs_readByte(0xEA, 0xFD); // Device 0xEA  0xFC
    ip53xs_writeByte(0xEA, 0xFD, reg_ip53xs);

    //! 11/11 add
    // if (bFlag_vol_bat_under_3v5) && bFlag_in_scp_A3) //! fix a bug  1029 要在SCP协议下 才需要降低功率
    if (bFlag_vol_bat_under_3v5)
    {

        derating_power_bat_under_3v5_no_reset();
    }

#if 1 //! a bug
    if (bFlag_temp_exception_chg)
    {
        // reg_ip53xs = ip53xs_readByte(0xEA, REG_SYS_STATE3); //
        // if (reg_ip53xs & BIT5)
        // if (bFlag_charge_on)
        // {
        // if (0 == bFlag_disable_quick_charge)
        // 1
        reg_ip53xs = ip53xs_readByte(0xEA, 0x91); // Device 0xEA
        //[3:2] 01
        reg_ip53xs &= 0x0C; // 1111 0011              //
        // reg_ip53xs |= 0x04;                       //(1<<2);
        // ip53xs_writeByte(0xEA, 0x91, reg_ip53xs); //! [3:2] 01

        if (0x04 != reg_ip53xs) //! 使能快充
        {
            // disable_quick_charge(); //! 充电
            disable_DP_quick_charge(); //! 不会自动恢复
            bFlag_disable_quick_charge = 1;

            // }
            // else
            // {
            //
            // }

            // if (0 == bFlag_derating_power_temp_ex) //! fix a bug
            // {
        }

        disable_DPDM_quick_charge(); //! 这个会自动恢复 关闭PD 9V 则不会自动恢复
        derating_power_temp_exception();
        timer_derating_power = 255; //! 32sec <-- 63; // 63/8 = 8sec
        // }
    }
    else //! add 12/27 fix a bug
    {
        // if (bFlag_disable_quick_charge)
        // 1
        reg_ip53xs = ip53xs_readByte(0xEA, 0x91); // Device 0xEA
        //[3:2] 01
        reg_ip53xs &= 0x0C; // 1111 0011              //
        // reg_ip53xs |= 0x04;                       //(1<<2);
        // ip53xs_writeByte(0xEA, 0x91, reg_ip53xs); //! [3:2] 01
        if (0x04 == reg_ip53xs) //! 禁止快充
        {
            // enable_quick_charge(); //充电
            enable_DP_quick_charge(); //! 不会自动恢复
            bFlag_disable_quick_charge = 0;
        }
    }
#endif
    // //! 0xE8 0xAA[3]=1 使能SCP加压补偿
    // reg_ip53xs = ip53xs_readByte(0xE8, 0xAA);
    // reg_ip53xs |= BIT3;
    // ip53xs_writeByte(0xE8, 0xAA, reg_ip53xs);

    // //! 0xEA 0x0E[3:2] //VOUT2 SCP 协议加压 00: 0mV; 01: 60mV;  10: 120mV; 11: 240mV
    // reg_ip53xs = ip53xs_readByte(0xEA, 0x0E);
    // reg_ip53xs &= 0xF3; // 1111 0011
    // reg_ip53xs |= BIT3; // 1111 1011  //! 10: 120mV;
    // ip53xs_writeByte(0xEA, 0x0E, reg_ip53xs);

    //! 1109 11/11 待完善！！！！！\
    //! 1<---
    //! MCU初始化0xEA 0x0B[6:4]=110，试试这个配置能不能改善
    //! (后记: 电池电压在4.16V 以上12v 9V 过流测试 没有出现 4V ，1.9A等的异常情况 但过流标志在 2.7A以下 没有读到)
    //! (后后记: 加欠压判断 改善了 读不到 过流导致一直打嗝的问题 单还是有概率出现 待ip进一步改善）
    reg_ip53xs = ip53xs_readByte(0xEA, 0x0B);
    reg_ip53xs &= 0x8F; // 1000 1111
    reg_ip53xs |= 0x60; // 0110 0000  //! [6:4]=110
    ip53xs_writeByte(0xEA, 0x0B, reg_ip53xs);

    //! 2 << ---

    // 快充输出接近过流值时，会出现4.2V 1.9A的异常现象
    // 1、MCU实时读取0Xea 0xa9[7:0]的值   //3.2V+40mV*N
    // 2、当满足0Xea 0xa9[7:0]的值大于7V并且VBAT大于4V时
    // 3、MCU判断VSYS电压值，当出现VSYS < 4.75V时，关闭输出，进入过流保护状态

    //!  i2c地址E8 寄存器地址8F bit3写0试下scp的问题
    //!  解决原装线 在20% - 30% 低电量的时候 不能进 SCP
    reg_ip53xs = ip53xs_readByte(0xE8, 0x8F);
    reg_ip53xs &= 0xF7; // 1111 0111
    // reg_ip53xs |= 0x60; // 0110 0000
    ip53xs_writeByte(0xE8, 0x8F, reg_ip53xs);

    // 4.61 BATLOW(模拟电芯低电关机电压)
    // I2C 地址 0XEA 寄存器地址= 0X03
    // Bit(s) Name Description R/W RESET
    // 7:1 Reserved R/W XX
    // 0 BATLOW_SET_A 模拟BATLOW电压设置(下降沿保护电压-上升沿恢复电
    // 压)
    // 0:2.9V-3.0V
    // 1:3.0V-3.1V
    reg_ip53xs = ip53xs_readByte(0xEA, 0x03);
    reg_ip53xs &= 0xFE; // 1111 1110
    ip53xs_writeByte(0xEA, 0x03, reg_ip53xs);

    //! 兼容性
    // 上电初始化时，0xE8 0xD0[2]=0 //移除CC选择PDdebounce。再测试验证下这些兼容性问题。
    reg_ip53xs = ip53xs_readByte(0xE8, 0xD0);
    reg_ip53xs &= 0xFB; // 1111 1011
    ip53xs_writeByte(0xE8, 0xD0, reg_ip53xs);

    //! vin 自适应
    // 寄存器地址0X39 bit7-5修改为010  I2C地址0XEA
    reg_ip53xs = ip53xs_readByte(0xEA, 0x39);
    reg_ip53xs &= 0x1F; // 0001 1111
    reg_ip53xs |= BIT6;
    ip53xs_writeByte(0xEA, 0x39, reg_ip53xs);

    //! 0xE8 0x90[1:0]=10
    //! 改善SCP兼容性的问题。
    reg_ip53xs = ip53xs_readByte(0xE8, 0x90);
    reg_ip53xs &= 0xFC; // 1111 1100
    reg_ip53xs |= BIT1;
    ip53xs_writeByte(0xE8, 0x90, reg_ip53xs); //! ifx a bug 写 0xE8 0x90 写到别的寄存器了 2022/01/04

    //! 解决 南芯SCP工具SCP下过流不断打嗝的问题
    //!  4.9 VOUT1_CTL2（VOUT1 控制寄存器）
    // I2C 地址 0XE8 寄存器地址= 0x1C
    // Bit(s) Name Description R/W RESET
    // 7:1 Reserved R/W XX
    // 0 En_Vout1_DmDp_Det VOUT1口DM DP负载检测使能
    // 1：enable
    // 0：disable

    reg_ip53xs = ip53xs_readByte(0xE8, 0x1C);
    reg_ip53xs &= 0xFE; // 1111 1110
    ip53xs_writeByte(0xE8, 0x1C, reg_ip53xs);

    // 4.12 VOUT2_CTL2（VOUT2 控制寄存器）
    // I2C 地址 0XE8 寄存器地址= 0x1D
    // Bit(s) Name Description R/W RESET
    // 7:1 Reserved R/W XX
    // 0 En_Vout2_DmDp_Det VOUT2口DM DP负载检测使能
    // 1：enable
    reg_ip53xs = ip53xs_readByte(0xE8, 0x1D);
    reg_ip53xs &= 0xFE; // 1111 1110
    ip53xs_writeByte(0xE8, 0x1D, reg_ip53xs);

    //! [3:2]
    // 1X：系统不转 boost 直接进入待机  10/11 add by kwangsi
    // 01：输出有负载才自动开启 boost，没有负载就进入关机
    // 00：无论输出是否有负载，自动开启 boost  //!default
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs &= 0xF3;                       // 1111 0011
    reg_ip53xs |= (BIT2);
    // reg_ip53xs |= (BIT3);                     //! Q2 : [3:2] 1X：系统不转 boost 直接进入待机  10/11 add by kwangsi
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00

    // !初始化  0XE8 0X00 bit3：2=01  & 0xE8 0x01[2:0]=100
    reg_ip53xs = ip53xs_readByte(0xE8, 0x01); // Device 0xE8 reg 0x01
    reg_ip53xs &= 0xF8;                       // 1111 1000
    reg_ip53xs |= (BIT2);
    ip53xs_writeByte(0xE8, 0x01, reg_ip53xs); // Device 0xE8 reg 0x01
}
#endif
// SYS_STATE2  放电
// SYS_STATE4  充电
// 判断是否在快充状态
void get_quick_charge_states(void)
{

    unsigned char reg_ip53xs; // 0x05
    unsigned char iitmp;
    static unsigned char counter;

    if (bFlag_charge_on)
    {
        // 充电快充判断
        bFlag_discharge_qc = 0;
        reg_ip53xs = ip53xs_readByte(0xEA, REG_SYS_STATE4); //
        iitmp = (reg_ip53xs & 0x07);

        if (bFlag_charge_qc)
        {
            if (0x03 != iitmp)
            {
                if (++counter > 2)
                {
                    counter = 0;
                    bFlag_charge_qc = 0;
                }
            }
            else
            {
                counter = 0;
            }
        }
        else
        {
            if (0x03 == iitmp)
            {
                if (++counter > 2)
                {
                    counter = 0;
                    bFlag_charge_qc = 1;
                }
            }
            else
            {
                counter = 0;
            }
        }
    }
    else
    {
        // 放电快充判断
        bFlag_charge_qc = 0;
        reg_ip53xs = ip53xs_readByte(0xEA, REG_SYS_STATE2); //
        iitmp = (reg_ip53xs & b_Src_qc_ok);

        if (bFlag_discharge_qc)
        {
            if (0 == iitmp)
            {
                if (++counter > CNST_FILTER_COM)
                {
                    counter = 0;
                    bFlag_discharge_qc = 0;
                }
            }
            else
            {
                counter = 0;
            }
        }
        else
        {
            if (iitmp)
            {
                if (++counter > CNST_FILTER_COM)
                {
                    counter = 0;
                    bFlag_discharge_qc = 1;
                }
            }
            else
            {
                counter = 0;
            }
        }
    }
}

//! 4.48 PD_STATE1（系统状态指示寄存器）
// I2C 地址 0XEA 寄存器地址= 0XC2
// Bit(s) Name Description R/W
//! 7 Src _Pd_Ok PD SRC 输出连接标志位
// 1：有效
// 0：无效

void get_pd_charge_states(void)
{

    unsigned char reg_ip53xs; // 0x05
    unsigned char iitmp;
    static unsigned char counter;

    // 放电快充判断

    reg_ip53xs = ip53xs_readByte(0xEA, 0xC2); //
    iitmp = (reg_ip53xs & b_Src_pd_ok);

    if (bFlag_discharge_pd)
    {
        if (0 == iitmp)
        {
            if (++counter > CNST_FILTER_COM)
            {
                counter = 0;
                bFlag_discharge_pd = 0;
                bFlag_ovp_in_pd_9v = 0;
                if (bFlag_disable_discharge_on)
                {
                    if (0 == bFlag_temp_exception_dischg)
                    {

                        enable_discharger_on();
                    }
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (iitmp)
        {
            if (++counter > CNST_FILTER_COM)
            {
                counter = 0;
                bFlag_discharge_pd = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
}
#ifdef IPC_FUNC
// ! IPC.2
// 判断到C口处于5V充电状态时（0XEA 0XC4[4]=1 && 0XEA 0XD0[7]=1，0XEA 0XE8[5:4]=00），
void get_input_voltage_status(void)
{
    unsigned char reg_ip53xs;
    static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, 0XE8);

    reg_ip53xs &= 0x30; //! 0011 0000

    if (bFlag_input_voltage_5v)
    {
        if (0 != reg_ip53xs)
        {
            if (++counter > CNST_FILTER_COM)
            {
                counter = 0;
                bFlag_input_voltage_5v = 0;
                cc_dcp_mode = 0;
                last_cc_dcp_mode = 0;
                reset_ipc_default();
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (0 == reg_ip53xs)
        {
            if (++counter > CNST_FILTER_COM)
            {
                counter = 0;
                bFlag_input_voltage_5v = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
}

// !IPC.3
// 通过0XEA 0xDF[2:0]先判断输入CC模式，再判断0XEA 0x2D[7:0] DCP模式状态，

// 根据CC状态和DCP状态来设定输入电流。设定规则如下：

// CC模式
// 001:defalult：   表示输入设备为USB模式的CC上拉。5V输入电流最大值限制为默认值，具体看DCP模式
// 011:1.5A：     表示输入设备为的1.5A模式的CC上拉。5V输入电流限制最大为1.5A，再看DCP模式
// 111:3A：      表示输入设备为的3A模式的CC上拉。5V输入电流最大值限制为默认值，具体看DCP模式

// DCP模式
// 苹果2.4A模式：  表示输入设备DPDM为苹果2.4模式。5V输入电流限制在2.4A
// 苹果2.10A模式：  表示输入设备DPDM为苹果2.0A模式。5V输入电流限制在2.0A
// 苹果1.0A模式：  表示输入设备DPDM为苹果1.0A模式。5V输入电流限制在1.0A
// 浮空模式：   表示输入设备DPDM为浮空模式。5V输入电流按照可以按照默认值设置，
// 三星模式、DCP模式、CDP模式、SDP模式：   其他模式，5V输入电流限制2A

// 要调节充电电流时，请在默认值的基础上进行减档，默认值校准为2.8A。比如：
// 调节到2.4A，0XE8 0x29[6:0]默认值基础上减16档，减小400ma   25ma/step
// 调节到2.0A，0XE8 0x29[6:0] 默认值基础上减32档，减小800ma

// 当退出充电模式，电流阈值需要恢复默认值。当DCP模式、CC模式有变化时，需要实时调整充电电流参数。
//! cc_dcp_mode   高4位 D+D-  低4位 CC
//! 通过0XEA 0xDF[2:0]先判断输入CC模式
void get_cc_status(void)
{
    unsigned char reg_ip53xs;
    // static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, 0xDF);
    reg_ip53xs &= 0x07;
    cc_dcp_mode &= 0xF0;
    cc_dcp_mode |= reg_ip53xs;

    // CC模式
    //! 001:defalult：   表示输入设备为USB模式的CC上拉。5V输入电流最大值限制为默认值，具体看DCP模式
    //! 011:1.5A：     表示输入设备为的1.5A模式的CC上拉。5V输入电流限制最大为1.5A，再看DCP模式
    //! 111:3A：      表示输入设备为的3A模式的CC上拉。5V输入电流最大值限制为默认值，具体看DCP模式

    //! CC 1.5A
    // if (0 == (cc_dcp_mode & BIT0))
    // {
    //     if (reg_ip53xs == 0x03)
    //     {
    //         cc_dcp_mode |= BIT0;
    //     }
    // }
    // else
    // {
    //     if (reg_ip53xs != 0x03) //! fix a bug  C1
    //     {
    //         cc_dcp_mode &= (~BIT0);
    //     }
    // }
}

//! 再判断0XEA 0xAD[7:0] DCP模式状态，
//! cc_dcp_mode   高4位 D+D-  低4位 CC
void get_dcp_status(void)
{
    unsigned char reg_ip53xs;
    // static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, 0xAD);
    cc_dcp_mode &= 0x0F; //! 0000 1111 清高4位

    if (reg_ip53xs & BIT0)
    {
        cc_dcp_mode |= BIT4; // apple 1.0A
    }
    else if (reg_ip53xs & BIT1)
    {
        cc_dcp_mode |= BIT5; // apple 2.1A
    }
    else if (reg_ip53xs & BIT2)
    {
        cc_dcp_mode |= BIT6; // apple 2.4
    }
    else if (reg_ip53xs & 0xF0)
    {
        cc_dcp_mode |= BIT7; //! 其他模式 (三星模式、DCP模式、CDP模式、SDP模式)   5V输入电流限制2.1A
    }
}

// 要调节充电电流时，请在默认值的基础上进行减档，默认值校准为2.8A。比如：
// 调节到2.4A，0XE8 0x29[6:0]默认值基础上减16档，减小400ma   25ma/step
// 调节到2.0A，0XE8 0x29[6:0] 默认值基础上减32档，减小800ma

// #define CONST_IPC_2P4 (96)
// #define CONST_IPC_2P1 (84)
// #define CONST_IPC_1P5 (60)
// #define CONST_IPC_1P0 (40)

void ipc_proc(void)
{
    unsigned char reg_ip53xs;
    unsigned char reg_ip53xs_read;
    unsigned char reg0x29_2F1; // 1400mA
    unsigned char reg0x29_4F1; // 700mA
    unsigned char reg0x29_8F1; // 350mA
    // if (0 == (cc_dcp_mode & 0xFE))
    // {
    //     return;
    // }

    reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
    reg_ip53xs = (restore_reg0x29 & 0x7F);
    reg_ip53xs >>= 1;
    reg0x29_2F1 = reg_ip53xs;
    reg_ip53xs >>= 1;
    reg0x29_4F1 = reg_ip53xs;
    reg_ip53xs >>= 1;
    reg0x29_8F1 = reg_ip53xs;

    switch (cc_dcp_mode & 0x0F)
    {
    case 0:                     // 按DCP去做
        if (cc_dcp_mode & BIT4) // 1.0A
        {
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            // reg_ip53xs = (restore_reg0x29 - 72);
            reg_ip53xs = restore_reg0x29;
            reg_ip53xs -= reg0x29_2F1;
            reg_ip53xs -= reg0x29_8F1;
            // reg_ip53xs = (restore_reg0x29 & BIT7);
            // reg_ip53xs |= CONST_IPC_1P0;
            // ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }
        else if (0 == bFlag_temp_exception_chg) //! 温度正常
        {
            if (cc_dcp_mode & BIT5) // 2.1A
            {
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P1;
                // reg_ip53xs = (restore_reg0x29 - 28);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_4F1;
            }
            else if (cc_dcp_mode & BIT6) // 2.4A
            {
                // reg_ip53xs = (restore_reg0x29 - 16);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_8F1;
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P4;
            }
            else
            {
                reg_ip53xs = restore_reg0x29; //! default
            }
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
        }

        break;
    case 1: //! default

        if (cc_dcp_mode & BIT4) // 1.0A
        {
            // reg_ip53xs = (restore_reg0x29 - 72);
            reg_ip53xs = restore_reg0x29;
            reg_ip53xs -= reg0x29_2F1;
            reg_ip53xs -= reg0x29_8F1;
            // reg_ip53xs = (restore_reg0x29 & BIT7);
            // reg_ip53xs |= CONST_IPC_1P0;
            // ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }
        else if (0 == bFlag_temp_exception_chg) //! 温度正常
        {
            if (cc_dcp_mode & BIT5) // 2.1A
            {
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P1;
                // reg_ip53xs = (restore_reg0x29 - 28);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_4F1;
            }
            else if (cc_dcp_mode & BIT6) // 2.4A
            {
                // reg_ip53xs = (restore_reg0x29 - 16);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_8F1;
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P4;
            }
            else
            {
                reg_ip53xs = restore_reg0x29; //! default
            }
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }

        break;
    case 3: //! 1A5

        if (cc_dcp_mode & BIT4) // 1.0A
        {
            // reg_ip53xs = (restore_reg0x29 - 72);
            reg_ip53xs = restore_reg0x29;
            reg_ip53xs -= reg0x29_2F1;
            reg_ip53xs -= reg0x29_8F1;
            // reg_ip53xs = (restore_reg0x29 & BIT7);
            // reg_ip53xs |= CONST_IPC_1P0;
            // ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }
        else if (0 == bFlag_temp_exception_chg) //! 温度正常
        {
            if (cc_dcp_mode & BIT5) // 2.1A
            {
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P1;
                // reg_ip53xs = (restore_reg0x29 - 28);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_4F1;
            }
            else if (cc_dcp_mode & BIT6) // 2.4A
            {
                // reg_ip53xs = (restore_reg0x29 - 16);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_8F1;
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P4;
            }
            else
            {
                // reg_ip53xs = (restore_reg0x29 - 52); //! 1.5A
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_2F1;
            }
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }

        break;
    case 7:                     //! 3A
        if (cc_dcp_mode & BIT4) // 1.0A
        {
            // reg_ip53xs = (restore_reg0x29 - 72);
            reg_ip53xs = restore_reg0x29;
            reg_ip53xs -= reg0x29_2F1;
            reg_ip53xs -= reg0x29_8F1;
            // reg_ip53xs = (restore_reg0x29 & BIT7);
            // reg_ip53xs |= CONST_IPC_1P0;
            // ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }
        else if (0 == bFlag_temp_exception_chg) //! 温度正常
        {
            if (cc_dcp_mode & BIT5) // 2.1A
            {
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P1;
                // reg_ip53xs = (restore_reg0x29 - 28);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_4F1;
            }
            else if (cc_dcp_mode & BIT6) // 2.4A
            {
                // reg_ip53xs = (restore_reg0x29 - 16);
                reg_ip53xs = restore_reg0x29;
                reg_ip53xs -= reg0x29_8F1;
                // reg_ip53xs = (restore_reg0x29 & BIT7);
                // reg_ip53xs |= CONST_IPC_2P4;
            }
            else
            {
                reg_ip53xs = restore_reg0x29; //! default
            }
            // reg_ip53xs_read = ip53xs_readByte(0xE8, 0x29);
            if (reg_ip53xs_read != reg_ip53xs)
            {
                ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
            }
        }

        break;

    default:
        break;
    }
    // reg_ip53xs = ip53xs_readByte(0xE8, 0x29); //
}

void reset_ipc_default(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x29);
    if (restore_reg0x29 != reg_ip53xs)
    {
        reg_ip53xs = restore_reg0x29;
        ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
    }
}
#endif
// 判断充电 放电 待机 状态
//  判断当前 C 口（VBUS）输入电压有效 0XEA 0XC4[4]=1 && 0XEA 0XD0[7]=1
void is_chg_or_dischg(void)
{
    unsigned char iitmp;
    unsigned char iitmp2;
    unsigned char reg_ip53xs;
    static unsigned char counter;

    reg_ip53xs = ip53xs_readByte(0xEA, REG_SYS_STATE0); // (0xC4) ---REG_SYS_STATE0//（系统状态指示寄存器）
    iitmp2 = (reg_ip53xs & b_VBUSOK);                   // bit 4

    reg_ip53xs = ip53xs_readByte(0xEA, REG_SYS_STATE3); // 0xD0 --REG_SYS_STATE3
    iitmp = (reg_ip53xs & b_VINOK);                     // bit 7

    if (bFlag_charge_on) //! 在充电状态下
    {
        delaySleepTimer = CONST_DSL_SHORT; //! 防止充电状态MCU关5356

        if (0 == (iitmp2 && iitmp))
        {
            bFlag_chg_or_dischg = 0;
            if (++counter > 5) // CNST_FILTER_COM
            {
                counter = 0;
                bFlag_charge_on = 0; //! 放电
                bFlag_charge_qc = 0;
                bFlag_cc_src_sink_ok = 0; //! fix a bug
                bFlag_input_ovp = 0;      // !important 配置成根据是否带载 开启boost 之后 必须在这里清除 否则可能不能解除ovp 之前是放休眠做 因为拔出充电直接转休眠了
                bFlag_charge_ext = 0;     // 无协议充电状态
                g_counter_cc = 0;
#ifdef IPC_FUNC
                cc_dcp_mode = 0;
                last_cc_dcp_mode = 0;
                reset_ipc_default();
#endif
            }
        }
        else
        {
            counter = 0;
            if (iitmp2 && iitmp)
            {
                bFlag_chg_or_dischg = 1;
            }
        }
#ifdef IPC_FUNC
        get_input_voltage_status();
#endif
    }
    else // 在放电状态下
    {
        if (iitmp2 && iitmp)
        {
            bFlag_chg_or_dischg = 1;
            if (++counter > CNST_FILTER_COM) // 2次
            {
                counter = 0;
                bFlag_charge_on = 1; //! 充电
                bFlag_charge_qc = 0;
                bFlag_vsys_over_12v8 = 0;
                bFlag_vsys_over_6v3 = 0;
                bFlag_ovp_in_pd_9v = 0;
                display_timer_10minutes = CONST_TIMER_10_MINS;
                timer_dly_chk_ovp = 31;
                if (bFlag_all_led_is_off)
                {
                    bFlag_all_led_is_off = 0;

                    forceDispTimer = 5; // 6 --5led  << -- 5 -- 4led 最后一个亮250ms               //跑马灯
                    bFlag_reverse = 0;
                    display_cycle = 125;                  //! 跑马灯
                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
            }
        }
        else
        {
            counter = 0;
            {
                if (0 == bFlag_light_load) //! 非轻载
                {
                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 电量==0的时候 闪烁5秒后熄灭,反之一直显示
                    if (0 == bFlag_in_small_current_mode) // 非小电流模式
                    {
                        delaySleepTimer = CNST_TIMER_DLY_SLP;
                    }
                }
                else
                { //! 轻载

                    if (bFlag_typec_in) //! 解决 typeC to lightning  线在 不需要小电流模式 也不需要轻载关机  但不能解决 C口轻载两分钟会关输出，有协议时 规格书要求C口 只灭灯不关输出
                    {
                        delaySleepTimer = CNST_TIMER_DLY_SLP; //! C口轻载只要关灯 不需要120秒后关机 也不需要小电流模式
                    }
                    //! 12/30 这个是A 口的 有 120sec 休眠的需求
                    // if (bFlag_temp_exception_dischg) //! add 12/29 解决放电状态 温度异常关闭 输出  不能恢复的问题  12/30 后记 A口120sec 休眠 温度没有恢复就休眠，不需要死等
                    // {
                    //     delaySleepTimer = CNST_TIMER_DLY_SLP; //! 放电状态 温度异常关闭 输出之后 不需要120秒后关机 也不需要小电流模式
                    // }
                }
            }
            if (0 == (iitmp2 && iitmp))
            {
                bFlag_chg_or_dischg = 0;
            }
        }
    }
}

// add for 5356
//  [6：4] 充电状态 chg_state
//  000 未充电状态
//  001 涓流充电
//  010 恒流充电
//  011 恒压充电
//  100 恒压断开检测电芯电压
//!  101 充满状态
//  110 充电超时状态
void is_charge_complete(void) // get_CHG_STATE2
{
    unsigned char reg_ip53xs; // 0x05
    unsigned char iitmp;
    static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_CHG_STATE2);

    iitmp = ((reg_ip53xs >> 4) & 0x07);

    if (bFlag_charge_complete)
    {
        if ((0 != iitmp) && (5 != iitmp))
        {
            if (++counter > CNST_FILTER_COM)
            {
                counter = 0;
                bFlag_charge_complete = 0;
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (5 == iitmp)
        {
            if (++counter > CNST_FILTER_COM)
            {
                counter = 0;
                bFlag_charge_complete = 1;
                displayData = 100;
                timer_display_full = 0;
                timer_dischg_minimum = 40;
            }
        }
        else
        {
            counter = 0;
        }
    }
}

#define CONST_P_VIN_FILTER 7
void get_p_ext_int_status(void)
{
    static unsigned char counter;

    if (bFlag_p_ext_int_is_high)
    {
        if (!P_I2C_INT)
        {
            if (++counter > 3)
            {
                counter = 0;
                bFlag_p_ext_int_is_high = 0;
                bFlag_init_ip5356 = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (P_I2C_INT)
        {
            if (++counter > CONST_P_VIN_FILTER)
            {
                counter = 0;
                bFlag_p_ext_int_is_high = 1;
                _dly_ms(100);
                // if (!P_I2C_INT)
                // {
                //     return;
                // }

                // if (P_I2C_INT)
                // {
                //     init_ip53xs();
                // }
            }
        }
        else
        {
            counter = 0;
        }
    }
}

#if 0
void init_ip53xs(void)
{
    unsigned char reg_ip53xs;
    unsigned char Temp2;
    if (bFlag_init_ip5356)
    {
        reg_ip53xs = ip53xs_readByte(0xE8, 0x03);
        // reg_ip53xs = ip53xs_readByte(0xEA, REG_CHG_STATE2);
        if (reg_ip53xs & 0x04)
        {
            ip53xs_writeByte(0xE8, 0x03, reg_ip53xs & 0xFB); // 关闭轻载关机选择VSYS电流使能
            // ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
        }
        //--------------------------------------------
        reg_ip53xs = ip53xs_readByte(0xE8, 0x33);
        if (reg_ip53xs & 0x10)
        {
            ip53xs_writeByte(0xE8, 0x33, reg_ip53xs & 0xEF); // 寄存器设置充满电压
        }
        //--------------------------------------------
        reg_ip53xs = ip53xs_readByte(0xEA, 0x3A);
        if ((reg_ip53xs & 0x0F) != 0x07)
        {
            reg_ip53xs &= 0xF0;                       // 充电恒压设置为00，恒压加压电压设置为00
            ip53xs_writeByte(0xEA, 0x3A, reg_ip53xs); // 充电恒压设置为4.20V，恒压加压00mV
        }
        //--------------------------------------------
        reg_ip53xs = ip53xs_readByte(0xE8, 0x24);
        if (reg_ip53xs & 0x20)
        {
            ip53xs_writeByte(0xE8, 0x24, reg_ip53xs & 0xDF); // VBUS关闭边充边放
        }
        //--------------------------------------------
        reg_ip53xs = ip53xs_readByte(0xE8, 0xF5);
        if (reg_ip53xs & 0x40)
        {
            ip53xs_writeByte(0xE8, 0xF5, reg_ip53xs & 0xBF); // VIN关闭边充边放
        }
        //--------------------------------------------
        reg_ip53xs = ip53xs_readByte(0xEA, 0x01);
        if (reg_ip53xs & 0x30)
        {
            ip53xs_writeByte(0xEA, 0x01, reg_ip53xs & 0xCF); // VIN输入过压保护调整为5.6V
        }
        bFlag_init_ip5356 = 0;
    }
    //--------------------------------------------
    // if (DET_12V == False) // 12V接入设备，屏蔽A口、C口快充输出
    if (bFlag_plus_in_12v)
    {
        //--------------------------------------------A1口关闭快充
        reg_ip53xs = ip53xs_readByte(0xE8, 0x10); // 读取VOUT1控制寄存器
        if (reg_ip53xs & 0x04)                    // VOUT1快充输出使能
        {
            if (reg_ip53xs & 0x01) // VOUT1 MOS输出通路使能
            {
                ip53xs_writeByte(0xE8, 0x10, reg_ip53xs & 0xFE); // 关闭MOS输出
            }
            else
            {
                ip53xs_writeByte(0xE8, 0x10, reg_ip53xs & 0xFB); // 关闭VOUT1快充输出使能
            }
        }
        else if ((reg_ip53xs & 0x01) == 0x00) // MOS是关闭的
        {
            ip53xs_writeByte(0xE8, 0x10, reg_ip53xs | 0x01); // 打开MOS输出
        }
        //--------------------------------------------C口关闭快充
        reg_ip53xs = ip53xs_readByte(0xE8, 0x18);            // 读取VBUS控制寄存器，控制DM、DP
        Temp2 = ip53xs_readByte(0xEA, 0x97);                 // 读取PD控制寄存器
        if ((reg_ip53xs & 0x04) || ((Temp2 & 0xC0) != 0x40)) // VBUS DM、DP快充输出使能或者PD使能
        {
            if (reg_ip53xs & 0x01) // VBUS MOS输出通路使能
            {
                ip53xs_writeByte(0xE8, 0x18, reg_ip53xs & 0xFE); // 关闭MOS输出
            }
            else
            {
                ip53xs_writeByte(0xE8, 0x18, reg_ip53xs & 0xFB);     // 关闭VBUS DM、DP快充输出使能
                ip53xs_writeByte(0xEA, 0x97, (Temp2 & 0x3F) | 0x40); // 关闭PD快充输出
            }
        }
        else if ((reg_ip53xs & 0x01) == 0x00) // MOS是关闭的
        {
            ip53xs_writeByte(0xE8, 0x18, reg_ip53xs | 0x01); // 打开MOS输出
        }
    }
}
#endif

void init_ip53xs(void) //初始化IP5356
{
	unsigned char reg_ip53xs;
	unsigned char Temp2;

	reg_ip53xs = ip53xs_readByte(0xE8,0x03);
	if(reg_ip53xs & 0x04)
	{
		ip53xs_writeByte(0xE8,0x03,reg_ip53xs & 0xFB); //关闭轻载关机选择VSYS电流使能
	}
	//--------------------------------------------
	reg_ip53xs = ip53xs_readByte(0xE8,0x33);
	if(reg_ip53xs & 0x10)
	{
		ip53xs_writeByte(0xE8,0x33,reg_ip53xs & 0xEF); //寄存器设置充满电压
	}
	//--------------------------------------------
	reg_ip53xs = ip53xs_readByte(0xEA,0x3A);
	if((reg_ip53xs & 0x0F) != 0x07)
	{
		reg_ip53xs &= 0xF0; //充电恒压设置为00，恒压加压电压设置为00
		ip53xs_writeByte(0xEA,0x3A,reg_ip53xs); //充电恒压设置为4.20V，恒压加压00mV
	}
	//--------------------------------------------
	reg_ip53xs = ip53xs_readByte(0xE8,0x24);
	if(reg_ip53xs & 0x20)
	{
		ip53xs_writeByte(0xE8,0x24,reg_ip53xs & 0xDF); //VBUS关闭边充边放
	}
	//--------------------------------------------
	reg_ip53xs = ip53xs_readByte(0xE8,0xF5);
	if(reg_ip53xs & 0x40)
	{
		ip53xs_writeByte(0xE8,0xF5,reg_ip53xs & 0xBF); //VIN关闭边充边放
	}
	//--------------------------------------------
	reg_ip53xs = ip53xs_readByte(0xEA,0x01);
	if(reg_ip53xs & 0x30)
	{
		ip53xs_writeByte(0xEA,0x01,reg_ip53xs & 0xCF); //VIN输入过压保护调整为5.6V
	}
	//--------------------------------------------
	// if(DET_12V == False) //12V接入设备，屏蔽A口、C口快充输出
    if(bFlag_plus_in_12v)
	{
		//--------------------------------------------A1口关闭快充
		reg_ip53xs = ip53xs_readByte(0xE8,0x10); //读取VOUT1控制寄存器
		if(reg_ip53xs & 0x04) //VOUT1快充输出使能
		{
			if(reg_ip53xs & 0x01) //VOUT1 MOS输出通路使能
			{
				ip53xs_writeByte(0xE8,0x10,reg_ip53xs & 0xFE); //关闭MOS输出
			}
			else
			{
				ip53xs_writeByte(0xE8,0x10,reg_ip53xs & 0xFB); //关闭VOUT1快充输出使能
			}
		}
		else if((reg_ip53xs & 0x01) == 0x00) //MOS是关闭的
		{
			ip53xs_writeByte(0xE8,0x10,reg_ip53xs | 0x01); //打开MOS输出
		}
		//--------------------------------------------C口关闭快充
		reg_ip53xs = ip53xs_readByte(0xE8,0x18); //读取VBUS控制寄存器，控制DM、DP
		Temp2 = ip53xs_readByte(0xEA,0x97); //读取PD控制寄存器
		if((reg_ip53xs & 0x04) || ((Temp2 & 0xC0) != 0x40)) //VBUS DM、DP快充输出使能或者PD使能
		{
			if(reg_ip53xs & 0x01) //VBUS MOS输出通路使能
			{
				ip53xs_writeByte(0xE8,0x18,reg_ip53xs & 0xFE); //关闭MOS输出
			}
			else
			{
				ip53xs_writeByte(0xE8,0x18,reg_ip53xs & 0xFB); //关闭VBUS DM、DP快充输出使能
				ip53xs_writeByte(0xEA,0x97,(Temp2 & 0x3F) | 0x40); //关闭PD快充输出
			}
		}
		else if((reg_ip53xs & 0x01) == 0x00) //MOS是关闭的
		{
			ip53xs_writeByte(0xE8,0x18,reg_ip53xs | 0x01); //打开MOS输出
		}
	}
	else //12V没接入设备，恢复A口、C口快充输出
	{
		//--------------------------------------------A2口打开快充
		reg_ip53xs = ip53xs_readByte(0xE8,0x10); //读取VOUT1控制寄存器
		if((reg_ip53xs & 0x04) == 0x00) //VOUT1快充输出关闭使能
		{
			if(reg_ip53xs & 0x01) //VOUT1 MOS输出通路使能
			{
				ip53xs_writeByte(0xE8,0x10,reg_ip53xs & 0xFE); //关闭MOS输出
			}
			else
			{
				ip53xs_writeByte(0xE8,0x10,reg_ip53xs | 0x04); //打开VOUT1快充输出使能
			}
		}
		else if((reg_ip53xs & 0x01) == 0x00) //MOS是关闭的
		{
			ip53xs_writeByte(0xE8,0x10,reg_ip53xs | 0x01); //打开MOS输出
		}
		//--------------------------------------------C口打开快充
		reg_ip53xs = ip53xs_readByte(0xE8,0x18); //读取VBUS控制寄存器
		Temp2 = ip53xs_readByte(0xEA,0x97); //读取PD控制寄存器
		if(((reg_ip53xs & 0x04) == 0x00) || ((Temp2 & 0xC0) == 0x40)) //VBUS DM、DP快充输出关闭使能或者PD使能关闭
		{
			if(reg_ip53xs & 0x01) //VBUS MOS输出通路使能
			{
				ip53xs_writeByte(0xE8,0x18,reg_ip53xs & 0xFE); //关闭MOS输出
			}
			else
			{
				ip53xs_writeByte(0xE8,0x18,reg_ip53xs | 0x04); //打开VBUS快充输出使能
				ip53xs_writeByte(0xEA,0x97,Temp2 & 0x3F); //打开PD使能
			}
		}
		else if((reg_ip53xs & 0x01) == 0x00) //MOS是关闭的
		{
			ip53xs_writeByte(0xE8,0x18,reg_ip53xs | 0x01); //打开MOS输出
		}
	}
}


/* unit: (mv) */

void get_system_voltage(void)
{
    unsigned char reg_ip53xs;
    unsigned int itmp_16bits;

    reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT1);
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT0);
    itmp_16bits |= reg_ip53xs;
    system_voltage = itmp_16bits;
}

void get_system_current(void)
{
    unsigned char reg_ip53xs;
    unsigned int itmp_16bits;

    //! IVSYS 端电流 VSYSIADC 数据的高 8bit
    reg_ip53xs = ip53xs_readByte(0xEA, REG_IVSYS_DATA1);
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;

    //! IVSYS 端电流 VSYSIADC 数据的低 8bit
    reg_ip53xs = ip53xs_readByte(0xEA, REG_IVSYS_DATA0);
    itmp_16bits |= reg_ip53xs;
    system_current = itmp_16bits;
}

// change to 5356
//  VSYS= VSYSVADC*1.611328mV

// #define CONST_VSYS_4V5_UP (CONST_VSYS_5V0) // 5 000 mv / 1.611328mV
// #define CONST_VSYS_4V5_DN (CONST_VSYS_4V9) // 5 000 mv / 1.611328mV

#define CONST_VSYS_4V5_UP (CONST_VSYS_5V0 + 48) // 5 000 mv / 1.611328mV
#define CONST_VSYS_4V5_DN (CONST_VSYS_5V0 - 48) // 5 000 mv / 1.611328mV

//! 加了线补120mv
// #define CONST_VSYS_4V5_UP (CONST_VSYS_5V1) // 5 000 mv / 1.611328mV
// #define CONST_VSYS_4V5_DN (CONST_VSYS_5V0) // 5 000 mv / 1.611328mV
// OK <--
void is_ovp_qc_12v(void) //!   输出过压保护  (输出OVP保护) QC协议下 只做12V
{
    // unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    static unsigned char counter;
    // static unsigned char counter2;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT1);
    // itmp_16bits = reg_ip53xs;
    // itmp_16bits <<= 8;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT0);
    // itmp_16bits |= reg_ip53xs;
    itmp_16bits = system_voltage;

    if (0 == bFlag_vsys_over_12v8)
    {
        if (itmp_16bits > CONST_VSYS_12V8)
        {
            if (++counter > 3)
            {
                counter = 0;
                bFlag_vsys_over_12v8 = 1;

                if (0 == bFlag_disable_discharge_on)
                {
                    disable_discharger_on();
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (itmp_16bits < CONST_VSYS_12V5)
        {
            if (++counter > 3)
            {
                counter = 0;
                bFlag_vsys_over_12v8 = 0;

                if (bFlag_disable_discharge_on)
                {
                    if (0 == bFlag_temp_exception_dischg)
                    {
                        enable_discharger_on();
                    }
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
}

// 4.47 SYS_STATE2（系统状态指示寄存器）
// I2C 地址 0XEA 寄存器地址= 0XCD
// Bit(s) Name Description R/W
// 7
// 6 Src_qc_ok 输出快充有效标志位
// 1：有效
// 0：无效
// QC5V 和 PD5V 不算快充 OK
//! 没协议的输出过压 (SCP的输出过压)
void is_ovp_6v3(void) //! 输出过压保护  (输出OVP保护) 无协议下 只做5V
{
    // unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    static unsigned char counter;
    // static unsigned char counter2;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT1);
    // itmp_16bits = reg_ip53xs;
    // itmp_16bits <<= 8;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT0);
    // itmp_16bits |= reg_ip53xs;
    itmp_16bits = system_voltage;

    if (0 == bFlag_vsys_over_6v3)
    {
        if (itmp_16bits > (CONST_VSYS_6V2))
        {
            if (++counter > 7)
            {
                counter = 15;
                if ((0 == bFlag_discharge_qc) || (bFlag_in_scp_A3)) // if (0 == bFlag_discharge_qc)
                {
                    bFlag_vsys_over_6v3 = 1;
                    if (0 == bFlag_disable_discharge_on)
                    {
                        disable_discharger_on();
                    }
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (itmp_16bits < (CONST_VSYS_5V9))
        {
            if (++counter > 7)
            {
                counter = 0;
                bFlag_vsys_over_6v3 = 0;
                if (bFlag_disable_discharge_on)
                {
                    if (0 == bFlag_temp_exception_dischg)
                    {
                        enable_discharger_on();
                    }
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
}

void is_ovp_pd_9v(void) //! 输出过压保护  (输出OVP保护) PD协议下 只做9V
{
    // unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    static unsigned char counter;
    // static unsigned char counter2;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT1);
    // itmp_16bits = reg_ip53xs;
    // itmp_16bits <<= 8;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT0);
    // itmp_16bits |= reg_ip53xs;
    itmp_16bits = system_voltage;

    if (0 == bFlag_ovp_in_pd_9v)
    {
        if (itmp_16bits > (CONST_VSYS_10V2))
        {
            if (++counter > 7)
            {
                counter = 0;
                // if (0 == bFlag_discharge_qc)
                {
                    bFlag_ovp_in_pd_9v = 1;

                    if (0 == bFlag_disable_discharge_on)
                    {
                        disable_discharger_on();
                    }
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (itmp_16bits < (CONST_VSYS_9V7))
        {
            if (++counter > 7)
            {
                counter = 0;
                bFlag_ovp_in_pd_9v = 0;

                if (bFlag_disable_discharge_on)
                {

                    if (0 == bFlag_temp_exception_dischg)
                    {

                        enable_discharger_on();
                    }
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
}

void is_vsys_under_4v75(void)
{
    unsigned int itmp_16bits;
    static unsigned char counter;
    itmp_16bits = system_voltage;

    if (bFlag_vsys_under_4v75)
    {
        if (itmp_16bits > (CONST_VSYS_4V75 + 31)) // 5v
        {

            if (++counter > 3)
            {
                counter = 3;

                bFlag_vsys_under_4v75 = 0;
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (itmp_16bits < (CONST_VSYS_4V75 - 31)) // 4.9
        {

            if (++counter > 3)
            {
                counter = 0;
                bFlag_vsys_under_4v75 = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
}

void is_scp_over_4v5(void)
{
    // unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    static unsigned char counter;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT1);
    // itmp_16bits = reg_ip53xs;
    // itmp_16bits <<= 8;
    // reg_ip53xs = ip53xs_readByte(0xEA, REG_VSYSVADC_DAT0);
    // itmp_16bits |= reg_ip53xs;
    itmp_16bits = system_voltage;

    //! add in 10/15
    // if (bFlag_in_scp_A3)
    // {

    if (0 == bFlag_vsys_under_4v5)
    {
        if (itmp_16bits < CONST_VSYS_4V5_DN) // 4.9
        {

            if (++counter > 3)
            {
                counter = 0;
                bFlag_vsys_under_4v5 = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (itmp_16bits > (CONST_VSYS_4V5_UP)) // 5v
        {

            if (++counter > 3)
            {
                counter = 3;
                if (bFlag_isys_over_1A5)
                {
                    counter = 0;
                    bFlag_vsys_under_4v5 = 0; //! 降低功率
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
    // }
}

//! 1. vsys < 7v <<-- current_battery*1
//! 2. vsys < 10v <<-- current_battery*1.05
//! 3. vsys > 10v <<-- current_battery*1.1
// void get_vsys_grade_chg(void)
// {
//     unsigned int itmp_16bits;
//     itmp_16bits = system_voltage;
//     if (itmp_16bits < CONST_VSYS_7V)
//     {
//         vsys_grade_chg = 0;
//     }
//     else if (itmp_16bits < CONST_VSYS_10V)
//     {
//         vsys_grade_chg = 1;
//     }
//     else
//     {
//         vsys_grade_chg = 2;
//     }
// }
//! 放电
//!  1. vsys < 6v <<-- current_battery*0.9
//!  2. vsys < 10v <<-- current_battery*0.95
//!  3. vsys > 10v <<-- current_battery*1
// void get_vsys_grade_dischg(void)
// {
//     unsigned int itmp_16bits;
//     itmp_16bits = system_voltage;
//     if (itmp_16bits < CONST_VSYS_6V)
//     {
//         vsys_grade_dischg = 0;
//     }
//     else if (itmp_16bits < CONST_VSYS_10V)
//     {
//         vsys_grade_dischg = 1;
//     }
//     else
//     {
//         vsys_grade_dischg = 2;
//     }
// }
// OK << -- change to 5356
// 4.30 IBATIADC_DAT1（BAT 端电流寄存器）
// I2C 地址 0XEA 寄存器地址= 0x6F
// Bit(s) Name Description R/W
// 7:0 IBATIADC[15:8] 电芯端电流 BATIADC 数据的高 8bit
//! IBAT=IBATVADC*1.6785mA
// 电流不区分正负方向

// 4.29 IBATIADC_DAT0（BAT 端电流寄存器）
// I2C 地址 0XEA 寄存器地址= 0x6E
// Bit(s) Name Description R/W
//! 7:0 IBATIADC[7:0] 电芯端电流 IBATIADC 数据的低 8bit
#if 0 //! 库伦计
void get_current_battery(void) // common
{
    unsigned char reg_ip53xs;

    unsigned int itmp_16bits;
    unsigned long itmp_32bits;

    reg_ip53xs = ip53xs_readByte(0xEA, 0x6F);
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;

    reg_ip53xs = ip53xs_readByte(0xEA, 0x6E);
    itmp_16bits |= reg_ip53xs;

    //! IBAT=IBATVADC*1.6785mA
    itmp_32bits = (unsigned long)itmp_16bits * 107;     //放大64倍  107 = 1.6785 x 64
    current_battery = (unsigned int)(itmp_32bits >> 6); // 除64

    //! IBAT=IBATVADC*1.875mA
    // itmp_32bits = (unsigned long)itmp_16bits * 15;     //放大15倍  107 = 1.875 x 8
    // current_battery = (unsigned int)(itmp_32bits >> 3); // 除8
}
#endif
//
#if 1
unsigned char get_percentage_voltage_Battery(void)
{
    unsigned char reg_ip53xs;
    // unsigned int itmp_16bits;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_SOC_CAP_DATA);
    return reg_ip53xs;
}
#endif

void get_current_vout1(void)
{
    unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_IVOUT1_IADC_DAT1);
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_IVOUT1_IADC_DAT0);
    itmp_16bits |= reg_ip53xs;
    ad_current_vout = itmp_16bits;
}

void get_current_vout2(void)
{
    unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_IVOUT2_IADC_DAT1);
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_IVOUT2_IADC_DAT0);
    itmp_16bits |= reg_ip53xs;
    ad_current_vout = itmp_16bits;
}

// I2C 地址 0XEA 寄存器地址= 0X51
// 7:0 BATVADC[15:8] BATVADC 数据的高 8bit
// VBAT=BATVADC*0.26855mv
// VBATPIN 的电压

// I2C 地址 0XEA 寄存器地址= 0X50
// Bit(s) Name Description R/W
// 7:0 BATVADC[7:0] BATVADC 数据的低 8bit
// VBATPIN 的电压

//  0.2666667 = 4/15
// VBAT=BATVADC*0.26855mv
//! 0.9929871532303109 = 0.2666667 / 0.26855
void get_voltage_battery(void)
{
    unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_BATVADC_DAT1);
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;
    reg_ip53xs = ip53xs_readByte(0xEA, REG_BATVADC_DAT0);
    itmp_16bits |= reg_ip53xs;
    ad_voltage_battery = itmp_16bits;
    // itmp_16bits <<= 2;
    // itmp_16bits /= 15;
    // voltage_battery = (itmp_16bits); // 5356
}

// VBAT=BATVADC*0.26855mv

// void get_ad_voltage_battery(void)
// {
//     unsigned char reg_ip53xs;
//     unsigned int itmp_16bits;
//     reg_ip53xs = ip53xs_readByte(0xEA, REG_BATVADC_DAT1);
//     itmp_16bits = reg_ip53xs;
//     itmp_16bits <<= 8;
//     reg_ip53xs = ip53xs_readByte(0xEA, REG_BATVADC_DAT0);
//     itmp_16bits |= reg_ip53xs;
//     ad_voltage_battery = itmp_16bits;
// }

// void get_test_ip5356(void) //common
// {
//     unsigned char reg_ip53xs;
//     unsigned char reg_ip53xx_2;
//     unsigned char reg_ip53xx_3;
//     unsigned char reg_ip53xx_4;

//     reg_ip53xs = ip53xs_readByte(0xE8,REG_SYS_CTL0);      //reg 0x00
//     reg_ip53xx_2 = ip53xs_readByte(0xE8,REG_IP5356_0x01); //reg 0x01
//     reg_ip53xx_2 = ip53xs_readByte(0xE8,REG_IP5356_0x02); //reg 0x02
//     reg_ip53xx_3 = ip53xs_readByte(0xE8,REG_SYS_CTL1);    //reg 0x03
//     reg_ip53xx_4 = ip53xs_readByte(0xE8,REG_IP5356_0x04); //reg 0x03
// }

// 写（
// I2C地址=0XE8 寄存器地址0X33 bit5=1，
// I2C地址=0XE8 寄存器地址0X31 bit1-0=00，5356
// ），
// 就可以使能常开2小时，进入常开2小时后就会屏蔽轻载关机和关输出口，MCU可读取（I2C地址=0XEA
// 寄存器地址0XE1 bit7=1就代表已经进入了常开模式，可以点绿灯，否则没有进常开模式）
void ip53xx_in_small_current_mode(void)
{

    unsigned char reg_ip53xs;
    //! 放初始化代码中做
    reg_ip53xs = ip53xs_readByte(0xE8, 0x31); // Device 0xEA ，Reg 0x86 bit7 < -- 1
    reg_ip53xs &= 0xFC;
    // reg_ip53xs |= b_Force_Standby;                    //
    ip53xs_writeByte(0xE8, 0x31, reg_ip53xs); //

    reg_ip53xs = ip53xs_readByte(0xE8, 0x33); // Device 0xEA ，Reg 0x86 bit7 < -- 1
    // reg_ip53xs &= (~(BIT5));
    reg_ip53xs |= BIT5;                       //
    ip53xs_writeByte(0xE8, 0x33, reg_ip53xs); //
}

void ip53xx_out_small_current_mode(void)
{

    unsigned char reg_ip53xs;
    //! 放初始化代码中做
    reg_ip53xs = ip53xs_readByte(0xE8, 0x31); // Device 0xEA ，Reg 0x86 bit7 < -- 1
    reg_ip53xs &= 0xFC;
    reg_ip53xs |= 0x02;                       //
    ip53xs_writeByte(0xE8, 0x31, reg_ip53xs); //! [1:0] 10

    reg_ip53xs = ip53xs_readByte(0xE8, 0x33); // Device 0xEA ，Reg 0x86 bit7 < -- 1
    reg_ip53xs &= (~(BIT5));
    // reg_ip53xs |= BIT5;                  //
    ip53xs_writeByte(0xE8, 0x33, reg_ip53xs); //
}

void get_small_current_mode_status(void)
{
    unsigned char reg_ip53xs;
    // if (bFlag_double_key)
    {
        // reg_ip53xs = ip53xs_readByte(0xE8,0xE1);
        reg_ip53xs = ip53xs_readByte(0xEA, 0xE1);
        if (bFlag_in_small_current_mode)
        {
            // ip53xx_out_small_current_mode();
            //  reg_ip53xs = ip53xs_readByte(0xEA,0xE1);
            if (0 == (reg_ip53xs & BIT7))
            {
                bFlag_in_small_current_mode = 0;
                // bFlag_double_key = 0;
            }
        }
        else
        {
            // ip53xx_in_small_current_mode();
            //  reg_ip53xs = ip53xs_readByte(0xEA,0xE1);
            if (reg_ip53xs & BIT7)
            {
                bFlag_in_small_current_mode = 1;
                delaySleepTimer = CNST_TIMER_DLY_SLP_SML; //! 关机倒计时

                // bFlag_double_key = 0;
            }
        }
    }
}

// REG_ILOW_STATE  5328   I2C 地址 0XEA 寄存器地址= 0XF2

// 2、判断处于单口放电并且处于非常开模式时，读取ISYSADC阈值（0xEA 0x70/0xEA 0x71）来判断：
// A口是否小于50ma，如果连续小于5s则灭灯，持续小于120s后则关机。如果电流大于100ma则亮灯；
// C口是否小于70ma，如果连续小于5s则灭灯，持续小于120s后则关机。如果电流大于100ma则亮灯；

// 4.31 ISYS_IADC_DAT0（IVSYS 端电流寄存器）
// I2C 地址 0XEA 寄存器地址= 0x70
// Bit(s) Name Description R/W
// 7:0 ISYSIADC[7:0] IVSYS 端电流 VSYSIADC 数据的低 8bit

// 4.32 IVSYS_IADC_DAT1（IVSYS 端电流寄存器）
// I2C 地址 0XEA 寄存器地址= 0x71
// Bit(s) Name Description R/W
// 7:0 IVSYSIADC[15:8
// ]
// IVSYS 端电流 VSYSIADC 数据的高 8bit
// IVSYS=ISYSVADC*0.671387mA
// 电流不区分正负方向

// USBA 60mA
// TYPEC 110

#define CONST_60mA 89   // 60/0.61387
#define CONST_110mA 179 // 110/0.61387
#define CONST_120mA 195 // 120/0.61387
void get_light_load_status(void)
{
    unsigned char reg_ip53xs;
    static unsigned char counter;
    unsigned int itmp_16bits;
    unsigned int itmp_16bits_up;
    unsigned int itmp_16bits_dn;

    reg_ip53xs = ip53xs_readByte(0xEA, 0x71); // 0xEA 0x71 IVSYS 端电流 VSYSIADC 数据的高 8bit
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;

    reg_ip53xs = ip53xs_readByte(0xEA, 0x70); // 0xEA 0x70 IVSYS 端电流 VSYSIADC 数据的低 8bit
    itmp_16bits |= reg_ip53xs;
    ad_i_input_output = itmp_16bits;

    if (bFlag_multi_port) //! 多口
    {
        itmp_16bits_up = CONST_120mA + 16;
        itmp_16bits_dn = CONST_120mA - 16;
    }
    else if (bFlag_typec_in) //! 单C口
    {
        itmp_16bits_up = CONST_110mA + 16;
        itmp_16bits_dn = CONST_110mA - 16;
    }
    else // if( bFlag_usb_a1_in || bFlag_usb_a2_in)  //! 单A口
    {
        itmp_16bits_up = CONST_60mA + 16;
        itmp_16bits_dn = CONST_60mA - 16;
    }

    if (bFlag_light_load)
    {

        // reg_ip53xs = ip53xs_readByte(0xEA,REG_ILOW_STATE);
        if (itmp_16bits > itmp_16bits_up)
        {
            if (++counter > 7)
            {
                counter = 0;
                bFlag_light_load = 0;
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {

        // reg_ip53xs = ip53xs_readByte(0xEA,REG_ILOW_STATE);
        if (itmp_16bits < itmp_16bits_dn)
        {
            if (++counter > 7)
            {
                counter = 0;
                bFlag_light_load = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
}

void disable_DPDM_quick_charge(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x81); // Device 0xE8
    //[4:1] 0000
    reg_ip53xs &= 0xE1;                       // 1110 0001              //
    ip53xs_writeByte(0xE8, 0x81, reg_ip53xs); //! [4:1] 0000
}

void disable_DP_quick_charge(void)
{
    unsigned char reg_ip53xs;
    // 1
    reg_ip53xs = ip53xs_readByte(0xEA, 0x91); // Device 0xEA
    //[3:2] 01
    reg_ip53xs &= 0xF3;                       // 1111 0011              //
    reg_ip53xs |= 0x04;                       //(1<<2);
    ip53xs_writeByte(0xEA, 0x91, reg_ip53xs); //! [3:2] 01

    //! important 1 add 02/24
    //! 拔掉充电 不转放电 直接关机导致的 在延时期间有概率关机 当然这个时间也跟适配器有关
    //! 建议在reset type c 之前 先把充电 不转放电这个功能 禁止
    //! [3:2]
    // 1X：系统不转 boost 直接进入待机  10/11 add by kwangsi
    // 01：输出有负载才自动开启 boost，没有负载就进入关机
    // 00：无论输出是否有负载，自动开启 boost  //!default
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs &= 0xF3;                       // 1111 0011
    // reg_ip53xs &= (~(BIT3));                  //! bit3 写0
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00

    // 2 reset type c
    reg_ip53xs = ip53xs_readByte(0xE8, 0xD1); // Device 0xE8
    //[5:4] 01
    reg_ip53xs &= 0xCF; // 1100 1111              //
    reg_ip53xs |= 0x10;
    ip53xs_writeByte(0xE8, 0xD1, reg_ip53xs); //! [5:4] 01
    _dly_ms(8);                               // !0314 change to 8
    reg_ip53xs = ip53xs_readByte(0xE8, 0xD1); // Device 0xE8
    //[5:4] 11
    reg_ip53xs &= 0xCF; // 1100 1111              //
    reg_ip53xs |= 0x30;
    ip53xs_writeByte(0xE8, 0xD1, reg_ip53xs); //! [5:4] 11

    //! important 2 add 02/24
    //[3:2] 1X：系统不转 boost 直接进入待机  10/11 add by kwangsi
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs &= 0xF3;                       // 1111 0011
    reg_ip53xs |= (BIT2);
    // reg_ip53xs |= (BIT3);                     //! Q2 : [3:2] 1X：系统不转 boost 直接进入待机  10/11 add by kwangsi
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00
}

void disable_quick_discharge(void)
{
    unsigned char reg_ip53xs;
    // 1 关闭vout1 vout2 vbus口 mos
    // 0xEA 0x86[2:0] = 111
    reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA
    //[2:0] 111
    reg_ip53xs &= 0xF8;                       //
    reg_ip53xs |= 0x04;                       //
    ip53xs_writeByte(0xEA, 0x86, reg_ip53xs); //! [2:0] 111
    // 2 关闭输出快充协议
    //! 2.1 关闭输出快充DPDM协议
    // 0xE8 0x85[7:1] 0000 000x
    reg_ip53xs = ip53xs_readByte(0xE8, 0x85); // Device 0xE8
    //[7:1] 0000 000x
    reg_ip53xs &= 0x01; // 0000 000x              //
    // reg_ip53xs |= 0x10;
    ip53xs_writeByte(0xE8, 0x85, reg_ip53xs); //! [7:1] 0000 000x
    //! 2.1 关闭VBUS输出DP快充
    // 0xEA 0x97[7:6] = 01
    reg_ip53xs = ip53xs_readByte(0xEA, 0x97); // Device 0xEA
    //[7:6] = 01
    reg_ip53xs &= 0x3F;                       //
    reg_ip53xs |= 0x40;                       // 0100 0000
    ip53xs_writeByte(0xEA, 0x97, reg_ip53xs); //! [7:6] = 01

    _dly_ms(30);
    //! 3 重新检测并开启有负载的 VOUT1/ VOUT2/ VBUS USB口
    // 0xEA 0x86  [5:3] 111
    reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA
    //[5:3] 111
    reg_ip53xs &= 0xC7;                       //
    reg_ip53xs |= 0x38;                       //[5:3] 111
    ip53xs_writeByte(0xEA, 0x86, reg_ip53xs); //! [5:3] 111
}

void enable_quick_discharge(void)
{
    unsigned char reg_ip53xs;
    // 1 关闭vout1 vout2 vbus口 mos
    // 0xEA 0x86[2:0] = 111
    reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA
    //[2:0] 111
    reg_ip53xs &= 0xF8;                       //
    reg_ip53xs |= 0x04;                       //
    ip53xs_writeByte(0xEA, 0x86, reg_ip53xs); //! [2:0] 111
    // 2 enable输出快充协议
    //! 2.1 enable 输出快充DPDM协议
    // 0xE8 0x85[7:1] 1111 111x
    reg_ip53xs = ip53xs_readByte(0xE8, 0x85); // Device 0xE8
    //[7:1] 1111 111x
    reg_ip53xs &= 0x01; // 0000 000x              //
    reg_ip53xs |= 0xFE;
    ip53xs_writeByte(0xE8, 0x85, reg_ip53xs); //! [7:1] 1111 111x
    //! 2.1 enableVBUS输出DP快充
    // 0xEA 0x97[7:6] = 00
    reg_ip53xs = ip53xs_readByte(0xEA, 0x97); // Device 0xEA
    //[7:6] = 00
    reg_ip53xs &= 0x3F; // 0xEA 0x97[7:6] = 00
    // reg_ip53xs |= 0x40;                       // 0100 0000
    ip53xs_writeByte(0xEA, 0x97, reg_ip53xs); //! [7:6] = 00

    _dly_ms(30);
    //! 3 重新检测并开启有负载的 VOUT1/ VOUT2/ VBUS USB口
    // 0xEA 0x86  [5:3] 111
    reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA
    //[5:3] 111
    reg_ip53xs &= 0xC7;                       //
    reg_ip53xs |= 0x38;                       //[5:3] 111
    ip53xs_writeByte(0xEA, 0x86, reg_ip53xs); //! [5:3] 111
}

void enable_DPDM_quick_charge(void)
{
    unsigned char reg_ip53xs;

    reg_ip53xs = ip53xs_readByte(0xE8, 0x81); // Device 0xE8
    //[4:1] 0000
    reg_ip53xs &= 0xE1;                       // 1110 0001              //
    reg_ip53xs |= 0x1E;                       // 0001 1110
    ip53xs_writeByte(0xE8, 0x81, reg_ip53xs); //! [4:1] 1111
}

void enable_DP_quick_charge(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xEA, 0x91); // Device 0xEA
    //[3:2] 00
    reg_ip53xs &= 0xF3;                       // 1111 0011              //
    ip53xs_writeByte(0xEA, 0x91, reg_ip53xs); //! [3:2] 00
}

void enable_output_quick_charge(void)
{
    unsigned char reg_ip53xs;
    // 1 关闭vout1 vout2 vbus口 mos
    // 0xEA 0x86[2:0] = 111
    reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA
    //[2:0] 111
    reg_ip53xs &= 0xF8;                       //
    reg_ip53xs |= 0x04;                       //
    ip53xs_writeByte(0xEA, 0x86, reg_ip53xs); //! [2:0] 111
    // 2 关闭输出快充协议
    //! 2.1 打开输出快充DPDM协议
    // 0xE8 0x85[7:1] 1111 111x
    reg_ip53xs = ip53xs_readByte(0xE8, 0x85); // Device 0xE8
    //[7:1] 1111 111x
    reg_ip53xs &= 0x01; // 1111 111x
    reg_ip53xs |= 0xFE;
    ip53xs_writeByte(0xE8, 0x85, reg_ip53xs); //! 1111 111x
    //! 2.1 开启VBUS输出DP快充
    // 0xEA 0x97[7:6] = 01
    reg_ip53xs = ip53xs_readByte(0xEA, 0x97); // Device 0xEA
    //[7:6] = 00
    reg_ip53xs &= 0x3F;                       //
    ip53xs_writeByte(0xEA, 0x97, reg_ip53xs); //! [7:6] = 00

    _dly_ms(30);
    //! 3 重新检测并开启有负载的 VOUT1/ VOUT2/ VBUS USB口
    // 0xEA 0x86  [5:3] 111
    reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA
    //[5:3] 111
    reg_ip53xs &= 0xC7;                       //
    reg_ip53xs |= 0x38;                       //[5:3] 111
    ip53xs_writeByte(0xEA, 0x86, reg_ip53xs); //! [5:3] 111
}

void disable_quick_charge(void)
{
    disable_DPDM_quick_charge();
    disable_DP_quick_charge(); //! 不会自动恢复
    bFlag_disable_quick_charge = 1;
}

void enable_quick_charge(void)
{

    enable_DPDM_quick_charge();
    enable_DP_quick_charge();
    bFlag_disable_quick_charge = 0;
}

//! 功率减半
void derating_power_temp_exception(void)
{
    unsigned char reg_ip53xs;
    unsigned char itmp;

    reg_ip53xs = ip53xs_readByte(0xE8, 0x29); // Device 0xE8 reg 0x29
    itmp = restore_reg0x29;
    itmp >>= 1;
    if (reg_ip53xs > itmp)
    {
        // restore_power = reg_ip53xs;
        // default_power = reg_ip53xs;
        default_power = restore_reg0x29;
        itmp = reg_ip53xs & 0x7F;
        itmp >>= 1;
        reg_ip53xs = (reg_ip53xs & 0x80) | (itmp & 0x7F); // 功率降低一半
        ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);         // Device 0xE8 reg 0x29
    }
    bFlag_derating_power_temp_ex = 1;
    derating_power_mode = 1;
}

void derating_power_temp_exception_again(void)
{
    unsigned char reg_ip53xs;
    unsigned char itmp;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x29); // Device 0xE8 reg 0x29
    itmp = reg_ip53xs & 0x7F;
    itmp >>= 1;
    reg_ip53xs = (reg_ip53xs & 0x80) | (itmp & 0x7F); // 功率降低一半
    ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);         // Device 0xE8 reg 0x29
    bFlag_derating_power_temp_ex = 1;
}
//! 功率恢复
void restore_power_temp_normal(void)
{
    unsigned char reg_ip53xs;
    // reg_ip53xs = restore_reg0x29;             //功率恢复
    // ip53xs_writeByte(0xE8, 0x29, reg_ip53xs); // Device 0xE8 reg 0x29
    reg_ip53xs = ip53xs_readByte(0xE8, 0x29);
    if (restore_reg0x29 != reg_ip53xs)
    {
        reg_ip53xs = restore_reg0x29;
        ip53xs_writeByte(0xE8, 0x29, reg_ip53xs);
    }
    bFlag_derating_power_temp_ex = 0;
}

// 通过判断VBUS电压（0XEA 0X63、0XEA 0X62）值判断当前输入电压值，
// 超出阈值时进行关闭灯显和关闭充电使能0XE8 0X00[0]。
// #define CONST_AD_5V_DN (2389) //3.85
#define CONST_AD_5V_DN (2358) // 3.80
#define CONST_AD_5V_UP (3848) // 6.2

#define CONST_AD_9V_DN (4841) // 7.8
#define CONST_AD_9V_UP (6331) // 10.2

// #define CONST_AD_12V_DN (6828) //11
#define CONST_AD_12V_DN (6331) // 10.2
#define CONST_AD_12V_UP (8193) // 13.2

#define CONST_OVP_FILTER 7

//! 欠压/过压，并进行灭灯，同时关闭充电使能0XE8 0X00[0]=0。
void disable_charger_on(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs &= (~BIT0);                    // 0xFE
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00
    bFlag_disable_charge_on = 1;
}
void enable_charger_on(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs |= BIT0;                       // 0x01
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00
    bFlag_disable_charge_on = 0;
    if (bFlag_is_exception_full)
    {
        displayData = 81;
        timer_led4_display = 100; // CONST_MINUTES_40; //! 40分钟
        timer_chg_minimum = 60;
        bFlag_is_exception_full = 0;
    }
}

//! 关闭充电使能0XE8 0X00[1]=0。
void disable_discharger_on(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs &= (~BIT1);
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00
    bFlag_disable_discharge_on = 1;
}
void enable_discharger_on(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0x00); // Device 0xE8 reg 0x00
    reg_ip53xs |= BIT1;
    ip53xs_writeByte(0xE8, 0x00, reg_ip53xs); // Device 0xE8 reg 0x00
    bFlag_disable_discharge_on = 0;
}
// Q3 & Q7
void ovp_input_proc(void)
{
    unsigned char reg_ip53xs;
    unsigned int itmp_16bits;
    static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, 0x63); // Device 0xEA
    itmp_16bits = reg_ip53xs;
    itmp_16bits <<= 8;

    reg_ip53xs = ip53xs_readByte(0xEA, 0x62); // Device 0xEA
    itmp_16bits |= reg_ip53xs;

    if (0 == bFlag_input_ovp)
    {
        if (bFlag_v_chg_5v && (CONST_AD_5V_DN < itmp_16bits) && (itmp_16bits < CONST_AD_5V_UP))
        {

            counter = 0;

            if ((bFlag_disable_charge_on))
            {
                if (bFlag_temp_alarm)
                {
                    return;
                }
                if (bFlag_temp_exception_chg)
                {
                    // if ((bFlag_vol_bat_over_4v) && bFlag_temp_exception_over_chg)
                    {
                        return;
                    }
                }

                enable_charger_on();
            }
            return;
        }

        if (bFlag_v_chg_9v && (CONST_AD_9V_DN < itmp_16bits) && (itmp_16bits < CONST_AD_9V_UP))
        {

            counter = 0;

            if ((bFlag_disable_charge_on))
            {
                if (bFlag_temp_alarm)
                {
                    return;
                }
                if (bFlag_charge_ext) // !03/15
                {
                    return;
                }
                if (bFlag_temp_exception_chg)
                {
                    // if ((bFlag_vol_bat_over_4v) && bFlag_temp_exception_over_chg)
                    {
                        return;
                    }
                }

                enable_charger_on();
            }
            return;
        }

        if (bFlag_v_chg_12v && (CONST_AD_12V_DN < itmp_16bits) && (itmp_16bits < CONST_AD_12V_UP))
        {

            counter = 0;

            if ((bFlag_disable_charge_on))
            {
                if (bFlag_temp_alarm)
                {
                    return;
                }
                if (bFlag_charge_ext) // !03/15
                {
                    return;
                }
                if (bFlag_temp_exception_chg)
                {
                    // if ((bFlag_vol_bat_over_4v) && bFlag_temp_exception_over_chg)
                    {
                        return;
                    }
                }

                enable_charger_on();
            }
            return;
        }

        // counter++;
        if (++counter > CONST_OVP_FILTER)
        {
            counter = 0;
            bFlag_input_ovp = 1;

            disable_charger_on();
        }
    }
}
//! is OK
void is_ocp_short_circuit(void)
{
    unsigned char reg_ip53xs;
    unsigned char i;
    // static unsigned char counter_gl = 0;
    // static unsigned char counter_dl = 0;

is_ocp_short_circuit_again:

    if ((bFlag_p_ext_int_is_high) && (P_I2C_INT))
    {
        reg_ip53xs = ip53xs_readByte(0xEA, 0xFC); // Device 0xEA  0xFC

        if (0 == bFlag_ocp) // 过流
        {
            if ((reg_ip53xs & BIT2))
            {
                ip53xs_writeByte(0xEA, 0xFC, reg_ip53xs);
                if (++counter_gl > 1)
                {
                    counter_gl = 0;
                    gl_timer_out = 0; //! why here is 2
                    bFlag_ocp = 1;
                    forceDispTimer = 0; //
                    bFlag_reverse = 0;
                    ledDispTimer = 0;          //
                    displayData = SEG_ALL_OFF; // ok
                    bFlag_all_led_is_off = 1;
                    //! disable_discharger_on(); //关输出 解决Q17 10/14
                    set_force_standby_mode();
                    return;
                }
                else
                {
                    // ip53xs_writeByte(0xEA, 0x00, reg_ip53xs); // Device 0xEA
                    gl_timer_out = 36; // 28; // 20;  3584mS
                }
                // bFlag_reg0xFC_bit2 = 1;
            }
            else
            {
                // bFlag_reg0xFC_bit2 = 0;
                if (0 == gl_timer_out)
                {
                    counter_gl = 0;
                }
                else
                {
                    gl_timer_out--;
                }
            }
        }

        if (0 == bFlag_short_circuit) // 短路
        {
            if ((reg_ip53xs & BIT0))
            {
                ip53xs_writeByte(0xEA, 0xFC, reg_ip53xs);
                if (++counter_dl > 1)
                {
                    counter_dl = 0;
                    dl_timer_out = 0; //! why here is 2
                    bFlag_short_circuit = 1;
                    forceDispTimer = 0; //
                    bFlag_reverse = 0;
                    ledDispTimer = 0;          //
                    displayData = SEG_ALL_OFF; // ok
                    bFlag_all_led_is_off = 1;
                    //! disable_discharger_on(); //关输出 解决Q17 10/14
                    set_force_standby_mode();
                    return;
                }
                else
                {
                    // ip53xs_writeByte(0xEA, 0x00, reg_ip53xs);
                    dl_timer_out = 36; // x128ms = 3584ms 20;
                }
                // bFlag_reg0xFC_bit0 = 1;
            }
            else
            {
                // bFlag_reg0xFC_bit0 = 0;
                if (0 == dl_timer_out)
                {
                    counter_dl = 0;
                }
                else
                {
                    dl_timer_out--;
                }
            }
        }

        if ((counter_dl) || (counter_gl))
        {
            // !tuneup  03/08
            for (i = 0; i < 2; i++)
            {
                _dly_ms(20);
                if ((bFlag_p_ext_int_is_high) && (P_I2C_INT))
                {
                    get_multi_port_status();
                }
                _dly_ms(32);
            }

            if ((bFlag_p_ext_int_is_high) && (P_I2C_INT)) // !important
            {
                goto is_ocp_short_circuit_again;
            }
        }
    }
}

//! 4.16-4.20

// 0xEA 0xFD[6]   //VOUT2输出欠压标志位，需写1清零
// 0xEA 0xFD[1]   //VOUT1输出欠压标志位，需写1清零
// 0xEA 0xFE[3]   //VBUS输出欠压标志位，需写1清零

void is_under_voltage(void)
{
    unsigned char reg_ip53xs;

    static unsigned char counter_is_uv = 0;

    reg_ip53xs = ip53xs_readByte(0xEA, 0xFD); // Device 0xEA  0xFC

    if (0 == bFlag_under_voltage) //! 欠压
    {
        if ((BIT1 == (reg_ip53xs & BIT1)) || (BIT6 == (reg_ip53xs & BIT6)))
        {
            ip53xs_writeByte(0xEA, 0xFD, reg_ip53xs);
            if (++counter_is_uv > 1)
            {
                counter_is_uv = 0;
                under_voltage_timer_out = 0; //! why here is 2
                bFlag_under_voltage = 1;
                //! disable_discharger_on(); //关输出 解决Q17 10/14
                set_force_standby_mode();
            }
            else
            {
                // ip53xs_writeByte(0xEA, 0x00, reg_ip53xs); // Device 0xEA
                under_voltage_timer_out = 36; // 28; // 20;  3584mS
            }
            // bFlag_reg0xFD_bitx = 1;
        }
        else
        {
            // bFlag_reg0xFD_bitx = 0;
            if (0 == under_voltage_timer_out)
            {
                counter_is_uv = 0;
            }
            else
            {
                under_voltage_timer_out--;
            }
        }
    }
}

//! 01/10 最大值改为 平均值 + 16挡 800mA
void change_total_current_limiting(void)
{
    unsigned char reg_ip53xs;
    unsigned char itmp_8bits;
    unsigned int itmp_16bits;

    reg_ip53xs = restore_reg0xb1; // ip53xs_readByte(0xE8, 0XB1); // Device 0xE8 reg 0xB1
    // restore_reg0xb1 = reg_ip53xs;
    reg_ip53xs &= 0x7F;
    itmp_16bits = (unsigned int)reg_ip53xs;
    // reg_ip53xs += 12;
    // ip53xs_writeByte(0xE8,0XB1, reg_ip53xs); // Device 0xE8 reg 0xB1
    reg_ip53xs = restore_reg0xb5; // ip53xs_readByte(0xE8, 0XB5); // Device 0xE8 reg 0xB5
    // restore_reg0xb5 = reg_ip53xs;
    reg_ip53xs &= 0x7F;
    itmp_16bits += (unsigned int)reg_ip53xs;
    // reg_ip53xs += 12;
    // ip53xs_writeByte(0xE8,0XB5, reg_ip53xs); // Device 0xE8 reg 0xB5

    reg_ip53xs = restore_reg0xb9; // ip53xs_readByte(0xE8, 0XB9); // Device 0xE8 reg 0xB9
    // restore_reg0xb9 = reg_ip53xs;
    reg_ip53xs &= 0x7F;
    itmp_16bits += (unsigned int)reg_ip53xs;

    //! 平均值
    reg_ip53xs = (unsigned char)(itmp_16bits / 3);
    reg_ip53xs &= 0x7F;
    //! 判断是否会溢出
    // if (reg_ip53xs < (0x7F - 0x10)) //! 01/10 最大值改为 平均值 + 16挡 800mA
    // {
    //     reg_ip53xs += 0x10; //! 16 --- 800mA + 3.47A
    // }
    if (reg_ip53xs < (0x7F - 0x0D)) //! 01/11 最大值改为 平均值 + 13挡 650mA
    {
        reg_ip53xs += 0x0D; //! 13 --- 650mA
    }
    else
    {
        reg_ip53xs = 0x7F;
    }
    // reg_ip53xs += 12;
    // ip53xs_writeByte(0xE8,0XB9, reg_ip53xs); // Device 0xE8 reg 0xB9
    // itmp = (restore_reg0xb1 & 0x7F);
    // if (itmp > reg_ip53xs)
    // {
    //     reg_ip53xs = itmp;
    // }
    // itmp = (restore_reg0xb5 & 0x7F);
    // if (itmp > reg_ip53xs)
    // {
    //     reg_ip53xs = itmp;
    // }
    // // reg_ip53xs += 12;  600mA + 3.47A
    // reg_ip53xs += 6; // 300mA + 3.47A

    itmp_8bits = (restore_reg0xb1 & 0x80);
    itmp_8bits |= reg_ip53xs;
    ip53xs_writeByte(0xE8, 0XB1, itmp_8bits); // Device 0xE8 reg 0xB1
    itmp_8bits = (restore_reg0xb5 & 0x80);
    itmp_8bits |= reg_ip53xs;
    ip53xs_writeByte(0xE8, 0XB5, itmp_8bits); // Device 0xE8 reg 0xB5
    itmp_8bits = (restore_reg0xb9 & 0x80);
    itmp_8bits |= reg_ip53xs;
    ip53xs_writeByte(0xE8, 0XB9, itmp_8bits); // Device 0xE8 reg 0xB9
    bFlag_change_total_i_limit = 1;
}

void restore_total_current_limiting(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = restore_reg0xb1;
    ip53xs_writeByte(0xE8, 0XB1, reg_ip53xs); // Device 0xE8 reg 0xB1

    reg_ip53xs = restore_reg0xb5;
    ip53xs_writeByte(0xE8, 0XB5, reg_ip53xs); // Device 0xE8 reg 0xB5

    reg_ip53xs = restore_reg0xb9;
    ip53xs_writeByte(0xE8, 0XB9, reg_ip53xs); // Device 0xE8 reg 0xB9
    bFlag_change_total_i_limit = 0;
}

void disable_vbus_dishg_i_low(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0X1B);
    if (reg_ip53xs & BIT0)
    {
        reg_ip53xs &= 0xFE;                       // 1111 1110
        ip53xs_writeByte(0xE8, 0X1B, reg_ip53xs); // Device 0xE8 reg 0x1B
    }
}

void enable_vbus_dishg_i_low(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xE8, 0X1B);
    if (0 == (reg_ip53xs & BIT0))
    {
        reg_ip53xs |= BIT0;                       // 1111 1110
        ip53xs_writeByte(0xE8, 0X1B, reg_ip53xs); // Device 0xE8 reg 0x1B
    }
}

// 4.53 MOS_STATE（输出 MOS 状态指示寄存器）
// I2C 地址 0XEA 寄存器地址= 0XEB
// [5] Mos_vout2_state Vout2 口输出 MOS 状态 0：关闭状态 1：开启状态
// [4] Mos_vout1_state Vout1 口输出 MOS 状态 0：关闭状态 1：开启状态
void get_multi_port_status(void)
{
    unsigned char reg_ip53xs;
    unsigned char port_num;
    reg_ip53xs = ip53xs_readByte(0xEA, 0xEB); // Device 0xEA  reg 0xEB

    port_num = 0;

    if (reg_ip53xs & BIT5) //! VOUT2  即 A2口
    {
        port_num++;
    }
    if (reg_ip53xs & BIT4) //! VOUT1  即 A1口
    {
        port_num++;
    }

    if (reg_ip53xs & BIT6) //! VBUS  即 C口
    {
        port_num++;

        if (port_num > 1)
        {
            disable_vbus_dishg_i_low();
        }
    }
    else
    {
        enable_vbus_dishg_i_low();
    }

    if (bFlag_multi_port)
    {
        if (port_num < 2)
        {
            bFlag_multi_port = 0;

            if (bFlag_change_total_i_limit)
            {
                restore_total_current_limiting();
            }
        }
    }
    else
    {
        if (port_num > 1)
        {
            bFlag_multi_port = 1;

            if (0 == bFlag_change_total_i_limit)
            {
                change_total_current_limiting();
            }
        }
    }

    if (bFlag_usb_a1_in)
    {
        if (0 == (reg_ip53xs & BIT4))
        {
            bFlag_usb_a1_in = 0;
            // if (bFlag_disable_discharge_on)
            // {
            //     enable_discharger_on();
            // }
        }
    }
    else
    {
        if (reg_ip53xs & BIT4)
        {
            bFlag_usb_a1_in = 1;

            if (bFlag_all_led_is_off)
            {
                bFlag_all_led_is_off = 0;
                if (displayData) //! 电量不等于0
                {

                    forceDispTimer = 5; // 6 --5led  << -- 5 -- 4led 最后一个亮250ms               //跑马灯
                    bFlag_reverse = 0;
                    display_cycle = 125;                  //! 跑马灯
                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
                else
                {

                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
            }
        }
    }

    if (bFlag_usb_a2_in)
    {
        if (0 == (reg_ip53xs & BIT5))
        {
            bFlag_usb_a2_in = 0;
            // if (bFlag_disable_discharge_on)
            // {
            //     enable_discharger_on();
            // }
        }
    }
    else
    {
        if (reg_ip53xs & BIT5)
        {
            bFlag_usb_a2_in = 1;

            if (bFlag_all_led_is_off)
            {
                bFlag_all_led_is_off = 0;

                if (displayData) //! 电量不等于0
                {

                    forceDispTimer = 5; // 6 --5led  << -- 5 -- 4led 最后一个亮250ms               //跑马灯
                    bFlag_reverse = 0;
                    display_cycle = 125;                  //! 跑马灯
                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
                else
                {

                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
            }
        }
    }
}
//! 4.05V << -- 4.12V  007EL-Test41 12/03
void vol_bat_is_over_4v(void)
{
}

void vol_bat_is_under_3v5(void)
{
}

//
#define CONST_FILTER_SCP 2
void get_protocol_indication(void)
{
}

//! 18. Q19：电池电压小于3.5V时，没有降功率
// 1．	步骤一：先关闭 VOUT2 口 MOS，将寄存器 0XEA 0X86[1]=1
// 2．	步骤二：进行调节SCP广播功率，0XE8 0X90[1:0]=10
// 3．	步骤三：同时SCP限流在默认值0XE8 0XA6[6:0]基础上要减1A（50ma/step）
// 4．	步骤四：延时500ms后，重新检测并开启有负载的 VOUT2 USB 口，将寄存器 0XEA 0X86[4]=1

//! 直接降到3.8A
void derating_power_bat_under_3v5(void) //! 3.6A
{
}

void derating_power_bat_under_3v5_no_reset(void) //! 3.6A
{
}
#if 0
void restore_power_bat_over_3v5(void)
{

    unsigned char reg_ip53xs;
    // unsigned char itmp;

    // 1.先关闭 VOUT2 口 MOS，将寄存器 0XEA 0X86[1]=1
    //  reg_ip53xs = ip53xs_readByte(0xEA,0x86); // Device 0xEA  reg 0x86
    //  restore_reg0x86 = reg_ip53xs;
    //  reg_ip53xs |= BIT1;
    // reg_ip53xs = restore_reg0x86;
    // ip53xs_writeByte(0xEA, 0x86, reg_ip53xs);

    // 2 进行调节SCP广播功率，0XE8 0X90[1:0]=10
    // reg_ip53xs = ip53xs_readByte(0xE8, 0x90); // Device 0xE8 reg 0x90
    // reg_ip53xs &= 0xFC;
    // reg_ip53xs |= BIT1; // 10
    // ip53xs_writeByte(0xE8, 0x90, reg_ip53xs);

    // 3 同时SCP限流在默认值0XE8 0XA6[6:0]基础上要减1A（50ma/step）
    //  reg_ip53xs = ip53xs_readByte(0xE8,0xA6); // Device 0xE8 reg 0xA6
    //  restore_reg0xA6 = reg_ip53xs;
    //  if (reg_ip53xs > 20)
    //  {
    //      reg_ip53xs -= 20;
    //  }

    reg_ip53xs = restore_reg0xA6;
    // if (bFlag_adjust_scp_ocp)
    // {
    //     reg_ip53xs -= 6; //!降低300mA reg_ip53xs -= 10; //!降低500mA
    // }
    ip53xs_writeByte(0xE8, 0xA6, reg_ip53xs);

    // 4.延时500ms后，重新检测并开启有负载的 VOUT2 USB 口，将寄存器 0XEA 0X86[4]=1
    // _dly_ms(250);
    // _dly_ms(250);
    // reg_ip53xs = ip53xs_readByte(0xEA, 0x86); // Device 0xEA  reg 0x86
    // reg_ip53xs |= BIT4;
    // ip53xs_writeByte(0xEA, 0x86, reg_ip53xs);
    bFlag_under_3v5_derating_power = 0;
    bFlag_adjust_scp_ocp_5A = 0;
    bFlag_adjust_scp_ocp_4A5 = 0;
}
#endif
// 已经更新硬件参数，调整SCP电流为5A，所以需要MCU配合调整SCP限流值：
// 进入SCP协议后根据输出电压调整限流，调整寄存器为0XE8 0XA6[6:0]，档位50ma/step
// 当vsys电压为4.5V以下时，则保持SCP限流值0XE8 0XA6[6:0]为默认值5A
// 当vsys电压为4.5V以上时，则调整SCP限流值0XE8 0XA6[6:0]为4.5A，在默认值基础上减小500ma
// 退出SCP协议时，需要恢复默认值

void derating_power_scp_over_4v5(void) //! 大于4V5 -- 4A5
{
    unsigned char reg_ip53xs = 0;
    // reg_ip53xs = ip53xs_readByte(0xE8,0xA6); // Device 0xE8 reg 0xA6
    // restore_reg0xA6_2 = reg_ip53xs;     //区别于 under 3v5 的降低电流
    //                                     // reg_ip53xs -= 10;
    // reg_ip53xs -= 6;
    // reg_ip53xs = 95; //90;
    // reg_ip53xs = (restore_reg0xA6 - 10);
    // reg_ip53xs = (restore_reg0xA6 - 13); //!-13档
    // reg_ip53xs = (restore_reg0xA6 - 12); //!-12档
    reg_ip53xs = (restore_reg0xA6 - 11); //!-11档
    ip53xs_writeByte(0xE8, 0xA6, reg_ip53xs);

    reg_ip53xs = ip53xs_readByte(0xE8, 0xA6); // Device 0xE8 reg 0xA6

    bFlag_adjust_scp_ocp_4A5 = 1;
    bFlag_adjust_scp_ocp_5A = 0;
}
#if 0 // new 5356 1109
void derating_power_scp_under_4v5(void) //! 小于4V5  -- 5A
{
    unsigned char reg_ip53xs = 0;
    // reg_ip53xs = ip53xs_readByte(0xE8,0xA6); // Device 0xE8 reg 0xA6
    // restore_reg0xA6_2 = reg_ip53xs;     //区别于 under 3v5 的降低电流
    //                                     // reg_ip53xs -= 10;
    // reg_ip53xs -= 6;
    // reg_ip53xs = (restore_reg0xA6 + 4); //!+4档 +200mA
    reg_ip53xs = (restore_reg0xA6 & 0x7F);
    if (reg_ip53xs > (0x7F - 0x06))
    {
        reg_ip53xs = 0x7F;
    }
    else
    {
        reg_ip53xs = (restore_reg0xA6 + 6); //!+6档 +300mA
    }
    ip53xs_writeByte(0xE8, 0xA6, reg_ip53xs);

    reg_ip53xs = ip53xs_readByte(0xE8, 0xA6); // Device 0xE8 reg 0xA6


    bFlag_adjust_scp_ocp_5A = 1;
    bFlag_adjust_scp_ocp_4A5 = 0;
}
#endif
void restore_power_no_in_scp_A3(void) //! 退出SCP恢复
{
    unsigned char reg_ip53xs = 0;
    // reg_ip53xs = ip53xs_readByte(0xE8,0xA6); // Device 0xE8 reg 0xA6
    // restore_reg0xA6 = reg_ip53xs;
    reg_ip53xs = restore_reg0xA6;
    ip53xs_writeByte(0xE8, 0xA6, reg_ip53xs);

    bFlag_adjust_scp_ocp_5A = 0;
    bFlag_adjust_scp_ocp_4A5 = 0;
    // bFlag_under_3v5_derating_power = 0;//!!! 11/11
}

void get_type_c_state(void) // 12/29  test OK
{
    // I2C 地址 0XEA 寄存器地址= 0XF3
    // [7]cc_src_ok cc_src_ok，typec 连接成 src(//!作为输出)1：有效0：无效  //! 放电
    // [6] cc_sink_ok, cc_sink_ok, typec 连接成 sink(//!作为输入)1：有效0：无效  //! 充电
    unsigned char reg_ip53xs = 0;

    reg_ip53xs = ip53xs_readByte(0xEA, 0xF3); // Device 0xEA  reg 0xF3
    // reg_ip53xs &= 0xC0;                       //[bit7:bit4]
    // reg_ip53xs &= 0x40; //! 0100 0000  !!!fuck
    reg_ip53xs &= 0x80;
    if (bFlag_typec_in)
    {
        if (0 == reg_ip53xs)
        {
            bFlag_typec_in = 0;
            // if (bFlag_in_small_current_mode) //! fix a bug
            // {
            //     delaySleepTimer = CNST_TIMER_DLY_SLP_SML; //!关机倒计时

            // }
            // if (bFlag_disable_discharge_on)
            // {
            //     enable_discharger_on();
            // }
        }
    }
    else
    {
        if (reg_ip53xs)
        {
            bFlag_typec_in = 1; //! typeC to lightning  线在 不需要小电流模式 也不需要轻载关机

            if (bFlag_all_led_is_off)
            {
                bFlag_all_led_is_off = 0;

                if (displayData) //! 电量不等于0
                {

                    forceDispTimer = 5; // 6 --5led  << -- 5 -- 4led 最后一个亮250ms               //跑马灯
                    bFlag_reverse = 0;
                    display_cycle = 125;                  //! 跑马灯
                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
                else
                {

                    ledDispTimer = CONST_TIMER_DISP_XSEC; //! 亮5秒
                }
            }
        }
    }
}

// 3、当时间到后需要关机时，可以通过写寄存器的方式让IP5356进入休眠状态（I2C 地址 0XEA 寄存器地址 0X86 Bit7 写 1），
// 写完后就不要再访问I2C，等INT为低后MCU就可以进入休眠状态。

// add for ip 5356
void set_force_standby_mode(void)
{
    unsigned char reg_ip53xs;
    unsigned char timerOut;

    reg_ip53xs = ip53xs_readByte(0xEA, REG_FORCE_STANDBY); // Device 0xEA ，Reg 0x86 bit7 < -- 1
    reg_ip53xs &= 0x7F;
    reg_ip53xs |= b_Force_Standby;                         //
    ip53xs_writeByte(0xEA, REG_FORCE_STANDBY, reg_ip53xs); //
    bFlag_p_ext_int_is_high = 0;
    timerOut = 100;
    while (P_I2C_INT)
    {

        _dly_ms(10);
        if (!(--timerOut))
        {

            break;
        }
    }
}

// Q26 Q32 10/14
//  建议MCU自己管理 Isys电流来控制系统关机，还能同步优化“问题26”  (这里是“问题32”)
//  1、MCU在初始化IP5356寄存器时候需要先将ISYSLOW轻载关机功能关闭（En_Isys_Low I2C地址 0XE8 寄存器地址 0X03  bit2 写 0）
//  2、判断处于单口放电并且处于非常开模式时，读取ISYSADC阈值（0xEA 0x70/0xEA 0x71）来判断：
//  A口是否小于50ma，如果连续小于5s则灭灯，持续小于120s后则关机。如果电流大于100ma则亮灯；
//  C口是否小于70ma，如果连续小于5s则灭灯，持续小于120s后则关机。如果电流大于100ma则亮灯；
//  3、当时间到后需要关机时，可以通过写寄存器的方式让IP5356进入休眠状态（I2C 地址 0XEA 寄存器地址 0X86 Bit7 写 1），写完后就不要再访问I2C，等INT为低后MCU就可以进入休眠状态。
//  shutdown_timer 正常模式赋值 120秒 小电流模式7200秒  2*60*60  直接用 delaySleepTimer 实现 shutdown_timer 的功能
//  小电流模式开启 2小时关机倒计时开始 （不区分小电流充电还是正常充电，快充)

// C口轻载只要关灯 不需要120秒后关机 也不需要小电流模式

// 充电模式下 C线拔出 不管A口是否带载 直接关机  A口插拔才转放电模式
// 3.1 SYS_CTL0(boost 和 charger 使能寄存器)
// I2C 地址 0XE8 寄存器地址= 0x00
// Bit(s) Name Description R/W RESET
// 7:4 Reserved R/W XX
// 3：2 En_C2B_Det 拔掉输入充电是否自动转 boost 输出
//! 1X：系统不转 boost 直接进入待机
// 01：输出有负载才自动开启 boost，没有负载就进入关
// 机
// 00：无论输出是否有负载，自动开启 boost

//! 1027

// 4.51 CHG_STATE1（系统状态指示寄存器）
// I2C 地址 0XEA 寄存器地址= 0XE8
// Bit(s) Name Description R/W
// 7 Vbus_mosi_
// state
// C 口输入 MOS 状态
// 1：开启
// 0：关闭
// R
// 6 Vin_mos_ state B 口输入 MOS 状态
// 1：开启
// 0：关闭
// R
// 5：4 Vchg_state
// 00：5V 充电
// 01：7V 充电
// 10：9V 充电
// 11：12V 充电
// R
// 3:0 Reserve

void get_v_chg_state(void)
{
    //! I2C 地址 0XEA 寄存器地址= 0XE8
    unsigned char reg_ip53xs;
    reg_ip53xs = ip53xs_readByte(0xEA, 0xE8); // Device 0xEA ，Reg 0XE8
    reg_ip53xs >>= 4;
    reg_ip53xs &= 0x03;
    switch (reg_ip53xs)
    {
    case 0:

        bFlag_v_chg_5v = 1;

        bFlag_v_chg_7v = 0;
        bFlag_v_chg_9v = 0;
        bFlag_v_chg_12v = 0;

        break;
    case 1:
        bFlag_v_chg_5v = 0;
        if (0 == bFlag_v_chg_7v)
        {
            bFlag_v_chg_7v = 1;
            g_counter_cc = 0;
        }
        bFlag_v_chg_9v = 0;
        bFlag_v_chg_12v = 0;

        break;
    case 2:
        bFlag_v_chg_5v = 0;
        bFlag_v_chg_7v = 0;
        if (0 == bFlag_v_chg_9v)
        {
            bFlag_v_chg_9v = 1;
            g_counter_cc = 0;
        }
        bFlag_v_chg_12v = 0;

        break;

    case 3:
        bFlag_v_chg_5v = 0;
        bFlag_v_chg_7v = 0;
        bFlag_v_chg_9v = 0;
        if (0 == bFlag_v_chg_12v)
        {
            bFlag_v_chg_12v = 1;
            g_counter_cc = 0;
        }

        break;
    default:

        break;
    }
}

//! << ----  非pd协议 9v 降低限流

//! 1. 判断是否处于pd输出 (0xea 0xc2[7] = 1),如果处于pd输出, 保持9v 限流不动 (0xE8,0xBB[6:0])
// 4.43 PD_STATE1（系统状态指示寄存器）
// I2C 地址 0XEA 寄存器地址= 0XC2
// Bit(s) Name Description R/W
// 7 Src _Pd_Ok PD SRC 输出连接标志位
// 1：有效
// 0：无效
// R
// 6:0 Reserved

void is_sink_pd_ok(void)
{
    unsigned char reg_ip53xs = 0;
    static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, 0xC2); // Device 0xEA  reg 0xC2
    reg_ip53xs &= BIT7;

    if (bFlag_sink_pd)
    {
        if (0 == reg_ip53xs)
        {
            if (++counter > 2)
            {
                counter = 0;
                bFlag_sink_pd = 0;
                if (0 == bFlag_derating_power_non_pd_9v)
                {
                    derating_power_non_pd_9v();
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
    else
    {
        if (reg_ip53xs)
        {
            if (++counter > 2)
            {
                counter = 0;
                bFlag_sink_pd = 1;
                if (bFlag_derating_power_non_pd_9v)
                {
                    restore_power_non_pd_9v();
                }
            }
        }
        else
        {
            counter = 0;
        }
    }
}
//! 2. 当不处于pd输出状态时，将C口输出限流。基于默认值减小 300ma，(0xE8,0xBB[6:0])
// 3.55 VBUS _9V（9V 输出电流设置寄存器）
// I2C 地址 0XE8 寄存器地址= 0XBB
// Bit(s) Name Description R/W RESET
// 77 Reserved R/W XX
// 6:0 TRSEL_REG 50mA*N
// 出厂时输出校准到 2.3A，如需要调

void derating_power_non_pd_9v(void)
{
    unsigned char reg_ip53xs;
    // reg_ip53xs = restore_reg0xBB & 0x7F;
    // if (reg_ip53xs > 6)
    // {
    //     reg_ip53xs -= 6;
    // }
    // reg_ip53xs |= (restore_reg0xBB & 0x80);
    reg_ip53xs = (restore_reg0xBB - 6);
    ip53xs_writeByte(0xE8, 0xBB, reg_ip53xs);
    bFlag_derating_power_non_pd_9v = 1;
}

void restore_power_non_pd_9v(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = restore_reg0xBB;
    ip53xs_writeByte(0xE8, 0xBB, reg_ip53xs);
    bFlag_derating_power_non_pd_9v = 0;
}

//! SCP 线补
//! 进入SCP协议后根据VSYS电流调整电压补偿，调整寄存器为0XE8 0XAC[7：4]，档位50mV/step
//! 1、	当判断到VSYS电流处于2.5A > ISYS时，保持默认值

//! 2、	当判断到VSYS电流增加到2.5A<= ISYS <3.5A时，将0XE8 0XAC的值基于默认值加1档；当电流减小到2.0A时，如果之前是有效加档，那么基于当前值减1档。否则不减档。

//! 3、	当判断到VSYS电流增加到3.5A<= ISYS <4.5A时，将0XE8 0XAC的基于默认值加2档；
//! 当电流减小到3.0A时，如果之前是有效加档，那么基于当前值减1档，。否则不减档。

//! 4、	当判断到VSYS电流增加到4.5A<= ISYS时，将0XE8 0XAC的基于默认值加3档；
//! 当电流减小到4.0A时，如果之前是有效加档，那么基于当前值减1档。否则不减档。

// 4.31 ISYS_IADC_DAT0（IVSYS 端电流寄存器）
// I2C 地址 0XEA 寄存器地址= 0x70
// Bit(s) Name Description R/W
// 7:0 ISYSIADC[7:0] IVSYS 端电流 VSYSIADC 数据的低 8bit R
// 4.32 IVSYS_IADC_DAT1（IVSYS 端电流寄存器）
// I2C 地址 0XEA 寄存器地址= 0x71
// Bit(s) Name Description R/W
// 7:0 IVSYSIADC[15:8
// ]
// IVSYS 端电流 VSYSIADC 数据的高 8bit
// IVSYS=ISYSVADC*0.671387mA
// 电流不区分正负方向

//! 2500/0.671387

#define CNST_AD_0A10 (148) //! 0.10V
#define CNST_AD_0A15 (223) //! 0.15V
#define CNST_AD_0A20 (298) //! 0.20V
#define CNST_AD_0A25 (372) //! 0.25V
#define CNST_AD_0A30 (447) //! 0.30V

#define CNST_SCHMIDT CNST_AD_0A20

#define CNST_AD_1A5 (2048)
#define CNST_AD_2A5 (3724)
#define CNST_AD_3A5 (5213)
#define CNST_AD_4A5 (6703)

#define CNST_ISYS_GRADE_1 CNST_AD_2A5
#define CNST_ISYS_GRADE_2 CNST_AD_3A5
#define CNST_ISYS_GRADE_3 CNST_AD_4A5

void in_scp_add_voltage_offset(void)
{
}
void restore_reg0xAC_in_scp(void)
{
    unsigned char reg_ip53xs;
    reg_ip53xs = restore_reg0xAC;
    ip53xs_writeByte(0xE8, 0xAC, reg_ip53xs);
    add_voltage_offset = 0;
}

//! 2<---

// 快充输出接近过流值时，会出现4.2V 1.9A的异常现象
// 1、MCU实时读取0Xea 0xa9[7:0]的值   //3.2V+40mV*N
// 2、当满足0Xea 0xa9[7:0]的值大于7V并且VBAT大于4V时
// 3、MCU判断VSYS电压值，当出现VSYS < 4.75V时，关闭输出，进入过流保护状态
// 7-3.2 = 3.8
//
#define CONST_TREL_AD_7V (95)
void get_0xea_0xa9(void)
{
    unsigned char reg_ip53xs;
    static unsigned char counter;
    reg_ip53xs = ip53xs_readByte(0xEA, 0xA9);
    if (bFlag_trel_over_7v)
    {
        if (reg_ip53xs < (CONST_TREL_AD_7V - 5))
        {
            if (++counter > 3)
            {
                counter = 0;
                bFlag_trel_over_7v = 0;
            }
        }

        else
        {
            counter = 0;
        }
    }
    else
    {
        if (reg_ip53xs > (CONST_TREL_AD_7V + 5))
        {
            if (++counter > 3)
            {
                counter = 0;
                bFlag_trel_over_7v = 1;
            }
        }
        else
        {
            counter = 0;
        }
    }
}

/*
void init_battery_volume(void)
{
    // unsigned char reg_ip53xs;

    get_voltage_battery(); // OK

    if (ad_voltage_battery <= CONST_AD_VOLTAGE_0)
    {
        battery_volume_voltage = 0;
    }
    else
    {
        battery_volume_voltage = (ad_voltage_battery - CONST_AD_VOLTAGE_0) / CONST_AD_VOL_EVERY_PERCENT;
    }

    if (battery_volume_voltage > 100)
        battery_volume_voltage = 100;

    // v_battery_average = voltage_battery;

    if (battery_volume_voltage < 50)
    {
        displayData = battery_volume_voltage >> 1;
    }
    else if (battery_volume_voltage < 85)
    {
        displayData = (battery_volume_voltage - 8);
    }
    else
    {
        // 100 保持; 99 98 -1;97 96 -2;
        displayData = (battery_volume_voltage - 50 + (battery_volume_voltage >> 1));
    }

    // get_indicator_light_mode();
}
*/
