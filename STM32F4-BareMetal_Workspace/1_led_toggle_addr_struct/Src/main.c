//Where is the LED connected
//Port: A
//Pin:  5
#include<stdint.h>
#define PERIPH_BASE  					(0x40000000UL) // UL-Unsigned Long Constant
#define AHB1PERIPH_OFFSET 				(0x00020000UL)
#define AHB1PERIPH_BASE                 (PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOA_OFFSET					(0x0000U) // Because the GPIOA is starting from the base of AHB1


#define GPIOA_BASE                      (AHB1PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET						(0x3800UL)
#define RCC_BASE						(AHB1PERIPH_BASE + RCC_OFFSET)


#define GPIOAEN							(1U<<0) // 0(0b): 0000 0000 0000 0000 0000 0000 0000 0000
												//1U <<0: 0000 0000 0000 0000 0000 0000 0000 0001
												//1U<<1 : 0000 0000 0000 0000 0000 0000 0000 0010
												//1U<<2 : 0000 0000 0000 0000 0000 0000 0000 0100

#define PIN5							(1U<<5)
#define LED_PIN                         (PIN5)

#define __IO volatile

typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;         // RCC AHB1 peripheral clock register,  Address offset:0x30
	}RCC_TypeDef;



/*typedef struct{
	__IO uint32_t MODER;   	  // GPIO Port mode register
	__IO uint32_t OTYPER;	  // GPIO port output type register
	__IO uint32_t OSPEEDR;    // GPIO port output speed register
	__IO uint32_t PUPDR;      //GPIO port pull-up/pull-down register
	__IO uint32_t IDR;        //GPIO port input data register
	__IO uint32_t ODR;        //GPIO port output data register
	__IO uint32_t BSRR;       //GPIO port bit set/reset register
	__IO uint32_t LCKR;       //GPIO port configuration lock register
	__IO uint32_t AFR[2];     //GPIO alternate function registers(HIGH/LOW)
} GPIO_TypeDef;

// The above structure can be simplified as
 *
 * typedef struct{
	__IO uint32_t MODER;   	  // GPIO Port mode register
	__IO uint32-t DUMY[4];    // For properly arranging the bit gap between MODER and ODR
	__IO uint32_t ODR;        //GPIO port output data register. We are using only MODER and ODR, Hence all others can be ignored

}; GPIO_TypeDef;


 *
 *
 */
// This can be further simplified as
typedef struct{
	volatile uint32_t MODER;   	  // GPIO Port mode register
	volatile uint32_t DUMMY[4];    // For properly arranging the bit gap between MODER and ODR
	volatile uint32_t ODR;        //GPIO port output data register. We are using only MODER and ODR, Hence all others can be ignored

}GPIO_TypeDef;

#define RCC		((RCC_TypeDef*)RCC_BASE)
#define GPIOA	((GPIO_TypeDef*)GPIOA_BASE)


int main (void)
{

	/* Enable clock access to GPIOA*/
	RCC->AHB1ENR |= GPIOAEN;

	/* Set PA5 as Output Pin*/

	GPIOA->MODER |= (1U<<10) ;      // Set only bit 10 to 1
	GPIOA->MODER &=~(1U<<11) ;   // Set only bit 11 to 0*




	while(1)
	{
		/* Set PA 5 High*/
		/* Trying LED Toggle Operation*/
		GPIOA->ODR ^= LED_PIN; // ^ key will automatically toggle operation in the loop (ON/OFF/ON/OFF/......)
		for(int i = 0; i< 100000;i++)  {}// Applying a delay to the toggle
	}
}


