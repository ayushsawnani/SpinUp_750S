#include "main.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include <cmath>

using namespace okapi;



void p_controller(int in, int vel) {
    float goal = in * 90 / M_PI;

    //constant for proper tuning
    double Kp = 0.1;

    //reset encoders
    leftBack.tare_position();
    rightBack.tare_position();
    leftFront.tare_position();
    rightFront.tare_position();
    leftReallyFront.tare_position();
    rightReallyFront.tare_position();


    pros::lcd::print(2, "pcontroller %f", leftBack.tare_position());
    //runs a loop until the position is reached
    while (goal > leftBack.get_position()) {
        leftBack.move_velocity((goal - leftBack.get_position()) * Kp);
        leftFront.move_velocity((goal - leftBack.get_position()) * Kp);
        rightBack.move_velocity((goal - leftBack.get_position()) * Kp);
        rightFront.move_velocity(-(goal - leftBack.get_position()) * Kp);
        leftReallyFront.move_velocity((goal - leftBack.get_position()) * Kp);
        rightReallyFront.move_velocity((goal - leftBack.get_position()) * Kp);

        if (goal - leftBack.get_position() < 10) break;

    }
}




void move_drive1(int in, int vel) {
    //vel needs to be converted from rpm to mps
    float d = 4;
    float ipm = d * M_PI * vel / 60; //inches per second
    float ms = (ipm/(double)in) * 1000;

    leftBack.move_velocity(vel);
    leftFront.move_velocity(vel);
    rightBack.move_velocity(vel);
    rightFront.move_velocity(vel);
    leftReallyFront.move_velocity(vel);
    rightReallyFront.move_velocity(vel);



    pros::delay(ms);
    leftBack.move_velocity(0);
    leftFront.move_velocity(0);
    rightBack.move_velocity(0);
    rightFront.move_velocity(0);
    leftReallyFront.move_velocity(0);
    rightReallyFront.move_velocity(0);


}
void move_drive(int ms, int vel) {

    //start moving drive
    leftBack.move_velocity(vel);
    leftFront.move_velocity(vel);
    rightBack.move_velocity(vel);
    rightFront.move_velocity(-vel);
    leftReallyFront.move_velocity(vel);
    rightReallyFront.move_velocity(vel);


    //delay until ms has been reached
    pros::delay(ms);

    //stop drive
    leftBack.move_velocity(0);
    leftFront.move_velocity(0);
    rightBack.move_velocity(0);
    rightFront.move_velocity(0);
    leftReallyFront.move_velocity(0);
    rightReallyFront.move_velocity(0);
}

void angle_drive(int ms, int vel) {

    leftBack.move_velocity(-vel);
    leftFront.move_velocity(-vel);
    rightBack.move_velocity(vel);
    rightFront.move_velocity(-vel);
    leftReallyFront.move_velocity(-vel);
    rightReallyFront.move_velocity(vel);


    pros::delay(ms);
    leftBack.move_velocity(0);
    leftFront.move_velocity(0);
    rightBack.move_velocity(0);
    rightFront.move_velocity(0);
    leftReallyFront.move_velocity(0);
    rightReallyFront.move_velocity(0);
}

void angle_drive1(int deg, int vel) {
    inertial_sensor.reset();
    while (inertial_sensor.is_calibrating()) {
		lcd::print(2, "calibrating");
	}

    lcd::print(2, "%f %f %f", (deg - inertial_sensor.get_heading()), deg, inertial_sensor.get_heading());

    while (deg > inertial_sensor.get_heading()) {
        lcd::print(2, "%f %f %f", (deg - inertial_sensor.get_heading()), deg, inertial_sensor.get_heading());
        leftBack.move_velocity(-vel);
        leftFront.move_velocity(-vel);
        rightBack.move_velocity(-vel);
        rightFront.move_velocity(-vel);
        leftReallyFront.move_velocity(vel);
        rightReallyFront.move_velocity(vel);

        if (abs(deg - inertial_sensor.get_heading()) < 5) break;
    }
    

}

//0 pts
void skills() {

    move_drive(500, -25);
	//lcd::clear_line(2);
    intake_roller.move_velocity(-800);
    pros::delay(250);
    intake_roller.move_velocity(0);
    pros::delay(10);

    p_controller(50, 100);
    // intake_roller.move_velocity(400);
    // pros::delay(1000);
    // intake_roller.move_velocity(0);

    angle_drive(1050, -50);
    move_drive(1000, -100);
    move_drive(750, -25);

    pros::delay(1);

    intake_roller.move_velocity(-800);
    pros::delay(250);
    intake_roller.move_velocity(0);

    move_drive(500, 50);

    angle_drive(1150, 50);

    p_controller(80, 100);

    int target_rpm = -500;
    flywheel_1.move_velocity(target_rpm);

    int disks_shot = 0;
    while (true) {
        pros::lcd::print(4, "flywheel: %f", flywheel_1.get_actual_velocity());
        if (flywheel_1.get_actual_velocity() <= target_rpm) {
            
            intake_roller.move_velocity(400);
            pros::delay(400);
            intake_roller.move_velocity(0);
            disks_shot ++;
            pros::delay(500);

        }

        if (disks_shot >= 2) break;
            
    }
    disks_shot = 0;

    angle_drive(1050, -50);





}

