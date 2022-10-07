#include "main.h"
#include "okapi/api/units/QAngle.hpp"
#include "okapi/impl/chassis/controller/chassisControllerBuilder.hpp"
#include <cmath>

using namespace okapi;

std::shared_ptr<ChassisController> chassis =
  ChassisControllerBuilder()
    .withMotors(
        1,  // Top left
        -2, // Top right (reversed)
        -3, // Bottom right (reversed)
        4   // Bottom left
    )
    // Green gearset, 4 in wheel diam, 11.5 in wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
    .build();

okapi::Motor intake_roller_motor(8);


void auton_run1() {
    int disks_carried = 0;

    Task turntableTask(fixTurntableOffset, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "turntable");

    while (disks_carried < 2) {
        double closest_disk_heading = 0;
        double closest_disk = 999999999999999;

        chassis->turnAngleAsync(360_deg);

        if (frontSensor.get() < closest_disk) {
            closest_disk = frontSensor.get();
            closest_disk_heading = inertial_sensor.get_heading();
        }
        chassis->waitUntilSettled();

        chassis->turnAngle((inertial_sensor.get_heading() - closest_disk_heading) * degree);
        sensorPID();
        
        intake_roller_motor.moveVelocity(200);
        pros::delay(3000);
        intake_roller_motor.moveVelocity(0);

        disks_carried ++;

        
        
    }

    delay(1);
    for(int i = 0; i < 3; i++){
        dispenser.set_value(true);
        pros::delay(50);
        dispenser.set_value(false);
        pros::delay(50);
    }


}

void auton_run2() {
    int disks_carried = 0;

    //Task turntableTask(fixTurntableOffset, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "turntable");

    while (disks_carried < 2) {
        double closest_disk_heading = 0;
        double closest_disk = 999999999999999;

        chassis->turnAngleAsync(360_deg);

        if (frontSensor.get() < closest_disk) {
            closest_disk = frontSensor.get();
            closest_disk_heading = inertial_sensor.get_heading();
        }
        chassis->waitUntilSettled();

        chassis->turnAngle((inertial_sensor.get_heading() - closest_disk_heading) * degree);
        sensorPID();
        
        intake_roller_motor.moveVelocity(200);
        pros::delay(3000);
        intake_roller_motor.moveVelocity(0);

        disks_carried ++;

        
        
    }

    delay(1);

    chassis->turnAngle((inertial_sensor.get_heading()) * degree);


    for(int i = 0; i < 3; i++){
        dispenser.set_value(true);
        pros::delay(50);
        dispenser.set_value(false);
        pros::delay(50);
    }


}

void sensorPID(void) {

    while(true) {
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
        delay(2);
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
    }
    
}



double distance(double x1, double x2, double y1, double y2){
    return std::sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
}

//calculates constant rpm to move from current position to x, y in inches
static double d_L;
static double d_R;

static double S_L = 9;
static double S_R = 9;

void calculateOdom(double x, double y, double x_0, double y_0, double theta_0) {
    
    double half_angle = atan( (1/tan( (theta_0 * M_PI)/360 ))) * (180/M_PI);

    double mid_d = 0.5 * distance(x, x_0, y, y_0);

    double height = tan((half_angle * M_PI)/180) * mid_d;

    double radius = sqrt((mid_d)*(mid_d) + (height * height));

    double radius_r = radius - S_L;

    d_R = radius_r * (theta_0 * M_PI/180);

    d_L = (theta_0 * M_PI/180) * (S_L + S_R) + d_R;

}

void movement_PID(){
    //refer to drivePID for info

    //left side pid
    double LK_p = 1.0;
    double LK_d = 1.0;
    double LK_i = 1.0;

    //right side pid
    double RK_p = 1.0;
    double RK_d = 1.0;
    double RK_i = 1.0;

    double prevOffset_L = 0;
    double totalOffset_L = 0;
    double prevOffset_R = 0;
    double totalOffset_R = 0;
    double i_L = 0;
    double i_R = 0;

    while(true){
        double p_L = encoder_L.get_value() - d_L;
        double p_R = encoder_R.get_value() - d_R;

        double dL = p_L - prevOffset_L;
        Task::delay(1);
        prevOffset_L = p_L;

        double dR = p_R - prevOffset_R;
        Task::delay(1);
        prevOffset_R = p_R;



        if (p_L >= -100 && p_L < 0) {
            i_L = 0;
        }
        else {
            i_L +=  p_L;
        }

        if (p_R >= -100 && p_R < 0) {
            i_R = 0;
        }
        else {
            i_R +=  p_R;
        }

        double rpm_L = p_L * LK_p + d_L * LK_d + i_L * LK_i;
        double rpm_R = p_R * RK_p + d_R * RK_d + i_R * RK_i;
        Task::delay(5);
    }

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