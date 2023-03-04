#include "main.h"
#include "pros/adi.hpp"


extern Controller master;
extern Controller extra;

extern Motor leftBack, leftFront, rightBack, rightFront, leftReallyFront, rightReallyFront;

extern Motor triLeft, triRight, triBottom;

extern Motor catapult;

//extern Motor expander;
extern ADIDigitalOut dispenser; //pneumatics

extern Motor endgame3000;

extern ADIDigitalOut blooper;

extern ADIDigitalOut endgame;


extern Motor dispenser2;

extern Motor intake_roller;

extern Motor flywheel_1;
extern Motor flywheel_2;

extern ADIButton limitSwitch;

extern Motor lift;

extern Motor turntable;

extern IMU inertial_sensor;
extern Vision disk_vision_sensor;
extern Vision roller_vision_sensor;

extern ADIEncoder encoder_L;
extern ADIEncoder encoder_R;

extern ADIEncoder encoder_B;

extern Distance frontSensor;
extern Distance backSensor;

extern Motor encoderL;
extern Motor encoderR;
extern Motor encoderS;

extern int position_x;
extern int position_y;
extern int goal_posx;
extern int goal_posy;