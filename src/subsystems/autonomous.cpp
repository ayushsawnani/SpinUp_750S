#include "main.h"
#include <cmath>

void sensorPID(void) {

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



double distance(double x1, double x2, double y1, double y2){
    return std::sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
}

//calculates constant rpm to move from current position to x, y in inches
static double d_L;
static double d_R;

static double S_L = 9;
static double S_R = 9;

void calculateOdom(double x, double y, double x_0, double y_0, double theta_0) {
    
    double half_angle = atan( (1/tan( (theta_0 * M_PI)/360 ))) * (180/M_PI);

    double mid_d = 0.5 * distance(x, x_0, y, y_0);

    double height = tan((half_angle * M_PI)/180) * mid_d;

    double radius = sqrt((mid_d)*(mid_d) + (height * height));

    double radius_r = radius - S_L;

    d_R = radius_r * (theta_0 * M_PI/180);

    d_L = (theta_0 * M_PI/180) * (S_L + S_R) + d_R;

}

void movement_PID(){
    //refer to drivePID for info

    //left side pid
    double LK_p = 1.0;
    double LK_d = 1.0;
    double LK_i = 1.0;

    //right side pid
    double RK_p = 1.0;
    double RK_d = 1.0;
    double RK_i = 1.0;

    double prevOffset_L = 0;
    double totalOffset_L = 0;
    double prevOffset_R = 0;
    double totalOffset_R = 0;
    double i_L = 0;
    double i_R = 0;

    while(true){
        double p_L = encoder_L.get_value() - d_L;
        double p_R = encoder_R.get_value() - d_R;

        double dL = p_L - prevOffset_L;
        Task::delay(1);
        prevOffset_L = p_L;

        double dR = p_R - prevOffset_R;
        Task::delay(1);
        prevOffset_R = p_R;



        if (p_L >= -100 && p_L < 0) {
            i_L = 0;
        }
        else {
            i_L +=  p_L;
        }

        if (p_R >= -100 && p_R < 0) {
            i_R = 0;
        }
        else {
            i_R +=  p_R;
        }

        double rpm_L = p_L * LK_p + d_L * LK_d + i_L * LK_i;
        double rpm_R = p_R * RK_p + d_R * RK_d + i_R * RK_i;
        Task::delay(5);
    }

}

void check_current_encoders(double x_0, double y_0, double theta_0){
    
    //checks the current position through encoders for L, R, and B
    while(true) {
        double eL = encoder_L.get_value();
        double eR = encoder_R.get_value();
        double eB = encoder_B.get_value();
    
        calculateOdom(eL, eR, x_0, y_0, theta_0);

        Task::delay(10);
    }
} 