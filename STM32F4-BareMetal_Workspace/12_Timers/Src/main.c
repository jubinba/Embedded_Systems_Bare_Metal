/*Create driver for General Purpose timer and introduce a one second time-out(with led)*/


#include<stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include"tim.h"


#define GPIOAEN		(1U<<0)
#define PIN5		(1U<<5)
#define LEDPIN      PIN5


int main(void)
{


		/* Enable clock access to GPIOA*/
		RCC->AHB1ENR |= GPIOAEN;

		/* Set PA5 as Output Pin*/

		GPIOA->MODER |= (1U<<10) ;      // Set only bit 10 to 1
		GPIOA->MODER &=~(1U<<11) ;   	// Set only bit 11 to 0*


		/*Enable UART_tx */
		uart2_tx_init(); // Only if this is there then we can print and see that on our display. Becasue the print statement is transferred to the PC using UART(Serial POrt)
		tim2_1hz_init();


	while(1)
	{
		/*Wait for UIF*/
		while(!(TIM2->SR & TIM2_SR_UIF)){}

		/*Clear UIF*/
		TIM2->SR &=~TIM2_SR_UIF;



		printf("A second has passed \n\r");
		GPIOA->ODR ^= LEDPIN ;




	}

}






