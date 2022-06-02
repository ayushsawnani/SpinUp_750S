#include "main.h"

void setDrive(int lB, int lF, int rB, int rF) {


    leftBack = lB;
    leftFront = lF;
    rightBack = rB;
    rightFront = rF;


}

static int prev = 0;

void calculateMotorSpeed(void) {

    int leftJoystickY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int rightJoystickX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);



    
    int vel_left = calculate_derivative(leftJoystickY, prev);
    int vel_right = calculate_derivative(rightJoystickX, prev);

    setDrive(leftJoystickY + vel_left, leftJoystickY + vel_left, rightJoystickX + vel_right, rightJoystickX + vel_right);

    prev = leftJoystickY;

}

int calculate_derivative(int current, int previous) {

    int derivative = current - previous;

    return derivative;

}

