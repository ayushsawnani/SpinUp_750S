#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"
#include <cmath>

static bool INTAKE_RUNNING = false;
static bool FLYWHEEL_RUNNING = false; 

static bool RUNNING_FLYWHEEL = 0;
static int RUNNING_INTAKE = 0;

static int running_endgame = false;

static int running_indexer = 0;

static int SHABALO = 0;

static bool printint_controller = false;




void setBuildMotors() {
    //In C++, 1 is true and 0 is false
    
    while(true){ //DONT TOUCH THIS




        if (master.get_digital(DIGITAL_B)) {
            running_endgame = !running_endgame;
            pros::delay(250);
        }

        if (master.get_digital(DIGITAL_R1)) {
            RUNNING_FLYWHEEL = !RUNNING_FLYWHEEL;
            pros::delay(250);
        }


        

       //dispenser2.move_velocity(master.get_digital(DIGITAL_A) * 200);

        lift.move_velocity(
            (master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN)) * 200);

        blooper.set_value(master.get_digital(DIGITAL_UP));

        endgame.set_value(running_endgame);



        //endgame.set_value(running_endgame);

        //catapult.move_velocity((master.get_digital(DIGITAL_A) - !limitSwitch.get_value()) * 200);

        

        //DIFFERENT FROM THE REGULAR DELAY THIS IS FOR MULTITASKING
        Task::delay(5);



        
    }
    
}

static double target_rpm = -450;
void flywheel_pid() {
    float Kfp = 1;
    float Kfd = 1;
    float Kfx = 0.5;
    float prevVelocity = 0;

    while (true) {


        //placeholder value
        float p = target_rpm;

        //error between current rpm and acc rpm
        float d = p - flywheel_1.get_actual_velocity();

        //error between prev error and current err
        float x = d - prevVelocity;
        //pros::lcd::print(7, "p: %f, vel: %f", d, prevVelocity);
        pros::delay(5);
        prevVelocity = d;

        
        float speed = Kfp * p + Kfd * d + Kfx * x;

        flywheel_1.move_velocity((speed) * RUNNING_FLYWHEEL);

        //if rpm drops too much then don't outtake

        pros::lcd::print(7, "flywheel temp: %f", flywheel_1.get_temperature());
        if (!master.get_digital(DIGITAL_DOWN)) {

            if (RUNNING_FLYWHEEL && flywheel_1.get_actual_velocity() >= target_rpm + 50)  {
                intake_roller.move_velocity(-master.get_digital(DIGITAL_L2) * 600);
            }
            else {
                    intake_roller.move_velocity(
            (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)) * 600);


            }

        } else {

            intake_roller.move_velocity(
            (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)) * 600);

        }
        pros::lcd::print(6, "flywheel vel: %f", flywheel_1.get_actual_velocity() * RUNNING_FLYWHEEL);

        Task::delay(1);

    }
}
