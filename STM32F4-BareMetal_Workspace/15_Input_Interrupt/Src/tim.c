#include "stm32f4xx.h"

#define TIM2_EN			(1U<<0)
#define TIM3_EN			(1U<<1)
#define TIM2_CR1_CEN	(1U<<0)
#define TIM2_CCMR1		(1U<<4 )| (1U<<5)
#define TIM3_CCMR1_CC1S (1U<<0)
#define TIM2_CCER_CC1E	(1U<<0)
#define TIM3_CCER_CC1	(1U<<0)
#define GPIOA_EN		(1U<<0)
#define GPIOA_AFR5		(1U<<20)
#define GPIOA_AFR6		(1U<<25)


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

void tim2_PA5_output_compare(void){

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Set PA5 to alternate function mode*/
	GPIOA->MODER &=~ (1U<<10);
	GPIOA->MODER |= (1U<<11);

	/*Set PA5 alternate function type to TIM2_CH1(AF1)*/
	GPIOA->AFR[0] |= GPIOA_AFR5;

	/*Enable Clock access to Timer 2*/
	RCC->APB1ENR |= TIM2_EN;

	/*Set pre-scaler value*/
	TIM2->PSC = 1600 -1; // 16 000 000 / 1600 = 10 000

	/*Set auto-reload value*/
	TIM2 ->ARR = 10000-1; // 10 000 / 10 000 = 1

	/*Set output compare toggle mode*/
	TIM2->CCMR1 = TIM2_CCMR1;

	/*Enable tim2 ch1 in compare mode*/
	TIM2->CCER = TIM2_CCER_CC1E;





	/*Clear counter*/
	TIM2 ->CNT = 0;

	/*Enable Timer*/
	TIM2->CR1 |= TIM2_CR1_CEN;

}

void tim3_input_capture(void){

	/*Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Set PA6 to alternate function mode*/
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	/*Set PA6 alternate function type to TIM3_CH1(AF2)*/
	GPIOA->AFR[0] |= GPIOA_AFR6;

	/*Enable Clock access to Timer 3*/
	RCC->APB1ENR = TIM3_EN	;


	/*Set Prescaler*/
	TIM3->PSC = 1600 -1; // 16 000 000 / 1600 = 10 000

	/*Set TIM3_CH1 to input capture */
	TIM3->CCMR1 |= TIM3_CCMR1_CC1S;

	/*Set TIM3_CH1 to capture at rising edge*/
	TIM3->CCER |= TIM3_CCER_CC1;
	/*Enable TIM3*/

	TIM3->CR1 = TIM2_CR1_CEN;
}
