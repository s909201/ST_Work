/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: task_led.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'8
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "typedef.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_def.h"
// --------------------------------------------------------------
#define led_duration    (u32)100
// --------------------------------------------------------------
u8 TASK_LED_STEP;
u32 TASK_LED_TIMER_START;
// --------------------------------------------------------------
extern SYSFlag sys;
extern uint32_t uwTick;
// --------------------------------------------------------------
void TASK_LED_INIT(void)
{
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
    sys.f.TASK_LED_GO = 1;
}
// --------------------------------------------------------------
void TASK_LED(void)
{
    if (sys.f.TASK_LED_GO)
    {
        switch (TASK_LED_STEP)
        {
        case 0:
            TASK_LED_TIMER_START = uwTick;
            TASK_LED_STEP = 2;
            break;

        case 2:
            if ((uwTick - TASK_LED_TIMER_START) >= led_duration)
            {
                HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
                TASK_LED_TIMER_START = uwTick;
                TASK_LED_STEP = 4;
            }
            break;

        case 4:
            if ((uwTick - TASK_LED_TIMER_START) >= led_duration)
            {
                HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
                TASK_LED_TIMER_START = uwTick;
                TASK_LED_STEP = 2;
            }
            break;
        }
    }
}
// --------------------------------------------------------------
