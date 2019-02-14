/********************************************************************
filename : wolf_key.c
discript : dreamwolf on board led control driver,there are three user 
					 keys on this board connect to PI8,PI9,PI10.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.2.27
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : edreamtek@163.com
           edreamtek.taobao.com
********************************************************************/

#include "wolf_key.h"

/* key driver module public variable */
uint32_t key_pushed;						//if user key is pushed down and after key up this flag will be TRUE
uint32_t key_down[BUTTONn];			//the pushed down key's flag will be TRUE
uint32_t key_up[BUTTONn];				//the pushed up key's flag will be TRUE
uint32_t key_value[BUTTONn];    //store the current key's value


/* key driver module private variable */
uint32_t key_old_value[BUTTONn];    //store the old key's value befor read new

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t PrescalerValue = 0;

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT, USER_BUTTON1_GPIO_PORT, USER_BUTTON2_GPIO_PORT,
																			USER_BUTTON3_GPIO_PORT}; 

const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN, USER_BUTTON1_PIN, USER_BUTTON2_PIN, USER_BUTTON3_PIN}; 

const uint32_t BUTTON_CLK[BUTTONn] = {WAKEUP_BUTTON_GPIO_CLK, USER_BUTTON1_GPIO_CLK, USER_BUTTON2_GPIO_CLK,
                                      USER_BUTTON3_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {WAKEUP_BUTTON_EXTI_LINE,
                                            USER_BUTTON1_EXTI_LINE, 
                                            USER_BUTTON2_EXTI_LINE,
																						USER_BUTTON3_EXTI_LINE};

const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {WAKEUP_BUTTON_EXTI_PORT_SOURCE,
                                              USER_BUTTON1_EXTI_PORT_SOURCE,
																							USER_BUTTON2_EXTI_PORT_SOURCE,
                                              USER_BUTTON3_EXTI_PORT_SOURCE};
								 
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {WAKEUP_BUTTON_EXTI_PIN_SOURCE,
                                             USER_BUTTON1_EXTI_PIN_SOURCE, 
																						 USER_BUTTON2_EXTI_PIN_SOURCE,
                                             USER_BUTTON3_EXTI_PIN_SOURCE}; 


/* key driver module private function */
void TIM_Config(void);

void board_tim_init(void);

void board_key_gpio_init(Button_TypeDef Button);

void board_key_get_gpio_state(Button_TypeDef Button);







/********************************************************************
function: board_key_init()
discript: init key module function use timer3 to scan key value
entrance: none
return  : none
time    : 2014.2.28
other   : none
********************************************************************/
void board_key_init(void)
{
	uint32_t i;
	key_pushed = 0x0;
	
	for(i=0;i<BUTTONn;i++)
	{
		key_down[i] = 0;			//the pushed down key's flag will be TRUE
		key_up[i] = 0;				//the pushed up key's flag will be TRUE
		key_value[i] = 1;    	//store the current key's value
	}
	/* init GPIO pin connected to key */
	board_key_gpio_init(BUTTON_USER1);
	board_key_gpio_init(BUTTON_USER2);
	board_key_gpio_init(BUTTON_USER3);
	
	/* init timer to scan key value */
	board_tim_init();
}

/********************************************************************
function: board_key_start_scan()
discript: start to scan key value via start timer
entrance: none
return  : none
time    : 2014.2.28
other   : none
********************************************************************/
void board_key_start_scan(void)
{
  /* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);
}

/********************************************************************
function: board_key_stop_scan()
discript: start to scan key value via stop timer
entrance: none
return  : none
time    : 2014.2.28
other   : none
********************************************************************/
void board_key_stop_scan(void)
{
  /* TIM3 disable counter */
	TIM_Cmd(TIM3, DISABLE);
}


/********************************************************************
function: board_key_get_value()
discript: get key value and caculate up,down state
entrance: none
return  : none
time    : 2014.2.28
other   : none
********************************************************************/
void board_key_get_value(void)
{
	uint32_t i,temp;
	Button_TypeDef Button;
	
	for(i=1;i<BUTTONn;i++)
	{
		Button = (Button_TypeDef)i;
		key_old_value[Button] = key_value[Button];
		board_key_get_gpio_state(Button); 
		temp = key_old_value[Button] ^ key_value[Button];
		if(temp)
		{
			if(key_value[Button])
			{
				key_up[Button] = TRUE;
				key_pushed = TRUE;
			}
			else
			{
				key_down[Button] = TRUE;
			}
		}
	}
}

/********************************************************************
function: board_key_gpio_init()
discript: init key GPIO as no pull input mode
entrance: none
return  : none
time    : 2014.2.28
other   : none
********************************************************************/
void board_key_gpio_init(Button_TypeDef Button)
{
  GPIO_InitTypeDef GPIO_InitStructure;


  /* Enable the BUTTON Clock */
  RCC_AHBPeriphClockCmd(BUTTON_CLK[Button], ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);
}

/********************************************************************
function: board_key_get_gpio_state()
discript: returns the selected Button state.
entrance: the key whitch will be checked
return  : value of key GPIO pin
time    : 2014.2.28
other   : none
********************************************************************/
void board_key_get_gpio_state(Button_TypeDef Button)
{
  key_value[Button] = GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/********************************************************************
function: board_tim_init()
discript: init timer3 as interrupt mode,sampling interval is 10ms
entrance: none
return  : none
time    : 2014.2.28
other   : none
********************************************************************/
void board_tim_init(void)
{
  /* TIM Configuration */
  TIM_Config();
  
  /* -----------------------------------------------------------------------
    In this example TIM3 input clock (TIM3CLK) is set to 2 * APB1 clock (PCLK1), 
    since APB1 prescaler is different from 1.   
      TIM3CLK = 2 * PCLK1  
      PCLK1 = HCLK / 4 
      => TIM3CLK = HCLK / 2 = SystemCoreClock /2
          
    To get TIM3 counter clock at 6 MHz, the prescaler is computed as follows:
       Prescaler = (TIM3CLK / TIM3 counter clock) - 1
       Prescaler = ((SystemCoreClock /2) /6 MHz) - 1
                                              
    Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f4xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect.    
  ----------------------------------------------------------------------- */   

  /* Compute the prescaler value */
  PrescalerValue = (uint16_t) ((SystemCoreClock / 2) / 6000000) - 1;

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 60000;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Prescaler configuration */
  TIM_PrescalerConfig(TIM3, PrescalerValue, TIM_PSCReloadMode_Immediate);
   
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}


/********************************************************************
function: TIM_Config
discript: Configure the TIM IRQ Handler.
entrance: none
return  : none
time    : 2014.2.28
other   : IRQ Handler function is in stm32f4xx_it.c
********************************************************************/
void TIM_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


