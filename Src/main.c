/**
 * @file  main.c

 */

#include "ringbuf.h"
#include "uart_trans_receive.h"
char msg_usart[] = "Hello, World!\r\n"; /* Message to be sent over USART2 */
Buffer_t rbc; /* ring buffer for received bytes */
int main(void)
{
	rb_init(&rbc);
	//test_ring_buffer(); /* Calling 4-phase wrap-around test ring buffer function */
	init_uart();
	uart_send_string(msg_usart);
	for (;;)
	{
		// Do nothing
	}
}
