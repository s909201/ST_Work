/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: task_led.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'26
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "stm32h7xx_hal.h"
#include "typedef.h"
// --------------------------------------------------------------
#define led_duration (u32)5000

u8 TASK_LED_STEP;
u32 TASK_LED_TIMER_START;

extern SYSFlag sys;
// --------------------------------------------------------------
void TASK_LED_INIT(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
    sys.f.TASK_LED_GO = 0;
}
// --------------------------------------------------------------
void TASK_LED(void)
{
    if (sys.f.TASK_LED_GO)
    {
        switch (TASK_LED_STEP)
        {
        case 0:
            TASK_LED_TIMER_START = HAL_GetTick();
            TASK_LED_STEP = 2;
            break;

        case 2:
            if ((HAL_GetTick() - TASK_LED_TIMER_START) >= led_duration)
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
                TASK_LED_TIMER_START = HAL_GetTick();
                TASK_LED_STEP = 4;
            }
            break;

        case 4:
            if ((HAL_GetTick() - TASK_LED_TIMER_START) >= led_duration)
            {
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
                HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
                TASK_LED_TIMER_START = HAL_GetTick();
                TASK_LED_STEP = 2;
            }
            break;
        }
    }
}
// --------------------------------------------------------------

// --------------------------------------------------------------

// --------------------------------------------------------------
