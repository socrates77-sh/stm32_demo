/********************************************************************
filename : wolf_delay.c
discript : This file offer some delay function use systerm tick.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.3.20
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : edreamtek@163.com
           edreamtek.taobao.com
********************************************************************/

#include "wolf_delay.h"


static __IO uint32_t TimingDelay_basic;


void delay_s(__IO uint32_t nTime)
{
	while(nTime--)
	{
		delay_10ms(100);
	}
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in 10 ms.
  * @retval None
  */
void delay_10ms(__IO uint32_t nTime)
{
  TimingDelay_basic = nTime;

  while(TimingDelay_basic != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay_basic != 0x00)
  { 
    TimingDelay_basic --;
  }
}
