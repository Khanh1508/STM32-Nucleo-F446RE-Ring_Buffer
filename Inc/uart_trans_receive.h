/*
 * uart_trans_receive.h
 *
 *  Created on: Oct 16, 2026
 *      Author: Admin
 */

#ifndef UART_TRANS_RECEIVE_H_
#define UART_TRANS_RECEIVE_H_
void init_uart(void);
void uart_send_char(char c);
void uart_send_string(const char *str);
#endif /* UART_TRANS_RECEIVE_H_ */
