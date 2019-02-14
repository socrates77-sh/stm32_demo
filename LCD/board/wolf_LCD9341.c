/********************************************************************
filename : wolf_LCD9341.c
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

#include "wolf_LCD9341.h"



uint16_t BACK_COLOR, POINT_COLOR;   //back color,brush color

sFONT Efont;

	

/********************************************************************
function: wolf_LCD_GPIO_conf(void)
discript: LCD port init
entrance: none
return  : none
other   : none
********************************************************************/
void wolf_LCD_GPIO_conf(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStruct;

  /* LCD_SPI_CS_GPIO, LCD_SPI_MOSI_GPIO, LCD_SPI_MISO_GPIO, LCD_SPI_DETECT_GPIO 
       and LCD_SPI_SCK_GPIO Periph clock enable */
  RCC_AHBPeriphClockCmd(LCD_CS_GPIO_CLK | LCD_SPI_MOSI_GPIO_CLK | LCD_SPI_MISO_GPIO_CLK |
                        LCD_SPI_SCK_GPIO_CLK | LCD_RESET_GPIO_CLK | LCD_C_D_GPIO_CLK |
												LCD_BACKUP_GPIO_CLK, ENABLE);
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); 

  /*!< Configure LCD_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = LCD_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; 
  GPIO_Init(LCD_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure LCD_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = LCD_SPI_MISO_PIN;
  GPIO_Init(LCD_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure LCD_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin =LCD_SPI_MOSI_PIN;
  GPIO_Init(LCD_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
  
  /* Connect PXx to LCD_SPI_SCK */
  GPIO_PinAFConfig(LCD_SPI_SCK_GPIO_PORT, LCD_SPI_SCK_SOURCE, LCD_SPI_SCK_AF);

  /* Connect PXx to LCD_SPI_MISO */
  GPIO_PinAFConfig(LCD_SPI_MISO_GPIO_PORT, LCD_SPI_MISO_SOURCE, LCD_SPI_MISO_AF); 

  /* Connect PXx to LCD_SPI_MOSI */
  GPIO_PinAFConfig(LCD_SPI_MOSI_GPIO_PORT, LCD_SPI_MOSI_SOURCE, LCD_SPI_MOSI_AF);
	
	 
  /*!< LCD_SPI Config */
  SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial = 7;
  SPI_Init(SPI1, &SPI_InitStruct);
  SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);
  SPI_Cmd(SPI1, ENABLE); /*!< LCD_SPI enable */


	/* Configure LCD_SPI_CS_PIN pin: SD Card CS pin */
  GPIO_InitStructure.GPIO_Pin = LCD_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);
	
	/* Configure LCD_SPI_RESET_PIN pin: LCD RESET pin */
  GPIO_InitStructure.GPIO_Pin = LCD_RESET_PIN;
  GPIO_Init(LCD_RESET_GPIO_PORT, &GPIO_InitStructure);

	/* Configure LCD_SPI_C_D_PIN pin: LCD C/D pin */
  GPIO_InitStructure.GPIO_Pin = LCD_C_D_PIN;
  GPIO_Init(LCD_C_D_GPIO_PORT, &GPIO_InitStructure);

	/* Configure LCD_SPI_BACKUP_PIN pin: LCD Backup pin */
  GPIO_InitStructure.GPIO_Pin = LCD_BACKUP_PIN;
  GPIO_Init(LCD_BACKUP_GPIO_PORT, &GPIO_InitStructure);
	
	
	LCD_CS_HIGH();
	LCD_SCK_HIGH();
	LCD_BACKUP_DISABLE();

}


