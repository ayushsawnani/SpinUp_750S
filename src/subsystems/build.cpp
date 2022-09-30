#include "main.h"
#include "pros/rtos.hpp"

static bool INTAKE_RUNNING = false;
static bool FLYWHEEL_RUNNING = false; 

static int RUNNING_FLYWHEEL = 0;
static int RUNNING_INTAKE = 0;

void setBuildMotors() {
    //In C++, 1 is true and 0 is false
    
    while(true){ //DONT TOUCH THIS
        //MASTER
        //TOGGLING
        //intake
        if (master.get_digital(DIGITAL_A)) {
            RUNNING_INTAKE = !RUNNING_INTAKE;
            delay(500);
        }    
        intake_roller.move_velocity(RUNNING_INTAKE * 200);



        //PRESSING ONE BUTTON TO MOVE FORWARD AND ONE BUTTON TO MOVE BACKWARD

        //1 - 0 * 200, 0 - 1 * 200, 0 - 0 * 200, 1 - 1 * 200

        //PARTNER
        turntable.move_velocity((extra.get_digital(DIGITAL_L1) - extra.get_digital(DIGITAL_R1)) * 100);


        //PNEUMATICS
        //either true or false
        dispenser.set_value(extra.get_digital(DIGITAL_R2));

        //flywheel
        if (extra.get_digital(DIGITAL_B)) {
            RUNNING_FLYWHEEL = !RUNNING_FLYWHEEL;
            //NORMAL DELAY IN CASE YOU WANNA USE
            delay(500);
        }    
        flywheel_1.move_velocity(RUNNING_FLYWHEEL * 600);
        
        //DIFFERENT FROM THE REGULAR DELAY THIS IS FOR MULTITASKING
        Task::delay(5);

        
    }

    


    
    
}