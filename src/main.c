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

#include <assert.h>

#define LED 	GPIO_PIN_3	/* Led Pin */
#define BUTTON	GPIO_PIN_12	/* Jumper Pin */

#define UART 	0
#define TIMER 	1

uint8_t ledEnable = 0;
unsigned long long int tick = 0;

void UART_Init();
void GPIO_Init();
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);


int main(void){

	int i = 0;
	int intervall = 1000;
	unsigned long long int curtime = tick;
	unsigned long long int prevtime = 0;


	TIM_Base_InitTypeDef tim6_init;
#if UART == 1
	//UART_InitTypeDef uart_init;
#endif

#if UART == 1
	__HAL_RCC_USART1_CLK_ENABLE();				/* enable clock for UART */
#endif


#if UART == 1
	/*Configure uart to 9600 baud 8n1 */
	uart_init.BaudRate = 9600;
	uart_init.WordLength = UART_WORDLENGTH_8B;	/* 8 data bit */
	uart_init.StopBits = UART_STOPBITS_1;		/* 1 stop bit */
	uart_init.Parity = UART_PARITY_NONE; 		/* No parity */
	uart_init.Mode = UART_MODE_TX_RX;			/* receive and transmit mode */
	uart_init.OverSampling = UART_OVERSAMPLING_8;	/* 8x oversampling */
	uart_init.HwFlowCtl = UART_HWCONTROL_NONE;		/* no flow control */
	uart_init.OneBitSampling = UART_ONE_BIT_SAMPLE_ENABLE; /* one sample */
#endif

	GPIO_Init(); /* init the gpios */

	while(1){
		curtime = tick;

		if (curtime - prevtime >= intervall) {
			HAL_GPIO_TogglePin(GPIOB, LED);
			prevtime = curtime;
		}

//
//		if(HAL_GPIO_ReadPin(GPIOA, BUTTON)){
//			intervall = 50000;
//		}
//		else {
//			intervall = 200000;
//		}

//		for(i = 0; i < intervall; i++){
//			asm("nop");
//		}
	}
}

/**
 * initializes the gpio ports and pins
 */
void GPIO_Init(){

	HAL_InitTick(0);
	__HAL_RCC_GPIOB_CLK_ENABLE(); 				/* enable clock on port B */
	__HAL_RCC_GPIOA_CLK_ENABLE(); 				/* enable clock on port A */
	GPIO_InitTypeDef gpio_init;

	gpio_init.Pin = LED;						/* Led is on PB.3 */
	gpio_init.Mode = GPIO_MODE_OUTPUT_PP; 	/* Output Push-pull */
	gpio_init.Speed = GPIO_SPEED_MEDIUM;		/* Speed is medium */
	gpio_init.Pull = GPIO_NOPULL;			/* No pull-up needed */
	HAL_GPIO_Init(GPIOB, &gpio_init);		/* init for output */

	gpio_init.Pin = BUTTON;					/* Jumper is on PA.12 */
	// gpio_init.Mode = GPIO_MODE_INPUT;		/* Input mode*/
	gpio_init.Mode = GPIO_MODE_IT_FALLING;
	gpio_init.Speed = GPIO_SPEED_MEDIUM;		/* Medium speed */
	gpio_init.Pull = GPIO_PULLUP;			/* No pullup Resistor */
	HAL_GPIO_Init(GPIOA, &gpio_init);		/* init for input */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	  if (GPIO_Pin == BUTTON){
		  ledEnable ^= 1;  /* toggle led enable */
	  }
  }

void HAL_SYSTICK_Callback(void){
	tick++;
}

/**
 *
 */
void UART_Init(){

}