/********************************************************************
function: wolf_LCD9341_reset(void)
discript: LCD hardware reset
entrance: none
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_reset(void)
{	
	LCD_RESET_LOW();
	delay_10ms(1);
	LCD_RESET_HIGH();
}

/********************************************************************
function: wolf_spi_write(uint8_t data)
discript: Write data to LCD
entrance: none
return  : none
other   : Do not read data from SPI interface,if need add the code 
					deleted below.
********************************************************************/
void wolf_spi_write(uint8_t data)
{  
  /* Wait until the transmit buffer is empty */ 
  while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_TXE) != SET)
  {
  }  
  /* Send the byte */
  SPI_SendData8(LCD_SPI, data);
  
  /* Wait to receive a byte */ 
 // while(SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) != SET)
 // {
 // }
  /* Return the byte read from the SPI bus */    
 // tmp = SPI_ReceiveData8(LCD_SPI);

  /* Return read Data */
  //return tmp;
}


/********************************************************************
function: wolf_LCD9341_write_cmd(uint8_t cmd)
discript: Write command to LCD
entrance: cmd
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_write_dat8(uint8_t dat)
{
	LCD_C_D_HIGH();
	wolf_spi_write(dat);
}

void wolf_LCD9341_write_dat16(uint16_t dat)
{
	LCD_C_D_HIGH();
	wolf_spi_write((uint8_t)(0xFF&(dat>>8)));
	wolf_spi_write((uint8_t)(0xFF&(dat)));
}

void wolf_LCD9341_write_reg(uint8_t reg)
{
	LCD_C_D_LOW();
	wolf_spi_write(reg);
}

void wolf_LCD9341_write_reg_dat16(uint8_t reg,uint16_t dat)
{
	wolf_LCD9341_write_reg(reg);
	wolf_LCD9341_write_dat16(dat);
}




/********************************************************************
function: wolf_LCD9341_Init(void)
discript: Init LCD controler
entrance: none
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_Init(void)
{ 
	BACK_COLOR= BLACK;
	POINT_COLOR=RED;
	Efont.Width = 8;
	
	wolf_LCD_GPIO_conf();
	wolf_LCD9341_reset();
	
  delay_10ms(1); 
	

	LCD_CS_LOW();
  delay_10ms(1); 

	wolf_LCD9341_write_reg(0xCB);
	wolf_LCD9341_write_dat8(0x39);
	wolf_LCD9341_write_dat8(0x2C);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x34);
	wolf_LCD9341_write_dat8(0x02);
			

	wolf_LCD9341_write_reg(0xCF);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0xC1);
	wolf_LCD9341_write_dat8(0x30);
	

	wolf_LCD9341_write_reg(0xE8);
	wolf_LCD9341_write_dat8(0x85);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x78);


	wolf_LCD9341_write_reg(0xEA);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x00);


	wolf_LCD9341_write_reg(0xED);
	wolf_LCD9341_write_dat8(0x64);
	wolf_LCD9341_write_dat8(0x03);
	wolf_LCD9341_write_dat8(0x12);
	wolf_LCD9341_write_dat8(0x81);


	wolf_LCD9341_write_reg(0xF7);
	wolf_LCD9341_write_dat8(0x20);


	wolf_LCD9341_write_reg(0xC0);
	wolf_LCD9341_write_dat8(0x23);
	

	wolf_LCD9341_write_reg(0xC1);
	wolf_LCD9341_write_dat8(0x10);
	

	wolf_LCD9341_write_reg(0xC5);
	wolf_LCD9341_write_dat8(0x3E);
	wolf_LCD9341_write_dat8(0x28);
	

	wolf_LCD9341_write_reg(0xC7);
	wolf_LCD9341_write_dat8(0x86);


	wolf_LCD9341_write_reg(0x36);
	wolf_LCD9341_write_dat8(0x48);
	

	wolf_LCD9341_write_reg(0x3A);
	wolf_LCD9341_write_dat8(0x55);


	wolf_LCD9341_write_reg(0xB1);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x18);


	wolf_LCD9341_write_reg(0xB6);
	wolf_LCD9341_write_dat8(0x08);
	wolf_LCD9341_write_dat8(0x82);
	wolf_LCD9341_write_dat8(0x27);
	

	wolf_LCD9341_write_reg(0xF2);
	wolf_LCD9341_write_dat8(0x00);


	wolf_LCD9341_write_reg(0x26);
	wolf_LCD9341_write_dat8(0x01);


	wolf_LCD9341_write_reg(0xE0);
	wolf_LCD9341_write_dat8(0x0F);
	wolf_LCD9341_write_dat8(0x31);
	wolf_LCD9341_write_dat8(0x2B);
	wolf_LCD9341_write_dat8(0x0C);
	wolf_LCD9341_write_dat8(0x0E);
	wolf_LCD9341_write_dat8(0x08);
	wolf_LCD9341_write_dat8(0x4E);
	wolf_LCD9341_write_dat8(0xF1);
	wolf_LCD9341_write_dat8(0x37);
	wolf_LCD9341_write_dat8(0x07);
	wolf_LCD9341_write_dat8(0x10);
	wolf_LCD9341_write_dat8(0x03);
	wolf_LCD9341_write_dat8(0x0E);
	wolf_LCD9341_write_dat8(0x09);
	wolf_LCD9341_write_dat8(0x00);


	wolf_LCD9341_write_reg(0xE1);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x0E);
	wolf_LCD9341_write_dat8(0x14);
	wolf_LCD9341_write_dat8(0x03);
	wolf_LCD9341_write_dat8(0x11);
	wolf_LCD9341_write_dat8(0x07);
	wolf_LCD9341_write_dat8(0x31);
	wolf_LCD9341_write_dat8(0xC1);
	wolf_LCD9341_write_dat8(0x48);
	wolf_LCD9341_write_dat8(0x08);
	wolf_LCD9341_write_dat8(0x0F);
	wolf_LCD9341_write_dat8(0x0C);
	wolf_LCD9341_write_dat8(0x31);
	wolf_LCD9341_write_dat8(0x36);
	wolf_LCD9341_write_dat8(0x0F);


	wolf_LCD9341_write_reg(0x2A);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0xEF);


	wolf_LCD9341_write_reg(0x2B);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x00);
	wolf_LCD9341_write_dat8(0x01);
	wolf_LCD9341_write_dat8(0x3F);


	wolf_LCD9341_write_reg(0x11);
	

	wolf_LCD9341_write_reg(0x29);
	wolf_LCD9341_write_reg(0x2C);

  delay_10ms(1); 

	wolf_LCD9341_clear_screen(BLUE);
}


/********************************************************************
function: LCD_Font(sFONT *font)
discript: Set display font
entrance: none
return  : none
other   : none
********************************************************************/
void LCD_Font(sFONT *font)
{
  	Efont= *font;
}

