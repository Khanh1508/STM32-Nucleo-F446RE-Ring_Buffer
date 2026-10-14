/**
 * @file  main.c
 * @brief Test for the ring buffer: push a string in, pop it back out, and
 *        check that every byte comes out unchanged and in the same order (FIFO).
 *        Result: fail_count == 0 means the test passed.
 */

#include "ringbuf.h"

/* Buffer instance allocated statically in SRAM (.bss segment) */
Buffer_t rb;

/* Test data: 5 letters + '\0' = 6 bytes. Must fit in the buffer (BUFFER_SIZE). */
const char msg[] = "hello";

/* Destination of rb_pop(). 0xAA = "not written yet", so an untouched value is visible. */
uint8_t received_byte = 0xAA;

/* Number of failed checks. 0 = pass. */
uint8_t fail_count = 0;

/* Bytes read back, kept so they can be inspected in the debugger. Size >= sizeof(msg). */
uint8_t popped_bytes[8u];

int main(void)
{

	/* Initialize ring buffer , head, tail and counter to zero */
	rb_init(&rb);

	/*Push data into buffer*/
	for (uint8_t i = 0; i < sizeof(msg); i++)
	{
		if (!rb_push(&rb, msg[i]))
		{
			fail_count++;
		}
	}

	/*Read data from buffer*/
	for (uint8_t j = 0; j < sizeof(msg); j++)
	{
		if (!rb_pop(&rb, &received_byte))
		{
			fail_count++;
		}
		if (received_byte != msg[j])
		{
			fail_count++;
		}

		popped_bytes[j] = received_byte;
	}
	for (;;)
	{
		// Do nothing
	}
}
