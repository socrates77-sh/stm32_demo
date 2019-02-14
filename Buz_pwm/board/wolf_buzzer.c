/********************************************************************
filename : wolf_buzzer.c
discript : This file offer buzzer option function.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.5.5
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : edreamtek@163.com
           edreamtek.taobao.com
********************************************************************/

#include "wolf_buzzer.h"

TIM_TimeBaseInitTypeDef  TIM1_TimeBaseStructure;
TIM_OCInitTypeDef  TIM1_OCInitStructure;
uint16_t TimerPeriod = 0;
uint16_t Channel1Pulse = 0, Channel2Pulse = 0, Channel3Pulse = 0, Channel4Pulse = 0;
/* Private function prototypes -----------------------------------------------*/
void TIM1_Config(void);


/********************************************************************
function: board_buzzer_init
discript: BUZZER pin function init.
entrance: none
return  : none
time    : 2014.5.5
other   : none
********************************************************************/
void board_buzzer_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the BUZZER_CLK Clock */
  RCC_AHBPeriphClockCmd(BUZZER_CLK, ENABLE);


  /* Configure the BUZZER pin */
  GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(BUZZER_PORT, &GPIO_InitStructure);
	
	board_buzzer_ctrl(OFF);
}

/********************************************************************
function: board_buzzer_ctrl
discript: buzzer control function.
entrance: value(true,false):buzzer status
return  : none
time    : 2014.5.5
other   : could control buzzer.
********************************************************************/
void board_buzzer_ctrl(unsigned char value)
{
	if(value)
	{
	  BUZZER_PORT->BSRR = BUZZER_PIN;
	}else
	{
	  BUZZER_PORT->BRR = BUZZER_PIN;  
	}
}

/********************************************************************
function: board_buzzer_toggle
discript: single toggle the buzzer
entrance: value(0-2)
return  : none
time    : 2014.2.24
other   : could toggle the buzzer. 
********************************************************************/
void board_buzzer_toggle(void)
{
  BUZZER_PORT->ODR ^= BUZZER_PIN;
}

/********************************************************************
function: TIM1_Config(void)
discript: single toggle the buzzer
entrance: value(0-2)
return  : none
time    : 2014.2.24
other   : could toggle the buzzer. 
********************************************************************/
void TIM1_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* GPIOA Clocks enable */
  RCC_AHBPeriphClockCmd( RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* GPIOA Configuration: Channel 1 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = BUZZER_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
}


void wolf_buzzer_TIM1_init(void)
{
	TIM1_Config();

  /* TIM1 Configuration ---------------------------------------------------
   Generate PWM signals with duty cycles:
   TIM1 input clock (TIM1CLK) is set to APB2 clock (PCLK2)    
    => TIM1CLK = PCLK2/4800 = SystemCoreClock/4800
   TIM1CLK = SystemCoreClock/4800, Prescaler = 4800, TIM1 counter clock = SystemCoreClock/4800
   SystemCoreClock is set to 48 MHz for STM32F0xx devices,TIM1CLK=10kHz
   
   The objective is to generate PWM signal at 1 Hz:
     - TIM1_Period = (TIM1CLK / 1) - 1
   The channel 1 and channel 1N duty cycle is set to 50%
   The Timer pulse is calculated as follows:
     - ChannelxPulse = DutyCycle * (TIM1_Period - 1) / 100
   
   Note: 
    SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
    Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
    function to update SystemCoreClock variable value. Otherwise, any configuration
    based on this variable will be incorrect. 
  ----------------------------------------------------------------------- */
  /* Compute the value to be set in ARR regiter to generate signal frequency at 10 hz */
  TimerPeriod = (SystemCoreClock/4800/ 10 ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  Channel1Pulse = (uint16_t) (((uint32_t) 5 * (TimerPeriod - 1)) / 10);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
  
  /* Time Base configuration */
  TIM1_TimeBaseStructure.TIM_Prescaler = 4800;
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM1_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM1_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseStructure);

  /* Channel 1 Configuration in PWM mode */
  TIM1_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM1_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM1_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
  TIM1_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM1_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

  TIM1_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM1, &TIM1_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);

}

void wolf_buzzer_PWM_test(uint8_t freq,uint8_t duty)
{
  /* Compute the value to be set in ARR regiter to generate signal frequency at 17.57 Khz */
  TimerPeriod = (SystemCoreClock/4800/ freq ) - 1;
  /* Compute CCR1 value to generate a duty cycle at 50% for channel 1 */
  Channel1Pulse = (uint16_t) (((uint32_t) duty * (TimerPeriod - 1)) / 10);
	
  TIM1_TimeBaseStructure.TIM_Period = TimerPeriod;
	TIM_TimeBaseInit(TIM1, &TIM1_TimeBaseStructure);

	
	TIM1_OCInitStructure.TIM_Pulse = Channel1Pulse;
  TIM_OC1Init(TIM1, &TIM1_OCInitStructure);

	/* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

}

void wolf_buzzer_PWM_disable(void)
{
	/* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, DISABLE);
}


