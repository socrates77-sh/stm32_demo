/* Includes -------------------------------------------------------*/
#include "main.h"

/* Private typedef ------------------------------------------------*/
/* Private define -------------------------------------------------*/

/* Private macro --------------------------------------------------*/
/* Private functions ----------------------------------------------*/
/* Private variables ----------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;

int main(void)
{
  /*
	Now system clock have been inited as:
	HCLK      = 48MHz
	PCLC      = 48MHz
	ADCCLK    = 14MHz
	CECCLK    = 32786Hz
	I2C1CLK   = 8MHz
	USART1CLK = 48MHz
	*/

  RCC_ClocksTypeDef RCC_Clocks;

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  // SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 50);

  board_led_init(LED1); //Init LED port
  board_led_init(LED2);
  board_led_init(LED3);

  delay_10ms(50);

  board_led_ctrl(LED1, OFF); //Light down LED
  board_led_ctrl(LED2, ON);
  board_led_ctrl(LED3, OFF);

  while (1)
  {
    delay_10ms(50);
    board_led_toggle(LED1); //Toggle LED
    board_led_toggle(LED2);
    board_led_toggle(LED3);
  }
}

