

#include "stm32f4xx.h"


#define SYSTICK_LOAD_VAL 	16000
#define CTRL_ENABLE			(1U<<0)
#define CTRL_CLKSRC			(1U<<2)
#define CTRL_COUNTFLAG		(1U<<16)


void systickDelayMs_Init (int delay){

	/*Reload with no of clocks per millisecond*/
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	/*Clear SysTick Current Value Register*/
	SysTick->VAL = 0;

	/*Enable SysTick & Select Internal Clk Src*/
	SysTick->CTRL = CTRL_ENABLE	 | CTRL_CLKSRC	;

	for (int i=0;i< delay; i++){
		/*Wait until COUNTFLAG is set*/
		while(!(SysTick->CTRL & CTRL_COUNTFLAG )){

		}




	}
		/*Disable the SysTick ctrl register*/
		SysTick->CTRL =0;



}
