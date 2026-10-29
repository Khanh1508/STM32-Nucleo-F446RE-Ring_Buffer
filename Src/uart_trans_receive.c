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


/*USART2*/
#define USART2_BASE   (0x40004400) //USART2 base address
#define USART2_SR     (*((volatile uint32_t *)(USART2_BASE + 0x00)))
#define USART2_DR     (*((volatile uint32_t *)(USART2_BASE + 0x04)))
#define USART2_BRR    (*((volatile uint32_t *)(USART2_BASE + 0x08)))
#define USART2_CR1    (*((volatile uint32_t *)(USART2_BASE + 0x0C)))


/*Clear data */

void uart_send_char(char c)
{
	while (!(USART2_SR & (1UL << 7))) { }   // Wait until TXE is set
	USART2_DR = c;                          // Write data to DR
}


void uart_send_string(const char *str)
{
	for(int i= 0 ; str[i] != '\0' ; i++)
	{
		uart_send_char(str[i]);
	}
	while (!(USART2_SR & (1UL << 6))) { }   // Wait until TC is set
}


void init_uart(void)
{
	RCC_AHB1ENR |= (1uL << 0);    // GPIOA clock
	RCC_APB1ENR |= (1uL << 17);   // USART2 clock

	GPIOA_MODER &=~(3uL << 4);   // PA2: clear mode bits
	GPIOA_MODER |= (2uL << 4);   // PA2: alternate function (10)

	GPIOA_AFRL &=~(0xFuL << 8);   // PA2: clear AF bits
	GPIOA_AFRL |= (0x7uL << 8);   // PA2: AF7 = USART2_TX

	USART2_CR1 |=(0x1uL << 13);   // USART2 enable
	USART2_BRR |=(0x8uL << 4)|(0xBuL <<0); //Set baud rate to 115200 ( 16MHz clock)
	USART2_CR1 |=(0x1uL <<3 );   // TE: Transmitter enable

	
}


