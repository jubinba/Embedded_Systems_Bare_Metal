#include "stm32f4xx.h"

#define TIM2_EN			(1U<<0)
#define TIM2_CR1_CEN	(1U<<0)


/*This function both initializes timer and creates time-out for 1 second*/

void tim2_1hz_init(void){

	/*Enable Clock access to Timer 2*/
	RCC->APB1ENR |= TIM2_EN;

	/*Set prescaler value*/
	TIM2->PSC = 1600 -1; // 16 000 000 / 1600 = 10 000

	/*Set auto-reload value*/
	TIM2 ->ARR = 10000-1; // 10 000 / 10 000 = 1

	/*Clear counter*/
	TIM2 ->CNT = 0;

	/*Enable Timer*/
	TIM2->CR1 |= TIM2_CR1_CEN;

}
