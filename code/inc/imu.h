#ifndef _IMU_H_
#define _IMU_H_
#include "zf_common_typedef.h"

typedef struct _Imu {
	float accel_x;	  /*uinit: m/s2*/
	float accel_y;	  // 三个方向上的加速度
	float accel_z;

	float angle_x;	  /*uinit: ° (deg)/s*/
	float angle_y;	  // 三个方向上的角度（欧拉角
	float angle_z;

	float mag_x;	/*uinit: ????*/
	float mag_y;	// 三个方向上的磁场
	float mag_z;

	float raw_mag_x;	/*uinit: mGauss*/
	float raw_mag_y;	// 三个方向上的原始磁场数据
	float raw_mag_z;

	float pitch;   /*uinit: °  (deg)*/
	float roll;	   // 俯仰、桶滚、回转角度
	float yaw;

	float quaternion_data0;
	float quaternion_data1;
	float quaternion_data2;
	float quaternion_data3;
} IMUType;

#endif