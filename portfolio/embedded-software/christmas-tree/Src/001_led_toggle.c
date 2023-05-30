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
	for (uint32_t i =0; i<500000; i++)
	{

	}
}

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

	// initialize clock peripherals
	GPIO_PeriClockControl(GPIOD, ENABLE);

	// Initialize GPIO
	GPIO_Init(&gpioLed);
	// Initialize orange
	GPIO_Init(&gpioLedOrange);
	// Initialize Red
	GPIO_Init(&gpioLedRed);
	// Initialize Blue
	GPIO_Init(&gpioLedBlue);

	// toggle the LEDs
	while(1)
	{
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
		Delay(); // Create a lazy SW delay
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_13);
		Delay();
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_14);
		Delay();
		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
		Delay();


	}
	return 0;
}
