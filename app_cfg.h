

#ifndef __APP_CFG_H_
#define __APP_CFG_H_

#define unchar unsigned char
#define unint unsigned int
#define unlong unsigned long

typedef unsigned char boolean;
typedef unsigned char BOOL;
typedef unsigned char BYTE;
typedef unsigned char INT8U;
typedef signed char INT8S;
typedef unsigned int INT16U;
typedef signed int INT16S;
typedef unsigned long INT32U;
typedef signed long INT32S;
typedef float FP32;
typedef double FP64;
typedef unsigned int clock_time_t;
typedef unsigned char u8_t;
typedef signed char s8_t;
// typedef unsigned char       uint8_t;

typedef unsigned int u16_t;
// typedef unsigned int        uint16_t;

typedef signed int s16_t;
typedef unsigned long int u32_t;
typedef signed long int s32_t;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u16;
typedef signed int s16;
typedef unsigned long u32;
typedef signed long s32;

typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned short WORD;
typedef unsigned long DWORD;

typedef const signed char sc8;  /*!< Read Only */
typedef const signed int sc16;  /*!< Read Only */
typedef const signed long sc32; /*!< Read Only */

typedef const unsigned char uc8;  /*!< Read Only */
typedef const unsigned int uc16;  /*!< Read Only */
typedef const unsigned long uc32; /*!< Read Only */

#define BIT0 0x01
#define BIT1 0x02
#define BIT2 0x04
#define BIT3 0x08
#define BIT4 0x10
#define BIT5 0x20
#define BIT6 0x40
#define BIT7 0x80

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef true
#define true (1)
#endif

#ifndef false
#define false (0)
#endif

typedef enum _GPIO_KEY_STATE
{
    GPIO_KEY_STATE_IDLE,
    GPIO_KEY_STATE_JITTER,
    GPIO_KEY_STATE_PRESS_DOWN,
    GPIO_KEY_STATE_CP

} GPIO_KEY_STATE;

#define CONST_DISP_TIME (11)
#define CONST_FLTR_NTC (7)
#define CONST_FLTR_STAT (10)
#define CONST_FLTR_COM (7)
#define CONST_FLTR_CC (3)
#define CONST_TIMER_DSL_SHORT (3)
#define CONST_TIMER_DLY_SLP (32)		 // 120sec 5356 才能休眠
#define CONST_TIMER_DLY_SLP_SML (7200UL) //小电流模式 关机倒计时
#define CONST_TIMER_UV_DISP (11)
#define CONST_TIMER_10_MINS (1200)
#define CONST_TIMER_DISP_XSEC (10)
#define DISPLAY_ALL 0x1F
#define SEG_ALL_OFF 0x00

#define IPC_FUNC
#define CONST_DSL_SHORT  3
#define CNST_TIMER_DLY_SLP (120)        // 120sec 5356 才能休眠
#define CNST_TIMER_DLY_SLP_SML (7200UL) //小电流模式 关机倒计时

#define CNST_TIMER_UV_DISP (11)
#define CONST_TIMER_10_MINS (1200)
#define USING_IO_UART
#define CONST_TIMER_DISP_XSEC (10)

#define CONST_MINUTES_40  80
#define CONST_MINUTES_30  60



#define G1_PIN PA0

// #define P_I2C_SCL PB7
// #define P_I2C_SDA PC1

#define SDA_OUT TRISC1 = 0
#define SDA_IN TRISC1 = 1
#define SCL_OUT TRISB7 = 0
#define SCL_IN TRISB7 = 1

//!QFN20  T61F145-NRT QFN20
//! PIN1 PC0  AN5 MCLRB
#define P_I2C_INT           PA4 
#define P_I2C_INT_CLR       P_I2C_INT = 0
#define P_I2C_INT_SET       P_I2C_INT = 1
#define P_I2C_INT_OUTPUT    TRISA4 = 0
#define P_I2C_INT_INPUT     TRISA4 = 1

//! PIN2 PC1  
#define P_I2C_SDA           PC1 
#define P_I2C_SDA_CLR       P_I2C_SDA = 0
#define P_I2C_SDA_SET       P_I2C_SDA = 1
#define P_I2C_SDA_OUTPUT    TRISC1 = 0
#define P_I2C_SDA_INPUT     TRISC1 = 1

