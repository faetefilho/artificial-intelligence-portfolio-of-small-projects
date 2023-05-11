/*
 * main.c
 *
 *  Created on: May 7, 2023
 *      Author: Tinho
 */

#include "STM32f4xx_hal.h"
#include "main.h"
#include <string.h>

void SystemClockConfig(void); //prototype
void GPIO_Init(void);
void Error_handler(void);
void TIMER2_Init(void);
void TIMER4_Init(void);
void UART2_Init(void);
void HSI_Configuration(void);

TIM_HandleTypeDef htimer2;
TIM_HandleTypeDef htimer4;
//uart handle variable
UART_HandleTypeDef huart2;

int main(void)
{
	uint16_t dimmer=0;

	// has to be the first function
	HAL_Init();
	SystemClockConfig();
	UART2_Init();
	GPIO_Init();

	TIMER2_Init();
	TIMER4_Init();
	// start the PWM timer and verify everything is ok
	if (HAL_TIM_PWM_Start(&htimer2, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}

	if (HAL_TIM_PWM_Start(&htimer4, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}


	HSI_Configuration();

	while(1)
	{
		while (dimmer < htimer4.Init.Period)
		{
			dimmer++;
			__HAL_TIM_SET_COMPARE(&htimer4, TIM_CHANNEL_1, dimmer);
			HAL_Delay(31); //delay in miliseconds
		}
		while (dimmer > 0)
		{
			dimmer--;
			__HAL_TIM_SET_COMPARE(&htimer4, TIM_CHANNEL_1, dimmer);
			HAL_Delay(31); //delay in miliseconds
		}

	}

	return 0;
}


void SystemClockConfig(void)
{
	// only needed if you need special clock configuration
}


void Error_handler(void)
{
	while(1);
}

void GPIO_Init(void)
{
	//enable its clock
	//__HAL_RCC_GPIOD_CLK_ENABLE();
	// initalize gpio pin to drive LED
	//GPIO_InitTypeDef ledgpio;
	//ledgpio.Pin = GPIO_PIN_12;
	//ledgpio.Mode = GPIO_MODE_OUTPUT_PP;
	//ledgpio.Pull = GPIO_NOPULL;
	//HAL_GPIO_Init(GPIOD, &ledgpio);

}

void TIMER2_Init(void)
{
	// initialize output PWM time base

	htimer2.Instance = TIM2;
	//initialize the time base unit, see excel for calculations
	htimer2.Init.Period = 16000-1;
	htimer2.Init.Prescaler =999;

	if (HAL_TIM_PWM_Init(&htimer2) != HAL_OK)
	{
		Error_handler();
	}

	// configure the channel output mode

	TIM_OC_InitTypeDef tim2_PWM_config;
	// initialise to zero
	memset(&tim2_PWM_config, 0, sizeof(tim2_PWM_config));

	tim2_PWM_config.OCMode = TIM_OCMODE_PWM1;
	tim2_PWM_config.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim2_PWM_config.Pulse = 4000; // 25% duty cycle
	// configure the output channels
	if(HAL_TIM_PWM_ConfigChannel(&htimer2, &tim2_PWM_config, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}



}


void TIMER4_Init(void)
{
	// initialize output PWM time base

	htimer4.Instance = TIM4;
	//initialize the time base unit, see excel for calculations
	htimer4.Init.Period = 64-1;
	htimer4.Init.Prescaler =249;

	if (HAL_TIM_PWM_Init(&htimer4) != HAL_OK)
	{
		Error_handler();
	}

	// configure the channel output mode

	TIM_OC_InitTypeDef tim4_PWM_config;
	// Initialize to zero
	memset(&tim4_PWM_config, 0, sizeof(tim4_PWM_config));

	tim4_PWM_config.OCMode = TIM_OCMODE_PWM1;
	tim4_PWM_config.OCPolarity = TIM_OCPOLARITY_HIGH;
	tim4_PWM_config.Pulse = 0; // 32 is 50% duty cycle
	// configure the output channels
	if(HAL_TIM_PWM_ConfigChannel(&htimer4, &tim4_PWM_config, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_handler();
	}



}

void HSI_Configuration(void)
{
	RCC_OscInitTypeDef Osc_Init;
	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	Osc_Init.HSIState = RCC_HSI_ON;
	// Activates HSI
	if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK )
	{
		Error_handler();
	}
	// sends HSI to PA8, divide by 5
	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_5);

}


void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	//check for errors
	if ( HAL_UART_Init(&huart2) != HAL_OK )
	{
		//there is a problem
		Error_handler();
	}
}

uint32_t ccr_content;
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{

	//tim3 ch1 500Hz toggle
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, ccr_content+16000);
	}

	//tim3 ch2 1000Hz toggle
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, ccr_content+8000);
	}

	//tim3 ch3 2000Hz toggle
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, ccr_content+4000);
	}

	//tim3 ch4 4000Hz toggle
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
	{
		ccr_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, ccr_content+2000);
	}

}
