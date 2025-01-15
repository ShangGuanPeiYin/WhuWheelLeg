#include "zf_common_headfile.h"

// �������˲�������
float Q_angle	= 0.001;	// �Ƕȹ�������
float Q_bias	= 0.003;	// ƫ���������
float R_measure = 0.03;		// ��������
float angle		= 0.0;		// ��ǰ���ƵĽǶ�
float bias		= 0.0;		// ��ǰ���Ƶ�ƫ�����ٶȼ��������ǵ�ƫ�
float rate;					// ���ٶ�
float P[2][2] = {
	{0.0f, 0.0f},
	  {0.0f, 0.0f}
};	// Э�������

float K1 = 0.1;					 // һ���˲���ϵ��
float FirstOrder_angle;			 // һ���˲�������Ƕ�
float K2 = 0.2;					 // �����˲���ϵ��
float x1, x2, y1;				 // �����˲�������
float SecondOrder_angle;		 // �����˲�������Ƕ�
float Low_Pass_Ratio_x = 0.5;	 // ��ͨ�˲����ı�����x�᷽��
float Low_Pass_Ratio_y = 0.5;	 // ��ͨ�˲����ı�����y�᷽��
float Low_Pass_Ratio_z = 0.5;	 // ��ͨ�˲����ı�����z�᷽��

#define dt (0.002)	  // 2ms

/**
 * @brief �������˲�������ͨ���Ƕȡ����ٶȺ�ʱ����������ƵĽǶ�
 *
 * @param newAngle �������ṩ���½Ƕ�ֵ
 * @param newRate ���ٶȣ����������ݣ�
 * @param t ʱ����
 * @return float ���ؾ����������˲��������ĽǶ�ֵ
 */
float Kalman_filter(float newAngle, float newRate, float t)
{
	rate	 = newRate - bias;	  // ȥ��ƫ��Ľ��ٶ�
	angle	+= t * rate;		  // ���½Ƕȹ���ֵ

	// ����Э�������
	P[0][0] += t * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);	// P00
	P[0][1] -= t * P[1][1];											// P01
	P[1][0] -= t * P[1][1];											// P10
	P[1][1] += Q_bias * t;											// P11

	// ���㿨��������
	float S	 = P[0][0] + R_measure;	   // ϵͳ��������
	float K[2];						   // ����������
	K[0]			= P[0][0] / S;
	K[1]			= P[1][0] / S;

	// �������ֵ��Ԥ��ֵ�Ĳ��죨����ֵ��
	float y			= newAngle - angle;

	// ���¹���ֵ
	angle		   += K[0] * y;	   // ���½Ƕ�
	bias		   += K[1] * y;	   // ����ƫ��

	// ����Э�������
	float P00_temp	= P[0][0];
	float P01_temp	= P[0][1];
	P[0][0]		   -= K[0] * P00_temp;
	P[0][1]		   -= K[0] * P01_temp;
	P[1][0]		   -= K[1] * P00_temp;
	P[1][1]		   -= K[1] * P01_temp;

	return angle;	 // �����˲���ĽǶ�
}

/**
 * @brief һ���˲���������ͨ����Ȩƽ�������ݽǶȺͽ��ٶȹ����µĽǶ�
 *
 * @param newAngle �������ṩ���½Ƕ�ֵ
 * @param newRate ���ٶȣ����������ݣ�
 * @param t ʱ����
 * @return float ����һ���˲�������ĽǶ�ֵ
 */
float FirstOrder(float newAngle, float newRate, float t)
{
	FirstOrder_angle = K1 * newAngle + (1 - K1) * (angle + newRate * t);
	return FirstOrder_angle;
}

/**
 * @brief  �����˲��������������ӵļ�Ȩƽ���������ڹ����µĽǶ�ֵ
 *
 * @param newAngle  �������ṩ���½Ƕ�ֵ
 * @param newRate  ���ٶȣ����������ݣ�
 * @param t ʱ����
 * @return float ���ض����˲�������ĽǶ�ֵ
 */
float SecondOrder(float newAngle, float newRate, float t)
{
	x1				  = (newAngle - SecondOrder_angle) * (1 - K2) * (1 - K2);			 // ����һ�ײ�ֵ
	y1				  = y1 + x1 * t;													 // ���¶����˲����е�״̬����
	x2				  = y1 + 2 * (1 - K2) * (newAngle - SecondOrder_angle) + newRate;	 // ���²�ֵ
	SecondOrder_angle = SecondOrder_angle + x2 * t;										 // ��������Ƕ�
	return SecondOrder_angle;															 // �����˲���ĽǶ�
}

/**
 * @brief �˲���1�������������������н����˲���ȥ�������е����ֵ����Сֵ������ƽ��ֵ
 *
 * @param num ��ǰ����
 * @param times ���ݵ�������
 * @return float �����˲�������ݣ�ȥ�����ֵ����Сֵ��ƽ��ֵ��
 */
float fliter1(float num, int times)
{
	static float lastnum[30] = {0};	   // �洢ǰ30�����ݵ�
	float		 average, max, min, sum = 0;

	// ������������
	for (int i = times - 2; i >= 0; i--) { lastnum[i + 1] = lastnum[i]; }
	lastnum[0] = num;

	max		   = lastnum[0];
	min		   = lastnum[0];
	sum		   = lastnum[0];

	// �������ֵ����Сֵ���ܺ�
	for (int j = 1; j < times; j++) {
		max	 = MAX(max, lastnum[j]);
		min	 = MIN(min, lastnum[j]);
		sum += lastnum[j];
	}

	// ȥ�������Сֵ�����ƽ��ֵ
	average = (sum - max - min) / (times - 2);
	return average;	   // �����˲��������
}

/**
 * @brief ��ͨ�˲���������x�᷽�򣩣������˲�x�᷽����������ݣ����ٸ�Ƶ����
 *
 * @param nowData ��ǰ����������
 * @return float �����˲��������
 */
float Low_Pass_Filter_x(float nowData)
{	 // ��ͨ�˲����������˲�x�᷽�������
	static float nowOutData, oldOutData;
	nowOutData = Low_Pass_Ratio_x * nowData + (1.0f - Low_Pass_Ratio_x) * oldOutData;
	oldOutData = nowOutData;
	return nowOutData;	  // �����˲��������
}

/**
 * @brief ��ͨ�˲���������y�᷽�򣩣������˲�y�᷽����������ݣ����ٸ�Ƶ����
 *
 * @param nowData ��ǰ����������
 * @return float �����˲��������
 */
float Low_Pass_Filter_y(float nowData)
{	 // ��ͨ�˲����������˲�y�᷽�������
	static float nowOutData, oldOutData;
	nowOutData = Low_Pass_Ratio_y * nowData + (1.0f - Low_Pass_Ratio_y) * oldOutData;
	oldOutData = nowOutData;
	return nowOutData;	  // �����˲��������
}

/**
 * @brief ��ͨ�˲���������z�᷽�򣩣������˲�z�᷽����������ݣ����ٸ�Ƶ����
 *
 * @param nowData ��ǰ����������
 * @return float �����˲��������
 */
float Low_Pass_Filter_z(float nowData)
{	 // ��ͨ�˲����������˲�z�᷽�������
	static float nowOutData, oldOutData;
	nowOutData = Low_Pass_Ratio_z * nowData + (1.0f - Low_Pass_Ratio_z) * oldOutData;
	oldOutData = nowOutData;
	return nowOutData;	  // �����˲��������
}
