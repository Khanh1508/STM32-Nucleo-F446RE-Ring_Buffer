/*
 * test_ring_buffer.c
 ** @brief Ring buffer wrap-around test: push 8, pop 3, push 3, pop 8.
 *        head and tail both wrap; popped bytes must match msg in order.
 *        fail_count == 0 means pass.
 *  Created on: Oct 15, 2026
 *      Author: Admin
 */
#include "ringbuf.h"

/* Buffer instance allocated statically in SRAM (.bss segment) */
Buffer_t rb;

/* 11 letters, more than BUFFER_SIZE: fits because pops free slots */
const char msg[] = "ABCDEFGHIJK";

/* Destination of rb_pop()*/
uint8_t received_byte;

/* Number of failed checks. 0 = pass. */
uint8_t fail_count = 0;

/* Bytes read back, one per msg index (0..10) */
uint8_t popped_bytes[11u];
/* Reset head, tail, count */
void test_ring_buffer(void)
{
	rb_init(&rb);

	/* Phase 1: push msg[0..7] -> buffer full. Expect head=0, tail=0, count=8 */
	for (uint8_t i = 0; i <= 7; i++)
	{
		if (!rb_push(&rb, msg[i]))
		{
			fail_count++;
		}
	}

	/* Phase 2: pop msg[0..2] (A,B,C) -> 3 slots free. Expect head=0, tail=3, count=5 */
	for (uint8_t j = 0; j <= 2; j++)
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

	/* Phase 3: push msg[8..10] (I,J,K) into buf[0..2] -> head wraps.
	 * Expect head=3, tail=3, count=8 (full again) */
	for (uint8_t i = 8; i <= 10; i++)
	{
		if (!rb_push(&rb, msg[i]))
		{
			fail_count++;
		}
	}

	/* Phase 4: pop msg[3..10] (D..K) -> tail wraps, buffer empty.
	 * Expect head=3, tail=3, count=0 */
	for (uint8_t j = 3; j <= 10; j++)
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
}
