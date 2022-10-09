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
    dac_init();
    // start();
    DAC->DHR12R1 = 2048u;
    __NOP();
    DAC->DHR12R1 |= 0xffe;

    // __disable_irq;
    // __disable_fault_irq;
    // FLASH_Unlock();
    // FLASH_EraseSector(4, VoltageRange_1);
    // FLASH_ProgramDoubleWord(0x001, 0x000000001);
    // FLASH_Lock();
    // __enable_irq;
    // __enable_fault_irq;

    while(1);
}
//=========================================================================================