/**********************************************************************
 Processor:                     STM
 Compiler:                      gcc
 Version:                       0.0.1
 Comment:                       first test app

**********************************************************************/
#ifndef BOARD_H
#define BOARD_H

#include "project_config.h"


void hardware_init(void);
void gpio_init(void);
void dma_init(void);
void tim_init(void);
void start(void);


#endif