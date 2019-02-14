/********************************************************************
filename : wolf_buzzer.h
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
contact  : edreamtek@163.com
           edreamtek.taobao.com
********************************************************************/

#ifndef __WOLF_BUZZER_H__
#define __WOLF_BUZZER_H__

#include "stm32f0xx.h"
#include "wolf_typedefine.h"
#include "wolf32f031_board_pinmap.h"
#include "wolf_delay.h"


#define ON					0
#define OFF					1

//BUZZER pin function init.
void board_buzzer_init(void);

//BUZZER control function.
void board_buzzer_ctrl(unsigned char value);

//BUZZER toggle function.
void board_buzzer_toggle(void);

//BUZZER init use timer,PWM output.
void wolf_buzzer_TIM1_init(void);

//BUZZER PWM output test.
void wolf_buzzer_PWM_test(uint8_t freq,uint8_t duty);

//BUZZER PWM output disable
void wolf_buzzer_PWM_disable(void);





#endif

