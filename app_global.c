/**
 *   @author      mathison.wai
 *   @Date        2023.02.14
 *   @Version     V1.0
 *
 **/

#include "SYSCFG.h"
#include "app_cfg.h"
#include "app_global.h"
#include "bsp_i2c.h"
#include "bsp_ip53xs.h"
#include "app_bms_ip53xs.h"
#include "bsp_io_uart.h"
#include "app_global.h"

void _dly_us(unsigned char Time)
{
    unsigned char a;
    for (a = 0; a < Time; a++)
    {
        NOP();
    }
}
void _dly_ms(unsigned char timer)
{
    unsigned char a, b;
    for (a = 0; a < timer; a++)
    {
        for (b = 0; b < 5; b++)
        {
            _dly_us(197); //快1%
        }
    }
}

/*
 *  INT-- ---------|1(PC0)           (PA7)20|---CLK
    !-唤醒-输入
 !  SDA------------|2(PC1)          (PA6)19|----WAKE  -唤醒-输入
 *  SCL------------|3(PB7)                (PA5)18|----
 *  GND------------|4(GND)         (PA4)17|-------IS  AN2
 *  IDA-------------|5(PB6)          (PA3)16|-------SW1  输入
 *  VCC-- ---------|6(VDD)          (PA2)15|-------ICK
 *      ------------|7(PB5)            (PA1)14|----
 *  L5------------|8(PB4)              (PA0)13|----G1
 *  L4------------|9(PB3)             (PB0)12|------L1
 *  L3-----------|10(PB2)            (PB1)11|-----L2
 *
 *    PORTA = 0B01011000;
    TRISA = 0B01011000; // PA输入输出 0-输出 1-输入

    PORTB = 0B10000000;
    TRISB = 0B10000000;
    // PA4->输出
    PORTC = 0B00000011;
    TRISC = 0B00000011; // PC输入输出 0-输出 1-输入
 */
void init_gpio(void)
{
    OSCCON = 0B01110001; // 16MHZ 1:1
    PCKEN |= 0B00000001; // AD模块时钟使能

    INTCON = 0; //暂禁止所有中断

    // !vrq
    PORTA = 0B00000000;
    //! OK	bit7,bit6,----,bit4,----,bit2,bit1,bit0
    TRISA = 0B11111110; // PA输入输出 0-输出 1-输入

    PORTB = 0B00000000;
    //! OK	bit7,bit6,----,bit4,bit3,bit2,bit1,bit0
    TRISB = 0B11111111; // PB输入输出 0-输出 1-输入	PB3->输出

    PORTC = 0B00000000;
    //! OK	----,----,----,----,----,----,bit1,----
    TRISC = 0B11111111; // PC输入输出 0-输出 1-输入

    WPUA = 0B00000000; // PA端口上拉控制 1-开上拉 0-关上拉
    WPUB = 0B00010000; // PB端口上拉控制 1-开上拉 0-关上拉
    WPUC = 0B00000000; // PC端口上拉控制 1-开上拉 0-关上拉

    WPDA = 0B00000000; // PA端口下拉控制 1-开下拉 0-关下拉
    WPDB = 0B00000000; // PB端口下拉控制 1-开下拉 0-关下拉
    WPDC = 0B00000000; // PC端口下拉控制 1-开下拉 0-关下拉

    PSRC0 = 0B11111111; // PORTA,PORTB源电流设置最大
    PSRC1 = 0B11111111; // PORTC,PORTD源电流设置最大

    PSINK0 = 0B11111111; // PORTA灌电流设置最大 0:最小，1:最大
    PSINK1 = 0B11111111; // PORTB灌电流设置最大 0:最小，1:最大
    PSINK2 = 0B11111111; // PORTC灌电流设置最大 0:最小，1:最大
}

void init_wdt(void)
{
    MISC0 = 0B00000000;  //看门狗时钟32k
    WDTCON = 0B00001011; // WDTPS=0101=1:1024,预分频1:1
}

void init_timer4(void)
{
    PCKEN |= 0B00001000; // TIME4模块时钟使能
    // CKOCON=0B00110000;
    // TCKSRC=0B00000011;

    TIM4CR1 = 0B00000101;
    // Bit7: 自动预装载位
    // 0: TIM4ARR寄存器没有缓冲，它可以被直接写入；
    // 1: TIM4ARR寄存器由预装载缓冲器缓冲。

    // Bit6:保留

    // Bit[5:4]: TIM4时钟选择位。
    // 00: 系统时钟/主时钟
    // 01: 内部快时钟HIRC
    // 10: LP时钟，只有当FOSC选择LP模式时才有意义
    // 11: XT时钟，只有当FOSC选择XT模式时才有意义

    // Bit3: 单脉冲模式
    // 0: 在发生更新事件时，计数器不停止；
    // 1: 在发生下一次更新事件(清除T4CEN位)时，计数器停止。

    // Bit2: 更新请求源
    // 0: 如果T4UDIS允许产生更新事件，则下述任一事件产生一个更新中断:
    //寄存器被更新(计数器上溢/下溢)
    //软件设置T4UG位
    //时钟/触发控制器产生的更新
    // 1: 如果T4UDIS允许产生更新事件，则仅当下列事件发生时才产生更新中断，T4UIF置1:
    //寄存器被更新(计数器上溢/下溢)

    // Bit1: 禁止更新
    // 0: 一旦下列事件发生，产生更新(UEV)事件:
    //计数器溢出/下溢
    //产生软件更新事件
    // 1: 不产生更新事件，影子寄存器(ARR、PSC、CCRx)保持它们的值。
    //如果设置了T4UG位，则计数器和预分频器被重新初始化。

    // Bit0: 允许计数器
    // 0: 禁止计数器；
    // 1: 使能计数器。

    TIM4IER = 0B00000001;
    // Bit0:  0：禁止更新中断；1：允许更新中断。

    TIM4SR = 0B00000000;
    // Bit[7:1]: 保留位。
    // Bit0: 更新中断标记
    //当产生更新事件时该位由硬件置1。它由软件写1清0
    // 0: 无更新事件产生；
    // 1: 更新事件等待响应。

    TIM4EGR = 0B00000000;
    // Bit[7:1]: 保留位。
    // Bit0: 产生更新事件
    //该位由软件置1，由硬件自动清0。
    // 0: 无动作；
    // 1: 重新初始化计数器，并产生一个更新事件。

    TIM4CNTR = 0; // TIM4 8位计数器

    TIM4PSCR = 0B00000110;
    // Bit[7:1]: 保留位。

    // Bit0: 预分频器的值
    //预分频器对输入的CK_PSC时钟进行分频。
    //计数器的时钟频率fCK_CNT等于fCK_PSC/2(PSC[2:0])。
    // PSCR包含了当更新事件产生时装入当前预分频器寄存器的值
    //(包括由于清除TIMx_EGR寄存器的UG位产生的计数器清除事件)这意味着如要新的预分频值生效，必须产生更新事件或者CEN=0。

    TIM4ARR = 248;
    // ARR包含了将要装载入实际的自动重装载寄存器的值。
    //当自动重装载的值为空时，计数器不工作。
}

