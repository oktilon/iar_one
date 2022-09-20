#include "project_config.h"

//======================================== MAIN ===========================================
void main(void)
{
    hardware_init();
    start();

    while(1);
}
//=========================================================================================


void TIM2_IRQHandler() {
    __NOP();
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update | TIM_IT_CC1);
}