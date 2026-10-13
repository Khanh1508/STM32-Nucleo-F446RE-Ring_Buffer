#include "ringbuf.h"

Buffer_t rb; //global variable get data in RAM

int main(void)
{

	//test gabarge value for head,tail,count
	rb.head =5;
	rb.tail=10;
	rb.count=15;
	rb_init(&rb);
  for(;;)
  {
             // infinite loop
  }
}
