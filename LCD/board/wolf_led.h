/********************************************************************
filename : wolf_led.h
discript : dreamwolf on board led control driver,there are three led
			     on this board contact to PH3,PH4,PH6.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.2.24
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : dreamwolf66@163.com
           www.zyltek.com
********************************************************************/

#ifndef __WOLF_LED_H__
#define __WOLF_LED_H__

#include "stm32f0xx.h"
#include "wolf32f031_board_pinmap.h"


#define ON					0
#define OFF					1

//LED pin function init.
void board_led_init(unsigned char led);

//single LED control function.
void board_led_ctrl(unsigned char led,unsigned char value);

//single LEDs toggle function.
void board_led_toggle(unsigned char led);


#endif

