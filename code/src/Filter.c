#include "zf_common_headfile.h"

#define dt (0.002)	  // 2ms

/**
 * @brief �������˲���ʼ������
 * @param kalman
 * @param Q_angle �Ƕȹ�������(0.001)
 * @param Q_bias ƫ���������(0.003)
 * @param R_measure ��������(0.03)
 * @param angle ��ʼ�Ƕ�
 */
void KalmanParamsInit(KalmanParams* kalman, float Q_angle, float Q_bias, float R_measure, float angle)
{
	kalman->Q_angle	  = Q_angle;
	kalman->Q_bias	  = Q_bias;
	kalman->R_measure = R_measure;
	kalman->angle	  = angle;	  // ��ǰ���ƵĽǶ�
	kalman->bias	  = 0.f;	  // ��ǰ���Ƶ�ƫ�����ٶȼ��������ǵ�ƫ�
	kalman->rate	  = 0.f;	  // ���ٶ�
	kalman->P[0][0]	  = 0.f;
	kalman->P[0][1]	  = 0.f;
	kalman->P[1][0]	  = 0.f;
	kalman->P[1][1]	  = 0.f;
}

/**
 * @brief �������˲�������ͨ���Ƕȡ����ٶȺ�ʱ����������ƵĽǶ�
 *
 * @param kalman
 * @param newAngle �������ṩ���½Ƕ�ֵ
 * @param newRate ���ٶȣ����������ݣ�
 * @param t ʱ����
 * @return float ���ؾ����������˲��������ĽǶ�ֵ
 */
float Kalman_filter(KalmanParams* kalman, float newAngle, float newRate, float t)
{
	kalman->rate	 = newRate - kalman->bias;	  // ȥ��ƫ��Ľ��ٶ�
	kalman->angle	+= t * kalman->rate;		  // ���½Ƕȹ���ֵ

	// ����Э�������
	kalman->P[0][0] += t * (dt * kalman->P[1][1] - kalman->P[0][1] - kalman->P[1][0] + kalman->Q_angle);	// P00
	kalman->P[0][1] -= t * kalman->P[1][1];																	// P01
	kalman->P[1][0] -= t * kalman->P[1][1];																	// P10
	kalman->P[1][1] += kalman->Q_bias * t;																	// P11

	// ���㿨��������
	float S			 = kalman->P[0][0] + kalman->R_measure;	   // ϵͳ��������
	float K[2];												   // ����������
	K[0]			 = kalman->P[0][0] / S;
	K[1]			 = kalman->P[1][0] / S;

	// �������ֵ��Ԥ��ֵ�Ĳ��죨����ֵ��
	float y			 = newAngle - kalman->angle;

	// ���¹���ֵ
	kalman->angle	+= K[0] * y;	// ���½Ƕ�
	kalman->bias	+= K[1] * y;	// ����ƫ��

	// ����Э�������
	float P00_temp	 = kalman->P[0][0];
	float P01_temp	 = kalman->P[0][1];
	kalman->P[0][0] -= K[0] * P00_temp;
	kalman->P[0][1] -= K[0] * P01_temp;
	kalman->P[1][0] -= K[1] * P00_temp;
	kalman->P[1][1] -= K[1] * P01_temp;

	return kalman->angle;	 // �����˲���ĽǶ�
}

/**
 * @brief һ���˲�����ʼ������
 *
 * @param firstorder
 * @param K1 һ���˲���ϵ��
 * @param angle ��ʼ�Ƕ�
 */
void FirstOrderInit(FirstOrderFilterParams* firstorder, float K1, float angle)
{
	firstorder->K1				 = K1;
	firstorder->FirstOrder_angle = angle;
}

/**
 * @brief һ���˲���������ͨ����Ȩƽ�������ݽǶȺͽ��ٶȹ����µĽǶ�
 *
 * @param firstorder
 * @param newAngle �������ṩ���½Ƕ�ֵ
 * @param newRate ���ٶȣ����������ݣ�
 * @param t ʱ����
 * @return float ����һ���˲�������ĽǶ�ֵ
 */
float FirstOrder(FirstOrderFilterParams* firstorder, float newAngle, float newRate, float t)
{
	firstorder->FirstOrder_angle = firstorder->K1 * newAngle + (1 - firstorder->K1) * (firstorder->FirstOrder_angle + newRate * t);
	return firstorder->FirstOrder_angle;
}

/**
 * @brief  �����˲�����ʼ������
 *
 * @param secondorder
 * @param K2 �����˲���ϵ��
 * @param angle ��ʼ�Ƕ�
 */
void SecondOrderInit(SecondOrderFilterParams* secondorder, float K2, float angle)
{
	secondorder->K2				   = K2;
	secondorder->SecondOrder_angle = angle;
}

/**
 * @brief  �����˲��������������ӵļ�Ȩƽ���������ڹ����µĽǶ�ֵ
 *
 * @param secondorder
 * @param newAngle  �������ṩ���½Ƕ�ֵ
 * @param newRate  ���ٶȣ����������ݣ�
 * @param t ʱ����
 * @return float ���ض����˲�������ĽǶ�ֵ
 */
float SecondOrder(SecondOrderFilterParams* secondorder, float newAngle, float newRate, float t)
{
	secondorder->x1
		= (newAngle - secondorder->SecondOrder_angle) * (1 - secondorder->K2) * (1 - secondorder->K2);	  // ����һ�ײ�ֵ
	secondorder->y1 = secondorder->y1 + secondorder->x1 * t;	// ���¶����˲����е�״̬����
	secondorder->x2
		= secondorder->y1 + 2 * (1 - secondorder->K2) * (newAngle - secondorder->SecondOrder_angle) + newRate;	  // ���²�ֵ
	secondorder->SecondOrder_angle = secondorder->SecondOrder_angle + secondorder->x2 * t;	  // ��������Ƕ�
	return secondorder->SecondOrder_angle;													  // �����˲���ĽǶ�
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
 * @brief ��ͨ�˲�����ʼ������
 *
 * @param lowpass
 * @param Rx ��ͨ�˲����ı�����x�᷽��
 * @param Ry ��ͨ�˲����ı�����y�᷽��
 * @param Rz ��ͨ�˲����ı�����z�᷽��
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
 * @brief ��ͨ�˲�������
 *
 * @param lowpass
 * @param nowData ��������
 * @param dir �˲�����x/y/z��
 * @return float �˲�������
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
