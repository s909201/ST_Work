/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: thread_led.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'26
Remark:
* I prefer to use method 2 to create Task Thread
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "stm32h7xx_hal.h"
#include "cmsis_os.h"
// --------------------------------------------------------------

#define led_duration (u32)100
// --------------------------------------------------------------
// osThreadId TaskHandle_Led1; // Morgan add, for showing method 1
TaskHandle_t TaskHandle_Led1; // Morgan add, for showing method 2
TaskHandle_t TaskHandle_Led2; // Morgan add, for showing method 2
TaskHandle_t TaskHandle_Led3; // Morgan add, for showing method 2
// --------------------------------------------------------------
void LED_INIT(void)
{
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);  // LED 1
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);  // LED 2
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET); // LED 3
}
// --------------------------------------------------------------
// LED 1 Control
void vTask_LED1(void *argument)
{
    while (1)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
        vTaskDelay(250);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
        vTaskDelay(250);
    }
}
// --------------------------------------------------------------
// LED 2 Control
void vTask_LED2(void *argument)
{
    while (1)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
        vTaskDelay(500);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
        vTaskDelay(500);
    }
}
// --------------------------------------------------------------
// LED 3 Control
void vTask_LED3(void *argument)
{
    while (1)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_RESET);
        vTaskDelay(1000);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, GPIO_PIN_SET);
        vTaskDelay(1000);
    }
}
// --------------------------------------------------------------
void TaskCreate_Led(void)
{
    // Two methods -
    // Method 1:
    // osThreadDef(LED1, vTask_LED1, osPriorityNormal, 0, 128); // created by ARM for CMIS-RTOS V1 package
    // TaskHandle_Led1 = osThreadCreate(osThread(LED1), NULL);

    // Method 2:
    xTaskCreate(vTask_LED1, "LED1", 128, NULL, 2, TaskHandle_Led1); // freeRTOS original function
    xTaskCreate(vTask_LED2, "LED2", 128, NULL, 2, TaskHandle_Led2); // freeRTOS original function
    xTaskCreate(vTask_LED3, "LED3", 128, NULL, 2, TaskHandle_Led3); // freeRTOS original function
}
// --------------------------------------------------------------
