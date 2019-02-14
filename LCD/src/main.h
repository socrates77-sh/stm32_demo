/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx.h"

#include "wolf_typedefine.h"
#include "wolf_delay.h"
#include "wolf_led.h"
#include "wolf_key.h"
#include "wolf32f031_board_pinmap.h"
#include "wolf_LCD9341.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  OVERLAY = 0,
  COVER = 1,
} DrawMode_TypeDef;

/* Exported constants --------------------------------------------------------*/
#define LINE_MAX 16
#define CHAR_MAX 30
#define LINE_HEIGHT 20

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */
