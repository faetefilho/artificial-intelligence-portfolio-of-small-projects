/*
 * stm32f407xx.h
 *
 *  Created on: May 12, 2023
 *      Author: Tinho
 */

#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>

#define __vo volatile

// Processor specific details
// ARM Cortex Mx processor NVIC ISERx register addresses (interrupt set enable register)
#define NVIC_ISER0				((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2				((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3				((__vo uint32_t*)0xE000E10C) // could continue up to 7

// ARM Cortex Mx processor NVIC ICERx register addresses (interrupt clear enable register)
#define NVIC_ICER0				((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1				((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2				((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3				((__vo uint32_t*)0xE000E18C) // could continue up to 7

// ARM Cortex Mx processor priority register address calculation
#define NVIC_PR_BASEADDR		((__vo uint32_t*)0xE000E400)

// ARM Cortex Mx processor number of priority bits implemented in priority register
#define NO_PR_BITS_IMPLEMENTED	4 // this is a generic value for the STM32F4xx family, could be different for other families

// base addresses of flash and sram memories

#define FLASH_BASEADDR			0x08000000U //U is added because by default it would considered signed numbers
#define SRAM1_BASEADDR			0x20000000U //112KB
#define SRAM2_BASEADDR			0x20001C00U
#define ROM_BASEADDR			0x1FFF0000U
#define SRAM SRAM1_BASEADDR		SRAM1_BASEADDR

// AHBx and APBx peripheral base address
#define PERIPH_BASEADDR			0x40000000U
#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000U
#define AHB1PERIPH_BASEADDR		0x40020000U
#define AHB2PERIPH_BASEADDR		0x50000000U

// Base addresses of peripherals which are hanging on AHB1 bus
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)	//offset is zero bc this is the first one hanging on the AHB bus
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)	//this one now have an offset
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR			(AHB1PERIPH_BASEADDR + 0x2000)

#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

// Base addresses of peripherals which are hanging on APB1 bus
#define I2C1_BASEADDR			APB1PERIPH_BASEADDR + 0x5400
#define I2C2_BASEADDR			APB1PERIPH_BASEADDR + 0x5800
#define I2C3_BASEADDR			APB1PERIPH_BASEADDR + 0x5C00

#define SPI2_BASEADDR			APB1PERIPH_BASEADDR + 0x3800
#define SPI3_BASEADDR			APB1PERIPH_BASEADDR + 0x3C00

#define USART2_BASEADDR			APB1PERIPH_BASEADDR + 0x4400
#define USART3_BASEADDR			APB1PERIPH_BASEADDR + 0x4800
#define UART4_BASEADDR			APB1PERIPH_BASEADDR + 0x4C00
#define UART5_BASEADDR			APB1PERIPH_BASEADDR + 0x5000

// Base addresses of peripherals which are hanging on APB2 bus
#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)
#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)
#define SYSCFG_BASEADDR			(APB2PERIPH_BASEADDR + 0x3800) //SYSCFG_BASEADDR
#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)

// Peripheral registers definition structure (those are MCU specific)
typedef struct
{
	__vo uint32_t MODER;		// address offset 0x00, gpio port mode register
	__vo uint32_t OTYPER;	// address offset 0x04 and so on, 1 byte per address
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];	//could have been two registers here AFRL & AFRH
						// AFR[0] is AFRL, AFR[1] is AFRH

}GPIO_RegDef_t ;

typedef struct
{
	__vo uint32_t RC;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	__vo uint32_t RESERVED0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t RESERVED1;
	__vo uint32_t RESERVED2;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	__vo uint32_t RESERVED3;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t RESERVED4;
	__vo uint32_t RESERVED5;
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	__vo uint32_t RESERVED6;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t RESERVED7;
	__vo uint32_t RESERVED8;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t RESERVED9;
	__vo uint32_t RESERVED10;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;
	__vo uint32_t PLLSAICFGR;
	__vo uint32_t DCKCFGR;

}RCC_RegDef_t;

