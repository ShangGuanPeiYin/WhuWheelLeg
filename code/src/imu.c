#include "zf_common_headfile.h"
#define pi acos(-1.0)

IMUType IMUdata;
#include "imu.h"

_IMU IMU = {0};

void IMU_init(void)
{
   //imu963ra_init();                                    // ��ʼ�� IMU963RA
    imu660ra_init();
}

// float Yawrate = 0.0f;
// float Turn_Speed=0.0f;
/**************************ʵ�ֺ���*********************************************************************
��  ����static float invSqrt(float x)
������: ���ټ��� 1/Sqrt(x)
��  ����Ҫ�����ֵ
����ֵ�����
��  ע������ͨSqrt()����Ҫ���ı�See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
*********************************************************************************************************/
static float invSqrt(float x)
{
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *)&i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}
void IMU_getdata(void)
{
    imu963ra_get_acc();                                     // ��ȡ IMU963RA ���ٶȼ�����
    imu963ra_get_gyro();                                     // ��ȡ IMU963RA ����������
    imu963ra_get_mag();                                     // ��ȡ IMU963RA ����������

    IMUdata.dataOri.accel.x=imu963ra_acc_transition(imu963ra_acc_x);
    IMUdata.dataOri.accel.y=imu963ra_acc_transition(imu963ra_acc_y);
    IMUdata.dataOri.accel.z=imu963ra_acc_transition(imu963ra_acc_z);

    IMUdata.dataOri.angle.x=imu963ra_gyro_transition(imu963ra_gyro_x);
    IMUdata.dataOri.angle.y=imu963ra_gyro_transition(imu963ra_gyro_y);
    IMUdata.dataOri.angle.z=imu963ra_gyro_transition(imu963ra_gyro_z);

    IMUdata.dataOri.mag.x=imu963ra_mag_transition(imu963ra_mag_x);
    IMUdata.dataOri.mag.y=imu963ra_mag_transition(imu963ra_mag_y);
    IMUdata.dataOri.mag.z=imu963ra_mag_transition(imu963ra_mag_z);

}

/**
 ******************************************************************************
 * ��������: Get_Attitude
 * ��������: ��ȡ������ԭʼ���ݣ������г�������
 * �����������:   ��
 * �����������:   ��
 * ʹ�÷�������user_c/isr.c�ļ� TIM7_IRQHandler �����е��ã��ڱ����޸ļ���ʵ���ж�����ע�⣬�ڶ�ʱ���жϳ�ʼ��ʱ���Ѿ���������ռ���ȼ�����Ϊ3,�����ȼ�����Ϊ1��
 * ��һ���޸�����   ��   2023��04��07�� ��κ��ࣩ
 ******************************************************************************
 */
