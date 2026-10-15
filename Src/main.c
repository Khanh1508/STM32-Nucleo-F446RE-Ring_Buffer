/**
 * @file  main.c

 */

#include "ringbuf.h"

int main(void)
{

	test_ring_buffer(); /* Calling 4-phase wrap-around test ring buffer function */
	for (;;)
	{
		// Do nothing
	}
}
