/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"
#include "app_global.h"
#include "bsp_adc.h"
void init_adc(void)
{

     ANSELA = 0B00000100;  //AN2
    ADCON1 = 0B11100100; //右对齐，转换时钟Fosc/64，负参考电压GND，正参考电压内部电压(2V)
	// Bit7: 对齐方式选择位
	// !1 = 右对齐
	// 0 = 左对齐

	// Bit[6:4]:ADC转换时钟选择位
	// 000 = FOSC/2
	// 001 = FOSC/8
	// 010 = FOSC/32
	// 011 = FRC（由专用RC振荡器提供时钟）
	// 100 = FOSC/4
	// 101 = FOSC/16
	// !110 = FOSC/64
	// 111 = FRC（由专用RC振荡器提供时钟）

	// Bit[3:2]:ADC负参考电压配置位（使用PB6连接外部参考电压或外部电容）
	// 00 = Int Vref（内部参考电压）
	// !01 = GND
	// 10 = Int Vref + Ext Cap（内部参考电压 + 外部电容）
	// 11 = Ext Vref（外部参考电压）

	// Bit[1:0]:ADC正参考电压配置位（使用PB5连接外部参考电压或外部电容）
	// !00 = Int Vref（内部参考电压）
	// 01 = VDD
	// 10 = Int Vref + Ext Cap（内部参考电压 + 外部电容）
	// 11 = Ext Vref（外部参考电压）

	ADCON0 = 0B00000000; //选择AD转换通道0，使能ADC
						 // Bit[6:4]:ADC模拟通道选择位
						 // 000 = AN0
						 // 001 = AN1
						 // 010 = AN2
						 // 011 = AN3
						 // 100 = AN4
						 // 101 = AN5
						 // 110 = AN6
						 // 111 = 1/4 VDD
						 //其余保留

	// Bit3: 保留位

	// Bit2:	ADC触发信号类型选择
	//该位决定启动ADC的触发条件
	// 0 = 当软件设定GO/DONE位，启动AD转换
	// 1 = 需要外部触发信号触发才可启动AD转换，触发事件置位GO/DONE位。
	//外部触发信号条件由寄存器ETGSEL<2:0>和ETGTYP<1:0>决定。

	// Bit1:AD转换状态位
	// 0 = A/D转换完成/未进行。
	// 1 = A/D转换正在进行或硬件触发延时正在计数。

	// Bit0:使能ADC
	// 0 = ADC被禁止且不消耗工作电流
	// 1 = ADC被使能

	// ADCON2 = 0B01000000; //选择内部正参考电压2V，无外部触发源
	// Bit[7:6]:ADC内部参考电压配置位
	// 00 = 0.5V
	// !01 = 2V
	// 10 = 3V
	// 11 = float（悬空）
	ADCON2 = 0B01000000; //选择内部正参考电压//!3V，无外部触发源
	// Bit[5:4]:外部触发信号类型选择
	//当ADEX置1，该位决定响应外部触发的类型
	// !00 = PWM 或 ADC_ETR脚的下降沿
	// 01 = PWM 或 ADC_ETR脚的上升沿
	// 10 = 一个PWM周期的中点
	// 11 = 一个PWM周期的终点

	// Bit3:ADC外部触发延时计数器阈值 第8位

	// Bit[2:0]:外部触发源选择
	//当ADEX为1，该位选择外部触发ADC的来源
	//选择PWM源时需要配置TIMER为PWM输出模式并使能输出。
	// 000 = PWM0
	// 001 = PWM1
	// 010 = PWM2
	// 011 = PWM3
	// 100 = PWM4
	// 101 = PWM5
	// 110 = PWM6
	// 111 = ADC_ETR

	ADCON3 = 0B00000000;
	// Bit7:ADC比较结果响应故障刹车使能
	// 0 = 禁止
	// 1 = ADC触发故障刹车功能使能

	// Bit6:ADC比较器输出极性选择位
	// 0 = 若ADC结果的高八位大于或等于ADCMPH[7:0]，ADCMPO为1
	// 1 = 若ADC结果的高八位小于ADCMPH[7:0]，ADCMPO为1

	// Bit5:ADC结果比较使能位
	// 0 = ADC结果比较功能关闭
	// 1 = ADC结果比较功能打开

	// Bit4:ADC比较结果输出位
	//该位输出ADCMPOP设定的比较输出结果。每次AD转换结束都会更新输出

	// Bit3:前沿消隐周期结束后，ADC触发使能
	// 1 = 触发ADC转换
	// 0 = 不触发ADC转换

	// Bit2:保留位
	// Bit[1:0]:外部LVD管脚输入选择，只有当LVDM为1时才有效
	// 00 = ELVD0
	// 01 = ELVD1
	// 10 = ELVD2
	// 11 = ELVD3

	ADDLY = 0B00000000; //外部触发延时，没用到
	// ADC外部触发启动延时计数器阈值低位
	//该8位寄存器与ADCON2.7组成9位计数器，用于在外部触发启动ADC之前加入一段延迟。延迟计数器结束再开始ADC转换
	//外部延迟时间 = (ADDLY+6)/FADC
	ADCMPH = 0B00000000; // ADC比较阈值,仅8位，用于ADC结果高8位比较。
	ADON = 1;			 // 使能ADC
}
void init_adc2(void)
{
    PCKEN |= 0B00000001; // AD模块时钟使能
    //模拟口设置，AN2为模拟管脚
    ANSELA = 0B00000100;
    ADCON1 = 0B11100100; //右对齐，转换时钟Fosc/64，负参考电压GND，正参考电压内部电压(2V)
    // Bit7: 对齐方式选择位
    // 1 = 右对齐
    // 0 = 左对齐

    // Bit[6:4]:ADC转换时钟选择位
    // 000 = FOSC/2
    // 001 = FOSC/8
    // 010 = FOSC/32
    // 011 = FRC（由专用RC振荡器提供时钟）
    // 100 = FOSC/4
    // 101 = FOSC/16
    // 110 = FOSC/64
    // 111 = FRC（由专用RC振荡器提供时钟）

    // Bit[3:2]:ADC负参考电压配置位（使用PB6连接外部参考电压或外部电容）
    // 00 = Int Vref（内部参考电压）
    // 01 = GND
    // 10 = Int Vref + Ext Cap（内部参考电压 + 外部电容）
    // 11 = Ext Vref（外部参考电压）

    // Bit[1:0]:ADC正参考电压配置位（使用PB5连接外部参考电压或外部电容）
    // 00 = Int Vref（内部参考电压）
    // 01 = VDD
    // 10 = Int Vref + Ext Cap（内部参考电压 + 外部电容）
    // 11 = Ext Vref（外部参考电压）

    ADCON0 = 0B00000000; //选择AD转换通道0，使能ADC
    // Bit[6:4]:ADC模拟通道选择位
    // 000 = AN0
    // 001 = AN1
    // 010 = AN2
    // 011 = AN3
    // 100 = AN4
    // 101 = AN5
    // 110 = AN6
    // 111 = 1/4 VDD
    //其余保留

    // Bit3: 保留位

    // Bit2:	ADC触发信号类型选择
    //该位决定启动ADC的触发条件
    // 0 = 当软件设定GO/DONE位，启动AD转换
    // 1 = 需要外部触发信号触发才可启动AD转换，触发事件置位GO/DONE位。
    //外部触发信号条件由寄存器ETGSEL<2:0>和ETGTYP<1:0>决定。

    // Bit1:AD转换状态位
    // 0 = A/D转换完成/未进行。
    // 1 = A/D转换正在进行或硬件触发延时正在计数。

    // Bit0:使能ADC
    // 0 = ADC被禁止且不消耗工作电流
    // 1 = ADC被使能

    ADCON2 = 0B01000000; //选择内部正参考电压2V，无外部触发源
    // Bit[7:6]:ADC内部参考电压配置位
    // 00 = 0.5V
    // 01 = 2V
    // 10 = 3V
    // 11 = float（悬空）

    // Bit[5:4]:外部触发信号类型选择
    //当ADEX置1，该位决定响应外部触发的类型
    // 00 = PWM 或 ADC_ETR脚的下降沿
    // 01 = PWM 或 ADC_ETR脚的上升沿
    // 10 = 一个PWM周期的中点
    // 11 = 一个PWM周期的终点

    // Bit3:ADC外部触发延时计数器阈值 第8位

    // Bit[2:0]:外部触发源选择
    //当ADEX为1，该位选择外部触发ADC的来源
    //选择PWM源时需要配置TIMER为PWM输出模式并使能输出。
    // 000 = PWM0
    // 001 = PWM1
    // 010 = PWM2
    // 011 = PWM3
    // 100 = PWM4
    // 101 = PWM5
    // 110 = PWM6
    // 111 = ADC_ETR

    ADCON3 = 0B00000000;
    // Bit7:ADC比较结果响应故障刹车使能
    // 0 = 禁止
    // 1 = ADC触发故障刹车功能使能

    // Bit6:ADC比较器输出极性选择位
    // 0 = 若ADC结果的高八位大于或等于ADCMPH[7:0]，ADCMPO为1
    // 1 = 若ADC结果的高八位小于ADCMPH[7:0]，ADCMPO为1

    // Bit5:ADC结果比较使能位
    // 0 = ADC结果比较功能关闭
    // 1 = ADC结果比较功能打开

    // Bit4:ADC比较结果输出位
    //该位输出ADCMPOP设定的比较输出结果。每次AD转换结束都会更新输出

    // Bit3:前沿消隐周期结束后，ADC触发使能
    // 1 = 触发ADC转换
    // 0 = 不触发ADC转换

    // Bit2:保留位
    // Bit[1:0]:外部LVD管脚输入选择，只有当LVDM为1时才有效
    // 00 = ELVD0
    // 01 = ELVD1
    // 10 = ELVD2
    // 11 = ELVD3

    ADDLY = 0B00000000; //外部触发延时，没用到
    // ADC外部触发启动延时计数器阈值低位
    //该8位寄存器与ADCON2.7组成9位计数器，用于在外部触发启动ADC之前加入一段延迟。延迟计数器结束再开始ADC转换
    //外部延迟时间 = (ADDLY+6)/FADC
    ADCMPH = 0B00000000; // ADC比较阈值,仅8位，用于ADC结果高8位比较。
    ADON = 1;            //全能ADC
}

