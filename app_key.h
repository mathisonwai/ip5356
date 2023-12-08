#ifndef _APP_KEY_H_
#define _APP_KEY_H_

#ifdef  KEY_GLOBALS
#define KEY_EXT
#else
#define KEY_EXT extern
#endif




//#define KEY_EVENT_BASE_ADDR         0xA0

//#define MSG_NONE                  0x00
#define KEY_BREAK                   0x20     //
#define KEY_LONG_START              0x40     //
#define KEY_LONG                    0x80     //
#define KEY_LONG_BREAK              0x60     //important

#define K1                          0x01
#define K1_BREAK                    0x21
#define K1_LONG_START               0x41
#define K1_LONG                     0x81
#define K1_LONG_BREAK               0x61
/*
#define GPIO_KEY_SCAN_TIME          15   //20ms
#define GPIO_KEY_JTTER_TIME         30
#define GPIO_KEY_CP_TIME            1000
#define GPIO_KEY_CPH_TIME           200  //
*/
// timer 20ms



#define GPIO_KEY_JTTER_TIME            2 //*16ms = 64ms
#define GPIO_KEY_CP_TIME               200//5sec <-- 32 -- 1024 ms
#define GPIO_KEY_CPH_TIME               24 //*16ms = 192ms


#define KEY_JTTER_TIMER            2 //*32ms = 64ms
#define KEY_CP_TIMER                 156//5sec <-- 32 -- 1024 ms
#define KEY_CPH_TIMER               7 //*32ms = 224ms
#define KEY_NKEY_TIMER              16 //*32ms = 512ms  //多击间隔超时 

typedef enum _KEY_EVENT
{
    MSG_NONE = 0x00,

    KEY_POWER = K1,                         // -- [0x01,0x1F]
    //TODO:

    MSG_MODE = K1_BREAK,             // -- [0x21,0x3F]
    MSG_LIGHT,
    //TODO:

    MSG_POWER_ON = K1_LONG_START,   // -- [0x41,0x5F]
    MSG_LIGHT_CPS,
    //TODO:

    KEY_POWER_LONG_BREAK = K1_LONG_BREAK,   // -- [0x61,0x7F]
    MSG_LIGHT_CPR,
    //TODO:

    KEY_POWER_LONG = K1_LONG,               // -- [0x81,0x5F]
    MSG_LIGHT_CPH,
    //TODO:

} KEY_EVENT;




#if 0//def MCU_CONTROL_KEY_OUT
void DriveKeyCtrl(void);
#endif

void init_gpio_key(void);

KEY_EVENT gpioKeyScan(void);



#endif

