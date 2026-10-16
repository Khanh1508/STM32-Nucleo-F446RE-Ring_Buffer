/**
 * @file  main.c

 */

#include "ringbuf.h"
#include "uart_trans_receive.h"
int main(void)
{

	//test_ring_buffer(); /* Calling 4-phase wrap-around test ring buffer function */
	init_uart();
	for (;;)
	{
		// Do nothing
	}
}
