#include<stdint.h>
#include "uart_trans_receive.h"

/*RCC*/
#define RCC_BASE      (0x40023800) //RCC base adress
#define RCC_AHB1ENR   (*((volatile uint32_t *)(RCC_BASE + 0x30))) // bit 0: GPIOAEN
#define RCC_APB1ENR   (*((volatile uint32_t *)(RCC_BASE + 0x40))) //bit 17: USART2EN

/*GPIOA*/
#define GPIOA_BASE    (0x40020000) //GPIOA base address
#define GPIOA_MODER   (*((volatile uint32_t *)(GPIOA_BASE + 0x00))) // 2 bits per pin, PA2 = [5:4] 10 mode - bit 5:4
#define GPIOA_AFRL    (*((volatile uint32_t *)(GPIOA_BASE + 0x20))) // 4 bits per pin, PA2 = [11:8] Alternative function

/*Clear data */
void init_uart(void)
{
	RCC_AHB1ENR |= (1uL << 0);    // GPIOA clock
	RCC_APB1ENR |= (1uL << 17);   // USART2 clock

	GPIOA_MODER &=~(3uL << 4);   // PA2: clear mode bits
	GPIOA_MODER |= (2uL << 4);   // PA2: alternate function (10)

	GPIOA_AFRL &=~(0xFuL << 8);   // PA2: clear AF bits
	GPIOA_AFRL |= (0x7uL << 8);   // PA2: AF7 = USART2_TX
}
