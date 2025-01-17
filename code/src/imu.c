#include "zf_common_headfile.h"

IMUType IMUdata;

/**
 * @brief 陀螺仪初始化函数
 *
 */
void IMU_init(void)
{
	while (true) {	  // 初始化 IMU963RA
		if (imu963ra_init() == 0)
			break;
	}

	// TODO: 初值要测量后填入
	IMUdata.dataRaw.accel.x	 = 0;	 // 三个方向上的加速度飘移
	IMUdata.dataRaw.accel.y	 = 0;
	IMUdata.dataRaw.accel.z	 = 1;

	IMUdata.dataRaw.angle.x	 = 0;	 // 三个方向上的角速度飘移
	IMUdata.dataRaw.angle.y	 = 0;
	IMUdata.dataRaw.angle.z	 = 0;

	IMUdata.dataRaw.mag.x	 = 0;
	IMUdata.dataRaw.mag.y	 = 0;
	IMUdata.dataRaw.mag.z	 = 0;

	IMUdata.calibration_flag = 0;	 // 未完成校准标志
}

// long IMUCnt = 0;

/**
 * @brief  测量加速度受重力影响初值（三轴方向飘移）
 *
 */
void IMU_acc_Offset(void)
{
	float gx_offset = 0, gy_offset = 0, gz_offset = 0;

	for (short i = RAWTIMES; i > 0; i--)	// 计算偏移量,只在静止时计算一次
	{
		imu963ra_get_acc();	   // 获取 IMU963RA 加速度计数据

		gx_offset += imu963ra_acc_transition(imu963ra_acc_x);
		gy_offset += imu963ra_acc_transition(imu963ra_acc_y);
		gz_offset += imu963ra_acc_transition(imu963ra_acc_z);
		// system_delay_10ns(100000);
	}

	IMUdata.dataRaw.accel.x = gx_offset / RAWTIMES;
	IMUdata.dataRaw.accel.y = gy_offset / RAWTIMES;
	IMUdata.dataRaw.accel.z = gz_offset / RAWTIMES;	   // 此处考虑以校准时间为准或是以重力加速度方向为准进行校正，我倾向于后者

	// IMUCnt++;
	// IMUdata.G=((sqrtf(gx_offset*gx_offset+gy_offset*gy_offset+gz_offset*gz_offset)/RAWTIMES)*(IMUCnt-1)+IMUdata.G)/IMUCnt;

	IMUdata.G = sqrtf(gx_offset * gx_offset + gy_offset * gy_offset + gz_offset * gz_offset) / RAWTIMES;
}

/**
 * @brief 测量角速度初值（三轴方向飘移）
 *
 * @return true
 * @return false
 */
bool IMUANG_Offset(void)
{
	bool  error		  = false;
	float angx_offset = 0, angy_offset = 0, angz_offset = 0;
	for (short i = RAWTIMES; i > 0; i--)	// 计算偏移量,只在静止时计算一次
	{
		imu963ra_get_gyro();	// 获取 IMU963RA 磁力计数据

		angx_offset += imu963ra_gyro_transition(imu963ra_gyro_x);
		angy_offset += imu963ra_gyro_transition(imu963ra_gyro_y);
		angz_offset += imu963ra_gyro_transition(imu963ra_gyro_z);
		system_delay_ms(1);
	}
	IMUdata.dataRaw.angle.x = angx_offset / RAWTIMES;
	IMUdata.dataRaw.angle.y = angy_offset / RAWTIMES;
	IMUdata.dataRaw.angle.z = angz_offset / RAWTIMES;

	if (IMUdata.dataRaw.angle.x > 10 || IMUdata.dataRaw.angle.y > 10 || IMUdata.dataRaw.angle.z > 10)
		error = true;

	return error;
}

/**
 * @brief  计算车辆姿态初值（三轴方向飘移）  函数应在重力加速度校准后调用
 *
 */
