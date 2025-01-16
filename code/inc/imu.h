#ifndef _IMU_H_
#define _IMU_H_
#include "vector.h"
#include "zf_common_typedef.h"

typedef struct _IMUParam {
	Vector3f accel;	   // ���������ϵļ��ٶ� m/s2
	Vector3f angle;	   // ���������ϵĽǶȣ�ŷ����)  �˴���ȥ��ƫ����  �� (deg)/s
	Vector3f mag;	   // ���������ϵĴų�  Gauss

	float pitch;	//  ��(deg)
	float roll;		// �����������ƫ���Ƕ�
	float yaw;		// Ϊ��ֱ�۲��ٶ���3ά����

} IMUParam;

typedef struct _Imu {
	IMUParam dataOri;	 // ԭʼ����
	IMUParam dataRaw;	 // ƫ������

	float G;				   // �����������ٶ�
	bool  calibration_flag;	   // ��ɸ�����У׼�ı�־

} IMUType;

extern IMUType IMUdata;

void IMU_init(void);	// INIT
void IMU_getdata(void);
bool IMU_ANG_CALIBRATION(void);	   // У׼�������ܺ�������ֹ״̬���ã������߳�//���ٶȽ��ٶ�����
void IMU_CORRECT(void);

bool IMU_ANG_INTEG(void);	 // �Խ��ٶȽ��л��֣��ⲿ�ַ����ж���

#endif
