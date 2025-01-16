#include "zf_common_headfile.h"
// #include "zf_device_imu963ra.h"

IMUType IMUdata;

void IMU_init(void)
{
	imu963ra_init();	// 初始化 IMU963RA

	///////////////////////////////////////////////////////// 初值要测量后填入
	//   IMUdata.raw_accel_x=0;    /*uinit:  m/s2*/
	//   IMUdata.raw_accel_y=0;    // 三个方向上的加速度飘移
	//   IMUdata.raw_accel_z=1;

	//   IMUdata.raw_angel_x=0;    /*uinit: (deg)/s*/
	//   IMUdata.raw_angel_y=0;    // 三个方向上的角速度飘移
	//   IMUdata.raw_angel_z=0;

	//   IMUdata.raw_mag_x=0;    /*uinit: mGauss*/
	//   IMUdata.raw_mag_y=0;    // 三个方向上的原始磁场数据
	//   IMUdata.raw_mag_z=0;

	IMUdata.calibration_flag = 0;	 // 未完成校准标志
}

#define times 2000	  // 漂移校准次数

// long zheshiyigejishuqi=0;
// float zheshileijiajishuqi=0;

void IMUACC_Offset(void)	// 测量加速度受重力影响初值（三轴方向飘移）
{
	float gx_offset = 0, gy_offset = 0, gz_offset = 0;
	for (short i = times; i > 0; i--)	 // 计算偏移量,只在静止时计算一次
	{
		imu963ra_get_acc();	   // 获取 IMU963RA 加速度计数据

		gx_offset += imu963ra_acc_transition(imu963ra_acc_x);
		gy_offset += imu963ra_acc_transition(imu963ra_acc_y);
		gz_offset += imu963ra_acc_transition(imu963ra_acc_z);
		// system_delay_10ns(100000);
	}
	IMUdata.raw_accel_x = gx_offset / times;
	IMUdata.raw_accel_y = gy_offset / times;
	IMUdata.raw_accel_z = gz_offset / times;	// 此处考虑以校准时间为准或是以重力加速度方向为准进行校正，我倾向于后者
	// zheshiyigejishuqi++;
	// IMUdata.G=((sqrtf(gx_offset*gx_offset+gy_offset*gy_offset+gz_offset*gz_offset)/times)*(zheshiyigejishuqi-1)+IMUdata.G)/zheshiyigejishuqi;
	IMUdata.G = sqrtf(gx_offset * gx_offset + gy_offset * gy_offset + gz_offset * gz_offset) / times;
}

bool IMUANG_Offset(void)	// 测量角速度初值（三轴方向飘移）
{
	bool  error		  = 0;
	float angx_offset = 0, angy_offset = 0, angz_offset = 0;
	for (short i = times; i > 0; i--)	 // 计算偏移量,只在静止时计算一次
	{
		imu963ra_get_gyro();	// 获取 IMU963RA 磁力计数据

		angx_offset += imu963ra_gyro_transition(imu963ra_gyro_x);
		angy_offset += imu963ra_gyro_transition(imu963ra_gyro_y);
		angz_offset += imu963ra_gyro_transition(imu963ra_gyro_z);
		system_delay_ms(1);
	}
	IMUdata.raw_angel_x = angx_offset / times;
	IMUdata.raw_angel_y = angy_offset / times;
	IMUdata.raw_angel_z = angz_offset / times;
	if (IMUdata.raw_angel_x > 10 || IMUdata.raw_angel_y > 10 || IMUdata.raw_angel_z > 10)
		error = 1;
	return error;
}

void IMUANG_ORI(void)	 // 计算车辆姿态初值（三轴方向飘移）//函数应在重力加速度校准后调用
{
	float x = 0;	// 存储器
	x		= IMUdata.raw_yaw;
	IMUdata.raw_yaw = x;	// 由于初值有重力场方向确定，自由度为1，无法结算出初始的航向角(回转角)，要由平衡后赛道循迹确定
	// 重力场角度为（0,IMUdata.G,0）可由此和初始acc值联合结算初始角度，这样可以使车辆自平衡，后期可人为测量填充flash写死数据，或多次优化数据，定死imu平衡角度
	x = (IMUdata.raw_accel_x > 0 ? 1 : -1) * IMUdata.raw_accel_y
		/ sqrtf(IMUdata.raw_accel_y * IMUdata.raw_accel_y + IMUdata.raw_accel_x * IMUdata.raw_accel_x);
	IMUdata.raw_pitch = 180 / PI * acosf(x);

	// 初始俯仰角
	x				  = (IMUdata.raw_accel_z > 0 ? -1 : 1) * IMUdata.raw_accel_y
		/ sqrtf(IMUdata.raw_accel_y * IMUdata.raw_accel_y + IMUdata.raw_accel_z * IMUdata.raw_accel_z);
	IMUdata.raw_roll = 180 / PI * acosf(x);
	// 初始滚摆角//由于陀螺仪位置原因，初始正负性相反
	if (IMUdata.raw_pitch > 90)
		IMUdata.raw_pitch -= 180;
	else if (IMUdata.raw_pitch < -90)
		IMUdata.raw_pitch += 180;
	if (IMUdata.raw_roll > 90)
		IMUdata.raw_roll -= 180;
	else if (IMUdata.raw_roll < -90)
		IMUdata.raw_roll += 180;
	// 防止近0cos判断+-180度正负性翻转，即结果归至0附近
}

