/*
 * stm32f407xx_gpio_driver.c
 *
 *  Created on: May 21, 2023
 *      Author: Tinho
 */

#include "stm32f407xx_gpio_driver.h"

// Here we will define the function prototypes from the header file
/*
 * @fn			GPIO_PeriClockControl
 *
 * @brief		This function enables and disables peripheral clock for the given GPIO port
 *
 * @param[in]	base address of the GPIO peripheral
 * @param[in]	macros ENABLE DISABLE
 * @param[in]
 *
 * @return
 *
 * @note
 *
 * */
// Peripheral clock setup
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi)
{
	if (EnorDi == ENABLE)
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_EN();
		}

	}else
	{
		if (pGPIOx == GPIOA)
		{
			GPIOA_PCLK_DIS();
		}else if (pGPIOx == GPIOB)
		{
			GPIOB_PCLK_DIS();
		}else if (pGPIOx == GPIOC)
		{
			GPIOC_PCLK_DIS();
		}else if (pGPIOx == GPIOD)
		{
			GPIOD_PCLK_DIS();
		}else if (pGPIOx == GPIOE)
		{
			GPIOE_PCLK_DIS();
		}else if (pGPIOx == GPIOF)
		{
			GPIOF_PCLK_DIS();
		}else if (pGPIOx == GPIOG)
		{
			GPIOG_PCLK_DIS();
		}else if (pGPIOx == GPIOH)
		{
			GPIOH_PCLK_DIS();
		}else if (pGPIOx == GPIOI)
		{
			GPIOI_PCLK_DIS();
		}
	}

}
// init and de init
void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	uint32_t temp;

	// on github GPIO_PeriClockControl is called here, check final version later

	// initialize port and pin

	// 1. configure mode of gpio pin
	if( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) // it is not an interrupt mode
	{
		// Need to reset the bit first before we set them
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ); // each pin has two bit to set this, that is why the shift by two
		// Now we set only the bits of interest using or logic
		pGPIOHandle->pGPIOx->MODER |= temp;
	}else
	{
		// interrupt mode

		if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
		{
			// 1. configure the falling trigger selection register
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear the RTSR bit just in case it might be set
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
		{
			// 1. configure the rising trigger selection register
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			// clear the FTSR bit just in case it might be set
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
		{
			// 1. configure the falling/rising trigger selection register
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

		}

		// 2. configure GPIO port selection in SYSCFG_EXTICR
		uint8_t regNum;		// 0 = EXTI 0 1 2 3, 1 = EXTI 4 5 6 7, etc
		regNum = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber/4;	// 0 to 3
		uint8_t extiPos;
		extiPos = (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%4)*4; // 0 4 8 12, four positions in EXTIx register, with x = regNum
		// enable syscfg peripheral clock
		SYSCFG_PCLK_EN();
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx); // get the port

		SYSCFG->EXTICR[regNum] &= ~(0xF << extiPos); // clear
		SYSCFG->EXTICR[regNum] = portCode << extiPos; //  set

		// enable the exti interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	temp = 0;

	//2. configure speed
	// Need to reset the bit first before we set them
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ); // each pin has two bit to set this, that is why the shift by two
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp=0;
	//3. configure pupd
	// Need to reset the bit first before we set them
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ); // each pin has two bit to set this, that is why the shift by two
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp=0;
	//4. configure optype
	// Need to reset the bit first before we set them
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << (1 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	temp = ( pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (1 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) ); // each pin has two bit to set this, that is why the shift by two
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp=0;
	//5. configure alt functionality
	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		// configure the alternate mode function registers
		uint8_t afr_H_or_L, regPos;

		afr_H_or_L = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; // less than 8 will be zero (lower register)
		regPos = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // mod: left over of division

		// need to reset the 4 bits before we set them
		pGPIOHandle->pGPIOx->AFR[afr_H_or_L] &= ~( 0xF << (regPos) );

		pGPIOHandle->pGPIOx->AFR[afr_H_or_L] |= ( pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunType << (4*regPos) );

	}

}
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) // We get RegDeg to know which port we are dealing with, then we go the RRC to reset that port
{
	if (pGPIOx == GPIOA)
	{
		GPIOA_REG_RESET();
	}else if (pGPIOx == GPIOB)
	{
		GPIOB_REG_RESET();
	}else if (pGPIOx == GPIOC)
	{
		GPIOC_REG_RESET();
	}else if (pGPIOx == GPIOD)
	{
		GPIOD_REG_RESET();
	}else if (pGPIOx == GPIOE)
	{
		GPIOE_REG_RESET();
	}else if (pGPIOx == GPIOF)
	{
		GPIOF_REG_RESET();
	}else if (pGPIOx == GPIOG)
	{
		GPIOG_REG_RESET();
	}else if (pGPIOx == GPIOH)
	{
		GPIOH_REG_RESET();
	}else if (pGPIOx == GPIOI)
	{
		GPIOI_REG_RESET();
	}
}
// Read and write functions
/*
 * @fn			GPIO_ReadFromInputPin
 *
 * @brief		This function reads from GPIO pin
 *
 * @param[in]	base address of the GPIO peripheral
 * @param[in]	pin number to read
 * @param[in]
 *
 * @return 		0 or 1
 *
 * @note
 *
 * */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	uint8_t value;
	value = (uint8_t)( (pGPIOx->IDR >> PinNumber) & 0x00000001 ); //
	return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) // port is 16 pins, return content of input data register
{
	uint16_t value;
	value = (uint16_t)( (pGPIOx->IDR) ); //
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{
	if (Value == GPIO_PIN_SET)
	{
		// write 1
		pGPIOx->ODR |= (1 << PinNumber);
	}else
	{
		// write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value)
{
	pGPIOx->ODR = Value;
}
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber)
{
	// XOR to toggle the pin number bit
	pGPIOx->ODR ^= (1 << PinNumber);
}
// IRQ number Configuration,
// configured to an max IRQ number of 95
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t enorDi)
{
	if (enorDi == ENABLE)
	{
		if (IRQNumber <= 31)
		{
			// program Interrup set enable register (ISER0) register
			*NVIC_ISER0 |= (1 << IRQNumber);
		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			// program ISER1 register
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			// program ISER2 register
			*NVIC_ISER2 |= (1 << (IRQNumber % 64));
		}
	}else
	{
		if (IRQNumber <= 31)
		{
			// program ICER0 register
			*NVIC_ICER0 |= (1 << IRQNumber);
		}else if (IRQNumber > 31 && IRQNumber < 64)
		{
			// program ICER1 register
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}else if (IRQNumber >= 64 && IRQNumber < 96)
		{
			// program ICER2 register
			*NVIC_ICER2 |= (1 << (IRQNumber % 64));
		}
	}
}

// IRQ priority configuration
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint32_t IRQPriority)
{
	// find out the IPR register, interrupt priority register
	uint8_t iprx = IRQNumber / 4;			// 4 IRQ numbers per register, 8 bits for each IRQ number
	uint8_t iprx_section = IRQNumber % 4; 	// each IPR register has 4 sections, each section is 8 bits
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTED); // 8 bit section, 4 bits implemented, so we need to shift 4 bits to the left
	// pointer arithmetic, because NVIC_IPR_BASEADDR is a 32 bit pointer, when we add iprx we are moving to the next 32 bit register
	*(NVIC_PR_BASEADDR + iprx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber)	// whenever an interrupt occurs the use user application can call this function to process the interrupt
{
	// clear the exti pr register corresponding to the pin number
	if (EXTI->PR & (1 << PinNumber)) // return zero if that pin is zero otherwise return some number greater than zero
	{
		// clear
		EXTI->PR |= (1 << PinNumber);
	}
}
