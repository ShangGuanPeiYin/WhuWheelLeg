#include "zf_common_headfile.h"

#define dt (0.002)	  // 2ms

/**
 * @brief 卡尔曼滤波初始化函数
 * @param kalman
 * @param Q_angle 角度过程噪声(0.001)
 * @param Q_bias 偏差过程噪声(0.003)
 * @param R_measure 测量噪声(0.03)
 * @param angle 初始角度
 */
void KalmanParamsInit(KalmanParams* kalman, float Q_angle, float Q_bias, float R_measure, float angle)
{
	kalman->Q_angle	  = Q_angle;
	kalman->Q_bias	  = Q_bias;
	kalman->R_measure = R_measure;
	kalman->angle	  = angle;	  // 当前估计的角度
	kalman->bias	  = 0.f;	  // 当前估计的偏差（如加速度计与陀螺仪的偏差）
	kalman->rate	  = 0.f;	  // 角速度
	kalman->P[0][0]	  = 0.f;
	kalman->P[0][1]	  = 0.f;
	kalman->P[1][0]	  = 0.f;
	kalman->P[1][1]	  = 0.f;
}

/**
 * @brief 卡尔曼滤波函数：通过角度、角速度和时间间隔计算估计的角度
 *
 * @param kalman
 * @param newAngle 传感器提供的新角度值
 * @param newRate 角速度（陀螺仪数据）
 * @param t 时间间隔
 * @return float 返回经过卡尔曼滤波器处理后的角度值
 */
float Kalman_filter(KalmanParams* kalman, float newAngle, float newRate, float t)
{
	kalman->rate	 = newRate - kalman->bias;	  // 去除偏差的角速度
	kalman->angle	+= t * kalman->rate;		  // 更新角度估计值

	// 更新协方差矩阵
	kalman->P[0][0] += t * (dt * kalman->P[1][1] - kalman->P[0][1] - kalman->P[1][0] + kalman->Q_angle);	// P00
	kalman->P[0][1] -= t * kalman->P[1][1];																	// P01
	kalman->P[1][0] -= t * kalman->P[1][1];																	// P10
	kalman->P[1][1] += kalman->Q_bias * t;																	// P11

	// 计算卡尔曼增益
	float S			 = kalman->P[0][0] + kalman->R_measure;	   // 系统的总噪声
	float K[2];												   // 卡尔曼增益
	K[0]			 = kalman->P[0][0] / S;
	K[1]			 = kalman->P[1][0] / S;

	// 计算测量值与预测值的差异（创新值）
	float y			 = newAngle - kalman->angle;

	// 更新估计值
	kalman->angle	+= K[0] * y;	// 更新角度
	kalman->bias	+= K[1] * y;	// 更新偏差

	// 更新协方差矩阵
	float P00_temp	 = kalman->P[0][0];
	float P01_temp	 = kalman->P[0][1];
	kalman->P[0][0] -= K[0] * P00_temp;
	kalman->P[0][1] -= K[0] * P01_temp;
	kalman->P[1][0] -= K[1] * P00_temp;
	kalman->P[1][1] -= K[1] * P01_temp;

	return kalman->angle;	 // 返回滤波后的角度
}

/**
 * @brief 一阶滤波器初始化函数
 *
 * @param firstorder
 * @param K1 一阶滤波器系数
 * @param angle 初始角度
 */
void FirstOrderInit(FirstOrderFilterParams* firstorder, float K1, float angle)
{
	firstorder->K1				 = K1;
	firstorder->FirstOrder_angle = angle;
}

/**
 * @brief 一阶滤波器函数：通过加权平均法根据角度和角速度估算新的角度
 *
 * @param firstorder
 * @param newAngle 传感器提供的新角度值
 * @param newRate 角速度（陀螺仪数据）
 * @param t 时间间隔
 * @return float 返回一阶滤波器估算的角度值
 */
float FirstOrder(FirstOrderFilterParams* firstorder, float newAngle, float newRate, float t)
{
	firstorder->FirstOrder_angle = firstorder->K1 * newAngle + (1 - firstorder->K1) * (firstorder->FirstOrder_angle + newRate * t);
	return firstorder->FirstOrder_angle;
}

/**
 * @brief  二阶滤波器初始化函数
 *
 * @param secondorder
 * @param K2 二阶滤波器系数
 * @param angle 初始角度
 */
