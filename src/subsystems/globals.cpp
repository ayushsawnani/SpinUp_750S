#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/motors.h"


//for drive, intake/roller, lift
Controller master(CONTROLLER_MASTER);

//for indexer, endgame, expansion
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



Motor leftBack(8, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor leftFront(9, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor leftReallyFront(10, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);

Motor rightBack(6, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightFront(5, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor rightReallyFront(2, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//the wheel to shoot out the disk
Motor flywheel_1(3, MOTOR_GEARSET_06, false, MOTOR_ENCODER_COUNTS);
//Motor catapult(7, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//radio is 1


//takes in the disks and ratcheted to intake roller
Motor intake_roller(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);


ADIDigitalOut blooper('D');
ADIDigitalOut dispenser('E');



/*
    tL        tR
    /         \

        tB
        __
*/

Motor triLeft(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor triRight(1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor triBottom(1, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);


//expands the robot during endgame
Motor expander(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);


Motor dispenser2(1, MOTOR_GEARSET_18);


IMU inertial_sensor(7);






//Motor flywheel_2(16, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

Motor turntable(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

Motor lift(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);




Motor endgame3000('A');





//configure vision sensor
Vision disk_vision_sensor(1);
 Vision roller_vision_sensor(1);

//encoders
//odd port, next highest port, reversed
ADIEncoder encoder_L('A', 'B', false);
ADIEncoder encoder_R('C', 'G', false);
ADIEncoder encoder_B('E', 'F', false);

//motors as encoders
Motor encoderL(1, MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor encoderR(1, MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor encoderS(1, MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);

Distance frontSensor(1);
Distance backSensor(1);


ADIButton limitSwitch('B');


int position_x = 0;
int position_y = 0;

int goal_posx = 0;
int goal_posy = 0;