/********************************************************************
function: LCD_Cursor(uint16_t Xpos, uint16_t Ypos)
discript: Write LCD cursor
entrance: none
return  : none
other   : none
********************************************************************/
void LCD_Cursor(uint16_t Xpos, uint16_t Ypos)
{
  	wolf_LCD9341_write_reg_dat16(0x20, Xpos);
  	wolf_LCD9341_write_reg_dat16(0x21, Ypos);
}

/********************************************************************
function: LCD_Window(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width)
discript: Set window
entrance: Xpos,Ypos,Height,Width
return  : none
other   : Make sure in the range of LCD display area 
********************************************************************/
void LCD_Window(uint16_t Xpos, uint16_t Ypos, uint16_t Height, uint16_t Width)
{
  	if(Xpos>=Height)wolf_LCD9341_write_reg_dat16(0x50,(Xpos-Height+1));
  	else wolf_LCD9341_write_reg_dat16(0x50,0);
  	wolf_LCD9341_write_reg_dat16(0x51,Xpos);
  	if(Ypos>=Width)wolf_LCD9341_write_reg_dat16(0x52,(Ypos-Width+1)); 
  	else wolf_LCD9341_write_reg_dat16(0x52,0);
  	wolf_LCD9341_write_reg_dat16(0x53,Ypos);
  	LCD_Cursor(Xpos,Ypos);
}



