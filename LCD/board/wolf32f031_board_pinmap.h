/********************************************************************
filename : wolf32f031_board_pinmap.h
discript : this file contain pinmap of wolf32f407 board.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.8.9
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : dreamwolf66@163.com
           edreamtek.taobao.com
********************************************************************/

#ifndef __WOLF32F031_BOARD_PINMAP_H__
#define __WOLF32F031_BOARD_PINMAP_H__


/*On blard LED pinmap*/
#define LEDn				3

#define LED1_PIN                         GPIO_Pin_13
#define LED1_GPIO_PORT                   GPIOB
#define LED1_GPIO_CLK                    RCC_AHBPeriph_GPIOB

#define LED2_PIN                         GPIO_Pin_14
#define LED2_GPIO_PORT                   GPIOB
#define LED2_GPIO_CLK                    RCC_AHBPeriph_GPIOB

#define LED3_PIN                         GPIO_Pin_15
#define LED3_GPIO_PORT                   GPIOB
#define LED3_GPIO_CLK                    RCC_AHBPeriph_GPIOB


typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2
} Led_TypeDef;


/*On blard IIC Bus IIC1 pinmap*/
#define I2C1_CLK												RCC_APB1Periph_I2C1
#define I2C1_SCL_PIN                  	GPIO_Pin_6                  /* PB.06 */
#define I2C1_SCL_GPIO_PORT            	GPIOB                       /* GPIOB */
#define I2C1_SCL_GPIO_CLK             	RCC_AHB1Periph_GPIOB
#define I2C1_SCL_SOURCE               	GPIO_PinSource6
#define I2C1_SCL_AF                   	GPIO_AF_I2C1
#define I2C1_SDA_PIN                  	GPIO_Pin_7                  /* PB.07 */
#define I2C1_SDA_GPIO_PORT            	GPIOB                       /* GPIOB */
#define I2C1_SDA_GPIO_CLK             	RCC_AHB1Periph_GPIOB
#define I2C1_SDA_SOURCE               	GPIO_PinSource7
#define I2C1_SDA_AF                   	GPIO_AF_I2C1

/*On blard IIC EEPROM AT24C64 pinmap*/
#define sEE_I2C                          I2C1
#define sEE_I2C_CLK                      RCC_APB1Periph_I2C1
#define sEE_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define sEE_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SCL_SOURCE               GPIO_PinSource6
#define sEE_I2C_SCL_AF                   GPIO_AF_1
#define sEE_I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define sEE_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define sEE_I2C_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define sEE_I2C_SDA_SOURCE               GPIO_PinSource7
#define sEE_I2C_SDA_AF                   GPIO_AF_1
#define sEE_AT24C64

/*On blard IIC accelerometer  MMA7455L pinmap*/
#define MMA7455_I2C                          I2C1
#define MMA7455_I2C_CLK                      RCC_APB1Periph_I2C1
#define MMA7455_I2C_SCL_PIN                  GPIO_Pin_6                  /* PB.06 */
#define MMA7455_I2C_SCL_GPIO_PORT            GPIOB                       /* GPIOB */
#define MMA7455_I2C_SCL_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define MMA7455_I2C_SCL_SOURCE               GPIO_PinSource6
#define MMA7455_I2C_SCL_AF                   GPIO_AF_1
#define MMA7455_I2C_SDA_PIN                  GPIO_Pin_7                  /* PB.07 */
#define MMA7455_I2C_SDA_GPIO_PORT            GPIOB                       /* GPIOB */
#define MMA7455_I2C_SDA_GPIO_CLK             RCC_AHBPeriph_GPIOB
#define MMA7455_I2C_SDA_SOURCE               GPIO_PinSource7
#define MMA7455_I2C_SDA_AF                   GPIO_AF_1

#define MMA7455_CS_PIN                       GPIO_Pin_11									/* PB.11 */
#define MMA7455_CS_GPIO_PORT                 GPIOB
#define MMA7455_CS_GPIO_CLK                  RCC_AHBPeriph_GPIOB




/*On blard SPI LCD/Touch/SD Card pinmap*/
#define LCD_SPI                           SPI1
#define LCD_SPI_CLK                       RCC_APB2Periph_SPI1

#define LCD_SPI_SCK_PIN                   GPIO_Pin_5                  /* PA.05 */
#define LCD_SPI_SCK_GPIO_PORT             GPIOA                       /* GPIOA */
#define LCD_SPI_SCK_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define LCD_SPI_SCK_SOURCE                GPIO_PinSource5
#define LCD_SPI_SCK_AF                    GPIO_AF_0

#define LCD_SPI_MISO_PIN                 GPIO_Pin_6                  /* PA.06 */
#define LCD_SPI_MISO_GPIO_PORT           GPIOA                       /* GPIOA */
#define LCD_SPI_MISO_GPIO_CLK            RCC_AHBPeriph_GPIOA
#define LCD_SPI_MISO_SOURCE              GPIO_PinSource6
#define LCD_SPI_MISO_AF                  GPIO_AF_0

#define LCD_SPI_MOSI_PIN                  GPIO_Pin_7                  /* PA.07 */
#define LCD_SPI_MOSI_GPIO_PORT            GPIOA                       /* GPIOA */
#define LCD_SPI_MOSI_GPIO_CLK             RCC_AHBPeriph_GPIOA
#define LCD_SPI_MOSI_SOURCE               GPIO_PinSource7
#define LCD_SPI_MOSI_AF                   GPIO_AF_0

#define LCD_CS_PIN                        GPIO_Pin_4                  /* PA.04 */
#define LCD_CS_GPIO_PORT                  GPIOA                       /* GPIOA */
#define LCD_CS_GPIO_CLK                   RCC_AHBPeriph_GPIOA

#define LCD_RESET_PIN                     GPIO_Pin_2                  /* PA.02 */
#define LCD_RESET_GPIO_PORT               GPIOA                       /* GPIOA */
#define LCD_RESET_GPIO_CLK                RCC_AHBPeriph_GPIOA

#define LCD_C_D_PIN                       GPIO_Pin_3                  /* PA.03 */
#define LCD_C_D_GPIO_PORT                 GPIOA                       /* GPIOA */
#define LCD_C_D_GPIO_CLK                  RCC_AHBPeriph_GPIOA

#define LCD_BACKUP_PIN                    GPIO_Pin_12                 /* PB.12 */
#define LCD_BACKUP_GPIO_PORT              GPIOB                       /* GPIOB */
#define LCD_BACKUP_GPIO_CLK               RCC_AHBPeriph_GPIOB

/*On blard BUZZER pinmap*/
#define BUZZER_PIN												GPIO_Pin_8									/* PA.08 */
#define BUZZER_PORT												GPIOA												/* GPIOA */
#define BUZZER_CLK												RCC_AHBPeriph_GPIOA


#endif

