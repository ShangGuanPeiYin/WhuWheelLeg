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
} LowPassFilterParams;

// TODO ��װ��һ����д

float Kalman_filter(float newAngle, float newRate, float t);
float FirstOrder(float newAngle, float newRate, float t);
float SecondOrder(float newAngle, float newRate, float t);
float fliter1(float num, int times);
float Low_Pass_Filter_x(float nowData);
float Low_Pass_Filter_y(float nowData);
float Low_Pass_Filter_z(float nowData);

#endif
