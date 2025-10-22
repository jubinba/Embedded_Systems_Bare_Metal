#include "stm32f4xx.h"


#define GPIOAEN     (1U<<0)  // Enable clock access for GPIO A (making lsb 1)
#define PIN5		 (1U<<5)
#define LED_PIN      PIN5


int main(void)
{
	// Enable the RCC Register
	RCC->AHB1ENR |= GPIOAEN; // Enabled the RCC Register
	// Enable MODE Register
	GPIOA->MODER |=(1U<<10);//Enable Bit 10 to 1
	GPIOA->MODER &=~(1U<<11); // Enable Bit 11 to 0
	while(1)
	{
		// LED Turn On
		GPIOA->ODR ^= LED_PIN; // LED Toggle operation
		// Setup Delay
		for(int i =0;i<200000;i++){}
	}
}
