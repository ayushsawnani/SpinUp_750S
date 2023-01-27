#include "main.h"

void setDrive(double lB, double lF, double rB, double rF) {

  /*
  leftBack.move_velocity(lB);
  leftFront.move_velocity(lF);
  rightBack.move_velocity(rB);
  rightFront.move_velocity(rF);
  */
  leftBack.move_voltage(lB * 1000);
  leftFront.move_voltage(lF * 1000);
  leftReallyFront.move_voltage(lF * 1000);
  rightBack.move_voltage(rB * 1000);
  rightFront.move_voltage(rF * 1000);
  rightReallyFront.move_voltage(rF * 1000);

    pros::lcd::print(2, "rightBack: %f RPM", rightBack.get_actual_velocity());
  pros::lcd::print(3, "rightFront: %f RPM", rightFront.get_actual_velocity());
  pros::lcd::print(4, "rightThird: %f RPM", rightReallyFront.get_actual_velocity());

}

double voltage(int vel) {
    return vel * 12.0 / 127;
}

void move_drive_tank(void) {
    while (true) {
        double lY = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
        double rX = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_X);

        int lB = lY + rX;
        int lF = lY + rX;
        int rB = lY - rX;
        int rF = lY - rX;

        setDrive(voltage(lB), -voltage(lF), voltage(rB), voltage(rF));
        Task::delay(5);
    }

}



