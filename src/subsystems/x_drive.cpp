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
    double lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    double lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    double rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);


    //we can measure the angle from the motor's vector to the joystick's vector
    //the motors vector is the vector perpendicular to the motor.

    //127 * sin(angle) = movement for the current motor.



    // double lF = calculate_angle_speed(lX, lY, LEFT_FRONT_ANGLE, rX, -1);
    // double lB = calculate_angle_speed(lX, lY, LEFT_BACK_ANGLE, rX, 1);
    // double rF = calculate_angle_speed(lX, lY, RIGHT_FRONT_ANGLE, rX, 1);
    // double rB = calculate_angle_speed(lX, lY, RIGHT_BACK_ANGLE, rX, -1);

    // lcd::print(0, "lF: %f", lF);
    // lcd::print(1, "lB: %f", lB);
    // lcd::print(2, "rF: %f", rF);
    // lcd::print(3, "rB: %f", rB);

    // if (lY == 0 && lX == 0) {
    //     setDrive(0, 0, 0, 0);
    // } else {
    //     setDrive(lB, lF, rB, rF);
    // }

    //inertial_sensor.get_rotation();

    double rotation = inertial_sensor.get_rotation();

    lcd::print(0, "rotation: %f", rotation);

    int pointer  = (int)rotation/90;

    double lF, lB, rF, rB;

    switch (pointer){
        case 0: {
              lF = -(lY + lX + rX);
              lB = lY - lX + rX;
              rF = -lY + lX + rX;
              rB = -lY - lX + rX;
            break;
        }
        case 1: {
              
               lF =  -lY + lX + rX;
              lB = -(lY + lX + rX);
              rF = -lY - lX + rX;
              rB =  lY - lX + rX;
            break;
        }
        case 2: {
                lF =  -lY - lX + rX;
              lB = -lY + lX + rX;
              rF = lY - lX + rX;
              rB =   -(lY + lX + rX); 
            break;
        }
        case 3: {
                lF =   lY - lX + rX;
              lB = -lY - lX + rX;
              rF = -(lY + lX + rX);
              rB =  -lY + lX + rX;
            break;
        }

    }

    // double lF = -(lY + lX + rX);
    // double lB = lY - lX + rX;
    // double rF = -lY + lX + rX;
    // double rB = -lY - lX + rX;

    

    setDrive(lB, lF, rB, rF);





}

double calculate_angle(double lX, double lY, double angle){


    //calculates the angle of the vector from the center of the joystick to the joystick's position

    int pos = angle/45;


    double vector_angle = atan(lY/lX) * 180.0 / M_PI;
    double final_angle = abs(vector_angle - angle);
    while (final_angle < 0) {
        final_angle += 90;
    }
    return final_angle;

}

//-1 for reversed, 1 for not
double calculate_angle_speed(double lX, double lY, double motor_angle, int rX, int reversed) {
    
    double final_angle = calculate_angle(lX, lY, motor_angle);
   
    double speed = 127 * sin(final_angle * M_PI / 180);


    return calculate_volt_speed(speed + rX * reversed);

}

double calculate_volt_speed(double speed) {
    //return speed / 127 * 12;
    return speed;
}


