#include "ringbuf.h"



void rb_init(Buffer_t *rb)
{
	rb->head =0;
	rb->tail =0;
	rb->count =0;
	/* Reset head, tail, count: buffer becomes empty */
}
