/* Ring buffer: fixed-size FIFO of bytes (data type only; functions are added later). */
#ifndef RING_BUFFER
#define RING_BUFFER

#include <stdint.h>  /* uint8_t */
#include <stdbool.h> /* bool, true, false (used by push/pop return values) */

#define BUFFER_SIZE 8u /* number of slots in the buffer (1 byte per slot) */

typedef struct
{
	uint8_t buf[BUFFER_SIZE]; /* storage for received bytes */
	uint8_t head;             /* index of the next slot to write */
	uint8_t tail;             /* index of the next slot to read */
	uint8_t count;            /* number of bytes stored and not yet read */
} Buffer_t;

#endif  /* RING_BUFFER */


