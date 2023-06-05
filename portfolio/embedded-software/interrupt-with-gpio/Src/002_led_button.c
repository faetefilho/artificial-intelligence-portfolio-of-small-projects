/*
 * 002_led_button.c
 *
 *  Created on: May 31, 2023
 *      Author: Tinho
 */

/*
 * 001_led_toggle.c
 *
 *  Created on: May 30, 2023
 *      Author: Tinho
 */
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h" // this could go inside stm32f407xx.h and then be called from that header file

void Delay(void)
{
	for (uint32_t i =0; i<200000; i++)
	{

	}
}

// Variable to toggle direction
uint8_t ledDirection = 0;

int main (void)
{
	// Green LED
	GPIO_Handle_t gpioLed;
	// initialize variable
	gpioLed.pGPIOx = GPIOD; // port to use
	gpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12; // macro GPIO_PIN_NO_12 only available after inclusion of stm32f407xx_gpio_driver.h
	gpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Orange LED
	GPIO_Handle_t gpioLedOrange;
	// initialize variable
	gpioLedOrange.pGPIOx = GPIOD; // port to use
	gpioLedOrange.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13; // macro GPIO_PIN_NO_12 only available after inclusion of stm32f407xx_gpio_driver.h
	gpioLedOrange.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLedOrange.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLedOrange.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLedOrange.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Red LED
	GPIO_Handle_t gpioLedRed;
	// initialize variable
	gpioLedRed.pGPIOx = GPIOD; // port to use
	gpioLedRed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14; // macro GPIO_PIN_NO_12 only available after inclusion of stm32f407xx_gpio_driver.h
	gpioLedRed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLedRed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLedRed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLedRed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Blue LED
	GPIO_Handle_t gpioLedBlue;
	// initialize variable
	gpioLedBlue.pGPIOx = GPIOD; // port to use
	gpioLedBlue.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15; // macro GPIO_PIN_NO_12 only available after inclusion of stm32f407xx_gpio_driver.h
	gpioLedBlue.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLedBlue.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLedBlue.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLedBlue.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	// Button
	GPIO_Handle_t gpioButton;
	// initialize variable
	gpioButton.pGPIOx = GPIOA; // port to use
	gpioButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0; // macro GPIO_PIN_NO_12 only available after inclusion of stm32f407xx_gpio_driver.h
	gpioButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RT; // interrupt rising edge trigger mode
	gpioButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	//gpioButton.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP; // not applicable when mode is input
	gpioButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	// initialize clock peripherals
	GPIO_PeriClockControl(GPIOD, ENABLE);
	GPIO_PeriClockControl(GPIOA, ENABLE);

	// Initialize GPIO
	GPIO_Init(&gpioLed);
	// Initialize orange
	GPIO_Init(&gpioLedOrange);
	// Initialize Red
	GPIO_Init(&gpioLedRed);
	// Initialize Blue
	GPIO_Init(&gpioLedBlue);
	// Initialize button on PA0
	GPIO_Init(&gpioButton);

	// IRQ configuration for PA0, rising edge
	// PA0 is connected to EXTI0, so we need to configure EXTI0
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRI15);
	GPIO_IRQInterruptConfig(IRQ_NO_EXTI0, ENABLE);

	
	// toggle the LEDs
	while(1)
	{
		if (ledDirection == 0)
		{
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
			Delay(); // Create a lazy SW delay
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
			Delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
			Delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
			Delay();
		}else
		{
			Delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
			//Delay(); // Create a lazy SW delay
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
			//Delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
			//Delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
			//Delay();
		}

	}
	return 0;
}

void EXTI0_IRQHandler(void) // IRQ handler for GPIOA pin 0, overriden from .weak on startup_stm32f407xx.s
{

	GPIO_IRQHandling(GPIO_PIN_NO_0); // clear the pending event from the exti line
	
	// toggle the LED direction from 0 to 1 or 1 to 0
	if (ledDirection == 0)
	{
		ledDirection = 1;
	}else
	{
		ledDirection = 0;
	}

}
