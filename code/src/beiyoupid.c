#include "beiyoupid.h"

PIDinit pid_init;

/**
 * @brief PID������ʼ��
 * ���԰�ÿ��PID�Ĳ�������������
 */
void PID_init(void)//��ʼ�����в���
{
    //���ٶ�����ʽ
    pid_init.pid_roll_speed.target = 0;
    pid_init.pid_roll_speed.ek = 0;
    pid_init.pid_roll_speed.ek1 = 0;
    pid_init.pid_roll_speed.ek2 = 0;
    pid_init.pid_roll_speed.kp = 4.5;
    pid_init.pid_roll_speed.ki = 0.145;
    pid_init.pid_roll_speed.kd = 0.45;
    pid_init.pid_roll_speed.integral = 0;
    pid_init.pid_roll_speed.output = 0;

    //�ǶȻ�λ��ʽ
    pid_init.pid_roll.target = 0;
    pid_init.pid_roll.ek = 0;
    pid_init.pid_roll.ek1 = 0;
    pid_init.pid_roll.kp = 4.5;
    pid_init.pid_roll.ki = 0;
    pid_init.pid_roll.kd = 0;
    pid_init.pid_roll.integral = 0;
    pid_init.pid_roll.output = 0;

    //�����ٶȻ�
    pid_init.pid_speed1.target = 0;//
    pid_init.pid_speed1.ek = 0;
    pid_init.pid_speed1.ek1 = 0;
    pid_init.pid_speed1.ek2 = 0;
    pid_init.pid_speed1.kp = 0.005;
    pid_init.pid_speed1.ki = 0.001;
    pid_init.pid_speed1.kd = 0;
    pid_init.pid_speed1.integral = 0;
    pid_init.pid_speed1.output = 0;

    //�����ٶȻ�
    pid_init.pid_speed2.target = 0;//
    pid_init.pid_speed2.ek = 0;
    pid_init.pid_speed2.ek1 = 0;
    pid_init.pid_speed2.ek2 = 0;
    pid_init.pid_speed2.kp = 0.005;
    pid_init.pid_speed2.ki = 0.001;
    pid_init.pid_speed2.kd = 0;
    pid_init.pid_speed2.integral = 0;
    pid_init.pid_speed2.output = 0;

    pid_init.pid_servo.target = 0;
    pid_init.pid_servo.ek = 0;
    pid_init.pid_servo.ek1 = 0;
    pid_init.pid_servo.kp = 0;
    pid_init.pid_servo.ki = 0;
    pid_init.pid_servo.kd = 0;
    pid_init.pid_servo.integral = 0;
    pid_init.pid_servo.output = 0;

}

/**
 * @brief λ��ʽPID
 * nowdata�ǵ�ǰ���ݣ�target��Ŀ��ֵ
 * ��������Ҫ�޷�����ֹ�����ۼ�
 * ������������Ҫ��Ҫ�޷�
 */
float PID_Roll(float nowdata,float target,float zero)//λ��ʽPID1
{
    pid_init.pid_roll.ek = target - nowdata - zero;
    pid_init.pid_roll.integral += pid_init.pid_roll.ek;
    pid_init.pid_roll.output = pid_init.pid_roll.kp * pid_init.pid_roll.ek +
                                   pid_init.pid_roll.ki * pid_init.pid_roll.integral +
                                   pid_init.pid_roll.kd * (pid_init.pid_roll.ek - pid_init.pid_roll.ek1);

    pid_init.pid_roll.ek1 = pid_init.pid_roll.ek;

    // �����޷�
    if (pid_init.pid_roll.integral > 5000)
        pid_init.pid_roll.integral = 5000;
   if (pid_init.pid_roll.integral < -5000)
       pid_init.pid_roll.integral = -5000;

    return pid_init.pid_roll.output;
}
float PID_Speed1(float nowdata, float target)//����ʽ���ٶȻ�1
{
    pid_init.pid_speed1.ek = target - nowdata;
    pid_init.pid_speed1.integral += pid_init.pid_speed1.ek;
    pid_init.pid_speed1.output += pid_init.pid_speed1.kp * (pid_init.pid_speed1.ek - pid_init.pid_speed1.ek1) +
                                     pid_init.pid_speed1.ki * pid_init.pid_speed1.ek +
                                     pid_init.pid_speed1.kd * (pid_init.pid_speed1.ek - 2.0f * pid_init.pid_speed1.ek1 + pid_init.pid_speed1.ek2);

    pid_init.pid_speed1.ek2 = pid_init.pid_speed1.ek1;
    pid_init.pid_speed1.ek1 = pid_init.pid_speed1.ek;

    // ����޷�
    if (pid_init.pid_speed1.output > 67.5)
        pid_init.pid_speed1.output = 67.5;
    if (pid_init.pid_speed1.output < -67.5)
        pid_init.pid_speed1.output = -67.5;

    return pid_init.pid_speed1.output;
}

