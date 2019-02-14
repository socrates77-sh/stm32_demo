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

  uint32_t i;
  RCC_ClocksTypeDef RCC_Clocks;

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  // SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 50);

  board_led_init(LED1); //Init LED port
  board_led_init(LED2);
  board_led_init(LED3);

  // RCC_HCLKConfig(RCC_SYSCLK_Div2);

  delay_10ms(50);

  board_led_ctrl(LED1, OFF); //Light down LED
  board_led_ctrl(LED2, OFF);
  board_led_ctrl(LED3, OFF);

  i = 0;

  while (1)
  {
    delay_10ms(50);

    if (i == 0)
    {
      board_led_ctrl(LED1, ON);
      board_led_ctrl(LED2, OFF);
      board_led_ctrl(LED3, OFF);
      i++;
    }
    else if (i == 1)
    {
      board_led_ctrl(LED1, OFF);
      board_led_ctrl(LED2, ON);
      board_led_ctrl(LED3, OFF);
      i++;
    }
    else
    {
      board_led_ctrl(LED1, OFF);
      board_led_ctrl(LED2, OFF);
      board_led_ctrl(LED3, ON);
      i = 0;
    }
  }
}
