#include "main.h"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

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


        if (master.get_digital(DIGITAL_X)) {
            running_endgame = !running_endgame;
            pros::delay(250);
        }

        if (master.get_digital(DIGITAL_R1)) {
            RUNNING_FLYWHEEL = !RUNNING_FLYWHEEL;
            pros::delay(250);
        }



        flywheel_1.move_velocity(RUNNING_FLYWHEEL * 600);

        dispenser2.move_velocity(master.get_digital(DIGITAL_A) * 200);

        lift.move_velocity(
            (master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN)) * 200);

        intake_roller.move_velocity(
            (master.get_digital(DIGITAL_L1) - master.get_digital(DIGITAL_L2)) * 200);

        endgame.set_value(running_endgame);

        catapult.move_velocity((master.get_digital(DIGITAL_A) - !limitSwitch.get_value()) * 200);

        

        //DIFFERENT FROM THE REGULAR DELAY THIS IS FOR MULTITASKING
        Task::delay(5);



        
    }
    
}