//! PIN3 RB7  
#define P_I2C_SCL           PB7
#define P_I2C_SCL_CLR       P_I2C_SCL = 0
#define P_I2C_SCL_SET       P_I2C_SCL = 1
#define P_I2C_SCL_OUTPUT    TRISB7 = 0
#define P_I2C_SCL_INPUT     TRISB7 = 1 

//! PIN4 VSS  

//! PIN5 PB6   ISPDAT  AN6 TX

//-----------------------------------------------------------------

//! PIN6 VDD 
//! PIN7 PB5  NC

//! PIN8 PB4 
#define P_LED_SEG5           PB4
#define P_LED_SEG5_CLR       P_LED_SEG5 = 0
#define P_LED_SEG5_SET       P_LED_SEG5 = 1
#define P_LED_SEG5_OUTPUT    TRISB4 = 0
#define P_LED_SEG5_INPUT     TRISB4 = 1 

//! PIN9 RB3 
#define P_LED_SEG4           PB3
#define P_LED_SEG4_CLR       P_LED_SEG4 = 0
#define P_LED_SEG4_SET       P_LED_SEG4 = 1
#define P_LED_SEG4_OUTPUT    TRISB3 = 0
#define P_LED_SEG4_INPUT     TRISB3 = 1

//! PIN10 RB2 
#define P_LED_SEG3              PB2
#define P_LED_SEG3_CLR          P_LED_SEG3 = 0
#define P_LED_SEG3_SET          P_LED_SEG3 = 1
#define P_LED_SEG3_OUTPUT       TRISB2 = 0
#define P_LED_SEG3_INPUT        TRISB2 = 1 

//-----------------------------------------------------------------------


//! PIN11 RB1 
#define P_LED_SEG2              PB1
#define P_LED_SEG2_CLR          P_LED_SEG2 = 0
#define P_LED_SEG2_SET          P_LED_SEG2 = 1
#define P_LED_SEG2_OUTPUT       TRISB1 = 0
#define P_LED_SEG2_INPUT        TRISB1 = 1

//! PIN12 RB0  
#define P_LED_SEG1              PB0
#define P_LED_SEG1_CLR          P_LED_SEG1 = 0
#define P_LED_SEG1_SET          P_LED_SEG1 = 1
#define P_LED_SEG1_OUTPUT       TRISB0 = 0
#define P_LED_SEG1_INPUT        TRISB0 = 1 

//!  PIN13 RA0 
// #define P_LED_SEG3              PA0
// #define P_LED_SEG3_CLR          P_LED_SEG3 = 0
// #define P_LED_SEG3_SET          P_LED_SEG3 = 1
// #define P_LED_SEG3_OUTPUT       TRISA0 = 0
// #define P_LED_SEG3_INPUT        TRISA0 = 1 

//! PIN14 PA1  NC

//! PIN15 PA2    ISPCLK 烧录 
#define P_ISPCLK         PA2 
#define P_ISPCLK_CLR     P_ISPCLK = 0
#define P_ISPCLK_SET     P_ISPCLK = 1
#define P_ISPCLK_OUTPUT  TRISA2 = 0
#define P_ISPCLK_INPUT   TRISA2 = 1

//--------------------------------------------------------------------------
//! PIN16 PA3    KEY

#define P_KEY              PA3
#define P_KEY_CLR          P_KEY = 0
#define P_KEY_SET          P_KEY = 1
#define P_KEY_OUTPUT       TRISA3 = 0
#define P_KEY_INPUT        TRISA3 = 1 

//! PIN17 PA4    IS


//! PIN18 PA5    NC

//! PIN19 PA6   WAKE
#define P_USBA_WAKE              PA6
#define P_USBA_WAKE_CLR          P_USBA_WAKE = 0
#define P_USBA_WAKE_SET          P_USBA_WAKE = 1
#define P_USBA_WAKE_OUTPUT       TRISA6 = 0
#define P_USBA_WAKE_INPUT        TRISA6 = 1 


//! PIN20 PA7   NC  带电烧录
#define P_IO_UART_TX        PA7 
#define P_IO_UART_TX_CLR    P_IO_UART_TX = 0
#define P_IO_UART_TX_SET    P_IO_UART_TX = 1
#define P_IO_UART_TX_OUTPUT TRISA7 = 0
#define P_IO_UART_TX_INPUT  TRISA7 = 1

#endif