void SecondOrderInit(SecondOrderFilterParams* secondorder, float K2, float angle)
{
	secondorder->K2				   = K2;
	secondorder->SecondOrder_angle = angle;
}

/**
 * @brief  二阶滤波器函数：更复杂的加权平滑处理，用于估算新的角度值
 *
 * @param secondorder
 * @param newAngle  传感器提供的新角度值
 * @param newRate  角速度（陀螺仪数据）
 * @param t 时间间隔
 * @return float 返回二阶滤波器估算的角度值
 */
float SecondOrder(SecondOrderFilterParams* secondorder, float newAngle, float newRate, float t)
{
	secondorder->x1
		= (newAngle - secondorder->SecondOrder_angle) * (1 - secondorder->K2) * (1 - secondorder->K2);	  // 计算一阶差值
	secondorder->y1 = secondorder->y1 + secondorder->x1 * t;	// 更新二阶滤波器中的状态变量
	secondorder->x2
		= secondorder->y1 + 2 * (1 - secondorder->K2) * (newAngle - secondorder->SecondOrder_angle) + newRate;	  // 更新差值
	secondorder->SecondOrder_angle = secondorder->SecondOrder_angle + secondorder->x2 * t;	  // 更新输出角度
	return secondorder->SecondOrder_angle;													  // 返回滤波后的角度
}

/**
 * @brief 滤波器1函数：对输入数据序列进行滤波，去除序列中的最大值和最小值，计算平均值
 *
 * @param num 当前数据
 * @param times 数据的样本数
 * @return float 返回滤波后的数据（去掉最大值和最小值的平均值）
 */
float fliter1(float num, int times)
{
	static float lastnum[30] = {0};	   // 存储前30个数据点
	float		 average, max, min, sum = 0;

	// 更新数据序列
	for (int i = times - 2; i >= 0; i--) { lastnum[i + 1] = lastnum[i]; }
	lastnum[0] = num;

	max		   = lastnum[0];
	min		   = lastnum[0];
	sum		   = lastnum[0];

	// 计算最大值、最小值和总和
	for (int j = 1; j < times; j++) {
		max	 = MAX(max, lastnum[j]);
		min	 = MIN(min, lastnum[j]);
		sum += lastnum[j];
	}

	// 去除最大最小值后计算平均值
	average = (sum - max - min) / (times - 2);
	return average;	   // 返回滤波后的数据
}

/**
 * @brief 低通滤波器初始化函数
 *
 * @param lowpass
 * @param Rx 低通滤波器的比例（x轴方向）
 * @param Ry 低通滤波器的比例（y轴方向）
 * @param Rz 低通滤波器的比例（z轴方向）
 */
void LowPassInit(LowPassFilterParams* lowpass, float Rx, float Ry, float Rz)
{
	lowpass->Low_Pass_Ratio_x = Rx;
	lowpass->Low_Pass_Ratio_y = Ry;
	lowpass->Low_Pass_Ratio_z = Rz;
	lowpass->OldData_x		  = 0.0;
	lowpass->OldData_y		  = 0.0;
	lowpass->OldData_z		  = 0.0;
}

/**
 * @brief 低通滤波器函数
 *
 * @param lowpass
 * @param nowData 输入数据
 * @param dir 滤波方向（x/y/z）
 * @return float 滤波后数据
 */
float Low_Pass_Filter(LowPassFilterParams* lowpass, float nowData, char dir)
{
	float nowOutData;
	switch (dir) {
		case 'x':
			nowOutData		   = lowpass->Low_Pass_Ratio_x * nowData + (1.0f - lowpass->Low_Pass_Ratio_x) * lowpass->OldData_x;
			lowpass->OldData_x = nowOutData;
			break;
		case 'y':
			nowOutData		   = lowpass->Low_Pass_Ratio_y * nowData + (1.0f - lowpass->Low_Pass_Ratio_y) * lowpass->OldData_y;
			lowpass->OldData_y = nowOutData;
			break;
		case 'z':
			nowOutData		   = lowpass->Low_Pass_Ratio_z * nowData + (1.0f - lowpass->Low_Pass_Ratio_z) * lowpass->OldData_z;
			lowpass->OldData_z = nowOutData;
			break;
		default:
			nowOutData = -1;
			break;
	}
	return nowOutData;
}