// Peripheral definition structure for EXTI
typedef struct
{
	__vo uint32_t IMR;		// address offset 0x00
	__vo uint32_t EMR;		// address offset 0x04 and so on, 1 byte (8 bits) per address, for for a 32 bit register is 4 addresses
	__vo uint32_t RTSR;		// 0x08
	__vo uint32_t FTSR;		// 0x0C
	__vo uint32_t SWEIR;	// 0x10
	__vo uint32_t PR;		// 0x14

}EXTI_RegDef_t;

// peripheral definition structure for SYSCFG
typedef struct
{
	__vo uint32_t MEMRMP;		// address offset 0x00
	__vo uint32_t PMC;		// address offset 0x04 and so on, 1 byte (8 bits) per address, for for a 32 bit register is 4 addresses
	__vo uint32_t EXTICR[4];		// 0x08 - 0x14
	uint32_t RESERVED[2];	// 0x18, 0x1C, // there is this gap on the register map so we assign reserved to get to the 0x20 address
	__vo uint32_t CMPCR;		// 0x0x20

}SYSCFG_RegDef_t;


// peripheral addresses typecasted to XX_RegDef_t (from uint ?)

#define GPIOA				((GPIO_RegDef_t*) GPIOA_BASEADDR)
#define GPIOB				((GPIO_RegDef_t*) GPIOB_BASEADDR)
#define GPIOC				((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD				((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE				((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF				((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG				((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH				((GPIO_RegDef_t*) GPIOH_BASEADDR)
#define GPIOI				((GPIO_RegDef_t*) GPIOI_BASEADDR)

#define RCC					((RCC_RegDef_t*) RCC_BASEADDR) // without the outer parenthesis here it would throw an error

#define EXTI				((EXTI_RegDef_t*) EXTI_BASEADDR)

#define SYSCFG				((SYSCFG_RegDef_t*) SYSCFG_BASEADDR)


// clock enable macros for GPIO peripherals

#define GPIOA_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 0 )
#define GPIOB_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 1 )
#define GPIOC_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 2 )
#define GPIOD_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 3 )
#define GPIOE_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 4 )
#define GPIOF_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 5 )
#define GPIOG_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 6 )
#define GPIOH_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 7 )
#define GPIOI_PCLK_EN()	RCC->AHB1ENR |= ( 1 << 8 )

// Clock enable macros for I2Cx peripherals

#define I2C1_PCLK_EN()	RCC->APB1ENR |= ( 1 << 21)
#define I2C2_PCLK_EN()	RCC->APB1ENR |= ( 1 << 22)
#define I2C3_PCLK_EN()	RCC->APB1ENR |= ( 1 << 23)

// Clock enable macros for SPIx peripherals

#define SPI1_PCLK_EN()	RCC->APB2ENR |= ( 1 << 12)
#define SPI2_PCLK_EN()	RCC->APB1ENR |= ( 1 << 14)
#define SPI3_PCLK_EN()	RCC->APB1ENR |= ( 1 << 15)
// no SPI4 on APB2 for F407

// Clock enable macro for usartx and uartx peripherals

#define USART1_PCLK_EN()	RCC->APB2ENR |= ( 1 << 04)
#define USART2_PCLK_EN()	RCC->APB1ENR |= ( 1 << 17)
#define USART3_PCLK_EN()	RCC->APB1ENR |= ( 1 << 18)
#define UART4_PCLK_EN()		RCC->APB1ENR |= ( 1 << 19)
#define UART5_PCLK_EN()		RCC->APB1ENR |= ( 1 << 20)
#define UART6_PCLK_EN()		RCC->APB2ENR |= ( 1 << 05)

// Clock enable for SYSCFG

#define SYSCFG_PCLK_EN()		RCC->APB2ENR |= ( 1 << 14)


// Clock disable macros for GPIO peripherals