void Get_Attitude()
{
//    //    static _Attitude Acc_filtold,Gyr_filtold;
//    /******************��ȡ������ԭʼ����******************/
//    imu963ra_get_acc();                                     // ��ȡ IMU963RA ���ٶȼ�����
//    imu963ra_get_gyro();                                     // ��ȡ IMU963RA ����������
//    /******************�����Ǽ��ٶ�ADֵ ת���� ��/ƽ���� ******************/
//    IMU.T_Acc.x = -(imu963ra_acc_transition(imu963ra_acc_x)-0);
//    IMU.T_Acc.y = -(imu963ra_acc_transition(imu963ra_acc_z)-0);
//    IMU.T_Acc.z = -(imu963ra_acc_transition(imu963ra_acc_y)-0);
//    /******************�����ǽ��ٶ�ADֵ ת���� ����/�루��������Ʈ���� ******************/
//    IMU.T_Gyro.x = -(imu963ra_gyro_transition(imu963ra_gyro_x)   - 0.07508);//TODO:��Ư����
//    IMU.T_Gyro.y = -(imu963ra_gyro_transition(imu963ra_gyro_z)   + 0.003024);
//    IMU.T_Gyro.z = -(imu963ra_gyro_transition(imu963ra_gyro_y)   + 0.118375);
//    /******************��ȡ��̬�Ƕ� ******************/
//    IMUupdate(&(IMU.T_Gyro), &(IMU.T_Acc), &(IMU.T_Mag), &(IMU.Angle));
//    /******************��ȡ��̬���ٶ� ******************/
//    IMU.Gyro.x = IMU.T_Gyro.x * Radian_2_Degree;// - Balance_Correct_GyroX;//TODO:Ӳ��λ�ò���
//    IMU.Gyro.y = IMU.T_Gyro.y * Radian_2_Degree;// - Balance_Correct_GyroY;
//    IMU.Gyro.z = IMU.T_Gyro.z * Radian_2_Degree;
    imu660ra_get_acc();
    imu660ra_get_gyro();
    /******************�����Ǽ��ٶ�ADֵ ת���� ��/ƽ���� ******************/
    IMU.T_Acc.x = (float)imu660ra_acc_x * Acc_Gain * G;
    IMU.T_Acc.y = (float)imu660ra_acc_y * Acc_Gain * G;
    IMU.T_Acc.z = (float)imu660ra_acc_z * Acc_Gain * G;
    /******************�����ǽ��ٶ�ADֵ ת���� ����/�루��������Ʈ���� ******************/
    IMU.T_Gyro.x = (float)imu660ra_gyro_x * Gyro_Gr + 0;
    IMU.T_Gyro.y = (float)imu660ra_gyro_y * Gyro_Gr + 0;
    IMU.T_Gyro.z = (float)imu660ra_gyro_z * Gyro_Gr + 0;
    /******************��ȡ��̬�Ƕ� ******************/
    IMUupdate(&(IMU.T_Gyro), &(IMU.T_Acc), &(IMU.T_Mag), &(IMU.Angle));
    /******************��ȡ��̬���ٶ� ******************/
    IMU.Gyro.x = IMU.T_Gyro.x * Radian_2_Degree;// - Balance_Correct_GyroX;
    IMU.Gyro.y = IMU.T_Gyro.y * Radian_2_Degree;// - Balance_Correct_GyroY;
    IMU.Gyro.z = IMU.T_Gyro.z * Radian_2_Degree;

    // ���ٶ�һ���˲�
    static float last_YPitchrate = 0;
    float Ya = 0.7;
    IMU.Gyro.y = last_YPitchrate * Ya + IMU.Gyro.y * (1 - Ya);
    last_YPitchrate = IMU.Gyro.y;

    // ���ٶ�һ���˲�
    static float last_XPitchrate = 0;
    float Xa = 0.7;
    IMU.Gyro.x = last_XPitchrate * Xa + IMU.Gyro.x * (1 - Xa);
    last_XPitchrate = IMU.Gyro.x;

    static float last_ZPitchrate = 0;
    float Za = 0.7;
    IMU.Gyro.z = last_ZPitchrate * Za + IMU.Gyro.z * (1 - Za);
    last_ZPitchrate = IMU.Gyro.z;

    IMUdata.dataOri.pitch=(IMU.Angle.y+1.6);///TODO:������е��ֵ
    IMUdata.dataOri.roll=IMU.Angle.x;
    IMUdata.dataOri.yaw=-IMU.Angle.z;


    IMUdata.dataOri.angle.x=IMU.Gyro.y-0.1;//TODO:����ϸ�»���Ư
    IMUdata.dataOri.angle.y=IMU.Gyro.x;
    IMUdata.dataOri.angle.z=IMU.Gyro.z;
}

float acc_ratio = 1.6;   // ���ٶȼƱ���
float gyro_ratio = 4.08; // �����Ǳ���
/**
 ******************************************************************************
 * ��������:һ�׻����˲�
 * ��������: ��ȡ������ԭʼ���ݣ������г�������
 * �����������:   ��
 * �����������:   ��
 * ʹ�÷�������user_c/isr.c�ļ� TIM7_IRQHandler �����е��ã��ڱ����޸ļ���ʵ���ж�����ע�⣬�ڶ�ʱ���жϳ�ʼ��ʱ���Ѿ���������ռ���ȼ�����Ϊ3,�����ȼ�����Ϊ1��
 * ��һ���޸�����   ��   2023��04��07�� ��κ��ࣩ
 ******************************************************************************
 */
float angle_calc(float angle_m, float gyro_m, int index)
{
    float temp_angle;
    float gyro_now;
    float error_angle;
    static float last_angle[3];
    static uint8 first_angle[3];

    if (!first_angle[index]) // �ж��Ƿ�Ϊ��һ�����б�����
    {
        // ����ǵ�һ�����У����ϴνǶ�ֵ����Ϊ����ٶ�ֵһ��
        first_angle[index] = 1;
        last_angle[index] = angle_m;
    }
    gyro_now = gyro_m * gyro_ratio;
    // ���ݲ������ļ��ٶ�ֵת��Ϊ�Ƕ�֮�����ϴεĽǶ�ֵ��ƫ��
    error_angle = (angle_m - last_angle[index]) * acc_ratio;
    // ����ƫ���������ǲ����õ��ĽǶ�ֵ���㵱ǰ�Ƕ�ֵ
    temp_angle = last_angle[index] + (error_angle + gyro_now) * Sampling_Time;
    // ���浱ǰ�Ƕ�ֵ
    last_angle[index] = temp_angle;

    return temp_angle;
}

/*********************************************************************************************************
 *��  ����void IMUupdate(FLOAT_XYZ *Gyr_rad,FLOAT_XYZ *Acc_filt,FLOAT_ANGLE *Att_Angle)
 *�����ܣ���ȡ��̬��
 *��  ����  Gyr_rad ָ����ٶȵ�ָ�루ע�ⵥλ�����ǻ��ȣ�
 *        Acc_filt ָ����ٶȵ�ָ��
 *        Mag_filt ָ��ش�ǿ�ȵ�ָ��
 *        Att_Angle ָ����̬�ǵ�ָ��
 *����ֵ����
 *��  ע�������Ԫ����ŷ���Ƕ��ڴ˺��������
 **********************************************************************************************************/
