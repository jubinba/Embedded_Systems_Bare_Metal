#include<stdio.h> // Required for printf
#include <stdint.h>
#include "stm32f4xx.h"
#include "uart.h"











int main(void)
{

	uart2_tx_init();			//Configure uart tx gpio pin
	while(1)
	{

	printf("Hello from STM32F4..............\n\r");
	}
}






