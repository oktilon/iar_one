/*******************************************************************************
 Processor:                     STM
 Compiler:                      gcc
 Version:                       0.0.1
 Comment:                       first test app

*******************************************************************************/
//========================= INCLUDES ===========================================
#include "board.h"
//==============================================================================

//========================= VARIABLES ==========================================
RCC_ClocksTypeDef RCC_Clocks;
//==============================================================================



//========================= Private function prototype =========================
static void system_clock_init(void);
static void systick_init(void);
//==============================================================================

//==============================================================================
//*************             FUNCTIONS                            ***************
//==============================================================================

//========================= MPU MODULES INIT ===================================
void hardware_init(void) {
    SystemInit();
    system_clock_init();
    systick_init();
    gpio_init();
    adc_init();
    dma_init();


}

//========================= MPU SYSTEM CLOCK INIT ==============================
void system_clock_init(void) {
    SystemCoreClockUpdate();
    RCC_DeInit();
    RCC_HSEConfig(RCC_HSE_ON);
    RCC_WaitForHSEStartUp();
    RCC_PLLConfig(RCC_PLLSource_HSE, 8, 336, 2, 4); // Main delimiter, Main multiplier, Delimiter, AHB Delimiter
    RCC->CFGR = 0;
    RCC->CFGR = (RCC_CFGR_PPRE2_DIV2 | RCC_CFGR_PPRE1_DIV4 | RCC_CFGR_HPRE_DIV1);
    RCC_PLLCmd(ENABLE);
    while((RCC->CR & RCC_CR_PLLRDY) == 0);                       // wait pll ready
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    RCC->DCKCFGR |=  RCC_DCKCFGR_TIMPRE;                         // clock timer

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

//========================= MPU SYSTICK INIT ===================================
void systick_init(void) {
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}

void gpio_init(void) {
    // Choose GPIO pin
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0; // PA0 (GPIOA + Pin0) Discovery board User button
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_Init(GPIOA, &GPIO_InitStructure); // PA0 (GPIOA + Pin0)
}

void adc_init() {
    // Setup ADC 1
    ADC_InitTypeDef       ADC_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;

    // ADC common Init
    ADC_CommonInitStructure.ADC_Mode             = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler        = ADC_Prescaler_Div8;
    ADC_CommonInitStructure.ADC_DMAAccessMode    = ADC_DMAAccessMode_2;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);

    // ADC Init
    ADC_InitStructure.ADC_Resolution           = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode         = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode   = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ExternalTrigConv     = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign            = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion      = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Cmd(ADC1, ENABLE);

}

void dma_init() {
    DMA_InitTypeDef   DMA_InitStructure;

    DMA_DeInit(DMA2_Stream0);

    DMA_InitStructure.DMA_Channel            = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_BASE + 0x4Cu; // + DR offset
    DMA_InitStructure.DMA_Memory0BaseAddr    = SRAM1_BASE;
    DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize         = 2048;
    DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode           = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;      // If FIFO enabled
    DMA_InitStructure.DMA_MemoryBurst        = DMA_MemoryBurst_INC4;        // If FIFO enabled
    DMA_InitStructure.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;  // If FIFO enabled

    DMA_Init(DMA2_Stream0, &DMA_InitStructure);

    DMA_Cmd(DMA2_Stream0, ENABLE);
}