// kp=ki=0 ������ȫ����������
#define Kp 2.0f                        // ����������Ƽ��ٶȼƣ������Ƶ���������
#define Ki 0.01f                       // ���������������ƫ��������ٶ�
#define halfT (Sampling_Time / 2)      // �������ڵ�һ��
float q0 = 1, q1 = 0, q2 = 0, q3 = 0;  // quaternion elements representing the estimated orientation
float exInt = 0, eyInt = 0, ezInt = 0; // scaled integral error
void IMUupdate(_Attitude *Gyr_rad, _Attitude *Acc_filt, _Attitude *Mag_filt, _Attitude *Att_Angle)
{
    float ax = Acc_filt->x, ay = Acc_filt->y, az = Acc_filt->z;
    float gx = Gyr_rad->x, gy = Gyr_rad->y, gz = Gyr_rad->z;
    float mx = Mag_filt->x, my = Mag_filt->y, mz = Mag_filt->z;
    float hx, hy, hz, bx, bz;
    float vx, vy, vz, wx, wy, wz;
    float ex, ey, ez;
    float norm;

    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;

    if (ax * ay * az == 0)
        return;

    // ���ٶȼƲ�������������(��������ϵ)
    norm = invSqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

//    norm = invSqrt(mx * mx + my * my + mz * mz);
//    mx = mx / norm;
//    my = my / norm;
//    mz = mz / norm;
//
//    // ����������ϵ�еĵشżƷ���[mx,my,mz]ת������������ϵ,�õ�[hx,hy,hz]
//    hx = 2 * mx * (0.5 - q2q2 - q3q3) + 2 * my * (q1q2 - q0q3) + 2 * mz * (q1q3 + q0q2);
//    hy = 2 * mx * (q1q2 + q0q3) + 2 * my * (0.5 - q1q1 - q3q3) + 2 * mz * (q2q3 - q0q1);
//    hz = 2 * mx * (q1q3 - q0q2) + 2 * my * (q2q3 + q0q1) + 2 * mz * (0.5 - q1q1 - q2q2);
//
//    // �õ���������ϵ�еĵش���������ʵֵ[bx,bz,by],����by=0
//    bx = invSqrt((hx * hx) + (hy * hy));
//    bz = hz;
//
//    // ��������ϵ�еĵش�����[bx��by,bz]ת������������ϵ�У��õ�[wx,wy,wz]
//    wx = 2 * bx * (0.5 - q2q2 - q3q3) + 2 * bz * (q1q3 - q0q2);
//    wy = 2 * bx * (q1q2 - q0q3) + 2 * bz * (q0q1 + q2q3);
//    wz = 2 * bx * (q0q2 + q1q3) + 2 * bz * (0.5 - q1q1 - q2q2);

    // �����ǻ��ֹ�����������(��������ϵ)
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    // ��������������������������������������������
    //    ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    //    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    //    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);
    ex = (ay * vz - az * vy);
    ey = (az * vx - ax * vz);
    ez = (ax * vy - ay * vx);

    // ��������������л���
    exInt = exInt + ex * Ki;
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;

    // �����PI�󲹳���������
    gx = gx + Kp * ex + exInt;
    gy = gy + Kp * ey + eyInt;
    gz = gz + Kp * ez + ezInt; // �����gz����û�й۲��߽��н��������Ư�ƣ����ֳ����ľ��ǻ����������Լ�

    // ��Ԫ�ص�΢�ַ���
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    // ��λ����Ԫ��
    norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;

    // ��Ԫ��ת����ŷ����(Z->Y->X)
    //    Att_Angle->z += Gyr_rad->z *Radian_2_Degree*0.01f;
    Att_Angle->z = atan2(2.f * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3)* Radian_2_Degree; // yaw
    Att_Angle->y = -asin(2.f * (q1q3 - q0q2)) * Radian_2_Degree;                                // pitch(����Ҫע��)
    Att_Angle->x = atan2(2.f * q2q3 + 2.f * q0q1, q0q0 - q1q1 - q2q2 + q3q3) * Radian_2_Degree; // roll
}
void IMUANG_Offset(void)//�������ٶȳ�ֵ�����᷽��Ʈ�ƣ�
{
    int times=20000;
   // bool error=0;
    float angx_offset=0,angy_offset=0,angz_offset=0;
    for(int i=times;i>0;i--)//����ƫ����,ֻ�ھ�ֹʱ����һ��
    {
        imu963ra_get_gyro();                                     // ��ȡ IMU963RA ����������

        angx_offset+=imu963ra_gyro_transition(imu963ra_gyro_x);
        angy_offset+=imu963ra_gyro_transition(imu963ra_gyro_y);
        angz_offset+=imu963ra_gyro_transition(imu963ra_gyro_z);
        system_delay_10ns(100000);
    }
    IMUdata.dataRaw.angle.x=angx_offset/times;
    IMUdata.dataRaw.angle.y=angy_offset/times;
    IMUdata.dataRaw.angle.z=angz_offset/times;

}
