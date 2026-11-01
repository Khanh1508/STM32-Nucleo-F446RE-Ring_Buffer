/**
 * @file  main.c

 */

#include "ringbuf.h"
#include "uart_trans_receive.h"
#include <stdint.h>
//char msg_usart[] = "Hello, World!\r\n"; /* Message to be sent over USART2 */

uint8_t c;

int main(void)
{	
	init_uart();
	for (;;)
	{
		if (uart_read(&c)) /* Check if a character is available in the ring buffer */
		{
			uart_send_char(c); /* Echo the received character back */
		}
	
	}
}
