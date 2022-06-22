#define _USE_MATH_DEFINES

#include "main.h"

void setDrive(int tL, int tR, int tB) {
    
    triLeft.move_velocity(tL);
    triRight.move_velocity(tR);
    triBottom.move_velocity(tB);


}

const static int TRI_LEFT_ANGLE = 145;
const static int TRI_RIGHT_ANGLE = 45;
const static int TRI_BOTTOM_ANGLE = 270;

void calculateKiwiMotorSpeed(void) {

    //calculate the speed of the motors

    //lY indicates forward/backward motion,
    //lX indicates left/right motion
    //rX indicates turning motion
    int lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    int rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);


    //calculates inertial sensor rotation about the z axis
    double rotation = inertial_sensor.get_rotation();
    lcd::print(0, "rotation: %f", rotation);



    //determines which side of the robot is facing forward (away from driver)
    int pointer  = (int)rotation/120;

    double tL, tR, tB;

    switch (pointer) {


        case 0: {
            tL = lY + lX + rX;
            tR = lY - lX - rX;
            tB = lX + rX;
            break;

        }
        case 1: {
            tL = lX + rX;
            tR = lY + lX + rX; 
            tB = lY - lX - rX; 
            break;
        }
        case 2: {
            tL = lY - lX - rX; 
            tR = lX + rX; 
            tB = lY + lX + rX; 
            break;
        }

    }

    setDrive(tL, tR, tB);






}


