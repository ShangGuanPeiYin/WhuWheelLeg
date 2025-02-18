#ifndef CODE_BEIYOUPID_H_
#define CODE_BEIYOUPID_H_
#include "zf_common_headfile.h"

typedef struct
{
        float target;
        float ek;
        float ek1;
        float ek2;
        float kp,ki,kd;
        float integral;
        float output;
}PID;

typedef struct
{
        PID pid_roll_speed;
        PID pid_roll;
        PID pid_speed1;
        PID pid_speed2;
        PID pid_increment;
        PID pid_servo;
}PIDinit;

extern PIDinit pid_init;

void PID_init(void);
float PID_Roll(float nowdata,float target,float zero);
float PID_Roll_Speed(float nowdata,float target);
float PID_Speed1(float nowdata, float target);
float PID_Speed2(float nowdata, float target);

#endif /* CODE_PID_H_ */
