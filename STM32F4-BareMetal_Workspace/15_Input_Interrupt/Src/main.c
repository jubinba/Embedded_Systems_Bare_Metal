/*Code: An interrupt will occur when the push button is pressed*/

#include<stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include"tim.h"
#include"exti.h"

#define GPIOAEN		(1U<<0)
#define PIN5		(1U<<5)
#define LEDPIN      PIN5

static void exti_callback(void);

int timestamp = 0;




int main(void)
{

	/* Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA5 as Output Pin*/

	GPIOA->MODER |= (1U<<10) ;      // Set only bit 10 to 1
	GPIOA->MODER &=~(1U<<11) ;   	// Set only bit 11 to 0*


	pc13_exti_init();
	uart2_tx_init();



}
static void exti_callback(void)
{
	printf("button presses....\n\r");
	GPIOA->ODR ^= LEDPIN;
}

void EXTI15_10_IRQHandler (void){
	if((EXTI->PR & LINE13)!=0)
	{
		/*Clear PR flag*/
		EXTI->PR |= LINE13;

		/*Do something*/
		exti_callback();
	}

}








