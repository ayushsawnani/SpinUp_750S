#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>


void setDrive(int lB, int lF, int rB, int rF) {


    leftBack.move_velocity(lB);
    leftFront.move_velocity(lF);
    rightBack.move_velocity(rB);
    rightFront.move_velocity(rF);


}

//constant values for the motor vector angle

const static int LEFT_FRONT_ANGLE = 135;
const static int LEFT_BACK_ANGLE = 45;
const static int RIGHT_FRONT_ANGLE = 225;
const static int RIGHT_BACK_ANGLE = 315;




void calculateXMotorSpeed(void) {


    //calculate the speed of the motors

    //lY indicates forward/backward motion,
    //lX indicates left/right motion
    //rX indicates turning motion
    double lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    double lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    double rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);


    
    //calculates inertial sensor rotation about the z axis
    double rotation = inertial_sensor.get_rotation();
    lcd::print(0, "rotation: %f", rotation);



    //determines which side of the robot is facing forward (away from driver)
    int pointer  = (int)rotation/90;

    double lF, lB, rF, rB;


    //NOT 100% --> WE DON'T KNOW IF IT IS 0 - 360 OR  -180 - 180

    //also left front is monkey garbage idk why

    switch (pointer){

        //initially the front side
        //angle is from 0 to 89
        case 0: {
              lF = -(lY + lX + rX);
              lB = lY - lX + rX;
              rF = -lY + lX + rX;
              rB = -lY - lX + rX;
            break;
        }
        //initially the left side
        //angle is from 90 to 179
        case 1: {
              
               lF =  -lY + lX + rX;
              lB = -(lY + lX + rX);
              rF = -lY - lX + rX;
              rB =  lY - lX + rX;
            break;
        }
        //initially the back side
        //angle is from 180 to 269
        case 2: {
                lF =  -lY - lX + rX;
              lB = -lY + lX + rX;
              rF = lY - lX + rX;
              rB =   -(lY + lX + rX); 
            break;
        }
        //initially the right side
        //angle is from 270 to 359
        case 3: {
                lF =   lY - lX + rX;
              lB = -lY - lX + rX;
              rF = -(lY + lX + rX);
              rB =  -lY + lX + rX;
            break;
        }

    }
    

    setDrive(lB, lF, rB, rF);


}




