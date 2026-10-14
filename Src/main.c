#include "ringbuf.h"

/* Buffer instance allocated statically in SRAM (.bss segment) */
Buffer_t rb;

/* Return value of the latest rb_push: true = stored, false = buffer full */
bool result;

int main(void)
{
    /* Initialize ring buffer , head, tail and counter to zero */
    rb_init(&rb);

    /* Push 9 elements sequentially to test buffer overflow handling
     * (Buffer size is 8, so the 9th push should return false) */
    for (uint8_t i = 1; i <= 9; i++)
    {
        result = rb_push(&rb, i);
    }


    for (;;)
    {
        // Do nothing
    }
}