/********************************************************************
function: wolf_LCD9341_clear_screen(uint16_t color)
discript: Clear screen with given color
entrance: color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_clear_screen(uint16_t color)
{
	uint16_t i,j;
	
	Address_set(0,0,LCD_WIDTH-1,LCD_HEIGHT-1);
	for(i=0;i<LCD_WIDTH;i++)
	{
		for (j=0;j<LCD_HEIGHT;j++)
	  {
			wolf_LCD9341_write_dat16(color);
	  }
	}
}

/********************************************************************
function: Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
discript: set fill area
entrance: start point address stop point address
return  : none
other   : none
********************************************************************/
void Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{ 
	wolf_LCD9341_write_reg(0x2A);
	wolf_LCD9341_write_dat8(x1>>8);
	wolf_LCD9341_write_dat8(x1&0x00FF);
	wolf_LCD9341_write_dat8(x2>>8);
	wolf_LCD9341_write_dat8(x2&0x00FF);

	wolf_LCD9341_write_reg(0x2B);
	wolf_LCD9341_write_dat8(y1>>8);
	wolf_LCD9341_write_dat8(y1&0x00FF);
	wolf_LCD9341_write_dat8(y2>>8);
	wolf_LCD9341_write_dat8(y2&0x00FF);

	wolf_LCD9341_write_reg(0x2C);
}

/********************************************************************
function: wolf_LCD9341_point(uint16_t xpos, uint16_t ypos,uint16_t color)
discript: Draw one pixel
entrance: Position,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_point(uint16_t xpos, uint16_t ypos,uint16_t color)
{
	Address_set(xpos,ypos,xpos,ypos);		//set cursor position
	wolf_LCD9341_write_dat16(color); 	    
}

/********************************************************************
function: wolf_LCD9341_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
discript: Draw one line
entrance: Start and stop address,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; 		//caculate delta value
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; 					//set direction 
	else if(delta_x==0)incx=0;		//vertical line
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;		//horizontal line
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //set basic increase axis
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )		//draw line
	{  
		wolf_LCD9341_point(uRow,uCol,color);		//draw one pixel	 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}

/********************************************************************
function: wolf_LCD9341_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
discript: Draw a rectangle
entrance: start and stop position,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
	wolf_LCD9341_line(x1,y1,x2,y1,color);
	wolf_LCD9341_line(x1,y1,x1,y2,color);
	wolf_LCD9341_line(x1,y2,x2,y2,color);
	wolf_LCD9341_line(x2,y1,x2,y2,color);
}

/********************************************************************
function: wolf_LCD9341_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t color)
discript: Draw a circle
entrance: center position,radius,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_circle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, uint16_t color)
{
  	int32_t  Dec;
  	uint32_t  CurX;
  	uint32_t  CurY;
	 
  	CurX=0;
  	CurY=Radius;   
  	Dec=3-(Radius<<1);
  	while(CurX<=CurY)
  	{
			wolf_LCD9341_point(Xpos+CurX,Ypos+CurY,color);
			wolf_LCD9341_point(Xpos+CurX,Ypos-CurY,color);
			wolf_LCD9341_point(Xpos-CurX,Ypos+CurY,color);
			wolf_LCD9341_point(Xpos-CurX,Ypos-CurY,color);
			wolf_LCD9341_point(Xpos+CurY,Ypos+CurX,color);
			wolf_LCD9341_point(Xpos+CurY,Ypos-CurX,color);
			wolf_LCD9341_point(Xpos-CurY,Ypos+CurX,color);
			wolf_LCD9341_point(Xpos-CurY,Ypos-CurX,color);
			if(Dec<0)Dec+=(CurX<<2)+6;
	    else
	    {
	      	Dec+=((CurX-CurY)<<2)+10;
	      	CurY--;
	    }
	    CurX++;
  	}
}


/********************************************************************
function: wolf_LCD9341_fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
discript: Fill a rectangle
entrance: start and stop position,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color)
{          

	uint16_t i,j; 
	Address_set(xsta,ysta,xend,yend);      //set cursor position
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)wolf_LCD9341_write_dat16(color);//fill data 	    
	} 					  	    
	
}  


/********************************************************************
function: wolf_LCD9341_pic(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t *pdat)
discript: Draw a bmp picture
entrance: Start and stop position,picture data pointer
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_pic(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint8_t *pdat)
{          

	uint16_t i,j; 
	Address_set(xsta,ysta,xend,yend);      //set filled area
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)wolf_LCD9341_write_dat8(*(pdat++));//filled with bmp picture data 
	} 					  	    
	
}  

/********************************************************************
function: wolf_LCD9341_char(uint16_t x,uint16_t y,uint8_t num,uint8_t mode)
discript: Display char
entrance: Position,data,mode
return  : none
other   : if mode=0 cover old data,mode=1 overlay with old data.
					display color is set by POINT_COLOR
********************************************************************/
void wolf_LCD9341_char(uint16_t x,uint16_t y,uint8_t ch,uint8_t mode)
{
	uint8_t temp;
  uint8_t pos,t;
	uint16_t x0=x;
	uint16_t colortemp=POINT_COLOR;      
  
	if(x>LCD_WIDTH-8||y>LCD_HEIGHT-8)return;	    
	//Check if position is right		   
	ch=ch-' ';
	Address_set(x,y,x+8-1,y+16-1);      //set display area
	if(!mode) 			//cover mode
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=asc2_1608[(uint16_t)ch*16+pos];		 //call 1608 font
			for(t=0;t<8;t++)
		  {                 
				if(temp&0x01)POINT_COLOR=colortemp;
				else POINT_COLOR=BACK_COLOR;
				wolf_LCD9341_write_dat16(POINT_COLOR);	
				temp>>=1; 
				x++;
		  }
			x=x0;
			y++;
		}	
	}else			//overlay mode
	{
		for(pos=0;pos<16;pos++)
		{
		  temp=asc2_1608[(uint16_t)ch*16+pos];		 //call 1608 font
			for(t=0;t<8;t++)
		  {                 
				if(temp&0x01)wolf_LCD9341_point(x+t,y+pos,POINT_COLOR);//draw one pixel    
		    temp>>=1; 
		  }
		}
	}
	POINT_COLOR=colortemp;	    	   	 	  
}   

