#include "zf_common_headfile.h"
// #include "zf_device_imu963ra.h"

IMUType IMUdata;

void IMU_init(void)
{
	imu963ra_init();	// ��ʼ�� IMU963RA

	///////////////////////////////////////////////////////// ��ֵҪ����������
	//   IMUdata.raw_accel_x=0;    /*uinit:  m/s2*/
	//   IMUdata.raw_accel_y=0;    // ���������ϵļ��ٶ�Ʈ��
	//   IMUdata.raw_accel_z=1;

	//   IMUdata.raw_angel_x=0;    /*uinit: (deg)/s*/
	//   IMUdata.raw_angel_y=0;    // ���������ϵĽ��ٶ�Ʈ��
	//   IMUdata.raw_angel_z=0;

	//   IMUdata.raw_mag_x=0;    /*uinit: mGauss*/
	//   IMUdata.raw_mag_y=0;    // ���������ϵ�ԭʼ�ų�����
	//   IMUdata.raw_mag_z=0;

	IMUdata.calibration_flag = 0;	 // δ���У׼��־
}

#define times 2000	  // Ư��У׼����

// long zheshiyigejishuqi=0;
// float zheshileijiajishuqi=0;

void IMUACC_Offset(void)	// �������ٶ�������Ӱ���ֵ�����᷽��Ʈ�ƣ�
{
	float gx_offset = 0, gy_offset = 0, gz_offset = 0;
	for (short i = times; i > 0; i--)	 // ����ƫ����,ֻ�ھ�ֹʱ����һ��
	{
		imu963ra_get_acc();	   // ��ȡ IMU963RA ���ٶȼ�����

		gx_offset += imu963ra_acc_transition(imu963ra_acc_x);
		gy_offset += imu963ra_acc_transition(imu963ra_acc_y);
		gz_offset += imu963ra_acc_transition(imu963ra_acc_z);
		// system_delay_10ns(100000);
	}
	IMUdata.raw_accel_x = gx_offset / times;
	IMUdata.raw_accel_y = gy_offset / times;
	IMUdata.raw_accel_z = gz_offset / times;	// �˴�������У׼ʱ��Ϊ׼�������������ٶȷ���Ϊ׼����У�����������ں���
	// zheshiyigejishuqi++;
	// IMUdata.G=((sqrtf(gx_offset*gx_offset+gy_offset*gy_offset+gz_offset*gz_offset)/times)*(zheshiyigejishuqi-1)+IMUdata.G)/zheshiyigejishuqi;
	IMUdata.G = sqrtf(gx_offset * gx_offset + gy_offset * gy_offset + gz_offset * gz_offset) / times;
}

bool IMUANG_Offset(void)	// �������ٶȳ�ֵ�����᷽��Ʈ�ƣ�
{
	bool  error		  = 0;
	float angx_offset = 0, angy_offset = 0, angz_offset = 0;
	for (short i = times; i > 0; i--)	 // ����ƫ����,ֻ�ھ�ֹʱ����һ��
	{
		imu963ra_get_gyro();	// ��ȡ IMU963RA ����������

		angx_offset += imu963ra_gyro_transition(imu963ra_gyro_x);
		angy_offset += imu963ra_gyro_transition(imu963ra_gyro_y);
		angz_offset += imu963ra_gyro_transition(imu963ra_gyro_z);
		system_delay_ms(1);
	}
	IMUdata.raw_angel_x = angx_offset / times;
	IMUdata.raw_angel_y = angy_offset / times;
	IMUdata.raw_angel_z = angz_offset / times;
	if (IMUdata.raw_angel_x > 10 || IMUdata.raw_angel_y > 10 || IMUdata.raw_angel_z > 10)
		error = 1;
	return error;
}

