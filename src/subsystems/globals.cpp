#include "main.h"
#include "pros/motors.h"

Controller master(CONTROLLER_MASTER);


/*
    lF     rF
    /       \


    lB     rB
    \       /

*/



Motor leftBack(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor leftFront(2, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor rightFront(3, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor rightBack(4, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);



/*
    tL        tR
    /         \

        tB
        __
*/

Motor triLeft(1, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);
Motor triRight(2, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);
Motor triBottom(3, MOTOR_GEARSET_18, true, MOTOR_ENCODER_COUNTS);


//expands the robot during endgame
Motor expander(10, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//pushes the disk to shoot it
ADIDigitalOut dispenser('A');

//takes in the disks
Motor intake(12, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//rolls the color roller
Motor roller(13, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//angles the outtake
Motor angler(14, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);

//the wheel to shoot out the disk
Motor flywheel(15, MOTOR_GEARSET_18, false, MOTOR_ENCODER_COUNTS);


IMU inertial_sensor(20);