#define GPIOA_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 0 )
#define GPIOB_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 1 )
#define GPIOC_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 2 )
#define GPIOD_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 3 )
#define GPIOE_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 4 )
#define GPIOF_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 5 )
#define GPIOG_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 6 )
#define GPIOH_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 7 )
#define GPIOI_PCLK_DIS()	RCC->AHB1ENR &= ~( 1 << 8 )

// Clock disable for I2Cx peripherals

#define I2C1_PCLK_DIS()	RCC->APB1ENR &= ~( 1 << 21)
#define I2C2_PCLK_DIS()	RCC->APB1ENR &= ~( 1 << 22)
#define I2C3_PCLK_DIS()	RCC->APB1ENR &= ~( 1 << 23)

// Clock disable macros for SPIx peripherals

#define USART1_PCLK_DIS()		RCC->APB2ENR &= ~( 1 << 04)
#define USART2_PCLK_DIS()		RCC->APB1ENR &= ~( 1 << 17)
#define USART3_PCLK_DIS()		RCC->APB1ENR &= ~( 1 << 18)
#define UART4_PCLK_DIS()		RCC->APB1ENR &= ~( 1 << 19)
#define UART5_PCLK_DIS()		RCC->APB1ENR &= ~( 1 << 20)
#define UART6_PCLK_DIS()		RCC->APB2ENR &= ~( 1 << 05)

// Disable macros for SYSCFG

#define SYSCFG_PCLK_DIS()		RCC->APB2ENR &= ~( 1 << 14)

// Macros to reset GPIOx peripherals, set (to reset) then clear, do while is used to execute multiple statement in on C macro, note that no semicolon is needed

#define GPIOA_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 0));		(RCC->AHB1RSTR &= ~( 1 << 0));}while(0)
#define GPIOB_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 1));		(RCC->AHB1RSTR &= ~( 1 << 1));}while(0)
#define GPIOC_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 2));		(RCC->AHB1RSTR &= ~( 1 << 2));}while(0)
#define GPIOD_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 3));		(RCC->AHB1RSTR &= ~( 1 << 3));}while(0)
#define GPIOE_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 4));		(RCC->AHB1RSTR &= ~( 1 << 4));}while(0)
#define GPIOF_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 5));		(RCC->AHB1RSTR &= ~( 1 << 5));}while(0)
#define GPIOG_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 6));		(RCC->AHB1RSTR &= ~( 1 << 6));}while(0)
#define GPIOH_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 7));		(RCC->AHB1RSTR &= ~( 1 << 7));}while(0)
#define GPIOI_REG_RESET()		do{ (RCC->AHB1RSTR |= ( 1 << 8));		(RCC->AHB1RSTR &= ~( 1 << 8));}while(0)

#define GPIO_BASEADDR_TO_CODE(x)		(	(x == GPIOA)?0:\
											(x == GPIOB)?1:\
											(x == GPIOC)?2:\
											(x == GPIOD)?3:\
											(x == GPIOE)?4:\
											(x == GPIOF)?5:\
											(x == GPIOG)?6:\
											(x == GPIOH)?7:8 	) // could create issue later and default to port H



// Some generic macros
#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISBALE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

//IRQ numbers for STM32F407x

#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40

// NVIC IRQ Priority macros
#define NVIC_IRQ_PRI0		0
#define NVIC_IRQ_PRI1		1
#define NVIC_IRQ_PRI2		2
#define NVIC_IRQ_PRI3		3
#define NVIC_IRQ_PRI4		4
#define NVIC_IRQ_PRI5		5
#define NVIC_IRQ_PRI6		6
#define NVIC_IRQ_PRI7		7
#define NVIC_IRQ_PRI8		8
#define NVIC_IRQ_PRI9		9
#define NVIC_IRQ_PRI10		10
#define NVIC_IRQ_PRI11		11
#define NVIC_IRQ_PRI12		12
#define NVIC_IRQ_PRI13		13
#define NVIC_IRQ_PRI14		14
#define NVIC_IRQ_PRI15		15



#endif /* INC_STM32F407XX_H_ */
