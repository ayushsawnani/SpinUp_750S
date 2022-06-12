#define _USE_MATH_DEFINES

#include "main.h"

void setDrive(int tL, int tR, int tB) {
    
    triLeft.move_voltage(tL);
    triRight.move_voltage(tR);
    triBottom.move_voltage(tB);


}

void calculateMotorSpeed(void) {

    //calculate the speed of the motors
    int lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    int rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

    //calculates angle of the joystick
    double angle = map_circular_coordinates(lX, lY);

    //finish kiwi







}


int map_circular_coordinates(int x, int y) {

    int angle = atan2(y, x) * 180 / M_PI;

    return angle;

}