/********************************************************************
function: wolf_LCD9341_string(uint16_t xpos, uint16_t ypos, uint8_t *ptr, uint16_t color)
discript: Display string on LCD
entrance: Start position,string pointer,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_string(uint16_t xpos, uint16_t ypos, char *ptr, uint8_t mode)
{

  while((*ptr!=0)&&((xpos+Efont.Width)<= LCD_WIDTH))
  {
   	wolf_LCD9341_char(xpos,ypos,*ptr,mode);
   	xpos+= (Efont.Width);
   	ptr++;
  }
}


/********************************************************************
function: mypow(uint8_t m,uint8_t n)
discript: Caculate m^n
entrance: m,n
return  : result of m^n
other   : none
********************************************************************/
uint32_t mypow(uint8_t m,uint8_t n)
{
	uint32_t result=1;	 
	while(n--)result*=m;    
	return result;
}			 
	 
/********************************************************************
function: wolf_LCD9341_num(uint16_t x, uint16_t y, s32 num, uint8_t len, uint16_t color)
discript: Display number
entrance: Start position,num,len,color
return  : none
other   : none
********************************************************************/
void wolf_LCD9341_num(uint16_t x, uint16_t y, int32_t num, uint8_t len, uint8_t mode)
{         	
	uint8_t t,temp;
	//uint8_t enshow=0;
	t=0;
	if(num<0)
	{
		wolf_LCD9341_char(x+(Efont.Width)*t,y,'-',mode);
		num=-num;
		t++;
	}						   
	for(;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
	 	wolf_LCD9341_char(x+(Efont.Width)*t,y,temp+'0',mode); 
	}
} 




