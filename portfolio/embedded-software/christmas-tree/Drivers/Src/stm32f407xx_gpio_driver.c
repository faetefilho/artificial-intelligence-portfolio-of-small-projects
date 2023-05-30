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
// IRQ Configuration and IRS handler
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t enorDi)
{

}
void GPIO_IRQHandling(uint8_t PinNumber)	// whenever an interrupt occurs the use user application can call this function to process the interrupt
{

}
