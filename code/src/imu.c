#include "zf_common_headfile.h"
#define pi acos(-1.0)

IMUType IMUdata;
#include "imu.h"

_IMU IMU = {0};

void IMU_init(void)
{
   //imu963ra_init();                                    // 初始化 IMU963RA
    imu660ra_init();
}

// float Yawrate = 0.0f;
// float Turn_Speed=0.0f;
/**************************实现函数*********************************************************************
函  数：static float invSqrt(float x)
功　能: 快速计算 1/Sqrt(x)
参  数：要计算的值
返回值：结果
备  注：比普通Sqrt()函数要快四倍See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
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
    imu963ra_get_acc();                                     // 获取 IMU963RA 加速度计数据
    imu963ra_get_gyro();                                     // 获取 IMU963RA 陀螺仪数据
    imu963ra_get_mag();                                     // 获取 IMU963RA 磁力计数据

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
 * 函数名称: Get_Attitude
 * 函数功能: 获取陀螺仪原始数据，并进行初步处理
 * 函数输入参数:   无
 * 函数输出参数:   无
 * 使用方法：在user_c/isr.c文件 TIM7_IRQHandler 函数中调用，在本处修改即可实现中断任务（注意，在定时器中断初始化时，已经设置了抢占优先级设置为3,次优先级设置为1）
 * 第一次修改日期   ：   2023年04月07日 （魏灵洁）
 ******************************************************************************
 */
void Get_Attitude()
{
//    //    static _Attitude Acc_filtold,Gyr_filtold;
//    /******************获取陀螺仪原始数据******************/
//    imu963ra_get_acc();                                     // 获取 IMU963RA 加速度计数据
//    imu963ra_get_gyro();                                     // 获取 IMU963RA 陀螺仪数据
//    /******************陀螺仪加速度AD值 转换成 米/平方秒 ******************/
//    IMU.T_Acc.x = -(imu963ra_acc_transition(imu963ra_acc_x)-0);
//    IMU.T_Acc.y = -(imu963ra_acc_transition(imu963ra_acc_z)-0);
//    IMU.T_Acc.z = -(imu963ra_acc_transition(imu963ra_acc_y)-0);
//    /******************陀螺仪角速度AD值 转换成 弧度/秒（并且作零飘处理） ******************/
//    IMU.T_Gyro.x = -(imu963ra_gyro_transition(imu963ra_gyro_x)   - 0.07508);//TODO:零漂补偿
//    IMU.T_Gyro.y = -(imu963ra_gyro_transition(imu963ra_gyro_z)   + 0.003024);
//    IMU.T_Gyro.z = -(imu963ra_gyro_transition(imu963ra_gyro_y)   + 0.118375);
//    /******************获取姿态角度 ******************/
//    IMUupdate(&(IMU.T_Gyro), &(IMU.T_Acc), &(IMU.T_Mag), &(IMU.Angle));
//    /******************获取姿态角速度 ******************/
//    IMU.Gyro.x = IMU.T_Gyro.x * Radian_2_Degree;// - Balance_Correct_GyroX;//TODO:硬件位置补偿
//    IMU.Gyro.y = IMU.T_Gyro.y * Radian_2_Degree;// - Balance_Correct_GyroY;
//    IMU.Gyro.z = IMU.T_Gyro.z * Radian_2_Degree;
    imu660ra_get_acc();
    imu660ra_get_gyro();
    /******************陀螺仪加速度AD值 转换成 米/平方秒 ******************/
    IMU.T_Acc.x = (float)imu660ra_acc_x * Acc_Gain * G;
    IMU.T_Acc.y = (float)imu660ra_acc_y * Acc_Gain * G;
    IMU.T_Acc.z = (float)imu660ra_acc_z * Acc_Gain * G;
    /******************陀螺仪角速度AD值 转换成 弧度/秒（并且作零飘处理） ******************/
    IMU.T_Gyro.x = (float)imu660ra_gyro_x * Gyro_Gr + 0;
    IMU.T_Gyro.y = (float)imu660ra_gyro_y * Gyro_Gr + 0;
    IMU.T_Gyro.z = (float)imu660ra_gyro_z * Gyro_Gr + 0;
    /******************获取姿态角度 ******************/
    IMUupdate(&(IMU.T_Gyro), &(IMU.T_Acc), &(IMU.T_Mag), &(IMU.Angle));
    /******************获取姿态角速度 ******************/
    IMU.Gyro.x = IMU.T_Gyro.x * Radian_2_Degree;// - Balance_Correct_GyroX;
    IMU.Gyro.y = IMU.T_Gyro.y * Radian_2_Degree;// - Balance_Correct_GyroY;
    IMU.Gyro.z = IMU.T_Gyro.z * Radian_2_Degree;

    // 角速度一阶滤波
    static float last_YPitchrate = 0;
    float Ya = 0.7;
    IMU.Gyro.y = last_YPitchrate * Ya + IMU.Gyro.y * (1 - Ya);
    last_YPitchrate = IMU.Gyro.y;

    // 角速度一阶滤波
    static float last_XPitchrate = 0;
    float Xa = 0.7;
    IMU.Gyro.x = last_XPitchrate * Xa + IMU.Gyro.x * (1 - Xa);
    last_XPitchrate = IMU.Gyro.x;

    static float last_ZPitchrate = 0;
    float Za = 0.7;
    IMU.Gyro.z = last_ZPitchrate * Za + IMU.Gyro.z * (1 - Za);
    last_ZPitchrate = IMU.Gyro.z;

    IMUdata.dataOri.pitch=(IMU.Angle.y+1.6);///TODO:测量机械中值
    IMUdata.dataOri.roll=IMU.Angle.x;
    IMUdata.dataOri.yaw=-IMU.Angle.z;


    IMUdata.dataOri.angle.x=IMU.Gyro.y-0.1;//TODO:测量细致化零漂
    IMUdata.dataOri.angle.y=IMU.Gyro.x;
    IMUdata.dataOri.angle.z=IMU.Gyro.z;
}

