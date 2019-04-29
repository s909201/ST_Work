/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: task_uart.c
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'29
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
#include "stm32h7xx_hal.h"
#include "task_uart.h"
#include "typedef.h"
#include "task_uart.h"

// Data String
u8 UART2_RX_Str[URQSize];
u16 UART2_RX_Stri, UART2_RX_StrLen;
u32 TASK_UART2_RX_REC_START_TIMER;

// USART 2 :
u8 UART2_RXQ[URQSize];
u16 UART2_RXQ_top, UART2_RXQ_btm;

u8 UART2_TXQ[URQSize];
u16 UART2_TXQ_top, UART2_TXQ_btm;

extern SYSFlag sys;
extern UART_HandleTypeDef huart2;
//---------------------------------------------------------------
void TASK_UART_INIT(void)
{
    UART2_TXQ_top = 0;
    UART2_TXQ_btm = 0;
    UART2_RXQ_top = 0;
    UART2_RXQ_btm = 0;

    UART2_RX_Stri = 0;
    TASK_UART2_RX_REC_START_TIMER = 0;
    sys.f.TASK_UART2_RX_REC_TIMEOUT_GO = 0;
    sys.f.TASK_UART2_RX_REC_DATA_GO = 0;
}
//---------------------------------------------------------------
void TASK_UART(void)
{
    TASK_UART_TX_Send(&huart2); // UART Tx
    TASK_UART2_RX_REC_TIMEOUT();
    TASK_UART_PROC();
}
//---------------------------------------------------------------
// Global parameters: UART2_TXQ_top, UART2_TXQ_btm, UART2_TXQ[]
void TASK_UART_TX_Send(UART_HandleTypeDef *huart)
{
    if (UART2_TXQ_top != UART2_TXQ_btm)
    {
        if (huart->Instance->ISR & USART_ISR_TC) // 1: transmission is complete
        {
            huart->Instance->TDR = UART2_TXQ[UART2_TXQ_btm++];
            if (UART2_TXQ_btm >= URQSize)
            {
                UART2_TXQ_btm = 0;
            }
        }
    }
}
// --------------------------------------------------------------
void UART2_SendByte(u8 data)
{
    UART2_TXQ[UART2_TXQ_top++] = data;
    if (UART2_TXQ_top >= URQSize)
    {
        UART2_TXQ_top = 0;
    }
}
//---------------------------------------------------------------
void UART2_Send_Str(u8 *str, u16 len)
{
    u16 i;
    for (i = 0; i < len; i++)
    {
        UART2_SendByte(*(str + i));
    }
}
//---------------------------------------------------------------
void TASK_UART2_RX_REC_TIMEOUT(void)
{
    if (sys.f.TASK_UART2_RX_REC_TIMEOUT_GO)
    {
        if ((HAL_GetTick() - TASK_UART2_RX_REC_START_TIMER) >= 200) // 20ms
        {
            sys.f.TASK_UART2_RX_REC_TIMEOUT_GO = 0;

            UART2_RX_StrLen = UART2_RX_Stri;
            UART2_RX_Stri = 0;
            sys.f.TASK_UART2_RX_REC_DATA_GO = 1;
        }
    }
    // ----------------------------
    if ((UART2_RXQ_top != UART2_RXQ_btm) && (!sys.f.TASK_UART2_RX_REC_DATA_GO))
    {
        UART2_RX_Str[UART2_RX_Stri++] = UART2_RXQ[UART2_RXQ_btm++];
        if (UART2_RXQ_btm >= URQSize)
        {
            UART2_RXQ_btm = 0;
        }
        TASK_UART2_RX_REC_START_TIMER = HAL_GetTick(); // 20ms
        sys.f.TASK_UART2_RX_REC_TIMEOUT_GO = 1;
    }
}
//---------------------------------------------------------------
void TASK_UART_PROC(void)
{
    // Rx/Tx Queue test
    // if (UART2_RXQ_top != UART2_RXQ_btm)
    // {
    //     UART2_TXQ[UART2_TXQ_top++] = UART2_RXQ[UART2_RXQ_btm++];
    //     if (UART2_TXQ_top >= URQSize)
    //     {
    //         UART2_TXQ_top = 0;
    //     }
    //     if (UART2_RXQ_btm >= URQSize)
    //     {
    //         UART2_RXQ_btm = 0;
    //     }
    // }
    // ----------------------------------------------------------
    if (sys.f.TASK_UART2_RX_REC_DATA_GO)
    {
        UART2_Send_Str(UART2_RX_Str, UART2_RX_StrLen);
        sys.f.TASK_UART2_RX_REC_DATA_GO = 0;
    }
}
//---------------------------------------------------------------
void HAL_UART_IRQHandler_LINK(UART_HandleTypeDef *huart)
{
    // uint32_t isrflags = READ_REG(huart->Instance->ISR);

    if (huart->Instance->ISR & USART_ISR_RXNE)
    {
        UART2_RXQ[UART2_RXQ_top++] = (uint8_t)(huart->Instance->RDR);
        if (UART2_RXQ_top >= URQSize)
        {
            UART2_RXQ_top = 0;
        }
        TASK_UART2_RX_REC_START_TIMER = HAL_GetTick();
        sys.f.TASK_UART2_RX_REC_TIMEOUT_GO = 1;
    }
}
//---------------------------------------------------------------
