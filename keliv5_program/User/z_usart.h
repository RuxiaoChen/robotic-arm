#ifndef __TB_USART_H__
#define __TB_USART_H__


#include "stm32f10x_usart.h"
#include "z_global.h"

#define TB_USART1_COM 1
#define TB_USART2_COM 2
#define TB_USART3_COM 3

#define TB_USART_FLAG_ERR  0X0F
#define TB_USART_FLAG_RXNE 0X20
#define TB_USART_FLAG_TXE  0X80

#define tb_interrupt_open() {__enable_irq();}

#define uart1_open() 	{USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);}
#define uart1_close() 	{USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);}

#define uart2_open() 	{USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);}		
#define uart2_close() 	{USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);}		

#define uart3_open() 	{USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);}		
#define uart3_close() 	{USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);}		

void tb_usart_init(void);
void tb_usart1_init(u32 rate);
void tb_usart2_init(u32 rate);
void tb_usart3_init(u32 rate);

void tb_usart1_send_byte(u8 Data);
void tb_usart1_send_nbyte(u8 *Data, u16 size);
void tb_usart1_send_str(u8 *Data);

void tb_usart2_send_byte(u8 Data);
void tb_usart2_send_nbyte(u8 *Data, u16 size);
void tb_usart2_send_str(u8 *Data);

void tb_usart3_send_byte(u8 Data);
void tb_usart3_send_nbyte(u8 *Data, u16 size);
void tb_usart3_send_str(u8 *Data);

int tb_usart1_interrupt(void);
int tb_usart2_interrupt(void);
int tb_usart3_interrupt(void);

void uart1_send_str(u8 *str);
void uart1_send_nbyte(u8 *Data, u16 size);
void uart1_send_byte(u8 data);

void uart2_send_str(u8 *str);
void uart2_send_nbyte(u8 *Data, u16 size);
void uart2_send_byte(u8 data);

void zx_uart_send_str(u8 *str);
void uart3_send_str(u8 *str);
void uart3_send_nbyte(u8 *Data, u16 size);
void uart3_send_byte(u8 data);


#endif

