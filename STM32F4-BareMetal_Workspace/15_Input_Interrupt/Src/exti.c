
#include "exti.h"

#define GPIOC_EN 		(1U<<2)

#define SYSCFG_EN		(1U<<14)
#define SYSCFG_EXTICR4 	(1U<<5)

#define EXTI_IMR		(1U<<13)
#define EXTI_FTSR		(1U<<13)

void pc13_exti_init(void){

	/*Disable global interrupt*/
	__disable_irq();

	/*Enable clock access for GPIOC*/
	RCC->AHB1ENR |= GPIOC_EN;

	/*Set PC_13 as input pin*/
	GPIOC->MODER &=~(1U<<26);
	GPIOC->MODER &=~(1U<<27);

	/*Enable clock access to SYSCNFG*/
	RCC->APB2ENR |= SYSCFG_EN;

	/*Select port C for EXTI13*/
	SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4;

	/*Unmask EXTI13*/
	EXTI->IMR |= EXTI_IMR;

	/*Select falling edge trigger (we can use either rising or falling edge)*/
	EXTI->FTSR |= EXTI_FTSR;

	/*Enable EXTI13 line in NVIC*/
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	/*Enable global interrupt*/
	__enable_irq();


}
