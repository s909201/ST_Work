/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: typedef.h
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'8
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/

#define VERSION "STM32F103ZET6_LED"

typedef unsigned char u8;
typedef signed char i8;
typedef unsigned int u16;
typedef signed short int i16;
typedef unsigned long u32;
typedef signed long i32;
// --------------------------------------------------------------
typedef union _SYSFlag {
    u32 V[3];

    struct
    {
        u16 TASK_BOOT_GO : 1;
        u16 TASK_LED_GO : 1;
    } f;
} SYSFlag;

// --------------------------------------------------------------


// --------------------------------------------------------------
