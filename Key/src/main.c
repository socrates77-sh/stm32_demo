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
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);

  board_led_init(LED1); //Init LED port
  board_led_init(LED2);
  board_led_init(LED3);

  delay_10ms(50);

  board_led_ctrl(LED1, OFF); //Light down LED
  board_led_ctrl(LED2, OFF);
  board_led_ctrl(LED3, OFF);

  board_key_init();       //Init key port,TIM3
  board_key_start_scan(); //Start scan

  while (1)
  {
    if (key_down[BUTTON_USER1]) //Check KEY status
    {
      board_led_ctrl(LED1, ON);
      key_down[BUTTON_USER1] = FALSE; //Key status should	clear manually
    }
    else if (key_up[BUTTON_USER1])
    {
      board_led_ctrl(LED1, OFF);
      key_up[BUTTON_USER1] = FALSE;
    }
    if (key_down[BUTTON_USER2])
    {
      board_led_ctrl(LED2, ON);
      key_down[BUTTON_USER2] = FALSE;
    }
    else if (key_up[BUTTON_USER2])
    {
      board_led_ctrl(LED2, OFF);
      key_up[BUTTON_USER2] = FALSE;
    }
    if (key_down[BUTTON_USER3])
    {
      board_led_ctrl(LED3, ON);
      key_down[BUTTON_USER3] = FALSE;
    }
    else if (key_up[BUTTON_USER3])
    {
      board_led_ctrl(LED3, OFF);
      key_up[BUTTON_USER3] = FALSE;
    }
  }
}
