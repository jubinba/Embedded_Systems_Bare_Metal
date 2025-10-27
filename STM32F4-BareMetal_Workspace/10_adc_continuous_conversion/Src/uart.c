/*Developing UART Reciever Driver*/

# include "uart.h"



#define GPIOAEN     (1U<<0)  // Enable clock access for GPIO A (making lsb 1)
#define UART2EN 	(1U<<17) // Enable clock access for USART 2

#define CR1_TE		(1U<<3)// Enable the transmitter control register -> configure transfer direction
#define CR1_RE		(1U<<2)// Enable the receiver control register

#define U_E			(1U<<13)// To Enable UART in control register
#define SR_TXE		(1U<<7)// For checking transmit data register is 1, So if we read SR_TXE and perform and operation (1U<<7),If TRUE then we can conclude that the transmit data register is empty
#define SR_RXNE		(1U<<5)//For checking read data register is not empty

#define SYS_FREQ			16000000 // 16Mhz // Default system clock of STM32
#define APB1_CLK			SYS_FREQ
#define UART_BAUDRATE		115200



static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRatre );
static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRatre);


void uart2_write(int ch);


// function for printf

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}



//Creating necessary functions for UART tx and rx configuration

void uart2_rxtx_init(void)
	{

	/**************Configure uart tx gpio pin***************/

	/*Enable Clock Access for GPIOA(GPIOA because pins is PA2)*/
	RCC->AHB1ENR |= GPIOAEN;

	/*Set PA2 mode to Alternate Function Mode*/
	GPIOA->MODER &=~(1<<4); // set bit 4 to 0
	GPIOA->MODER |=(1<<5); // set bit 5 to 1

	/*Set PA2 alternate function type to UART_TX (AF7)*/

	GPIOA->AFR[0] |= (1U<<8);// AFRL -> AFR[0], AFRH -> AFR[1], Setting AF7 to AFRL2 (bit 8)
	GPIOA->AFR[0] |= (1U<<9);// Setting AF7 to AFRL2 (bit 9)
	GPIOA->AFR[0] |= (1U<<10); //Setting AF7 to AFRL2 (bit 10)
	GPIOA->AFR[0] &=~ (1U<<11);//Setting AF7 to AFRL2 (bit 11)

	/**************Configure uart rx gpio pin***************/

	/*Set PA3 mode to Alternate Function Mode*/
	GPIOA->MODER &=~(1<<6); // set bit 6 to 0
	GPIOA->MODER |=(1<<7); // set bit 7 to 1

	/*Set PA3 alternate function type to UART_RX (AF7) (PA3- AFRL3)*/
	GPIOA->AFR[0] |= (1U<<12);// AFRL -> AFR[0], AFRH -> AFR[1], Setting AF7 to AFRL3 (bit 12)
	GPIOA->AFR[0] |= (1U<<13);// Setting AF7 to AFRL3 (bit 13)
	GPIOA->AFR[0] |= (1U<<14); //Setting AF7 to AFRL3 (bit 14)
	GPIOA->AFR[0] &=~ (1U<<15);//Setting AF7 to AFRL3 (bit 15)



	/****************Configure UART module************************/

	/*Enable clock access to uart2*/
	RCC->APB1ENR |= UART2EN ;

	/*Configure baud rate*/
	uart_set_baudrate(USART2, APB1_CLK, 115200);

	/*Configure the transfer direction (RX and TX)*/
	USART2->CR1 = CR1_TE; //  Transmitter Enabled(No OR operation because we want to clear all other bits and write to bit 3 only
	USART2->CR1	|=CR1_RE; //  Receiver Enabled(USART_CR1)
	/*Enable uart2 module*/
	USART2->CR1 |= U_E	;// Enable UART
	}






//Creating necessary functions for UART configuration

void uart2_tx_init(void)
	{

	/**************Configure uart tx gpio pin***************/

	/*Enable Clock Access for GPIOA(GPIOA because pins is PA2)*/
	RCC->AHB1ENR |= GPIOAEN;
	/*Set PA2 mode to Alternate Function Mode*/
	GPIOA->MODER &=~(1<<4); // set bit 4 to 0
	GPIOA->MODER |=(1<<5); // set bit 5 to 1
	/*Set PA2 alternate function type to UART_TX (AF7)*/
	GPIOA->AFR[0] |= (1U<<8);// AFRL -> AFR[0], AFRH -> AFR[1], Setting AF7 to AFRL2 (bit 8)
	GPIOA->AFR[0] |= (1U<<9);// Setting AF7 to AFRL2 (bit 9)
	GPIOA->AFR[0] |= (1U<<10); //Setting AF7 to AFRL2 (bit 10)
	GPIOA->AFR[0] &=~ (1U<<11);//Setting AF7 to AFRL2 (bit 11)


	/****************Configure UART module************************/
	/*Enable clock access to uart2*/
	RCC->APB1ENR |= UART2EN ;
	/*Configure baud rate*/
	uart_set_baudrate(USART2, APB1_CLK, 115200);

	/*Configure the transfer direction*/
	USART2->CR1 = CR1_TE; // No OR operation because we want to clear all other bits and write to bit 3 only

	/*Enable uart2 module*/
	USART2->CR1 |= U_E	;// Enable UART
	}

/****************Function for writing a character to UART************************/

void uart2_write(int ch)
{
	/*Make sure the transmit data register is empty*/

	// For checking transmit data register is empty, So if we read SR_TXE and perform and operation (1U<<7)
	//If TRUE then we can conclude that the transmit data register is not empty
	while(!(USART2->SR & SR_TXE)) {}   // while(!(USART2->SR & SR_TXE)) -> while((USART2->SR & SR_TXE) is false[!])
	/*Write to transmit data register*/
	USART2->DR = (ch & 0xFF); // converting the character to an unsigned 8-bit value (0–255).

}

/****************Function for reading data(character) from UART************************/

char uart2_read(void)
{
	/*Make sure that the receive data is not empty*/
	while(!(USART2->SR & SR_RXNE)) {}

	/*Read data*/
	return USART2->DR;
}








/*Function for Computing Baud Rate*/


static void uart_set_baudrate(USART_TypeDef *USARTx,uint32_t PeriphClk, uint32_t BaudRatre )
{

USARTx->BRR = compute_uart_bd(PeriphClk, BaudRatre);


}


static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRatre)
{
	return (( PeriphClk + (BaudRatre/2U))/BaudRatre);
	}