float PID_Speed2(float nowdata, float target)//����ʽ���ٶȻ�2
{
    pid_init.pid_speed2.ek = target - nowdata;
    pid_init.pid_speed2.integral += pid_init.pid_speed2.ek;
    pid_init.pid_speed2.output += pid_init.pid_speed2.kp * (pid_init.pid_speed2.ek - pid_init.pid_speed2.ek1) +
                                     pid_init.pid_speed2.ki * pid_init.pid_speed2.ek +
                                     pid_init.pid_speed2.kd * (pid_init.pid_speed2.ek - 2.0f * pid_init.pid_speed2.ek1 + pid_init.pid_speed2.ek2);

    pid_init.pid_speed2.ek2 = pid_init.pid_speed2.ek1;
    pid_init.pid_speed2.ek1 = pid_init.pid_speed2.ek;

    // ����޷�
    if (pid_init.pid_speed2.output > 67.5)
        pid_init.pid_speed2.output = 67.5;
    if (pid_init.pid_speed2.output < -67.5)
        pid_init.pid_speed2.output = -67.5;

    return pid_init.pid_speed2.output;
}

/**
 * @brief ����ʽPID
 * nowdata�ǵ�ǰ���ݣ�target��Ŀ��ֵ
 * ������һ�㲻��Ҫ�޷���ֻ��Ҫ������޷�
 */
//���ٶ�
float PID_Roll_Speed(float nowdata, float target)//���ٶ�����ʽ
{
    pid_init.pid_roll_speed.ek = target - nowdata;
    pid_init.pid_roll_speed.integral += pid_init.pid_roll_speed.ek;
    pid_init.pid_roll_speed.output += pid_init.pid_roll_speed.kp * (pid_init.pid_roll_speed.ek - pid_init.pid_roll_speed.ek1) +
                                     pid_init.pid_roll_speed.ki * pid_init.pid_roll_speed.ek +
                                     pid_init.pid_roll_speed.kd * (pid_init.pid_roll_speed.ek - 2.0f * pid_init.pid_roll_speed.ek1 + pid_init.pid_roll_speed.ek2);

    pid_init.pid_roll_speed.ek2 = pid_init.pid_roll_speed.ek1;
    pid_init.pid_roll_speed.ek1 = pid_init.pid_roll_speed.ek;

    // ����޷�
    if (pid_init.pid_roll_speed.output > 5000)
        pid_init.pid_roll_speed.output = 5000;
    if (pid_init.pid_roll_speed.output < -5000)
        pid_init.pid_roll_speed.output = -5000;

    return pid_init.pid_roll_speed.output;
}
float PID_SERVO(float nowdata, float target)
{
        pid_init.pid_servo.ek = target - nowdata;
        pid_init.pid_servo.integral += pid_init.pid_servo.ek;
        pid_init.pid_servo.output = pid_init.pid_servo.kp * pid_init.pid_servo.ek +
                                       pid_init.pid_servo.ki * pid_init.pid_servo.integral +
                                       pid_init.pid_servo.kd * (pid_init.pid_servo.ek - pid_init.pid_servo.ek1);

        pid_init.pid_servo.ek1 = pid_init.pid_servo.ek;

        // �����޷�
        if (pid_init.pid_servo.integral > 5000)
            pid_init.pid_servo.integral = 5000;
       if (pid_init.pid_servo.integral < -5000)
           pid_init.pid_servo.integral = -5000;

        return pid_init.pid_servo.output;
}
