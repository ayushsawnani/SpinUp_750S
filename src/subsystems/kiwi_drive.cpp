#define _USE_MATH_DEFINES

#include "main.h"

void setDrive(int tL, int tR, int tB) {
    
    triLeft.move_voltage(tL);
    triRight.move_voltage(tR);
    triBottom.move_voltage(tB);


}

const static int TRI_LEFT_ANGLE = 145;
const static int TRI_RIGHT_ANGLE = 45;
const static int TRI_BOTTOM_ANGLE = 270;

void calculateKiwiMotorSpeed(void) {

    //calculate the speed of the motors
    int lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    int rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

    //we can measure the angle from the motor's vector to the joystick's vector

    //the motors vector is the vector perpendicular to the motor.
    //127 * sin(angle) = movement for the current motor.

    int tL = calculate_angle_speed(lX, lY, TRI_LEFT_ANGLE, rX, 1);
    int tR = calculate_angle_speed(lX, lY, TRI_RIGHT_ANGLE, rX, -1);
    int tB = calculate_angle_speed(lX, lY, TRI_BOTTOM_ANGLE, rX, 1);

    setDrive(tL, tR, tB);






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




