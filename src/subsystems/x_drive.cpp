#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>


void setDrive(int lB, int lF, int rB, int rF) {


    leftBack.move_voltage(lB);
    leftFront.move_voltage(lF);
    rightBack.move_voltage(rB);
    rightFront.move_voltage(rF);


}

//constant values for the motor vector angle

const static int LEFT_FRONT_ANGLE = 135;
const static int LEFT_BACK_ANGLE = 225;
const static int RIGHT_FRONT_ANGLE = 45;
const static int RIGHT_BACK_ANGLE = 315;




void calculateXMotorSpeed(void) {


    //calculate the speed of the motors
    int lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    int rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);


    //we can measure the angle from the motor's vector to the joystick's vector
    //the motors vector is the vector perpendicular to the motor.

    //127 * sin(angle) = movement for the current motor.

    int lF = calculate_angle_speed(lX, lY, LEFT_FRONT_ANGLE, rX, 1);
    int lB = calculate_angle_speed(lX, lY, LEFT_BACK_ANGLE, rX, 1);
    int rF = calculate_angle_speed(lX, lY, RIGHT_FRONT_ANGLE, rX, -1);
    int rB = calculate_angle_speed(lX, lY, RIGHT_BACK_ANGLE, rX, -1);

    setDrive(lB, lF, rB, rF);





}

double calculate_angle(int lX, int lY, double angle){


    //calculates the angle of the vector from the center of the joystick to the joystick's position
    double vector_angle = atan2(lY, lX) * 180 / M_PI;

    double final_angle = abs(vector_angle - angle);

    while (final_angle > 90) {
        final_angle -= 90;
    }

}

//-1 for reversed, 1 for not
double calculate_angle_speed(int lX, int lY, double motor_angle, int rX, int reversed) {
    
    double final_angle = calculate_angle(lX, lY, motor_angle);
   
    double speed = 127 * sin(final_angle * M_PI / 180);


    return calculate_volt_speed(speed + rX * reversed);

}

int calculate_volt_speed(double speed) {
    return speed / 127 * 12;
}


