/**
  ******************************************************************************
  * @file    main.c
  * @author  Mate Bartfai
  * @version V1.0
  * @date    06-09-2017.
  * @brief
  ******************************************************************************
*/


#include "stm32l0xx.h"
#include "stm32l0xx_nucleo_32.h"
#include "stm32l0xx_hal_gpio.h"
#include "stm32_hal_legacy.h"
#include "stm32l0xx_hal_rcc.h"
#include "stm32l0xx_hal_uart.h"

#define LED 	GPIO_PIN_3	/* Led Pin */
#define BUTTON	GPIO_PIN_12	/* Jumper Pin */
			

int main(void){

	int i = 0;
	int intervall = 0;
	GPIO_InitTypeDef gpio_init;
	UART_InitTypeDef uart_init;

	__HAL_RCC_GPIOB_CLK_ENABLE(); 				/* enable clock on port B */
	__HAL_RCC_GPIOA_CLK_ENABLE(); 				/* enable clock on port A */
	__HAL_RCC_USART1_CLK_ENABLE();				/* enable clock for UART */

	gpio_init.Pin = LED;						/* Led is on PB.3 */
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP; 	/* Output Push-pull */
	gpio_init.Speed = GPIO_SPEED_MEDIUM;		/* Speed is medium */
	gpio_init.Pull = GPIO_NOPULL;			/* No pull-up needed */
	HAL_GPIO_Init(GPIOB, &gpio_init);		/* init for output */

	gpio_init.Pin = BUTTON;					/* Jumper is on PA.12 */
	gpio_init.Mode = GPIO_MODE_INPUT;		/* Input mode*/
	gpio_init.Speed = GPIO_SPEED_MEDIUM;		/* Medium speed */
	gpio_init.Pull = GPIO_PULLUP;			/* No pullup Resistor */
	HAL_GPIO_Init(GPIOA, &gpio_init);		/* init for input */

	/*Configure uart to 9600 baud 8n1 */
	uart_init.BaudRate = 9600;
	uart_init.WordLength = UART_WORDLENGTH_8B;	/* 8 data bit */
	uart_init.StopBits = UART_STOPBITS_1;		/* 1 stop bit */
	uart_init.Parity = UART_PARITY_NONE; 		/* No parity */
	uart_init.Mode = UART_MODE_TX_RX;			/* receive and transmit mode */
	uart_init.OverSampling = UART_OVERSAMPLING_8;	/* 8x oversampling */
	uart_init.HwFlowCtl = UART_HWCONTROL_NONE;		/* no flow control */
	uart_init.OneBitSampling = UART_ONE_BIT_SAMPLE_ENABLE; /* one sample */

	while(1){

		HAL_GPIO_TogglePin(GPIOB, LED);

		if(HAL_GPIO_ReadPin(GPIOA, BUTTON)){
			intervall = 50000;
		}
		else {
			intervall = 200000;
		}

		for(i = 0; i < intervall; i++){
			asm("nop");
		}
	}
}