void IMUANG_ORI(void)	 // ���㳵����̬��ֵ�����᷽��Ʈ�ƣ�//����Ӧ���������ٶ�У׼�����
{
	float x = 0;	// �洢��
	x		= IMUdata.raw_yaw;
	IMUdata.raw_yaw = x;	// ���ڳ�ֵ������������ȷ�������ɶ�Ϊ1���޷��������ʼ�ĺ����(��ת��)��Ҫ��ƽ�������ѭ��ȷ��
	// �������Ƕ�Ϊ��0,IMUdata.G,0�����ɴ˺ͳ�ʼaccֵ���Ͻ����ʼ�Ƕȣ���������ʹ������ƽ�⣬���ڿ���Ϊ�������flashд�����ݣ������Ż����ݣ�����imuƽ��Ƕ�
	x = (IMUdata.raw_accel_x > 0 ? 1 : -1) * IMUdata.raw_accel_y
		/ sqrtf(IMUdata.raw_accel_y * IMUdata.raw_accel_y + IMUdata.raw_accel_x * IMUdata.raw_accel_x);
	IMUdata.raw_pitch = 180 / PI * acosf(x);

	// ��ʼ������
	x				  = (IMUdata.raw_accel_z > 0 ? -1 : 1) * IMUdata.raw_accel_y
		/ sqrtf(IMUdata.raw_accel_y * IMUdata.raw_accel_y + IMUdata.raw_accel_z * IMUdata.raw_accel_z);
	IMUdata.raw_roll = 180 / PI * acosf(x);
	// ��ʼ���ڽ�//����������λ��ԭ�򣬳�ʼ�������෴
	if (IMUdata.raw_pitch > 90)
		IMUdata.raw_pitch -= 180;
	else if (IMUdata.raw_pitch < -90)
		IMUdata.raw_pitch += 180;
	if (IMUdata.raw_roll > 90)
		IMUdata.raw_roll -= 180;
	else if (IMUdata.raw_roll < -90)
		IMUdata.raw_roll += 180;
	// ��ֹ��0cos�ж�+-180�������Է�ת�����������0����
}

void IMU_ANG_GET_ORIDAT(void)	 // ��������̬��ֵ��ֵ������Ƕ�//����Ӧ��У׼��ֹʱ���Ϻ���ͬʱ����
{
	IMUdata.pitch = IMUdata.raw_pitch;
	IMUdata.roll  = IMUdata.raw_roll;
	IMUdata.yaw	  = IMUdata.raw_yaw;
}

void IMUMAG_Offset(void)	// �����ų���ֵ�����᷽��Ʈ�ƣ�
{
	float rawx_offset = 0, rawy_offset = 0, rawz_offset = 0;
	for (short i = times; i > 0; i--)	 // ����ƫ����,ֻ�ھ�ֹʱ����һ��
	{
		imu963ra_get_mag();	   // ��ȡ IMU963RA ����������

		rawx_offset += imu963ra_mag_transition(imu963ra_mag_x);
		rawy_offset += imu963ra_mag_transition(imu963ra_mag_y);
		rawz_offset += imu963ra_mag_transition(imu963ra_mag_z);
	}
	IMUdata.raw_mag_x = imu963ra_mag_transition(rawx_offset / times);
	IMUdata.raw_mag_y = imu963ra_mag_transition(rawy_offset / times);
	IMUdata.raw_mag_z = imu963ra_mag_transition(rawz_offset / times);
}

