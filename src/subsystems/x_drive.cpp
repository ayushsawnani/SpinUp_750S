#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>


void setDrive(int lB, int lF, int rB, int rF) {


    leftBack = lB;
    leftFront = lF;
    rightBack = rB;
    rightFront = rF;


}

//prev values to calculate d_movement and d_turn
static int prev_movement = 0;
static int prev_turn = 0;



void calculateMotorSpeed(void) {


    //calculate the speed of the motors
    int leftJoystickY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int leftJoystickX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    int rightJoystickX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);


    //calculates angle of the joystick
    double angle = map_circular_coordinates(leftJoystickX, leftJoystickY);

    
    


    

  

    //calculate lateral and angular speed
    double lB = calculate_speed(angle, 2, leftJoystickX, leftJoystickY);
    double lF = calculate_speed(angle, 1, leftJoystickX, leftJoystickY);

    lB = calculate_angle_speed(rightJoystickX, lB, 1);
    lF = calculate_angle_speed(rightJoystickX, lF, 1);
    

    double rB = calculate_speed(angle, 1, leftJoystickX, leftJoystickY);
    double rF = calculate_speed(angle, 2, leftJoystickX, leftJoystickY);
    
    rB = calculate_angle_speed(rightJoystickX, rB, -1);
    rF = calculate_angle_speed(rightJoystickX, rF, -1);

    //calculate the acceleration of the motors
    int accel_movement = calculate_derivative( lB, prev_movement);
    int accel_turn = calculate_derivative(rB, prev_turn);

    //acceleration of the movement of the drive
    accel_movement = constrain(accel_movement, -127, 127);

    //acceleration of the turning of the drive
    accel_turn = constrain(accel_turn, -127, 127);



    //set the motors to the calculated speed + the powereq for the acceleration for smoothness
    setDrive(lB + (accel_movement + accel_turn), lF + (accel_movement + accel_turn), rB + (accel_movement - accel_turn), rF + (accel_movement - accel_turn));

    prev_movement = lB;
    prev_turn = rB;


}

//create constrains
int constrain(int val, int min, int max) {
    if (val > max) {
        return max;
    } else if (val < min) {
        return min;
    } else {
        return val;
    }
}



//calculates the acceleration of the joystick, used for the drivetrain
int calculate_derivative(int current, int previous) {

    int derivative = current - previous;

    return derivative;

}

int map_circular_coordinates(int x, int y) {

    int angle = atan2(y, x) * 180 / M_PI;

    return angle;

}

double calculate_distance(int x, int y) {

    double distance = sqrt(pow(x, 2) + pow(y, 2));

    return distance;

}


//1 is right diagonal (/), 2 is left diagonal (\)
double calculate_speed(int angle, int motor, int x, int y) {
    double speed = 0;
    switch (motor){
        case 1:
            if (angle <= 225 || angle >= 45) {
                speed = calculate_distance(x, y) ;
            } else {
                speed = -calculate_distance(x, y);
            }
            break;
        case 2:
            if (angle >= 315 || angle <= 135) {
                speed = calculate_distance(x, y);
            } else {
                speed = -calculate_distance(x, y);
            }
            break;
        default:
            speed = 0;
            break;
    }

    return speed;
    
}

//-1 for reversed, 1 for not
double calculate_angle_speed(int rX, double lateral_speed, int reversed) {
    
    return lateral_speed + (rX * reversed);
}





