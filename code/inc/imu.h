#ifndef _IMU_H_
#define _IMU_H_
#include "vector.h"
#include "zf_common_typedef.h"

#define RAWTIMES	 2000	 // 漂移校准次数
#define irq_interval 5		 // 中断周期，单位为ms，此处示例为1ms

#define IMUERR 0.02	   // atan 0.02 近似0.02度

typedef struct _IMUParam {
	Vector3f accel;	   // 三个方向上的加速度 m/s2
	Vector3f angle;	   // 三个方向上的角度（欧拉角)  此处减去了偏移量  ° (deg)/s
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

void IMU_init(void);	// INIT
void IMU_getdata(void);
bool IMU_ang_calibration(void);	   // 校准陀螺仪总函数，静止状态调用，阻塞线程 加速度角速度作用
void IMU_correct(void);

bool IMU_ang_integ(void);	 // 对角速度进行积分，这部分放在中断里

#endif
