#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

Controller master(CONTROLLER_MASTER);
Controller extra(CONTROLLER_PARTNER);




/*
    lF     rF
    /       \


    lB     rB
    \       /

    for x drive

*/



/*

    |   |
    |   |
    |   |

6 wheel tank drive (top down is really front to bacl
w)
*/



Motor leftBack(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor leftFront(9, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor leftThird(17, E_MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightFront(20, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor rightBack(2, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor leftReallyFront(1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor rightReallyFront(1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);



/*
    tL        tR
    /         \

        tB
        __
*/

Motor triLeft(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor triRight(2, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor triBottom(3, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);


//expands the robot during endgame
Motor expander(10, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//pushes the disk to shoot it
ADIDigitalOut dispenser('E');

Motor dispenser2(12, MOTOR_GEARSET_18);


//takes in the disks and ratcheted to intake roller
Motor intake_roller(8, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//the wheel to shoot out the disk
Motor flywheel_1(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//Motor flywheel_2(16, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

Motor turntable(3, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

Motor lift(11, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

ADIDigitalOut endgame('H');


Motor endgame3000('A');


IMU inertial_sensor(19);

//configure vision sensor
Vision disk_vision_sensor(12);
Vision roller_vision_sensor(11);

//encoders
//odd port, next highest port, reversed
ADIEncoder encoder_L('A', 'B', false);
ADIEncoder encoder_R('C', 'G', false);
ADIEncoder encoder_B('E', 'F', false);

//motors as encoders
Motor encoderL(1, MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor encoderR(1, MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor encoderS(1, MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);

Distance frontSensor(19);
Distance backSensor(13);

int position_x = 0;
int position_y = 0;

int goal_posx = 0;
int goal_posy = 0;
