/*******************************************************************************
 Processor:                     STM
 Compiler:                      gcc
 Version:                       0.0.1
 Comment:                       first test app

*******************************************************************************/
//========================= INCLUDES ===========================================
#include "motor.h"
//==============================================================================

//========================= VARIABLES ==========================================
volatile static uint8_t PhaseStep = 0u;
step_motor_t motor;
//==============================================================================



//========================= Private function prototype =========================
static void Step(void);
//==============================================================================


//========================= IRQ Handlers =======================================
void SysTick_Handler() {
    TimerStepMotor();
}
//==============================================================================

//==============================================================================
//*************             FUNCTIONS                            ***************
//==============================================================================

//========================= MOTOR MODULES INIT =================================
void motor_init() {
    GPIO_InitTypeDef GPIO_InitStructure;

    // YELLOW
    GPIO_InitStructure.GPIO_Pin  = YELLOW_PIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(YELLOW_PORT, &GPIO_InitStructure);
    // ORANGE
    GPIO_InitStructure.GPIO_Pin  = ORANGE_PIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(ORANGE_PORT, &GPIO_InitStructure);
    // PINK
    GPIO_InitStructure.GPIO_Pin  = PINK_PIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(PINK_PORT, &GPIO_InitStructure);
    // BLUE
    GPIO_InitStructure.GPIO_Pin  = BLUE_PIN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(BLUE_PORT, &GPIO_InitStructure);

    // PWM
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    // Timer 2

    motor.speed     = HIGH;
    motor.step      = 0;
    motor.direction = FORWARD;
    motor.timerTick = 0;

    ORANGE_CLEAR();
    YELLOW_CLEAR();
    PINK_CLEAR();
    BLUE_CLEAR();
}

//========================= Motor Start ==============================
void MotorStart(uint32_t step, uint32_t direction, uint32_t speed) {
    motor.step = step;
    motor.direction = direction;
    motor.speed = speed;
    motor.timerTick = 0;
}
//========================= Step ==============================
static void Step() {
    PhaseStep++;

    if(motor.direction == REVERSE) {
        switch(PhaseStep) {
            case 0:                                                               break;
            case 1: ORANGE_SET();    YELLOW_CLEAR(); PINK_CLEAR(); BLUE_SET();    break;
            case 2: ORANGE_CLEAR();  YELLOW_CLEAR(); PINK_CLEAR(); BLUE_SET();    break;
            case 3: ORANGE_CLEAR();  YELLOW_CLEAR(); PINK_SET();   BLUE_SET();    break;
            case 4: ORANGE_CLEAR();  YELLOW_CLEAR(); PINK_SET();   BLUE_CLEAR();  break;
            case 5: ORANGE_CLEAR();  YELLOW_SET();   PINK_SET();   BLUE_CLEAR();  break;
            case 6: ORANGE_CLEAR();  YELLOW_SET();   PINK_CLEAR(); BLUE_CLEAR();  break;
            case 7: ORANGE_SET();    YELLOW_SET();   PINK_CLEAR(); BLUE_CLEAR();  break;
            case 8: ORANGE_SET();    YELLOW_CLEAR(); PINK_CLEAR(); BLUE_CLEAR();
                    PhaseStep = 0;   motor.step--;                                break;
            default:                                                              break;
        }
    } else { // FORWARD
        switch(PhaseStep) {
            case 0:                                                               break;
            case 1: ORANGE_SET();    YELLOW_CLEAR(); PINK_CLEAR(); BLUE_CLEAR();  break;
            case 2: ORANGE_SET();    YELLOW_SET();   PINK_CLEAR(); BLUE_CLEAR();  break;
            case 3: ORANGE_CLEAR();  YELLOW_SET();   PINK_CLEAR(); BLUE_CLEAR();  break;
            case 4: ORANGE_CLEAR();  YELLOW_SET();   PINK_SET();   BLUE_CLEAR();  break;
            case 5: ORANGE_CLEAR();  YELLOW_CLEAR(); PINK_SET();   BLUE_CLEAR();  break;
            case 6: ORANGE_CLEAR();  YELLOW_CLEAR(); PINK_SET();   BLUE_SET();    break;
            case 7: ORANGE_CLEAR();  YELLOW_CLEAR(); PINK_CLEAR(); BLUE_SET();    break;
            case 8: ORANGE_SET();    YELLOW_CLEAR(); PINK_CLEAR(); BLUE_SET();
                    PhaseStep = 0;   motor.step--;                                break;
            default:                                                              break;
        }
    }
}
//========================= Timer hanadler ==============================
void TimerStepMotor() {
    if(motor.step > 0) {
        motor.timerTick++;
        if(motor.speed == motor.timerTick) {
            Step();
            motor.timerTick = 0;
        }
    }
}

void MotorStop(void) {
    ORANGE_CLEAR();
    YELLOW_CLEAR();
    PINK_CLEAR();
    BLUE_CLEAR();
}

uint32_t getStep(void) {
    return motor.step;
}