/*Code for direct toggle of hardware pin(PA5) which is connected to a timer*/

#include<stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include"tim.h"




int main(void)
{

	tim2_PA5_output_compare();



	while(1)
	{



	}

}