void IMU_ang_ori(void)
{
	float x = IMUdata.dataRaw.yaw;	  // 存储器

	IMUdata.dataRaw.yaw = x;	// 由于初值有重力场方向确定，自由度为1，无法结算出初始的航向角(回转角)，要由平衡后赛道循迹确定

	// 重力场角度为（0,IMUdata.G,0）可由此和初始acc值联合结算初始角度，这样可以使车辆自平衡，后期可人为测量填充flash写死数据，或多次优化数据，定死imu平衡角度
	x = (IMUdata.dataRaw.accel.x > 0 ? 1 : -1) * IMUdata.dataRaw.accel.y
		/ sqrtf(IMUdata.dataRaw.accel.y * IMUdata.dataRaw.accel.y + IMUdata.dataRaw.accel.x * IMUdata.dataRaw.accel.x);
	IMUdata.dataRaw.pitch = 180 / PI * acosf(x);

	// 初始俯仰角
	x					  = (IMUdata.dataRaw.accel.z > 0 ? -1 : 1) * IMUdata.dataRaw.accel.y
		/ sqrtf(IMUdata.dataRaw.accel.y * IMUdata.dataRaw.accel.y + IMUdata.dataRaw.accel.z * IMUdata.dataRaw.accel.z);
	IMUdata.dataRaw.roll = 180 / PI * acosf(x);

	// 初始滚摆角//由于陀螺仪位置原因，初始正负性相反
	if (IMUdata.dataRaw.pitch > 90)
		IMUdata.dataRaw.pitch -= 180;
	else if (IMUdata.dataRaw.pitch < -90)
		IMUdata.dataRaw.pitch += 180;

	if (IMUdata.dataRaw.roll > 90)
		IMUdata.dataRaw.roll -= 180;
	else if (IMUdata.dataRaw.roll < -90)

		IMUdata.dataRaw.roll += 180;
	// 防止近0cos判断+-180度正负性翻转，即结果归至0附近
}

/**
 * @brief 将车辆姿态初值赋值给三轴角度  函数应在校准或静止时与上函数同时调用
 *
 */
void IMU_ang_get_oridat(void)
{
	IMUdata.dataOri.pitch = IMUdata.dataRaw.pitch;
	IMUdata.dataOri.roll  = IMUdata.dataRaw.roll;
	IMUdata.dataOri.yaw	  = IMUdata.dataRaw.yaw;
}

/**
 * @brief  测量磁场初值（三轴方向飘移）
 *
 */
void IMUMAG_Offset(void)
{
	float rawx_offset = 0, rawy_offset = 0, rawz_offset = 0;
	for (short i = RAWTIMES; i > 0; i--)	// 计算偏移量,只在静止时计算一次
	{
		imu963ra_get_mag();	   // 获取 IMU963RA 磁力计数据

		rawx_offset += imu963ra_mag_transition(imu963ra_mag_x);
		rawy_offset += imu963ra_mag_transition(imu963ra_mag_y);
		rawz_offset += imu963ra_mag_transition(imu963ra_mag_z);
	}

	IMUdata.dataRaw.mag.x = imu963ra_mag_transition(rawx_offset / RAWTIMES);
	IMUdata.dataRaw.mag.y = imu963ra_mag_transition(rawy_offset / RAWTIMES);
	IMUdata.dataRaw.mag.z = imu963ra_mag_transition(rawz_offset / RAWTIMES);
}

/**
 * @brief 读取陀螺仪的值
 *
 */
void IMU_getdata(void)
{
	imu963ra_get_acc();		// 获取 IMU963RA 加速度计数据
	imu963ra_get_gyro();	// 获取 IMU963RA 陀螺仪数据
	imu963ra_get_mag();		// 获取 IMU963RA 磁力计数据

	// 数据转化
	IMUdata.dataOri.accel.x = imu963ra_acc_transition(imu963ra_acc_x);
	IMUdata.dataOri.accel.y = imu963ra_acc_transition(imu963ra_acc_y);
	IMUdata.dataOri.accel.z = imu963ra_acc_transition(imu963ra_acc_z);

	IMUdata.dataOri.angle.x = imu963ra_gyro_transition(imu963ra_gyro_x) - IMUdata.dataRaw.angle.x;
	IMUdata.dataOri.angle.y = imu963ra_gyro_transition(imu963ra_gyro_y) - IMUdata.dataRaw.angle.y;
	IMUdata.dataOri.angle.z = imu963ra_gyro_transition(imu963ra_gyro_z) - IMUdata.dataRaw.angle.z;

	IMUdata.dataOri.mag.x	= imu963ra_mag_transition(imu963ra_mag_x);
	IMUdata.dataOri.mag.y	= imu963ra_mag_transition(imu963ra_mag_y);
	IMUdata.dataOri.mag.z	= imu963ra_mag_transition(imu963ra_mag_z);
}

