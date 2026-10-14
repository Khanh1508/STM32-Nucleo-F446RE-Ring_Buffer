#include "ringbuf.h"

/**
 * @brief  Reset the buffer to the empty state.
 * @param  rb: Buffer to reset.
 * @note   Call once before the first push/pop, or to discard all stored data.
 */
void rb_init(Buffer_t *rb) {
	rb->head = 0;
	rb->tail = 0;
	rb->count = 0;
}

/**
 * @brief  Store one byte at the head of the buffer.
 * @param  rb:   Buffer to write to.
 * @param  byte: Byte to store.
 * @retval true  - the byte was stored.
 * @retval false - the buffer is full; the byte is dropped and the
 *                 stored data is left untouched (no overwrite).
 * @note   Not yet safe to share between an ISR and main (race on count).
 */
bool rb_push(Buffer_t *rb, uint8_t byte) {
	if (rb->count == BUFFER_SIZE) {
		return false;
	}

	rb->buf[rb->head] = byte;

	/* head is the next slot to write; wrap to 0 after the last slot */
	rb->head = (rb->head + 1) % BUFFER_SIZE;
	rb->count++;

	return true;
}
/**
 * @brief  take out the data in buffer with oldest index FIFO
 * @param  rb: a pointer which point to data buffer to read
 * @param  store: a pointer to store data from buffer
 * @retval true: when data store successfully
 *         false: when data is empty
 *
 **/
bool rb_pop(Buffer_t *rb, uint8_t *store)
{
	if (rb->count == 0) {
		return false; /* The buffer is empty,stop reading*/
	}

	*store = rb->buf[rb->tail];
	rb->tail = (rb->tail + 1) % BUFFER_SIZE;
	rb->count--;
	return true;
}
