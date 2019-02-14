/********************************************************************
filename : wolf_key.h
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
contact  : dreamwolf66@163.com
           www.zyltek.com
********************************************************************/

#ifndef __WOLF_KEY_H__
#define __WOLF_KEY_H__


#include "stm32f0xx.h"
#include "wolf_typedefine.h"
#include "wolf32f031_board_pinmap.h"


typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_USER1 = 1,
  BUTTON_USER2 = 2,
  BUTTON_USER3 = 3,
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;




#define BUTTONn                          4 /*!< Joystick pins are connected to 
                                                an IO Expander (accessible through 
                                                I2C1 interface) */

/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_AHBPeriph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    EXTI_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_1_IRQn 

/**
 * @brief user push-button
 */
#define USER_BUTTON1_PIN                GPIO_Pin_0
#define USER_BUTTON1_GPIO_PORT          GPIOB
#define USER_BUTTON1_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define USER_BUTTON1_EXTI_LINE          EXTI_Line0
#define USER_BUTTON1_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOB
#define USER_BUTTON1_EXTI_PIN_SOURCE    EXTI_PinSource0
#define USER_BUTTON1_EXTI_IRQn          EXTI0_1_IRQn 


#define USER_BUTTON2_PIN                GPIO_Pin_1
#define USER_BUTTON2_GPIO_PORT          GPIOB
#define USER_BUTTON2_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define USER_BUTTON2_EXTI_LINE          EXTI_Line1
#define USER_BUTTON2_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOB
#define USER_BUTTON2_EXTI_PIN_SOURCE    EXTI_PinSource1
#define USER_BUTTON2_EXTI_IRQn          EXTI0_1_IRQn 

#define USER_BUTTON3_PIN                GPIO_Pin_2
#define USER_BUTTON3_GPIO_PORT          GPIOB
#define USER_BUTTON3_GPIO_CLK           RCC_AHBPeriph_GPIOB
#define USER_BUTTON3_EXTI_LINE          EXTI_Line2
#define USER_BUTTON3_EXTI_PORT_SOURCE   EXTI_PortSourceGPIOB
#define USER_BUTTON3_EXTI_PIN_SOURCE    EXTI_PinSource2
#define USER_BUTTON3_EXTI_IRQn          EXTI2_3_IRQn 

/* key driver module public variable */
/* after key_pushed,key_down,key_up is signed,
   they must cleared by user manually */
extern uint32_t key_pushed;							//if user key is pushed down and after key up this flag will be TRUE
extern uint32_t key_down[BUTTONn];			//the pushed down key's flag will be TRUE
extern uint32_t key_up[BUTTONn];				//the pushed up key's flag will be TRUE
extern uint32_t key_value[BUTTONn];     //store the current key's value

/* key driver module public function */
void board_key_init(void);				//before use key,we should init related function

void board_key_start_scan(void);	//start timer and check key value

void board_key_stop_scan(void);		//stop timer and stop check key value

/* protected function,normally should not be called by user */
void board_key_get_value(void);		//check key value


#endif

