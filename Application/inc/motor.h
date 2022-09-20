/**********************************************************************
 Processor:                     STM
 Compiler:                      gcc
 Version:                       0.0.1
 Comment:                       first test app

**********************************************************************/
#ifndef MOTOR_H
#define MOTOR_H

#include "project_config.h"

//========================= DEFINES ============================================
#define     YELLOW_PORT     GPIOD
#define     YELLOW_PIN      GPIO_Pin_1
#define     YELLOW_BIT      1

#define     ORANGE_PORT     GPIOD
#define     ORANGE_PIN      GPIO_Pin_0
#define     ORANGE_BIT      0

#define     PINK_PORT       GPIOD
#define     PINK_PIN        GPIO_Pin_2
#define     PINK_BIT        2

#define     BLUE_PORT       GPIOD
#define     BLUE_PIN        GPIO_Pin_3
#define     BLUE_BIT        3

#define     FORWARD         1
#define     REVERSE         0

#define     HIGH            1
#define     FAST            2
#define     MEDUIUM         4
#define     SLOW            8
#define     VERY_SLOW       16
//==============================================================================

//========================= MACROSES ===========================================
#define     YELLOW_SET()    (YELLOW_PORT->ODR |= (1 << YELLOW_BIT))
#define     YELLOW_CLEAR()  (YELLOW_PORT->ODR &= (~(1 << YELLOW_BIT)))

#define     ORANGE_SET()    (ORANGE_PORT->ODR |= (1 << ORANGE_BIT))
#define     ORANGE_CLEAR()  (ORANGE_PORT->ODR &= (~(1 << ORANGE_BIT)))

#define     PINK_SET()      (PINK_PORT->ODR |= (1 << PINK_BIT))
#define     PINK_CLEAR()    (PINK_PORT->ODR &= (~(1 << PINK_BIT)))

#define     BLUE_SET()      (BLUE_PORT->ODR |= (1 << BLUE_BIT))
#define     BLUE_CLEAR()    (BLUE_PORT->ODR &= (~(1 << BLUE_BIT)))
//==============================================================================

//========================= TYPEDEFS ===========================================
typedef struct stStepMotor {
    uint32_t    timerTick;
    uint8_t     speed;
    uint8_t     direction;
    uint32_t    step;
} step_motor_t;
//==============================================================================

//========================= Private function prototype =========================
void motor_init(void);
void MotorStart(uint32_t step, uint32_t direction, uint32_t speed);
void MotorStop(void);
void TimerStepMotor(void);
uint32_t getStep(void);
//==============================================================================



#endif // MOTOR_H