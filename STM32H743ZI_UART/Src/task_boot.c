/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: task_boot.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'26
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_def.h"
#include "typedef.h"
// --------------------------------------------------------------
u8 TASK_BOOT_STEP;
u32 TASK_BOOT_TIMER_START;

extern SYSFlag sys;
extern void ALL_STACK_INIT(void);

extern UART_HandleTypeDef huart2;
uint8_t aHello[] = "Intel\n";
extern void UART2_Send_Str(uint8_t *str, uint16_t len);
// --------------------------------------------------------------
void TASK_BOOT_INIT(void)
{
    TASK_BOOT_STEP = 0;
    TASK_BOOT_TIMER_START = 0;
}
// --------------------------------------------------------------
void TASK_BOOT(void)
{
    if (sys.f.TASK_BOOT_GO)
    {
        switch (TASK_BOOT_STEP)
        {
        case 0:
            // ENV.
            ALL_STACK_INIT();
            // Start ---
            TASK_BOOT_TIMER_START = HAL_GetTick();
            TASK_BOOT_STEP = 2;
            break;

        case 2:
            if ((HAL_GetTick() - TASK_BOOT_TIMER_START) >= 10000)
            {
                sys.f.TASK_LED_GO = 1;
                TASK_BOOT_TIMER_START = HAL_GetTick();
                TASK_BOOT_STEP = 10;
            }
            break;

        // UART Tx Test
        case 10:
            if ((HAL_GetTick() - TASK_BOOT_TIMER_START) >= 10000)
            {
                printf("Apple\n"); // hyper terminal test
                TASK_BOOT_TIMER_START = HAL_GetTick();
                TASK_BOOT_STEP = 12;
            }
            break;

        case 12:
            if ((HAL_GetTick() - TASK_BOOT_TIMER_START) >= 10000)
            {
                if (HAL_UART_Transmit(&huart2, (uint8_t *)aHello, 6, 200) != HAL_OK)
                {
                    Error_Handler();
                }
                TASK_BOOT_TIMER_START = HAL_GetTick();
                TASK_BOOT_STEP = 14;
            }
            break;

        case 14:
            if ((HAL_GetTick() - TASK_BOOT_TIMER_START) >= 10000)
            {
                UART2_Send_Str("Good\n", 5);
                TASK_BOOT_TIMER_START = HAL_GetTick();
                TASK_BOOT_STEP = 10;
            }
            break;
        }
    }
}
// --------------------------------------------------------------