void IMU_ANG_GET_ORIDAT(void)	 // 将车辆姿态初值赋值给三轴角度//函数应在校准或静止时与上函数同时调用
{
	IMUdata.pitch = IMUdata.raw_pitch;
	IMUdata.roll  = IMUdata.raw_roll;
	IMUdata.yaw	  = IMUdata.raw_yaw;
}

void IMUMAG_Offset(void)	// 测量磁场初值（三轴方向飘移）
{
	float rawx_offset = 0, rawy_offset = 0, rawz_offset = 0;
	for (short i = times; i > 0; i--)	 // 计算偏移量,只在静止时计算一次
	{
		imu963ra_get_mag();	   // 获取 IMU963RA 磁力计数据

		rawx_offset += imu963ra_mag_transition(imu963ra_mag_x);
		rawy_offset += imu963ra_mag_transition(imu963ra_mag_y);
		rawz_offset += imu963ra_mag_transition(imu963ra_mag_z);
	}
	IMUdata.raw_mag_x = imu963ra_mag_transition(rawx_offset / times);
	IMUdata.raw_mag_y = imu963ra_mag_transition(rawy_offset / times);
	IMUdata.raw_mag_z = imu963ra_mag_transition(rawz_offset / times);
}

void IMU_getdata(void)
{
	imu963ra_get_acc();		// 获取 IMU963RA 加速度计数据
	imu963ra_get_gyro();	// 获取 IMU963RA 陀螺仪数据
	imu963ra_get_mag();		// 获取 IMU963RA 磁力计数据

	IMUdata.accel_x = imu963ra_acc_transition(imu963ra_acc_x);
	IMUdata.accel_y = imu963ra_acc_transition(imu963ra_acc_y);
	IMUdata.accel_z = imu963ra_acc_transition(imu963ra_acc_z);

	IMUdata.angle_x = imu963ra_gyro_transition(imu963ra_gyro_x) - IMUdata.raw_angel_x;
	IMUdata.angle_y = imu963ra_gyro_transition(imu963ra_gyro_y) - IMUdata.raw_angel_y;
	IMUdata.angle_z = imu963ra_gyro_transition(imu963ra_gyro_z) - IMUdata.raw_angel_z;

	IMUdata.mag_x	= imu963ra_mag_transition(imu963ra_mag_x);
	IMUdata.mag_y	= imu963ra_mag_transition(imu963ra_mag_y);
	IMUdata.mag_z	= imu963ra_mag_transition(imu963ra_mag_z);
}
void IMU_CORRECT()	  // 陀螺仪动态校准函数，放在主函数while循环中，消除累积误差（只有G较小时可以调用）
{
	float current_G;
	float x;
	IMU_getdata();
	current_G = sqrtf(IMUdata.accel_x * IMUdata.accel_x + IMUdata.accel_y * IMUdata.accel_y + IMUdata.accel_z * IMUdata.accel_z);
	if (fabsf(current_G - IMUdata.G) < 0.02 * fabsf(IMUdata.G))	   // 这个决定了刷新的严苛成度，需要调整范围
	{
		IMUdata.calibration_flag = 0;

		x						 = (IMUdata.accel_x > 0 ? 1 : -1) * IMUdata.accel_y
			/ sqrtf(IMUdata.accel_y * IMUdata.accel_y + IMUdata.accel_x * IMUdata.accel_x);
		IMUdata.pitch = 180 / PI * acosf(x);
		x			  = (IMUdata.accel_z > 0 ? -1 : 1) * IMUdata.accel_y
			/ sqrtf(IMUdata.accel_y * IMUdata.accel_y + IMUdata.accel_z * IMUdata.accel_z);
		IMUdata.roll = 180 / PI * acosf(x);
		if (IMUdata.pitch > 90)
			IMUdata.pitch -= 180;
		else if (IMUdata.pitch < -90)
			IMUdata.pitch += 180;
		if (IMUdata.roll > 90)
			IMUdata.roll -= 180;
		else if (IMUdata.roll < -90)
			IMUdata.roll += 180;
		IMUdata.calibration_flag = 1;
	}
	//  oled_show_int(10, 0, (int)(current_G*1000), 5);
}

#define irq_interval 1	  // 中断周期，单位为ms，此处示例为1ms
bool IMU_ANG_INTEG()	  // 对角速度进行积分，这部分放在中断里
{
	IMU_CORRECT();
	if (IMUdata.calibration_flag) {
		IMU_getdata();
		IMUdata.pitch += IMUdata.angle_z * irq_interval / 1000;
		IMUdata.roll  += IMUdata.angle_x * irq_interval / 1000;
		IMUdata.yaw	  += IMUdata.angle_y * irq_interval / 1000;
	}

	return IMUdata.calibration_flag;	// 返回0表示未完成校准，或正在校准
}

bool IMU_ANG_CALIBRATION()	  // 校准陀螺仪总函数，静止状态调用，阻塞线程//加速度角速度作用//此时结构体中存储校准（静止）时三值数据
{
	IMUdata.calibration_flag = 0;
	IMUACC_Offset();		 // 测量加速度受重力影响初值（三轴方向飘移）
	IMUANG_Offset();		 // 测量角速度初值（三轴方向飘移）
	IMUANG_ORI();			 // 计算车辆姿态初值（三轴方向飘移）//函数应在重力加速度校准后调用
	IMU_ANG_GET_ORIDAT();	 // 将车辆姿态初值赋值给三轴角度//函数应在校准或静止时与上函数同时调用
	IMUdata.calibration_flag = 1;

	return IMUdata.calibration_flag;
}
