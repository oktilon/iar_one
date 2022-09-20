/*******************************************************************************
 Processor:                     STM32
 Compiler:                      gcc
 Version:                       0.0.1
 Comment:                       Test DMA copy from ADC to memory
                                ADC1 from PA0 (Analog) (blue button pin)
                                DMA2 Stream 0 - Channel 0 PeripheralToMemory

*******************************************************************************/
#include "project_config.h"

//======================================== MAIN ===========================================
void main(void)
{
    hardware_init();
    start();

    while(1);
}
//=========================================================================================