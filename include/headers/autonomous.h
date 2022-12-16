#include "main.h"

void sensorPID(void);

extern void calculateCurrentPosition();

void auton_run1();

void auton_run2();

void auton_run3();

double distance(double x1, double x2, double y1, double y2);

void calculateOdom(double x, double y, double x_0, double y_0, double theta_0);

void movement_PID(double goal_L, double goal_R);

void shauton();

void check_current_encoders();