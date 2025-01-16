#ifndef _IMU_H_
#define _IMU_H_
#include "zf_common_typedef.h"

typedef struct _Imu {
	float accel_x;	  /*uinit: m/s2*/
	float accel_y;	  // 三个方向上的加速度
	float accel_z;

	float angle_x;	  /*uinit: ° (deg)/s*/
	float angle_y;	  // 三个方向上的角度（欧拉角)
	float angle_z;

	float mag_x;	/*uinit: ????*/
	float mag_y;	// 三个方向上的磁场
	float mag_z;

	float pitch;   /*uinit: °  (deg)*/
	float roll;	   // 俯仰、桶滚、回转角度
	float yaw;

	float raw_accel_x;	  /*uinit:  m/s2*/
	float raw_accel_y;	  // 三个方向上的加速度飘移
	float raw_accel_z;

	float raw_angel_x;	  /*uinit: (deg)/s*/
	float raw_angel_y;	  // 三个方向上的角速度飘移
	float raw_angel_z;

	float raw_mag_x;	/*uinit: mGauss*/
	float raw_mag_y;	// 三个方向上的原始磁场数据
	float raw_mag_z;

	float raw_pitch;   /*uinit: °  (deg)*/
	float raw_roll;	   // 初始及静止校准状态下的，俯仰、桶滚、回转角度
	float raw_yaw;

	float G;				   // 当地重力加速度
	bool  calibration_flag;	   // 完成俯仰角校准的标志

} IMUType;

extern IMUType IMUdata;

void IMU_init(void);	// INIT
void IMU_getdata(void);
bool IMU_ANG_CALIBRATION(void);	   // 校准陀螺仪总函数，静止状态调用，阻塞线程//加速度角速度作用
void IMU_CORRECT(void);

bool IMU_ANG_INTEG(void);	 // 对角速度进行积分，这部分放在中断里

#endif