float acc_ratio = 1.6;   // 加速度计比例
float gyro_ratio = 4.08; // 陀螺仪比例
/**
 ******************************************************************************
 * 函数名称:一阶互补滤波
 * 函数功能: 获取陀螺仪原始数据，并进行初步处理
 * 函数输入参数:   无
 * 函数输出参数:   无
 * 使用方法：在user_c/isr.c文件 TIM7_IRQHandler 函数中调用，在本处修改即可实现中断任务（注意，在定时器中断初始化时，已经设置了抢占优先级设置为3,次优先级设置为1）
 * 第一次修改日期   ：   2023年04月07日 （魏灵洁）
 ******************************************************************************
 */
float angle_calc(float angle_m, float gyro_m, int index)
{
    float temp_angle;
    float gyro_now;
    float error_angle;
    static float last_angle[3];
    static uint8 first_angle[3];

    if (!first_angle[index]) // 判断是否为第一次运行本函数
    {
        // 如果是第一次运行，则将上次角度值设置为与加速度值一致
        first_angle[index] = 1;
        last_angle[index] = angle_m;
    }
    gyro_now = gyro_m * gyro_ratio;
    // 根据测量到的加速度值转换为角度之后与上次的角度值求偏差
    error_angle = (angle_m - last_angle[index]) * acc_ratio;
    // 根据偏差与陀螺仪测量得到的角度值计算当前角度值
    temp_angle = last_angle[index] + (error_angle + gyro_now) * Sampling_Time;
    // 保存当前角度值
    last_angle[index] = temp_angle;

    return temp_angle;
}

/*********************************************************************************************************
 *函  数：void IMUupdate(FLOAT_XYZ *Gyr_rad,FLOAT_XYZ *Acc_filt,FLOAT_ANGLE *Att_Angle)
 *功　能：获取姿态角
 *参  数：  Gyr_rad 指向角速度的指针（注意单位必须是弧度）
 *        Acc_filt 指向加速度的指针
 *        Mag_filt 指向地磁强度的指针
 *        Att_Angle 指向姿态角的指针
 *返回值：无
 *备  注：求解四元数和欧拉角都在此函数中完成
 **********************************************************************************************************/
// kp=ki=0 就是完全相信陀螺仪
#define Kp 2.0f                        // 比例增益控制加速度计，磁力计的收敛速率
#define Ki 0.01f                       // 积分增益控制陀螺偏差的收敛速度
#define halfT (Sampling_Time / 2)      // 采样周期的一半
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

    // 加速度计测量的重力向量(机体坐标系)
    norm = invSqrt(ax * ax + ay * ay + az * az);
    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