/**
 * @brief  对角速度进行积分，这部分放在中断里
 *
 * @return true
 * @return false
 */
bool IMU_ang_integ()
{
	IMU_correct();
	if (IMUdata.calibration_flag) {
		IMU_getdata();

		IMUdata.dataOri.pitch += IMUdata.dataOri.angle.z * irq_interval / 1000;
		IMUdata.dataOri.roll  += IMUdata.dataOri.angle.x * irq_interval / 1000;
		IMUdata.dataOri.yaw	  += IMUdata.dataOri.angle.y * irq_interval / 1000;
	}

	return IMUdata.calibration_flag;	// 返回0表示未完成校准，或正在校准
}

/**
 * @brief  陀螺仪动态校准函数，放在主函数while循环中，消除累积误差（只有G较小时可以调用）
 *
 */
void IMU_correct()
{
	float current_G;
	float x;
	IMU_getdata();
	current_G = sqrtf(IMUdata.dataOri.accel.x * IMUdata.dataOri.accel.x + IMUdata.dataOri.accel.y * IMUdata.dataOri.accel.y
					  + IMUdata.dataOri.accel.z * IMUdata.dataOri.accel.z);
	if (fabsf(current_G - IMUdata.G) < 0.02 * fabsf(IMUdata.G))	   // 这个决定了刷新的严苛成度，需要调整范围
	{
		IMUdata.calibration_flag = 0;

		x						 = (IMUdata.dataOri.accel.x > 0 ? 1 : -1) * IMUdata.dataOri.accel.y
			/ sqrtf(IMUdata.dataOri.accel.y * IMUdata.dataOri.accel.y + IMUdata.dataOri.accel.x * IMUdata.dataOri.accel.x);
		IMUdata.dataOri.pitch = 180 / PI * acosf(x);
		x					  = (IMUdata.dataOri.accel.z > 0 ? -1 : 1) * IMUdata.dataOri.accel.y
			/ sqrtf(IMUdata.dataOri.accel.y * IMUdata.dataOri.accel.y + IMUdata.dataOri.accel.z * IMUdata.dataOri.accel.z);
		IMUdata.dataOri.roll = 180 / PI * acosf(x);
		if (IMUdata.dataOri.pitch > 90)
			IMUdata.dataOri.pitch -= 180;
		else if (IMUdata.dataOri.pitch < -90)
			IMUdata.dataOri.pitch += 180;
		if (IMUdata.dataOri.roll > 90)
			IMUdata.dataOri.roll -= 180;
		else if (IMUdata.dataOri.roll < -90)
			IMUdata.dataOri.roll += 180;
		IMUdata.calibration_flag = 1;
	}
	//  oled_show_int(10, 0, (int)(current_G*1000), 5);
}

/**
 * @brief 校准陀螺仪总函数，静止状态调用，阻塞线程，加速度角速度作用，此时结构体中存储校准（静止）时三值数据
 *
 * @return true
 * @return false
 */
bool IMU_ang_calibration(void)
{
	IMUdata.calibration_flag = 0;
	IMU_acc_Offset();		 // 测量加速度受重力影响初值（三轴方向飘移）
	IMUANG_Offset();		 // 测量角速度初值（三轴方向飘移）
	IMU_ang_ori();			 // 计算车辆姿态初值（三轴方向飘移）//函数应在重力加速度校准后调用
	IMU_ang_get_oridat();	 // 将车辆姿态初值赋值给三轴角度//函数应在校准或静止时与上函数同时调用
	IMUdata.calibration_flag = 1;

	return IMUdata.calibration_flag;
}