/*-------------------------------------------------
* 函数名：GET_ADC_DATA
* 功能：  读取通道ADC值
* 输入：  adcChannel 通道序号
* 输出：  INT类型AD值(单次采样无滤波)
 --------------------------------------------------*/
void GET_ADC_DATA(unchar adcChannel)
{
//    ADON = 1; //全能ADC
//    ADCON0 &= 0B00001111;
//    ADCON0 |= adcChannel << 4; //重新加载通道值
//    ADCON2 = 0B01000000;
//    DelayUs(40); //延时等待电压稳定 Tst >10us
//    GO = 1; //启动ADC
//    NOP();
//    NOP();
//    while (GO)
//        ; //等待ADC转换完成
//    TempRam8 = 8;
//    TempRam16 = 0;
//    while (TempRam8)
//    {
//        TempRam8--;
//        GO = 1; //启动ADC
//        NOP();
//        NOP();
//        while (GO)
//            ; //等待ADC转换完成
//        adcData = ADRESH;
//        adcData = (adcData << 8);
//        adcData |= ADRESL; //整合12位AD值
//        TempRam16 += adcData;
//    }
//    adcData = (TempRam16 >> 3);
}
// adcData = GET_ADC_DATA(2); 					//通道0 AD值
// theVoltage = (unlong)adcData*2*1000/4096;	//电压放大1000倍
