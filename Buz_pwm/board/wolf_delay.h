/********************************************************************
filename : wolf_delay.h
discript : This file offer some delay function use systerm tick.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.3.20
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : dreamwolf66@163.com
           www.zyltek.com
********************************************************************/

#ifndef __WOLF_DELAY_H__
#define __WOLF_DELAY_H__

#include "stm32f0xx.h"
#include "wolf_typedefine.h"

/*-------------------------------------------------------*/
//public function
void delay_10ms(__IO uint32_t nTime);

void delay_s(__IO uint32_t nTime);


/*-------------------------------------------------------*/
//private function
void TimingDelay_Decrement(void);


#endif

