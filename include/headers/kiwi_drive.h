#include "main.h"

void setDrive(int tL, int tR, int tB);

void calculateKiwiMotorSpeed(void);

double calculate_kiwi_angle(int lX, int lY, double angle);

double calculate_kiwi_angle_speed(int lX, int lY, double motor_angle, int rX, int reversed);

double calculate_kiwi_volt_speed(double speed);