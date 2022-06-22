#include "main.h"

static bool INTAKE_RUNNING = false;
static bool FLYWHEEL_RUNNING = false; 
void setBuildMotors() {

    //sets the dispenser
    dispenser.set_value(master.get_digital(DIGITAL_R2));

    //sets the angler motor
    angler.move_velocity((master.get_digital(DIGITAL_UP) - master.get_digital(DIGITAL_DOWN) )* 200);

    //set roller motor
    roller.move_velocity((master.get_digital(DIGITAL_L2) - master.get_digital(DIGITAL_L1) )* 200);

    //sets expansion
    expander.move_velocity(master.get_digital(DIGITAL_B) * 200);

    //toggles intake motors
    if (master.get_digital(DIGITAL_A)) INTAKE_RUNNING = !INTAKE_RUNNING;
    intake.move_velocity(INTAKE_RUNNING * 200);

    //toggles flywheel motors
    if (master.get_digital(DIGITAL_R1)) FLYWHEEL_RUNNING = !FLYWHEEL_RUNNING;
    intake.move_velocity(FLYWHEEL_RUNNING * 200);

    
    
}