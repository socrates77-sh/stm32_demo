/* Includes -------------------------------------------------------*/
#include "main.h"

/* Private typedef ------------------------------------------------*/
/* Private define -------------------------------------------------*/

/* Private macro --------------------------------------------------*/
/* Private functions ----------------------------------------------*/
/* Private variables ----------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
uint8_t freq, duty;

int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f0xx.c file
     */

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

  board_key_init();       //Init KEY port,TIM3
  board_key_start_scan(); //Start key scan

  wolf_buzzer_TIM1_init(); //Init Buzzer TIM1

  freq = 2;
  duty = 5;
  // wolf_buzzer_PWM_test(freq, duty); //Init buzzer PWM frequency 2,50% duty

  while (1)
  {
    delay_10ms(10);
    if (key_down[BUTTON_USER1])
    {
      freq++; //Frequency up
      freq %= 10;
      wolf_buzzer_PWM_test(freq, duty);
      board_led_ctrl(LED1, ON);
      key_down[BUTTON_USER1] = FALSE;
    }
    else if (key_up[BUTTON_USER1])
    {
      board_led_ctrl(LED1, OFF);
      key_up[BUTTON_USER1] = FALSE;
    }
    if (key_down[BUTTON_USER2])
    {
      duty++; //Duty up
      duty %= 10;
      wolf_buzzer_PWM_test(freq, duty);
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
      wolf_buzzer_PWM_disable(); //Disable buzzer
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