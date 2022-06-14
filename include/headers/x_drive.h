#include "main.h"


void setDrive(int lB, int lF, int rB, int rF);

void calculateXMotorSpeed(void);

double calculate_angle(double lX, double lY, double angle);

double calculate_angle_speed(double lX, double lY, double motor_angle, int rX, int reversed);

double calculate_volt_speed(double speed);