void init_system_parameter(void) //
{
    bFlag_gSysTick_change = 0;
    forceDispTimer = 5; // 6 --5led  << -- 5 -- 4led 最后一个亮250ms
    bFlag_reverse = 0;
    delaySleepTimer = CONST_TIMER_DLY_SLP;
    display_cycle = 8;
    displayData = 0;
    underVoltageDispTimer = 0;
    indicator_light_mode = 0x0F;          //回滚到led4 不回滚 !!!
    ledDispTimer = CONST_TIMER_DISP_XSEC; // 5sec
    bFlag_disable_charge_on = 0;
    bFlag_temp_exception_chg = 0;
    bFlag_temp_exception_dischg = 0;
    bFlag_charge_on = 0;
    bFlag_power_on = 1;
    bFlag_init_battery_volume = 1;
    forceDispTimer = 10;
}

void enable_Exit(void)
{
    // ITYPE
    // ITYPE0 = 0b01010101; //!上升沿
    // ITYPE1 = 0b01010101; //!上升沿
    // EPS0 &= 0b00111111;
    //! EPS0 |= BIT6; // PB3 -DISPLAY_ALL_OFF
    EPS0 &= 0b11111110; // PC0
    EPS1 &= 0b11001111; // PA6

    //  EPS0 = 0B01000000; //选择PA0管脚中断
    //  Px0~Px3中断管脚选择s
    //  EPS1 = 0B00000000;
    //  Px4~Px7中断管脚选择

    // ITYPE0 = 0B11000000; // Px0上升沿下降沿唤醒(x = A/B)
    // ITYPE0 = 0B01000000; // ! ITYPE0[7:6] << -- PA3 PB3上升沿唤醒
    ITYPE0 = 0B00000001; // ! ITYPE0[1:0] << -- PA0 PB0 PC0 上升沿唤醒
    ITYPE1 = 0B00010000; // ! ITYPE1[5:4] << -- PA6 PB6上升沿唤醒

    EPIE0 = 0B01000001; //允许外部中断Px0
    EPIF0 = 0xFF;       //写1清中断响应标志位

    PEIE = 1; //使能外部中断

    GIE = 1; //开总中断
}

void disable_Exit(void)
{
    EPIE0 = 0B00000000; //外部中断Px0
    EPIF0 = 0xFF;       //写1清中断响应标志位
    PEIE = 0;           //使能外部中断
}

void sleep_proc(void)
{

    if (!delaySleepTimer)
    {

        if (P_I2C_INT)
        {
            return;
        }
        // HAL_NVIC_DisableIRQ(SysTick_IRQn); // add in 02/26
        GIE = 0;
        // io_uart_tx(0x33);
        // io_uart_tx(0x22);
        // io_uart_tx(0x11);
        // P_USB_DET_INPUT;

        // P_LED1_INPUT;
        // P_LED2_INPUT;
        // P_LED3_INPUT;
        P_LED_SEG1_CLR;
        P_LED_SEG2_CLR;
        P_LED_SEG3_CLR;
        P_LED_SEG1_OUTPUT;
        P_LED_SEG2_OUTPUT;
        P_LED_SEG3_OUTPUT;
        P_IO_UART_TX_CLR;
        P_IO_UART_TX_OUTPUT;
        P_ISPCLK_CLR;
        P_ISPCLK_OUTPUT;
        ADON = 0; //禁止ADC
        bFlag_charge_on = 0;
        // displayData = SEG_OFF; //! 2022 01/10  fix a bug 小电流模式计时结束 之后 充电有概率绿灯会亮
        bFlag_all_led_is_off = 1;

        enable_Exit();
        SLEEP();
        disable_Exit();
        // init_adc();
        delaySleepTimer = CONST_TIMER_DLY_SLP;
        // io_uart_tx(0x11);
        // io_uart_tx(0x22);
        // io_uart_tx(0x33);
        GIE = 1;
    }
    else
    {
        delaySleepTimer--;
        // io_uart_tx(0xAA);
        // io_uart_tx(delaySleepTimer);
        // io_uart_tx(0xAA);
    }
}