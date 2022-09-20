#include "project_config.h"

//======================================== MAIN ===========================================
void main(void)
{
    hardware_init();
    motor_init();

    uint32_t dir = FORWARD;
    uint32_t step = 200;
    uint32_t speed = HIGH;
    uint8_t loops = 5;

    MotorStart(step, dir, speed);
    //for(int i=0; i<100000; i++) { __NOP(); }
    //MotorStart(50, REVERSE, 10);

    while(1) {
        if(loops) {
            if(getStep() == 0) {
                if(dir == FORWARD) {
                    dir = REVERSE;
                    MotorStart(step, dir, speed);
                } else {
                    dir = FORWARD;
                    MotorStart(step, dir, speed);
                    loops--;
                }
            }
        } else {
            MotorStop();
        }
    }
}
//=========================================================================================