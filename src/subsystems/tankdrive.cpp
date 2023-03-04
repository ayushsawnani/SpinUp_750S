#include "main.h"
#include "pros/llemu.hpp"

void setDrive(double lB, double lF, double rB, double rF) {

  /*
  leftBack.move_velocity(lB);
  leftFront.move_velocity(lF);
  rightBack.move_velocity(rB);
  rightFront.move_velocity(rF);
  */

  lcd::print(5, "lb: %f", lB);
  leftBack.move_voltage(lB * 1000);
  leftFront.move_voltage(lF * 1000);
  rightBack.move_voltage(rB * 1000);
  rightFront.move_voltage(rF * -1000);

  leftReallyFront.move_voltage(lF * 1000);
  rightReallyFront.move_voltage(rF * 1000);

//   leftBack.move_velocity(lB * -1000);
//   leftFront.move_velocity(lF * 1000);
//   rightBack.move_velocity(rB * 1000);
//   rightFront.move_velocity(rF * 1000);

//   leftReallyFront.move_velocity(lF * 1000);
//   rightReallyFront.move_velocity(rF * 1000);

  double rCurr = rightReallyFront.get_current_draw()/1000.0;
  double lCurr = leftReallyFront.get_current_draw()/1000.0;

  lcd::print(1, "Right Side: %f", rightBack.get_voltage());
  lcd::print(2, "Left Side: %f", leftBack.get_voltage());


}

double voltage(int vel) {
    //ratio from voltage to velocity
    return vel * 12.0 / 127;
}

void move_drive_tank(void) {

    
    while (true) {



        //getting the analog values from the joystick
        double lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        double rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

        //applying power equation
        int lB = lY + rX;
        int lF = lY + rX;
        int rB = lY - rX;
        int rF = lY - rX;
        // pros::lcd::print(2, "lY: %f RPM", (lY + rX));
        // pros::lcd::print(3, "rX: %f RPM", (lY - rX));

        pros::lcd::print(4, "lB: %f, rB: %f",voltage(lY + rX), voltage(lY - rX) );


        //sets the motor values to the current voltage
        setDrive(voltage(lB), voltage(lF), voltage(rB), voltage(rF));
        Task::delay(5);
    }

}



