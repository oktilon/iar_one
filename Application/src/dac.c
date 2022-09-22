/*******************************************************************************
 Processor:                     STM
 Compiler:                      gcc
 Version:                       0.0.1
 Comment:                       first test app

*******************************************************************************/
//========================= INCLUDES ===========================================
#include "dac.h"
//==============================================================================

//========================= VARIABLES ==========================================
//==============================================================================



//========================= Private function prototype =========================
//==============================================================================

//==============================================================================
//*************             FUNCTIONS                            ***************
//==============================================================================

//========================= DAC MODULE INIT ===================================
void dac_init(void) {
    // Choose GPIO pin
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Setup DAC 1
    DAC_InitTypeDef       DAC_InitStructure;

    // DAC common Init
    DAC_DeInit();

    DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
    DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_Triangle;
    DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bits11_0;
    DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Disable;

    //DAC_SoftwareTriggerCmd()

    DAC_Init(DAC_Channel_1, &DAC_InitStructure);
    DAC_Cmd(DAC_Channel_1, ENABLE);
}
