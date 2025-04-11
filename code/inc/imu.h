#ifndef _IMU_H_
#define _IMU_H_
#include "vector.h"
#include "zf_common_typedef.h"

#define Sampling_Time (1. / 1000.)			  // 采样周期
#define irq_interval  Sampling_Time * 1000	  // 中断周期，单位为ms，此处示例为5ms

typedef struct _IMUParam {
	Vector3f accel;	   // 三个方向上的加速度 m/s2
	Vector3f angle;	   // 三个方向上的角速度（欧拉角)  此处减去了偏移量  ° (deg)/s
	Vector3f mag;	   // 三个方向上的磁场  Gauss

	float pitch;	//  °(deg)
	float roll;		// 俯仰、横滚、偏航角度
	float yaw;		// 为了直观不再定义3维向量

} IMUParam;

typedef struct _Imu {
	IMUParam dataOri;	 // 原始数据  机体真实值
	IMUParam dataRaw;	 // 偏移数据

	IMUParam dataSet;	 // 设定值

	float G;				   // 当地重力加速度
	bool  calibration_flag;	   // 完成俯仰角校准的标志
} IMUType;

extern IMUType IMUdata;

#define Kp_New			0.9f	// 互补滤波当前数据的权重
#define G				9.80665f
#define Acc_Gain		0.0002441f	   // 加速度变成G (初始化加速度满量程-+4g LSBa = 2*8/65535.0)
#define Gyro_Gain		0.0609756f	   // 角速度变成度 (初始化陀螺仪满量程+-2000 LSBg = 2*2000/65535.0)
#define Gyro_Gr			0.00106528f	   // 角速度变成弧度(pi/180 * LSBg)
#define Radian_2_Degree 57.2957795f
#define Degree_2_Radian 0.01745329f

/*************IMU构体************/
typedef struct _IMU_ {
	Vector3f T_Acc;		// 陀螺仪加速度AD值 转换成 米/平方秒
	Vector3f T_Gyro;	// 陀螺仪角速度AD值 转换成 弧度/秒
	Vector3f T_Mag;

	Vector3f Gyro;	   // 解算后姿态角速度
	Vector3f Angle;	   // 解算后姿态角度
} _IMU;

void IMU_getdata(void);

void  IMU_init(void);
void  Get_Attitude(void);
float angle_calc(float angle_m, float gyro_m, int index);
void  IMUupdate(Vector3f* Gyr_rad, Vector3f* Acc_filt, Vector3f* Mag_filt, Vector3f* Att_Angle);
void  IMUANG_Offset(void);

#endif