void single_rollerL_auton() {
    
    move_drive(500, -25);
	//lcd::clear_line(2);
    intake_roller.move_velocity(800);
    pros::delay(150);
    intake_roller.move_velocity(0);
    pros::delay(10);

    move_drive(250, 50);


    // intake_roller.move_velocity(400);
    // pros::delay(1000);
    // intake_roller.move_velocity(0);

    pros::delay(1);


}


void single_rollerR_auton() {


    p_controller(50, 100);

    intake_roller.move_velocity(-400);
    move_drive(1000, 45);
    intake_roller.move_velocity(0);
    angle_drive(500, 50);
    move_drive(1650, -100);

    


    intake_roller.move_velocity(400);
    pros::delay(500);
    intake_roller.move_velocity(0);
    pros::delay(10);

}




void double_roller_auton() {
    
    inertial_sensor.reset();
    while (inertial_sensor.is_calibrating()) {
		lcd::print(2, "calibrating");
	}
    move_drive(500, -100);
	lcd::clear_line(2);
    //intake_roller_motor.moveVelocity(-200);
    pros::delay(200);
    //intake_roller_motor.moveVelocity(0);
    pros::delay(10);
    p_controller(12,100); //should take like 1.744 seconds -> dont know if i should make p or reg
    //hassis->turnAngle(180_deg);
    angle_drive(1100, -50);
    p_controller(315, 100);

    angle_drive(950, 50);
    p_controller(50, 100);
    
    angle_drive(1600, 100);
    move_drive(900, -100);
    pros::delay(10);
    //chassis->turnAngle(520_deg);
    //intake_roller_motor.moveVelocity(-200);
    pros::delay(2000);
    //intake_roller_motor.moveVelocity(0);
    pros::delay(10);

    angle_drive(1200, 50);
    p_controller(110, 100); //move into low goal
    //angle_drive(1600, -100);

    flywheel_1.move_velocity(600);    //shoot into low goal
    pros::delay(950);
    dispenser2.move_velocity(0);
    pros::delay(5);
    dispenser2.move_velocity(-200);
    pros::delay(200);
    dispenser2.move_velocity(0);

    

}




void sensorPID(void) {

    //tuning

    //rise time = time it takes to get to the desired value
    //overshoot = how much farther ur robot goes from the val
    //settling time = time it takes to settle back to normal after there has been a change
    //steady state error = the error (if any) when pid is complete
    //stability = smoothness


    //rise time decreases, overshoot increases, steady state error decreases, stability worsens
    double K_p = 1.0;

    //overshoot decreases, settling time decreases, stability improves IF NOT TOO MUCH
    double K_d = 1.0;

    //rise time decreases, overshoot increases, settling time increases, steady state error decreases, stability worsens
    double K_i = 1.0;

    //tune kP until robot oscillates slightly
    //tune kD until the steady state error decreases to smth normal
    //tune kI until the steady state error and any disturbances are minimized (can be 0)

    double prevOffset = 0;

    //goal is to reach 50mm distance for distance sensor

    //wheel diameter is 4 inches

    while(true) {

        

        //calculate current offset (p)
        double p = frontSensor.get() - 50;
        if (std::abs(p) < 10) {
            leftBack.move_velocity(0);
            leftFront.move_velocity(0);
            rightBack.move_velocity(0);
            rightFront.move_velocity(0);
            break;
        }
        

        //calculate rate of change (d) (when oscillating around value) so we can speed up or slow down a bit
        double d = p - prevOffset;
        pros::delay(2);
        prevOffset = p;


        //calculate total offset (i) (any remaining error) only if error is less than or equal to 0 and if the error is small
        //if error >= 100mm or smth then i = 0
        int i = 0;
        if (p <= 100) i += p;
        

        //pid = p * kp + i * ki + d * kd

        double speed = p * K_p + i * K_i + d * K_d;

        leftBack.move_velocity(speed);
        leftFront.move_velocity(speed);
        rightBack.move_velocity(speed);
        rightFront.move_velocity(speed);

        Task::delay(5);
    }
    
}



double distance(double x1, double x2, double y1, double y2){
    return std::sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
}



void calculateOdom(double x, double y, double x_0, double y_0, double theta_0) {
    


}


void check_current_encoders(double x_0, double y_0, double theta_0){
    
    //checks the current position through encoders for L, R, and B
    while(true) {
        double eL = encoder_L.get_value();
        double eR = encoder_R.get_value();
        double eB = encoder_B.get_value();
    
        calculateOdom(eL, eR, x_0, y_0, theta_0);

        Task::delay(10);
    }
} 