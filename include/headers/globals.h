#include "main.h"
#include "pros/adi.hpp"


extern Controller master;
extern Controller extra;

extern Motor leftBack, leftFront, rightBack, rightFront;

extern Motor triLeft, triRight, triBottom;

//extern Motor expander;
extern ADIDigitalOut dispenser; //pneumatics

extern Motor intake_roller;

extern Motor flywheel_1;
extern Motor flywheel_2;

extern Motor turntable;

extern IMU inertial_sensor;
extern Vision vision_sensor;

extern ADIEncoder encoder_L;
extern ADIEncoder encoder_R;

extern ADIEncoder encoder_B;

extern Distance frontSensor;
extern Distance backSensor;