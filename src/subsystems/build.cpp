#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

static bool INTAKE_RUNNING = false;
static bool FLYWHEEL_RUNNING = false; 

static int RUNNING_FLYWHEEL = 0;
static int RUNNING_INTAKE = 0;

using namespace okapi;

std::shared_ptr<ChassisController> chassis_driver =
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

void setBuildMotors() {
    //In C++, 1 is true and 0 is false
    
    while(true){ //DONT TOUCH THIS
        //MASTER
        //TOGGLING
        //intake
        if (master.get_digital(DIGITAL_A)) {
            RUNNING_INTAKE = !RUNNING_INTAKE;
            pros::delay(500);
        }    
        intake_roller.move_velocity(RUNNING_INTAKE * 200);

        if (master.get_digital(DIGITAL_Y)) {
            chassis_driver->turnAngle((inertial_sensor.get_heading()) * degree);
        }

        //PNEUMATICS
        //either true or false
        dispenser.set_value(master.get_digital(DIGITAL_R2));

        //flywheel
        if (master.get_digital(DIGITAL_B)) {
            RUNNING_FLYWHEEL = !RUNNING_FLYWHEEL;
            //NORMAL DELAY IN CASE YOU WANNA USE
            pros::delay(500);
        }    
        flywheel_1.move_velocity(RUNNING_FLYWHEEL * 600);



        //PRESSING ONE BUTTON TO MOVE FORWARD AND ONE BUTTON TO MOVE BACKWARD

        //1 - 0 * 200, 0 - 1 * 200, 0 - 0 * 200, 1 - 1 * 200

        //PARTNER
        /*turntable.move_velocity((extra.get_digital(DIGITAL_L1) - extra.get_digital(DIGITAL_R1)) * 100);


        

         */
        
        //DIFFERENT FROM THE REGULAR DELAY THIS IS FOR MULTITASKING
        Task::delay(5);

        
    }

    


    
    
}