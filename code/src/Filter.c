#include "zf_common_headfile.h"

// 卡尔曼滤波器参数
float Q_angle	= 0.001;	// 角度过程噪声
float Q_bias	= 0.003;	// 偏差过程噪声
float R_measure = 0.03;		// 测量噪声
float angle		= 0.0;		// 当前估计的角度
float bias		= 0.0;		// 当前估计的偏差（如加速度计与陀螺仪的偏差）
float rate;					// 角速度
float P[2][2] = {
	{0.0f, 0.0f},
	  {0.0f, 0.0f}
};	// 协方差矩阵

float K1 = 0.1;					 // 一阶滤波器系数
float FirstOrder_angle;			 // 一阶滤波器输出角度
float K2 = 0.2;					 // 二阶滤波器系数
float x1, x2, y1;				 // 二阶滤波器变量
float SecondOrder_angle;		 // 二阶滤波器输出角度
float Low_Pass_Ratio_x = 0.5;	 // 低通滤波器的比例（x轴方向）
float Low_Pass_Ratio_y = 0.5;	 // 低通滤波器的比例（y轴方向）
float Low_Pass_Ratio_z = 0.5;	 // 低通滤波器的比例（z轴方向）

#define dt (0.002)	  // 2ms

/**
 * @brief 卡尔曼滤波函数：通过角度、角速度和时间间隔计算估计的角度
 *
 * @param newAngle 传感器提供的新角度值
 * @param newRate 角速度（陀螺仪数据）
 * @param t 时间间隔
 * @return float 返回经过卡尔曼滤波器处理后的角度值
 */
float Kalman_filter(float newAngle, float newRate, float t)
{
	rate	 = newRate - bias;	  // 去除偏差的角速度
	angle	+= t * rate;		  // 更新角度估计值

	// 更新协方差矩阵
	P[0][0] += t * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);	// P00
	P[0][1] -= t * P[1][1];											// P01
	P[1][0] -= t * P[1][1];											// P10
	P[1][1] += Q_bias * t;											// P11

	// 计算卡尔曼增益
	float S	 = P[0][0] + R_measure;	   // 系统的总噪声
	float K[2];						   // 卡尔曼增益
	K[0]			= P[0][0] / S;
	K[1]			= P[1][0] / S;

	// 计算测量值与预测值的差异（创新值）
	float y			= newAngle - angle;

	// 更新估计值
	angle		   += K[0] * y;	   // 更新角度
	bias		   += K[1] * y;	   // 更新偏差

	// 更新协方差矩阵
	float P00_temp	= P[0][0];
	float P01_temp	= P[0][1];
	P[0][0]		   -= K[0] * P00_temp;
	P[0][1]		   -= K[0] * P01_temp;
	P[1][0]		   -= K[1] * P00_temp;
	P[1][1]		   -= K[1] * P01_temp;

	return angle;	 // 返回滤波后的角度
}

/**
 * @brief 一阶滤波器函数：通过加权平均法根据角度和角速度估算新的角度
 *
 * @param newAngle 传感器提供的新角度值
 * @param newRate 角速度（陀螺仪数据）
 * @param t 时间间隔
 * @return float 返回一阶滤波器估算的角度值
 */
float FirstOrder(float newAngle, float newRate, float t)
{
	FirstOrder_angle = K1 * newAngle + (1 - K1) * (angle + newRate * t);
	return FirstOrder_angle;
}

/**
 * @brief  二阶滤波器函数：更复杂的加权平滑处理，用于估算新的角度值
 *
 * @param newAngle  传感器提供的新角度值
 * @param newRate  角速度（陀螺仪数据）
 * @param t 时间间隔
 * @return float 返回二阶滤波器估算的角度值
 */
float SecondOrder(float newAngle, float newRate, float t)
{
	x1				  = (newAngle - SecondOrder_angle) * (1 - K2) * (1 - K2);			 // 计算一阶差值
	y1				  = y1 + x1 * t;													 // 更新二阶滤波器中的状态变量
	x2				  = y1 + 2 * (1 - K2) * (newAngle - SecondOrder_angle) + newRate;	 // 更新差值
	SecondOrder_angle = SecondOrder_angle + x2 * t;										 // 更新输出角度
	return SecondOrder_angle;															 // 返回滤波后的角度
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
 * @brief 低通滤波器函数（x轴方向）：用于滤波x轴方向的输入数据，减少高频噪声
 *
 * @param nowData 当前的输入数据
 * @return float 返回滤波后的数据
 */
float Low_Pass_Filter_x(float nowData)
{	 // 低通滤波器：用于滤波x轴方向的数据
	static float nowOutData, oldOutData;
	nowOutData = Low_Pass_Ratio_x * nowData + (1.0f - Low_Pass_Ratio_x) * oldOutData;
	oldOutData = nowOutData;
	return nowOutData;	  // 返回滤波后的数据
}

/**
 * @brief 低通滤波器函数（y轴方向）：用于滤波y轴方向的输入数据，减少高频噪声
 *
 * @param nowData 当前的输入数据
 * @return float 返回滤波后的数据
 */
float Low_Pass_Filter_y(float nowData)
{	 // 低通滤波器：用于滤波y轴方向的数据
	static float nowOutData, oldOutData;
	nowOutData = Low_Pass_Ratio_y * nowData + (1.0f - Low_Pass_Ratio_y) * oldOutData;
	oldOutData = nowOutData;
	return nowOutData;	  // 返回滤波后的数据
}

/**
 * @brief 低通滤波器函数（z轴方向）：用于滤波z轴方向的输入数据，减少高频噪声
 *
 * @param nowData 当前的输入数据
 * @return float 返回滤波后的数据
 */
float Low_Pass_Filter_z(float nowData)
{	 // 低通滤波器：用于滤波z轴方向的数据
	static float nowOutData, oldOutData;
	nowOutData = Low_Pass_Ratio_z * nowData + (1.0f - Low_Pass_Ratio_z) * oldOutData;
	oldOutData = nowOutData;
	return nowOutData;	  // 返回滤波后的数据
}
