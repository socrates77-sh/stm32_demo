/********************************************************************
filename : wolf_led.c
discript : dreamwolf on board led control driver,there are three led
			     on this board connect to PH3,PH4,PH6.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.8.10
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : edreamtek@163.com
           edreamtek.taobao.com
********************************************************************/


#include "wolf_led.h"


GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};




/********************************************************************
function: board_led_init
discript: LED pin function init.
entrance: led(0-2):init givern led control pin.
return  : none
time    : 2014.8.10
other   : none
********************************************************************/
void board_led_init(unsigned char led)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO_LED Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[led], ENABLE);			//Enable GPIO clock

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIO_PORT[led], &GPIO_InitStructure);		//Config GPIO
}

/********************************************************************
function: board_led_ctrl
discript: single LED control function.
entrance: led(0-2):led position
          value(true,false):led status
return  : none
time    : 2014.8.10
other   : could control led one by one.
********************************************************************/
void board_led_ctrl(unsigned char led,unsigned char value)
{
	if(value)		//Value is TRUE,light up LED.
	{
		  GPIO_PORT[led]->BSRR = GPIO_PIN[led];
	}
	else				//Value is FALSE,light down LED.
	{
		  GPIO_PORT[led]->BRR = GPIO_PIN[led];
	}
}

/********************************************************************
function: board_led_toggle
discript: single toggle the led
entrance: value(0-2)
return  : none
time    : 2014.8.10
other   : could toggle the led one by one. 
********************************************************************/
void board_led_toggle(unsigned char led)
{
	  GPIO_PORT[led]->ODR ^= GPIO_PIN[led];
}