void IMU_getdata(void)
{
	imu963ra_get_acc();		// ��ȡ IMU963RA ���ٶȼ�����
	imu963ra_get_gyro();	// ��ȡ IMU963RA ����������
	imu963ra_get_mag();		// ��ȡ IMU963RA ����������

	IMUdata.accel_x = imu963ra_acc_transition(imu963ra_acc_x);
	IMUdata.accel_y = imu963ra_acc_transition(imu963ra_acc_y);
	IMUdata.accel_z = imu963ra_acc_transition(imu963ra_acc_z);

	IMUdata.angle_x = imu963ra_gyro_transition(imu963ra_gyro_x) - IMUdata.raw_angel_x;
	IMUdata.angle_y = imu963ra_gyro_transition(imu963ra_gyro_y) - IMUdata.raw_angel_y;
	IMUdata.angle_z = imu963ra_gyro_transition(imu963ra_gyro_z) - IMUdata.raw_angel_z;

	IMUdata.mag_x	= imu963ra_mag_transition(imu963ra_mag_x);
	IMUdata.mag_y	= imu963ra_mag_transition(imu963ra_mag_y);
	IMUdata.mag_z	= imu963ra_mag_transition(imu963ra_mag_z);
}
void IMU_CORRECT()	  // �����Ƕ�̬У׼����������������whileѭ���У������ۻ���ֻ��G��Сʱ���Ե��ã�
{
	float current_G;
	float x;
	IMU_getdata();
	current_G = sqrtf(IMUdata.accel_x * IMUdata.accel_x + IMUdata.accel_y * IMUdata.accel_y + IMUdata.accel_z * IMUdata.accel_z);
	if (fabsf(current_G - IMUdata.G) < 0.02 * fabsf(IMUdata.G))	   // ���������ˢ�µ��Ͽ��ɶȣ���Ҫ������Χ
	{
		IMUdata.calibration_flag = 0;

		x						 = (IMUdata.accel_x > 0 ? 1 : -1) * IMUdata.accel_y
			/ sqrtf(IMUdata.accel_y * IMUdata.accel_y + IMUdata.accel_x * IMUdata.accel_x);
		IMUdata.pitch = 180 / PI * acosf(x);
		x			  = (IMUdata.accel_z > 0 ? -1 : 1) * IMUdata.accel_y
			/ sqrtf(IMUdata.accel_y * IMUdata.accel_y + IMUdata.accel_z * IMUdata.accel_z);
		IMUdata.roll = 180 / PI * acosf(x);
		if (IMUdata.pitch > 90)
			IMUdata.pitch -= 180;
		else if (IMUdata.pitch < -90)
			IMUdata.pitch += 180;
		if (IMUdata.roll > 90)
			IMUdata.roll -= 180;
		else if (IMUdata.roll < -90)
			IMUdata.roll += 180;
		IMUdata.calibration_flag = 1;
	}
	//  oled_show_int(10, 0, (int)(current_G*1000), 5);
}

#define irq_interval 1	  // �ж����ڣ���λΪms���˴�ʾ��Ϊ1ms
bool IMU_ANG_INTEG()	  // �Խ��ٶȽ��л��֣��ⲿ�ַ����ж���
{
	IMU_CORRECT();
	if (IMUdata.calibration_flag) {
		IMU_getdata();
		IMUdata.pitch += IMUdata.angle_z * irq_interval / 1000;
		IMUdata.roll  += IMUdata.angle_x * irq_interval / 1000;
		IMUdata.yaw	  += IMUdata.angle_y * irq_interval / 1000;
	}

	return IMUdata.calibration_flag;	// ����0��ʾδ���У׼��������У׼
}

bool IMU_ANG_CALIBRATION()	  // У׼�������ܺ�������ֹ״̬���ã������߳�//���ٶȽ��ٶ�����//��ʱ�ṹ���д洢У׼����ֹ��ʱ��ֵ����
{
	IMUdata.calibration_flag = 0;
	IMUACC_Offset();		 // �������ٶ�������Ӱ���ֵ�����᷽��Ʈ�ƣ�
	IMUANG_Offset();		 // �������ٶȳ�ֵ�����᷽��Ʈ�ƣ�
	IMUANG_ORI();			 // ���㳵����̬��ֵ�����᷽��Ʈ�ƣ�//����Ӧ���������ٶ�У׼�����
	IMU_ANG_GET_ORIDAT();	 // ��������̬��ֵ��ֵ������Ƕ�//����Ӧ��У׼��ֹʱ���Ϻ���ͬʱ����
	IMUdata.calibration_flag = 1;

	return IMUdata.calibration_flag;
}
