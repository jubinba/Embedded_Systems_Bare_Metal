/* ADC Driver*/

#include "stm32f4xx.h"
#include "adc.h"



#define GPIOA_EN			(1U<<0) // GPIOA clock enable
#define ADC1_EN				(1U<<8) // Clock Enable ADC1
#define ADC_CH1				(1U<<0)
#define ADC_SEQ_LEN_1 		0x00
#define CR2_AD_ON			(1U<<0)
#define CR2_SW_START		(1U<<30)
#define SR_EOC				(1U<<1)







void pa1_adc_init(void){

	/*Clock Enable for GPIOA*/
	RCC->AHB1ENR |= GPIOA_EN;

	/*Configure PA1 as analog pin*/
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/*Configure ADC module*/
	/*Enable ADC clock access*/
	RCC->APB2ENR |= ADC1_EN;
	/*Conversion Sequence Start*/
	ADC1->SQR3 = ADC_CH1;
	/*Conversion Sequence Length*/
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	/*Enable ADC Module*/
	ADC1->CR2 |= CR2_AD_ON;
				}



/*Function for ADC conversion*/
void start_conversion(void){
	/*Start ADC Conversion*/
	ADC1->CR2 |= CR2_SW_START;
	}



/*Function to read data from ADC*/

uint32_t adc_read(void){

	/*Wait for conversion to be complete*/
	while(!(ADC1->SR & SR_EOC))	{
		// while false(SR_E0C is 0) get stuck in the loop
	}

	/*Read Converted Result*/
	return (ADC1->DR);

}
