#ifndef _IMU_H_
#define _IMU_H_
#include "vector.h"
#include "zf_common_typedef.h"

#define Sampling_Time (1. / 1000.)			  // ��������
#define irq_interval  Sampling_Time * 1000	  // �ж����ڣ���λΪms���˴�ʾ��Ϊ5ms

typedef struct _IMUParam {
	Vector3f accel;	   // ���������ϵļ��ٶ� m/s2
	Vector3f angle;	   // ���������ϵĽ��ٶȣ�ŷ����)  �˴���ȥ��ƫ����  �� (deg)/s
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

#define Kp_New			0.9f	// �����˲���ǰ���ݵ�Ȩ��
#define G				9.80665f
#define Acc_Gain		0.0002441f	   // ���ٶȱ��G (��ʼ�����ٶ�������-+4g LSBa = 2*8/65535.0)
#define Gyro_Gain		0.0609756f	   // ���ٶȱ�ɶ� (��ʼ��������������+-2000 LSBg = 2*2000/65535.0)
#define Gyro_Gr			0.00106528f	   // ���ٶȱ�ɻ���(pi/180 * LSBg)
#define Radian_2_Degree 57.2957795f
#define Degree_2_Radian 0.01745329f

/*************IMU����************/
typedef struct _IMU_ {
	Vector3f T_Acc;		// �����Ǽ��ٶ�ADֵ ת���� ��/ƽ����
	Vector3f T_Gyro;	// �����ǽ��ٶ�ADֵ ת���� ����/��
	Vector3f T_Mag;

	Vector3f Gyro;	   // �������̬���ٶ�
	Vector3f Angle;	   // �������̬�Ƕ�
} _IMU;

void IMU_getdata(void);

void  IMU_init(void);
void  Get_Attitude(void);
float angle_calc(float angle_m, float gyro_m, int index);
void  IMUupdate(Vector3f* Gyr_rad, Vector3f* Acc_filt, Vector3f* Mag_filt, Vector3f* Att_Angle);
void  IMUANG_Offset(void);

#endif