//    norm = invSqrt(mx * mx + my * my + mz * mz);
//    mx = mx / norm;
//    my = my / norm;
//    mz = mz / norm;
//
//    // 将机体坐标系中的地磁计分量[mx,my,mz]转换到地理坐标系,得到[hx,hy,hz]
//    hx = 2 * mx * (0.5 - q2q2 - q3q3) + 2 * my * (q1q2 - q0q3) + 2 * mz * (q1q3 + q0q2);
//    hy = 2 * mx * (q1q2 + q0q3) + 2 * my * (0.5 - q1q1 - q3q3) + 2 * mz * (q2q3 - q0q1);
//    hz = 2 * mx * (q1q3 - q0q2) + 2 * my * (q2q3 + q0q1) + 2 * mz * (0.5 - q1q1 - q2q2);
//
//    // 得到地理坐标系中的地磁向量的真实值[bx,bz,by],其中by=0
//    bx = invSqrt((hx * hx) + (hy * hy));
//    bz = hz;
//
//    // 地理坐标系中的地磁向量[bx，by,bz]转换到机体坐标系中，得到[wx,wy,wz]
//    wx = 2 * bx * (0.5 - q2q2 - q3q3) + 2 * bz * (q1q3 - q0q2);
//    wy = 2 * bx * (q1q2 - q0q3) + 2 * bz * (q0q1 + q2q3);
//    wz = 2 * bx * (q0q2 + q1q3) + 2 * bz * (0.5 - q1q1 - q2q2);

    // 陀螺仪积分估计重力向量(机体坐标系)
    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = q0q0 - q1q1 - q2q2 + q3q3;

    // 测量的重力向量与估算的重力向量差积求出向量间的误差
    //    ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    //    ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    //    ez = (ax*vy - ay*vx) + (mx*wy - my*wx);
    ex = (ay * vz - az * vy);
    ey = (az * vx - ax * vz);
    ez = (ax * vy - ay * vx);

    // 用上面求出误差进行积分
    exInt = exInt + ex * Ki;
    eyInt = eyInt + ey * Ki;
    ezInt = ezInt + ez * Ki;

    // 将误差PI后补偿到陀螺仪
    gx = gx + Kp * ex + exInt;
    gy = gy + Kp * ey + eyInt;
    gz = gz + Kp * ez + ezInt; // 这里的gz由于没有观测者进行矫正会产生漂移，表现出来的就是积分自增或自减

    // 四元素的微分方程
    q0 = q0 + (-q1 * gx - q2 * gy - q3 * gz) * halfT;
    q1 = q1 + (q0 * gx + q2 * gz - q3 * gy) * halfT;
    q2 = q2 + (q0 * gy - q1 * gz + q3 * gx) * halfT;
    q3 = q3 + (q0 * gz + q1 * gy - q2 * gx) * halfT;

    // 单位化四元数
    norm = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    q0 = q0 * norm;
    q1 = q1 * norm;
    q2 = q2 * norm;
    q3 = q3 * norm;

    // 四元数转换成欧拉角(Z->Y->X)
    //    Att_Angle->z += Gyr_rad->z *Radian_2_Degree*0.01f;
    Att_Angle->z = atan2(2.f * (q1q2 + q0q3), q0q0 + q1q1 - q2q2 - q3q3)* Radian_2_Degree; // yaw
    Att_Angle->y = -asin(2.f * (q1q3 - q0q2)) * Radian_2_Degree;                                // pitch(负号要注意)
    Att_Angle->x = atan2(2.f * q2q3 + 2.f * q0q1, q0q0 - q1q1 - q2q2 + q3q3) * Radian_2_Degree; // roll
}
void IMUANG_Offset(void)//测量角速度初值（三轴方向飘移）
{
    int times=20000;
   // bool error=0;
    float angx_offset=0,angy_offset=0,angz_offset=0;
    for(int i=times;i>0;i--)//计算偏移量,只在静止时计算一次
    {
        imu963ra_get_gyro();                                     // 获取 IMU963RA 磁力计数据

        angx_offset+=imu963ra_gyro_transition(imu963ra_gyro_x);
        angy_offset+=imu963ra_gyro_transition(imu963ra_gyro_y);
        angz_offset+=imu963ra_gyro_transition(imu963ra_gyro_z);
        system_delay_10ns(100000);
    }
    IMUdata.dataRaw.angle.x=angx_offset/times;
    IMUdata.dataRaw.angle.y=angy_offset/times;
    IMUdata.dataRaw.angle.z=angz_offset/times;

}
