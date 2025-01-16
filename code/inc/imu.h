#ifndef _IMU_H_
#define _IMU_H_
#include "zf_common_typedef.h"

typedef struct _Imu {
	float accel_x;	  /*uinit: m/s2*/
	float accel_y;	  // ���������ϵļ��ٶ�
	float accel_z;

	float angle_x;	  /*uinit: �� (deg)/s*/
	float angle_y;	  // ���������ϵĽǶȣ�ŷ����)
	float angle_z;

	float mag_x;	/*uinit: ????*/
	float mag_y;	// ���������ϵĴų�
	float mag_z;

	float pitch;   /*uinit: ��  (deg)*/
	float roll;	   // ������Ͱ������ת�Ƕ�
	float yaw;

	float raw_accel_x;	  /*uinit:  m/s2*/
	float raw_accel_y;	  // ���������ϵļ��ٶ�Ʈ��
	float raw_accel_z;

	float raw_angel_x;	  /*uinit: (deg)/s*/
	float raw_angel_y;	  // ���������ϵĽ��ٶ�Ʈ��
	float raw_angel_z;

	float raw_mag_x;	/*uinit: mGauss*/
	float raw_mag_y;	// ���������ϵ�ԭʼ�ų�����
	float raw_mag_z;

	float raw_pitch;   /*uinit: ��  (deg)*/
	float raw_roll;	   // ��ʼ����ֹУ׼״̬�µģ�������Ͱ������ת�Ƕ�
	float raw_yaw;

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
