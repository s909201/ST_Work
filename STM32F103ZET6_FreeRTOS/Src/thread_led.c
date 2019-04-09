/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: thread_led.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'9
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
// --------------------------------------------------------------

#define led_duration    (u32)100
// --------------------------------------------------------------
osThreadId TaskHandle_Led1;   // Morgan add, for showing method 1
TaskHandle_t TaskHandle_Led2; // Morgan add, for showing method 2

// --------------------------------------------------------------
// LED 1 Control
void StartTask_Led1(void const *argument)
{
    while (1)
    {
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_SET);
        vTaskDelay(250);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8, GPIO_PIN_RESET);
        vTaskDelay(250);
    }
}
// --------------------------------------------------------------
// LED 2 Control
void vTask_LED2(void *argument)
{
    while (1)
    {
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_RESET);
        vTaskDelay(1000);
        HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9, GPIO_PIN_SET);
        vTaskDelay(1000);
    }
}
// --------------------------------------------------------------
void TaskCreate_Led(void)
{
    // Two methods -
    // Method 1:
    osThreadDef(Task_Led1, StartTask_Led1, osPriorityNormal, 0, 128); // created by ARM for CMIS-RTOS V1 package
    TaskHandle_Led1 = osThreadCreate(osThread(Task_Led1), NULL);

    // Method 2:
    xTaskCreate(vTask_LED2, "LED2", 128, NULL, 2, TaskHandle_Led2); // freeRTOS original function
}
// --------------------------------------------------------------
