#include "main.h"

Controller master(E_CONTROLLER_MASTER);


Motor leftBack(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor leftFront(2, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor rightFront(3, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor rightBack(4, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);


//tri left (/) tri right (\) tri bottom (_)

Motor triLeft(1, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor triRight(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor triBottom(3, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
