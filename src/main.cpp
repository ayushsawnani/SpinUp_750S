#include "main.h"
#include "pros/llemu.hpp"
#include "pros/rtos.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);


	//set signature for the red goal
/*
  	vision_signature_s_t RED_SIG = Vision::signature_from_utility(1, 8973, 11143, 10058, -2119, -1053, -1586, 5.4, 0);
  	vision_sensor.set_signature(1, &RED_SIG); */
	

	

	inertial_sensor.reset();

	
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	//LCD auton selector based on tile we are placed on
	//
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

	//AUTON
	//double_roller_auton();

	single_rollerL_auton();

	//single_rollerR_auton();
	
	//skills();
	

}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {







	bool frightened = true;


	dispenser.set_value(false);
	
	

	//aimbot
	//DONT UNCOMMENT
	/*
	Task anglerTask(fixAnglerOffset, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "angler");

	Task turntableTask(fixTurntableOffset, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "turntable");
	*/


	//driver
	//DO NOT TOUCH THIS
	Task driverControlTask(move_drive_tank, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "driver control");
	Task buildMotorTask(setBuildMotors, TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT, "build");
	//Task flywheelTask(print_flywheel_stuff, TASK_PRIORITY_MIN, TASK_STACK_DEPTH_DEFAULT, "flywheelprinty");

	//auton_run2();

	

	

	
}
