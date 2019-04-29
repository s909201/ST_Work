/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: typedef.h
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'29
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "stm32h7xx_hal.h" // need this for uint8_t

#define VERSION "STM32H743ZI"

#define URQSize 128

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;

// --------------------------------------------------------------
typedef union _SYSFlag {
    u32 V[3];

    struct
    {
        u16 TASK_BOOT_GO : 1;
        u16 TASK_LED_GO : 1;
        u16 TASK_UART_GO : 1;
        u16 TASK_UART2_RX_REC_TIMEOUT_GO : 1;
        u16 TASK_UART2_RX_REC_DATA_GO : 1;

    } f;
} SYSFlag;

// --------------------------------------------------------------

// --------------------------------------------------------------
