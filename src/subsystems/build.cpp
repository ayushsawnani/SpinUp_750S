#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

static bool INTAKE_RUNNING = false;
static bool FLYWHEEL_RUNNING = false; 

static int RUNNING_FLYWHEEL = 0;
static int RUNNING_INTAKE = 0;

static int SHABALO = 0;

static bool printint_controller = false;




void setBuildMotors() {
    //In C++, 1 is true and 0 is false
    
    while(true){ //DONT TOUCH THIS
        //MASTER
        //TOGGLING
        //intake   
        dispenser.set_value(false);



        lcd::print(1, "Inertial heading: %f", inertial_sensor.get_heading());

        // if (master.get_digital(DIGITAL_Y)) {
        //     SHABALO = !SHABALO;
        //     pros::delay(200);
        // }

        

        // if (SHABALO) {
        //     //1 is red, 2 is blue

        //     while (true){
        //         vision_object_s_t rtn = roller_vision_sensor.get_by_sig(0, 1);
        //         double offset = CX - (rtn.left_coord + (double)rtn.width/2);

        //         if (std::abs(offset) < 5) break;

        //         leftBack.move_velocity(offset);
        //         leftFront.move_velocity(offset);
        //         rightBack.move_velocity(offset);
        //         rightFront.move_velocity(offset);
        //     }






        //     leftBack.move_velocity(0);
        //     leftFront.move_velocity(0);
        //     rightBack.move_velocity(0);
        //     rightFront.move_velocity(0);

            
        //     //chassis_driver->waitUntilSettled();
        // }

        //PNEUMATICS
        //either true or false
        if (master.get_digital(DIGITAL_A)) {
            //dispenser.set_value(true);
            dispenser2.move_velocity(200);

            //NORMAL DELAY IN CASE YOU WANNA USE
            pros::delay(950);
            dispenser2.move_velocity(0);
            pros::delay(5);
            dispenser2.move_velocity(-200);
            pros::delay(200);
            dispenser2.move_velocity(0);

            //dispenser.set_value(false);
        }  

        if (master.get_digital(DIGITAL_R1)) {
            RUNNING_FLYWHEEL = !RUNNING_FLYWHEEL;
            pros::delay(250);
        }

        


 
        flywheel_1.move_velocity(RUNNING_FLYWHEEL * -600);

        intake_roller.move_velocity((master.get_digital(DIGITAL_L2) - master.get_digital(DIGITAL_L1)) * 200);



        //PRESSING ONE BUTTON TO MOVE FORWARD AND ONE BUTTON TO MOVE BACKWARD

        //1 - 0 * 200, 0 - 1 * 200, 0 - 0 * 200, 1 - 1 * 200

        //PARTNER
        /*turntable.move_velocity((extra.get_digital(DIGITAL_L1) - extra.get_digital(DIGITAL_R1)) * 100);


        

         */
        
        //DIFFERENT FROM THE REGULAR DELAY THIS IS FOR MULTITASKING
        Task::delay(5);

        
    }

    


    
    
}

void print_flywheel_stuff(void) {
    while(true) {

        if (master.get_digital(DIGITAL_DOWN)) {
            printint_controller = !printint_controller;
        }

        master.print(1, 0, "%d", (printint_controller ? flywheel_1.get_actual_velocity() * 7 : (flywheel_1.get_temperature() * (9.0/5) + 32)) );

        if (flywheel_1.get_temperature() > 38 ) {
            master.rumble("* * *");
        }

        
    }
}