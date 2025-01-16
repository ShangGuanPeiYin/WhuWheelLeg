#ifndef _IMU_H_
#define _IMU_H_
#include "vector.h"
#include "zf_common_typedef.h"

typedef struct _IMUParam {
	Vector3f accel;	   // 三个方向上的加速度 m/s2
	Vector3f angle;	   // 三个方向上的角度（欧拉角)  此处减去了偏移量  ° (deg)/s
	Vector3f mag;	   // 三个方向上的磁场  Gauss

	float pitch;	//  °(deg)
	float roll;		// 俯仰、横滚、偏航角度
	float yaw;		// 为了直观不再定义3维向量

} IMUParam;

typedef struct _Imu {
	IMUParam dataOri;	 // 原始数据
	IMUParam dataRaw;	 // 偏移数据

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
