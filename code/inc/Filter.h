#ifndef _FILTER_H_
#define _FILTER_H_
#include "zf_common_headfile.h"

// �������˲��������ṹ��
typedef struct {
	float Q_angle;		// �Ƕȹ�������
	float Q_bias;		// ƫ���������
	float R_measure;	// ��������
	float angle;		// ��ǰ���ƵĽǶ�
	float bias;			// ��ǰ���Ƶ�ƫ�����ٶȼ��������ǵ�ƫ�
	float rate;			// ���ٶ�
	float P[2][2];		// Э�������
} KalmanParams;

// һ���˲��������ṹ��
typedef struct {
	float K1;				   // һ���˲���ϵ��
	float FirstOrder_angle;	   // һ���˲�������Ƕ�
} FirstOrderFilterParams;

// �����˲��������ṹ��
typedef struct {
	float K2;					// �����˲���ϵ��
	float x1;					// �����˲�������
	float x2;					// �����˲�������
	float y1;					// �����˲�������
	float SecondOrder_angle;	// �����˲�������Ƕ�
} SecondOrderFilterParams;

// ��ͨ�˲��������ṹ��
typedef struct {
	float Low_Pass_Ratio_x;	   // ��ͨ�˲����ı�����x�᷽��
	float Low_Pass_Ratio_y;	   // ��ͨ�˲����ı�����y�᷽��
	float Low_Pass_Ratio_z;	   // ��ͨ�˲����ı�����z�᷽��
	float OldData_x;		   // ��һ������(x�᷽��)
	float OldData_y;		   // ��һ������(y�᷽��)
	float OldData_z;		   // ��һ������(z�᷽��)
} LowPassFilterParams;

// �������˲�����
void  KalmanParamsInit(KalmanParams* kalman, float Q_angle, float Q_bias, float R_measure, float angle);
float Kalman_filter(KalmanParams* kalman, float newAngle, float newRate, float t);

// һ���˲�������
void  FirstOrderInit(FirstOrderFilterParams* firstorder, float K1, float angle);
float FirstOrder(FirstOrderFilterParams* firstorder, float newAngle, float newRate, float t);

// �����˲�������
void  SecondOrderInit(SecondOrderFilterParams* secondorder, float K2, float angle);
float SecondOrder(SecondOrderFilterParams* secondorder, float newAngle, float newRate, float t);

// ��ͨ�˲�����
void  LowPassInit(LowPassFilterParams* lowpass, float Rx, float Ry, float Rz);
float Low_Pass_Filter(LowPassFilterParams* lowpass, float nowData, char dir);

// �˲���1����
float fliter1(float num, int times);

#endif
