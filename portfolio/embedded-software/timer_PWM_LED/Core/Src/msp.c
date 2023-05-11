/*
 * msp.c
 *
 *  Created on: May 7, 2023
 *      Author: Tinho
 */

#include "main.h"

void HAL_MspInit(void)
{
	//here we will do low level processor specific inits
	//1. setup up th epriority grouping of the arm cortex mx processor
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 <<16; // 111 shift by 16; usg fault, mem fault and bus fault system exceptions activated
	//3. configure the priority for the system exceptions
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;

	//here we are going to do the low level inits of the USART2 peripheral

	//1. Enable the clock for the USART2, GPIOA peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2. do the pin muxing configuration, PA2 for UART2_TX
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART2; //UART2_TX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; //UART2_RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. Enable the IRQ and set up priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn, 15, 0);

}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef tim2_OC_ch_gpios;
	GPIO_InitTypeDef tim4_OC_ch_gpios;

	//1. enable the peripheral clock for the timer 2 peripheral
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	// enable timer 4
	__HAL_RCC_TIM4_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();

	//2 configure gpios to have as timer 2, channel 1,2,3, and 4
	//PA0 (channel 1), PA1 (channel 2)
	tim2_OC_ch_gpios.Pin = GPIO_PIN_0 | GPIO_PIN_1;
	tim2_OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim2_OC_ch_gpios.Pull = GPIO_NOPULL;
	tim2_OC_ch_gpios.Speed = GPIO_SPEED_FREQ_LOW;
	tim2_OC_ch_gpios.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &tim2_OC_ch_gpios);

	// PB10 (channel 3), PB2 (channel 4)
	tim2_OC_ch_gpios.Pin = GPIO_PIN_2 | GPIO_PIN_10;
	tim2_OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim2_OC_ch_gpios.Pull = GPIO_NOPULL;
	tim2_OC_ch_gpios.Speed = GPIO_SPEED_FREQ_LOW;
	tim2_OC_ch_gpios.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOB, &tim2_OC_ch_gpios);

	// PD12 (channel 1) timer 4
	tim4_OC_ch_gpios.Pin = GPIO_PIN_12;
	tim4_OC_ch_gpios.Mode = GPIO_MODE_AF_PP;
	tim4_OC_ch_gpios.Pull = GPIO_NOPULL;
	tim4_OC_ch_gpios.Speed = GPIO_SPEED_LOW;
	tim4_OC_ch_gpios.Alternate = GPIO_AF2_TIM4;
	HAL_GPIO_Init(GPIOD, &tim4_OC_ch_gpios);

	//3 NVIC settings
	HAL_NVIC_SetPriority(TIM2_IRQn, 15, 0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
}
