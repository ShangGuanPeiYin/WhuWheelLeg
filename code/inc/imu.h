#ifndef _IMU_H_
#define _IMU_H_
#include "vector.h"
#include "zf_common_typedef.h"

#define RAWTIMES	 2000	 // Ư��У׼����
#define irq_interval 5		 // �ж����ڣ���λΪms���˴�ʾ��Ϊ1ms

#define IMUERR 0.02	   // atan 0.02 ����0.02��

typedef struct _IMUParam {
	Vector3f accel;	   // ���������ϵļ��ٶ� m/s2
	Vector3f angle;	   // ���������ϵĽǶȣ�ŷ����)  �˴���ȥ��ƫ����  �� (deg)/s
	Vector3f mag;	   // ���������ϵĴų�  Gauss

	float pitch;	//  ��(deg)
	float roll;		// �����������ƫ���Ƕ�
	float yaw;		// Ϊ��ֱ�۲��ٶ���3ά����

} IMUParam;

typedef struct _Imu {
	IMUParam dataOri;	 // ԭʼ����  ������ʵֵ
	IMUParam dataRaw;	 // ƫ������

	IMUParam dataSet;	 // �趨ֵ

	float G;				   // �����������ٶ�
	bool  calibration_flag;	   // ��ɸ�����У׼�ı�־
} IMUType;

extern IMUType IMUdata;

void IMU_init(void);	// INIT
void IMU_getdata(void);
bool IMU_ang_calibration(void);	   // У׼�������ܺ�������ֹ״̬���ã������߳� ���ٶȽ��ٶ�����
void IMU_correct(void);

bool IMU_ang_integ(void);	 // �Խ��ٶȽ��л��֣��ⲿ�ַ����ж���

#endif
