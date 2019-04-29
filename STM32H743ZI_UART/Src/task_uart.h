/*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
FileName: task_uart.h
ProjectName:
FunctionDesc:
CreateDate:
Version:
Author: Morgan
ModifyHistory:	2019'4'29
Remark:
<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*/
void TASK_UART_INIT(void);
void TASK_UART(void);
void TASK_UART_TX_Send(UART_HandleTypeDef *huart);
void TASK_UART_PROC(void);
void TASK_UART2_RX_REC_TIMEOUT(void);
void UART2_Send_Str(uint8_t *str, uint16_t len);
//---------------------------------------------------------------
