#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H
//========================= INCLUDES ===========================================
#include <stdio.h>
// system
#include "stm32f4xx.h"
// library
#include "misc.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
// user
#include "board.h"
#include "printf.h"
#include "lcd.h"
#include "lvgl.h"
#include "display_lvgl.h"
#include "lv_demo_widgets.h"
//==============================================================================

//========================= DEFINES ============================================
#define         SYSTEM_CLOCK                180000000
//==============================================================================

#endif // PROJECT_CONFIG_H