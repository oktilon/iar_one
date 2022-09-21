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
    tim_init();
    gpio_init();
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

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
}

//========================= MPU SYSTICK INIT ===================================
void systick_init(void) {
    RCC_GetClocksFreq(&RCC_Clocks);
    SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
}

void gpio_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);
}

void tim_init() {
    TIM_TimeBaseInitTypeDef TIM_InitBaseStructure;
    TIM_OCInitTypeDef TIM_InitStructure;
    TIM_DeInit(TIM2);

    // TIM_TimeBaseStructInit(&TIM_InitBaseStructure);
    TIM_InitBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_InitBaseStructure.TIM_Period = 4294964295;
    TIM_InitBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM2, &TIM_InitBaseStructure);

    TIM_InternalClockConfig(TIM2);

    TIM_InitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_InitStructure.TIM_OutputState = TIM_OutputState_Disable;
    TIM_InitStructure.TIM_Pulse = 0u;
    TIM_InitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(TIM2, &TIM_InitStructure);

    TIM_Cmd(TIM2, ENABLE);
}