#ifndef _IMU_H_
#define _IMU_H_
#include "zf_common_typedef.h"

typedef struct _Imu {
	float accel_x;	  /*uinit: m/s2*/
	float accel_y;	  // ���������ϵļ��ٶ�
	float accel_z;

	float angle_x;	  /*uinit: �� (deg)/s*/
	float angle_y;	  // ���������ϵĽǶȣ�ŷ����
	float angle_z;

	float mag_x;	/*uinit: ????*/
	float mag_y;	// ���������ϵĴų�
	float mag_z;

	float raw_mag_x;	/*uinit: mGauss*/
	float raw_mag_y;	// ���������ϵ�ԭʼ�ų�����
	float raw_mag_z;

	float pitch;   /*uinit: ��  (deg)*/
	float roll;	   // ������Ͱ������ת�Ƕ�
	float yaw;

	float quaternion_data0;
	float quaternion_data1;
	float quaternion_data2;
	float quaternion_data3;
} IMUType;

#endif