#include<stdio.h> // Required for printf
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIOAEN     (1U<<0)
#define PIN5		 (1U<<5)

#define LED_PIN      PIN5


char key;








int main(void)
{


	// Enable the clock access to GPIOA(LED)
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA5 as output pin (LED)
	GPIOA->MODER |=(1U<<10);
	GPIOA->MODER &=~(1U<<11);

	uart2_rxtx_init();
	while(1)
	{
		key = uart2_read();  // Reading from UART and storing it to a character key
		if(key == '1'){
			GPIOA->ODR |= LED_PIN ;
		}
		else{

			GPIOA->ODR &= ~LED_PIN ;

		}
	}
}






