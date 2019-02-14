/* Includes -------------------------------------------------------*/
#include "main.h"
#include "stdio.h"

/* Private typedef ------------------------------------------------*/
/* Private define -------------------------------------------------*/

/* Private macro --------------------------------------------------*/
/* Private functions ----------------------------------------------*/
/* Private variables ----------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
USART_InitTypeDef USART_InitStructure;

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

  int i;
  char str[CHAR_MAX + 1];

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
  board_key_start_scan(); //Start key scan

  //Init LCD controler
  wolf_LCD9341_Init();

  LCD_BACKUP_ENABLE(); //Light up LCD backup LED

  wolf_LCD9341_clear_screen(BLACK); //Clear screen with any color

  // wolf_LCD9341_rect(80, 80, LCD_WIDTH - 80, LCD_HEIGHT - 80, GREEN); //Draw rectangle
  // wolf_LCD9341_line(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1, BRED);      //Draw line
  // wolf_LCD9341_line(0, LCD_HEIGHT - 1, LCD_WIDTH - 1, 0, BRED);
  // wolf_LCD9341_circle(120, 160, 50, YELLOW);                           //Draw circle
  // wolf_LCD9341_fill(100, 100, LCD_WIDTH - 100, LCD_HEIGHT - 100, RED); //Fill rectangle
  // wolf_LCD9341_num(115, 60, 86, 2, COVER);                                 //Draw number
  // wolf_LCD9341_string(85, 240, "SINOMCU", COVER);                          //Draw string
  // wolf_LCD9341_string(85, 240, "zwr1", OVERLAY);                          //Draw string

  POINT_COLOR = CYAN; //Change color of pointer
  // wolf_LCD9341_string(0, 0, "012345678901234567890123456789", COVER);  //Draw string
  // wolf_LCD9341_string(0, 20, "012345678901234567890123456789", COVER); //Draw string

  // sprintf(str, "%d", 10);
  // wolf_LCD9341_string(0, 0, str, COVER);

  for (i = 0; i < 16; i++)
  {
    sprintf(str, "%d", i);
    wolf_LCD9341_string(0, i * LINE_HEIGHT, str, COVER);
    // wolf_LCD9341_string(0, i * 20, "012345678901234567890123456789", COVER); //Draw string
  }

  while (1)
  {
    if (key_down[BUTTON_USER1]) //Check KEY status
    {
      board_led_toggle(LED1);
      key_down[BUTTON_USER1] = FALSE; //Key status should	clear manually
    }
    if (key_down[BUTTON_USER2]) //Check KEY status
    {
      board_led_toggle(LED2);
      key_down[BUTTON_USER2] = FALSE; //Key status should	clear manually
    }
    if (key_down[BUTTON_USER3]) //Check KEY status
    {
      board_led_toggle(LED3);
      key_down[BUTTON_USER3] = FALSE; //Key status should	clear manually
    }
  }
}
