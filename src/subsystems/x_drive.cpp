#include "pros/llemu.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <istream>
#include <type_traits>
#define _USE_MATH_DEFINES

#include "main.h"
#include <cmath>



using namespace okapi;





void setDrive(int lB, int lF, int rB, int rF) {

  /*
  leftBack.move_velocity(lB);
  leftFront.move_velocity(lF);
  rightBack.move_velocity(rB);
  rightFront.move_velocity(rF);
  */
  leftBack.move_voltage(lB * 1000);
  leftFront.move_voltage(lF * 1000);
  rightBack.move_voltage(rB * 1000);
  rightFront.move_voltage(rF * 1000);
}


// gets polar coordinate r
double getR(double x, double y){
  return  std::sqrt(x*x + y*y);
}

// gets polar coordinate theta
double getTheta(double x, double y) {

  // only from -π to π
  double position = atan2(y, x);

  // from 0 to 2π
  return (position >= 0 ? position : (2 * M_PI + position));
}

// Diag1 is the movement value for the 1st diagonal of the drive
// position is the rotation from 0 to 2π
double getDiag1(double position) {

  double numerator = -cos(position + (M_PI / 4));
  double denominator = cos((M_PI / 4));

  // returns coefficient of speed
  return numerator / denominator;
}

// Diag2 is the movement value for the 2nd diagonal of the drive
// position is the rotation from 0 to 2π
double getDiag2(double position) {

  double numerator = -cos(position + ((3 * M_PI) / 4));
  double denominator = cos((M_PI / 4));

  // returns coefficient of speed
  return numerator / denominator;
}

double volted(double velocity) {
  return (12 * velocity) / 127;
  
}

double test(int indicator, double v) { return indicator * (127 - std::abs(v)); }


void calculateXMotorSpeed(void) {
  while(true) { //DONT TOUCH THIS

    // calculate the speed of the motors

    // lY indicates forward/backward motion,
    // lX indicates left/right motion
    // rX indicates turning motion
    double lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    double lX = master.get_analog(E_CONTROLLER_ANALOG_LEFT_X);
    double rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);


    double lF, lB, rF, rB;



    // POWER EQUATION
    /*
    this is inneficient because QQ while we are getting 1.4 times the speed of
    an x drive moving forward, left, back, and right, we are only getting 
    1 times the speed moving diagonally. therefore we have found another solution. 
    */
    // lF = lY + lX + rX;
    // lB = lY - lX + rX;
    // rF = -lY + lX + rX;
    // rB = -lY - lX + rX;


    //DIRECTIONAL CONTROL

    // values for setting the motors
    double d1 = getDiag1(getTheta(lX, lY));
    double d2 = getDiag2(getTheta(lX, lY));
    double max = std::max(d1, d2) * sqrt(d1*d1 + d2*d2);

    // diagional/max caps the max coefficient to 1 instead of a really small
    // difference

    // radius of joystick * coefficient of speed * turn importance + turning value

    /*
    d2 and d1 are the coefficients of speed so that when we strafe the bot, the motors slow down/speed up accordingly
    they can either have a constraint by setting it to (diagional/max) so that the greatest value will always be 1 or
    they are free without any constraints. we use constraints in auton for accuracy. 
    
    we chose not to have turn importance as we are mainly strafing around the field for driver control
    turn importance is R - rX
    */
    // acc value * diagonal damp + rx
    lF = (volted(getR(lX, lY)) * (d2)) - (volted(rX));
    lB = (volted(getR(lX, lY)) * (d1)) - (volted(rX));
    rF = (volted(getR(lX, lY)) * (d1)) + (volted(rX));
    rB = (volted(getR(lX, lY)) * (d2)) + (volted(rX));

    
    
    // lcd::print(1, "D1: %f", d1);
    // lcd::print(2, "D2: %f", d2);
    // lcd::print(7, "R: %f", getR(lX, lY));

    // lcd::print(3, "LF: %f", lF);
    // lcd::print(4, "lB: %f", lB);
    // lcd::print(5, "rF: %f", rF);
    // lcd::print(6, "rB: %f", rB);

    //rF is monkey ass idk why and lF
    setDrive(lB, lF, rB, -rF);

    //DO NOT TOUCH THIS DELAY
    Task::delay(20);
  }
}

//these parameters are WITHOUT volted
void calculate_final_pos(double max) {

  /*
  
    |    |

    |    |

    i don't know if this is the actual or theoretical movement

    if it is the theoretical ima change
  
  */

  
  double T = atan2(position_y, position_x);
  double Cx = cos(T)/max;
  double Cy = sin(T)/max;

  position_x += Cx;



  
}

//must have inertial sensor
void turn_drive(double desired_angle){
  double prev_offset = 0;
  double kp = 1;
  double kd = 1;
  while (std::abs(inertial_sensor.get_heading() - desired_angle) < 2){
    double p = inertial_sensor.get_heading() - desired_angle;

    double d = p - prev_offset;

    pros::delay(1);

    prev_offset = p;

    double speed = p * kp + d * kd;

    double lF = (speed);
    double lB = (speed);
    double rF = (-speed);
    double rB = (speed);
    lcd::print(4, "%f, %f, %f, %f", lB, lF, rB, -rF);
    setDrive(lB, lF, rB, -rF);
  }
}

//finds the goal
void find_goal() {

  //we need to find the goal x and y values 


  //distance formula

  double angle = (atan2(goal_posy - position_y,goal_posx- position_x) < 0 ? atan2(goal_posy - position_y, goal_posx - position_x) + 360 : atan2(goal_posy - position_y, goal_posx - position_x));
  
  turn_drive(angle);
  

}
