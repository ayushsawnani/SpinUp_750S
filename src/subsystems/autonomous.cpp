#include "main.h"

void drivePID(void) {

    //tuning

    //rise time = time it takes to get to the desired value
    //overshoot = how much farther ur robot goes from the val
    //settling time = time it takes to settle back to normal after there has been a change
    //steady state error = the error (if any) when pid is complete
    //stability = smoothness


    //rise time decreases, overshoot increases, steady state error decreases, stability worsens
    double K_p = 1.0;

    //overshoot decreases, settling time decreases, stability improves IF NOT TOO MUCH
    double K_d = 1.0;

    //rise time decreases, overshoot increases, settling time increases, steady state error decreases, stability worsens
    double K_i = 1.0;

    //tune kP until robot oscillates slightly
    //tune kD until the steady state error decreases to smth normal
    //tune kI until the steady state error and any disturbances are minimized (can be 0)

    double prevOffset = 0;
    double totalOffset = 0;

    //goal is to reach 50mm distance for distance sensor

    //wheel diameter is ___ cm
    

    //calculate current offset (p)
    //p = current distance sensor reading - 50mm

    //calculate rate of change (d) (when oscillating around value) so we can speed up or slow down a bit
    //d = offset - prev offset
    //wait 1 ms
    //prev offset = offset


    //calculate total offset (i) (any remaining error) only if error is less than or equal to 0 and if the error is small
    //if error >= 100mm or smth then i = 0
    //else i += offset
    

    //pid = p * kp + i * ki + d * kd
    
    

    
}