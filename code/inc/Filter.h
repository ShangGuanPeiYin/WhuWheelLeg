#ifndef _FILTER_H_
#define _FILTER_H_
#include "zf_common_headfile.h"

// 卡尔曼滤波器参数结构体
typedef struct {
	float Q_angle;		// 角度过程噪声
	float Q_bias;		// 偏差过程噪声
	float R_measure;	// 测量噪声
	float angle;		// 当前估计的角度
	float bias;			// 当前估计的偏差（如加速度计与陀螺仪的偏差）
	float rate;			// 角速度
	float P[2][2];		// 协方差矩阵
} KalmanParams;

// 一阶滤波器参数结构体
typedef struct {
	float K1;				   // 一阶滤波器系数
	float FirstOrder_angle;	   // 一阶滤波器输出角度
} FirstOrderFilterParams;

// 二阶滤波器参数结构体
typedef struct {
	float K2;					// 二阶滤波器系数
	float x1;					// 二阶滤波器变量
	float x2;					// 二阶滤波器变量
	float y1;					// 二阶滤波器变量
	float SecondOrder_angle;	// 二阶滤波器输出角度
} SecondOrderFilterParams;

// 低通滤波器参数结构体
typedef struct {
	float Low_Pass_Ratio_x;	   // 低通滤波器的比例（x轴方向）
	float Low_Pass_Ratio_y;	   // 低通滤波器的比例（y轴方向）
	float Low_Pass_Ratio_z;	   // 低通滤波器的比例（z轴方向）
	float OldData_x;		   // 上一次数据(x轴方向)
	float OldData_y;		   // 上一次数据(y轴方向)
	float OldData_z;		   // 上一次数据(z轴方向)
} LowPassFilterParams;

// 卡尔曼滤波函数
void  KalmanParamsInit(KalmanParams* kalman, float Q_angle, float Q_bias, float R_measure, float angle);
float Kalman_filter(KalmanParams* kalman, float newAngle, float newRate, float t);

// 一阶滤波器函数
void  FirstOrderInit(FirstOrderFilterParams* firstorder, float K1, float angle);
float FirstOrder(FirstOrderFilterParams* firstorder, float newAngle, float newRate, float t);

// 二阶滤波器函数
void  SecondOrderInit(SecondOrderFilterParams* secondorder, float K2, float angle);
float SecondOrder(SecondOrderFilterParams* secondorder, float newAngle, float newRate, float t);

// 低通滤波函数
void  LowPassInit(LowPassFilterParams* lowpass, float Rx, float Ry, float Rz);
float Low_Pass_Filter(LowPassFilterParams* lowpass, float nowData, char dir);

// 滤波器1函数
float fliter1(float num, int times);

#endif
