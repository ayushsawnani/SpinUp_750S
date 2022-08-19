#include "main.h"
#include "pros/rtos.hpp"

static bool INTAKE_RUNNING = false;
static bool FLYWHEEL_RUNNING = false; 

static int RUNNING = 0;

void setBuildMotors() {
    //In C++, 1 is true and 0 is false
    
    while(true){ //DONT TOUCH THIS

        //TOGGLING
        if (master.get_digital(DIGITAL_A)) {
            RUNNING = !RUNNING;

            //NORMAL DELAY IN CASE YOU WANNA USE
            delay(500);
        }    
        flywheel_1.move_velocity(RUNNING * 200);
        flywheel_2.move_velocity(RUNNING * 200);
        lcd::print(1, "RUNNING: %d", RUNNING);

        //PNEUMATICS
        //either true or false
        dispenser.set_value(master.get_digital(DIGITAL_R2));

        //PRESSING ONE BUTTON TO MOVE

        //1 * 200 or 0 * 200
        //expander.move_velocity(master.get_digital(DIGITAL_B) * 200);

        //PRESSING ONE BUTTON TO MOVE FORWARD AND ONE BUTTON TO MOVE BACKWARD

        //1 - 0 * 200, 0 - 1 * 200, 0 - 0 * 200, 1 - 1 * 200
        intake_roller.move_velocity((master.get_digital(DIGITAL_L2) - master.get_digital(DIGITAL_L1) )* 200);
        
        //DIFFERENT FROM THE REGULAR DELAY THIS IS FOR MULTITASKING
        Task::delay(5);
    }

    


    
    
}