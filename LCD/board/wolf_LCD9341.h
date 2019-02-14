/********************************************************************
filename : wolf_LCD9341.h
discript : dreamwolf LCD control driver use SPI,the LCD controller is
					 ILI9341V,the pinmap like as bellow:
					 TFT_CS      -> PA4,
					 TFT_RST     -> PA2,
					 TFT_D/C     -> PA3,
					 TFT_MOSI    -> PA7,
					 TFT_MISO    -> PA6,
					 TFT_SCK     -> PA5,
					 TFT_LED     -> PB12.
version  : V0.0
editor   : Icy - dreamwolf
time     : 2014.8.17
statement: This file is modified by dreamwolf under LGPL,you could use 
           it free.We cann't ensure there is no error in this file,and
				   if you detect an error please contact us freely,it is so a-
					 ppreciate for your help to improve our code that could help 
					 more people to use it safty.
contact  : edreamtek@163.com
           edreamtek.taobao.com
********************************************************************/

#ifndef __WOLF_LCD9341_H__
#define __WOLF_LCD9341_H__

#include "stm32f0xx.h"
#include "wolf_typedefine.h"
#include "wolf32f031_board_pinmap.h"
#include "wolf_delay.h"

#include "fonts.h"
#include "font.h"
 
#define WHITE         	 	0xFFFF
#define BLACK         	 	0x0000	  
#define BLUE         	 		0x001F  
#define BRED             	0XF81F
#define GRED 			 				0XFFE0
#define GBLUE			 				0X07FF
#define RED           	 	0xF800
#define MAGENTA       	 	0xF81F
#define GREEN         	 	0x07E0
#define CYAN          	 	0x7FFF
#define YELLOW        	 	0xFFE0
#define BROWN 			 			0XBC40 
#define BRRED 			 			0XFC07 
#define GRAY  			 			0X8430 
#define DARKBLUE      	 	0X01CF	
#define LIGHTBLUE      	 	0X7D7C	
#define GRAYBLUE       	 	0X5458 


#define wolf_LCD_reg	*(__IO uint16_t *)((uint32_t)0x68000000)	//LCD cmd address
#define wolf_LCD_data	*(__IO uint16_t *)((uint32_t)0x68000002)	//LCD data address


 //define resolution	
#define LCD_WIDTH	  240
#define LCD_HEIGHT	320

#define SPI_DUMMY_BYTE   0xFF



extern uint16_t BACK_COLOR, POINT_COLOR;   //back color,brush color

#define 	LCD_CS_HIGH()			LCD_CS_GPIO_PORT->BSRR = LCD_CS_PIN  
#define 	LCD_CS_LOW()			LCD_CS_GPIO_PORT->BRR = LCD_CS_PIN  

#define 	LCD_RESET_HIGH()	LCD_RESET_GPIO_PORT->BSRR = LCD_RESET_PIN  
#define 	LCD_RESET_LOW()		LCD_RESET_GPIO_PORT->BRR = LCD_RESET_PIN  

#define 	LCD_C_D_HIGH()		LCD_C_D_GPIO_PORT->BSRR = LCD_C_D_PIN  
#define 	LCD_C_D_LOW()			LCD_C_D_GPIO_PORT->BRR = LCD_C_D_PIN  

#define 	LCD_BACKUP_DISABLE()	LCD_BACKUP_GPIO_PORT->BSRR = LCD_BACKUP_PIN  		//High
#define 	LCD_BACKUP_ENABLE()		LCD_BACKUP_GPIO_PORT->BRR = LCD_BACKUP_PIN  		//Low

#define 	LCD_SCK_HIGH()		LCD_SPI_SCK_GPIO_PORT->BSRR = LCD_SPI_SCK_PIN  
#define 	LCD_SCK_LOW()			LCD_SPI_SCK_GPIO_PORT->BRR = LCD_SPI_SCK_PIN  

#define 	LCD_MOSI_HIGH()		LCD_SPI_MOSI_GPIO_PORT->BSRR = LCD_SPI_MOSI_PIN 
#define 	LCD_MOSI_LOW()		LCD_SPI_MOSI_GPIO_PORT->BRR = LCD_SPI_MOSI_PIN  

#define 	LCD_MISO()				GPIO_ReadInputDataBit(LCD_SPI_MISO_GPIO_PORT, LCD_SPI_MISO_PIN)




extern sFONT Efont;

void wolf_LCD9341_Init(void);

void wolf_LCD9341_clear_screen(uint16_t color);

void LCD_Font(sFONT *font);

void LCD_Cursor(uint16_t Xpos, uint16_t Ypos);

void LCD_Window(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width);

void wolf_LCD9341_string(uint16_t xpos, uint16_t ypos, char *ptr, uint8_t mode);

void wolf_LCD_write_reg(uint16_t Reg, uint16_t Value);

void Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);



void wolf_LCD_GPIO_conf(void);

void wolf_LCD_FSMC_conf(void);

void wolf_LCD9341_reset(void);

void wolf_LCD9341_point(uint16_t xpos, uint16_t ypos,uint16_t color);

void wolf_LCD9341_fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color);

void wolf_LCD9341_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void wolf_LCD9341_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

void wolf_LCD9341_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t color);

void wolf_LCD9341_char(uint16_t x,uint16_t y,uint8_t num,uint8_t mode);

void wolf_LCD9341_num(uint16_t x, uint16_t y, int32_t num, uint8_t len, uint8_t mode);

void wolf_LCD9341_pic(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint8_t *pdat);


void wolf_spi_write(uint8_t Data);



#endif

