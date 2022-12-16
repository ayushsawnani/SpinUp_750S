#include "main.h"

void setDrive(int tL, int tR, int tB) {
    
    triLeft.move_velocity(tL);
    triRight.move_velocity(tR);
    triBottom.move_velocity(tB);


}


void calculateKiwiMotorSpeed(void) {

    //calculate the speed of the motors

    //lY indicates forward/backward motion,
    //lX indicates left/right motion
    //rX indicates turning motion
    int lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    int rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

    double tL, tR, tB;

    tL = lY + lX + rX;
    tR = lY - lX - rX;
    tB = lX - rX;


    setDrive(tL, tR, tB);

}


