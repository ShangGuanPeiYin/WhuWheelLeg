#include "zf_common_headfile.h"

IMUType IMUdata;

/**
 * @brief �����ǳ�ʼ������
 *
 */
void IMU_init(void)
{
	while (true) {	  // ��ʼ�� IMU963RA
		if (imu963ra_init() == 0)
			break;
	}

	// TODO: ��ֵҪ����������
	IMUdata.dataRaw.accel.x	 = 0;	 // ���������ϵļ��ٶ�Ʈ��
	IMUdata.dataRaw.accel.y	 = 0;
	IMUdata.dataRaw.accel.z	 = 1;

	IMUdata.dataRaw.angle.x	 = 0;	 // ���������ϵĽ��ٶ�Ʈ��
	IMUdata.dataRaw.angle.y	 = 0;
	IMUdata.dataRaw.angle.z	 = 0;

	IMUdata.dataRaw.mag.x	 = 0;
	IMUdata.dataRaw.mag.y	 = 0;
	IMUdata.dataRaw.mag.z	 = 0;

	IMUdata.calibration_flag = 0;	 // δ���У׼��־
}

// long IMUCnt = 0;

/**
 * @brief  �������ٶ�������Ӱ���ֵ�����᷽��Ʈ�ƣ�
 *
 */
void IMU_acc_Offset(void)
{
	float gx_offset = 0, gy_offset = 0, gz_offset = 0;

	for (short i = RAWTIMES; i > 0; i--)	// ����ƫ����,ֻ�ھ�ֹʱ����һ��
	{
		imu963ra_get_acc();	   // ��ȡ IMU963RA ���ٶȼ�����

		gx_offset += imu963ra_acc_transition(imu963ra_acc_x);
		gy_offset += imu963ra_acc_transition(imu963ra_acc_y);
		gz_offset += imu963ra_acc_transition(imu963ra_acc_z);
		// system_delay_10ns(100000);
	}

	IMUdata.dataRaw.accel.x = gx_offset / RAWTIMES;
	IMUdata.dataRaw.accel.y = gy_offset / RAWTIMES;
	IMUdata.dataRaw.accel.z = gz_offset / RAWTIMES;	   // �˴�������У׼ʱ��Ϊ׼�������������ٶȷ���Ϊ׼����У�����������ں���

	// IMUCnt++;
	// IMUdata.G=((sqrtf(gx_offset*gx_offset+gy_offset*gy_offset+gz_offset*gz_offset)/RAWTIMES)*(IMUCnt-1)+IMUdata.G)/IMUCnt;

	IMUdata.G = sqrtf(gx_offset * gx_offset + gy_offset * gy_offset + gz_offset * gz_offset) / RAWTIMES;
}

/**
 * @brief �������ٶȳ�ֵ�����᷽��Ʈ�ƣ�
 *
 * @return true
 * @return false
 */
bool IMUANG_Offset(void)
{
	bool  error		  = false;
	float angx_offset = 0, angy_offset = 0, angz_offset = 0;
	for (short i = RAWTIMES; i > 0; i--)	// ����ƫ����,ֻ�ھ�ֹʱ����һ��
	{
		imu963ra_get_gyro();	// ��ȡ IMU963RA ����������

		angx_offset += imu963ra_gyro_transition(imu963ra_gyro_x);
		angy_offset += imu963ra_gyro_transition(imu963ra_gyro_y);
		angz_offset += imu963ra_gyro_transition(imu963ra_gyro_z);
		system_delay_ms(1);
	}
	IMUdata.dataRaw.angle.x = angx_offset / RAWTIMES;
	IMUdata.dataRaw.angle.y = angy_offset / RAWTIMES;
	IMUdata.dataRaw.angle.z = angz_offset / RAWTIMES;

	if (IMUdata.dataRaw.angle.x > 10 || IMUdata.dataRaw.angle.y > 10 || IMUdata.dataRaw.angle.z > 10)
		error = true;

	return error;
}

/**
 * @brief  ���㳵����̬��ֵ�����᷽��Ʈ�ƣ�  ����Ӧ���������ٶ�У׼�����
 *
 */
void IMU_ang_ori(void)
{
	float x = IMUdata.dataRaw.yaw;	  // �洢��

	IMUdata.dataRaw.yaw = x;	// ���ڳ�ֵ������������ȷ�������ɶ�Ϊ1���޷��������ʼ�ĺ����(��ת��)��Ҫ��ƽ�������ѭ��ȷ��

	// �������Ƕ�Ϊ��0,IMUdata.G,0�����ɴ˺ͳ�ʼaccֵ���Ͻ����ʼ�Ƕȣ���������ʹ������ƽ�⣬���ڿ���Ϊ�������flashд�����ݣ������Ż����ݣ�����imuƽ��Ƕ�
	x = (IMUdata.dataRaw.accel.x > 0 ? 1 : -1) * IMUdata.dataRaw.accel.y
		/ sqrtf(IMUdata.dataRaw.accel.y * IMUdata.dataRaw.accel.y + IMUdata.dataRaw.accel.x * IMUdata.dataRaw.accel.x);
	IMUdata.dataRaw.pitch = 180 / PI * acosf(x);

	// ��ʼ������
	x					  = (IMUdata.dataRaw.accel.z > 0 ? -1 : 1) * IMUdata.dataRaw.accel.y
		/ sqrtf(IMUdata.dataRaw.accel.y * IMUdata.dataRaw.accel.y + IMUdata.dataRaw.accel.z * IMUdata.dataRaw.accel.z);
	IMUdata.dataRaw.roll = 180 / PI * acosf(x);

	// ��ʼ���ڽ�//����������λ��ԭ�򣬳�ʼ�������෴
	if (IMUdata.dataRaw.pitch > 90)
		IMUdata.dataRaw.pitch -= 180;
	else if (IMUdata.dataRaw.pitch < -90)
		IMUdata.dataRaw.pitch += 180;

	if (IMUdata.dataRaw.roll > 90)
		IMUdata.dataRaw.roll -= 180;
	else if (IMUdata.dataRaw.roll < -90)

		IMUdata.dataRaw.roll += 180;
	// ��ֹ��0cos�ж�+-180�������Է�ת�����������0����
}

/**
 * @brief ��������̬��ֵ��ֵ������Ƕ�  ����Ӧ��У׼��ֹʱ���Ϻ���ͬʱ����
 *
 */
void IMU_ang_get_oridat(void)
{
	IMUdata.dataOri.pitch = IMUdata.dataRaw.pitch;
	IMUdata.dataOri.roll  = IMUdata.dataRaw.roll;
	IMUdata.dataOri.yaw	  = IMUdata.dataRaw.yaw;
}

/**
 * @brief  �����ų���ֵ�����᷽��Ʈ�ƣ�
 *
 */
void IMUMAG_Offset(void)
{
	float rawx_offset = 0, rawy_offset = 0, rawz_offset = 0;
	for (short i = RAWTIMES; i > 0; i--)	// ����ƫ����,ֻ�ھ�ֹʱ����һ��
	{
		imu963ra_get_mag();	   // ��ȡ IMU963RA ����������

		rawx_offset += imu963ra_mag_transition(imu963ra_mag_x);
		rawy_offset += imu963ra_mag_transition(imu963ra_mag_y);
		rawz_offset += imu963ra_mag_transition(imu963ra_mag_z);
	}

	IMUdata.dataRaw.mag.x = imu963ra_mag_transition(rawx_offset / RAWTIMES);
	IMUdata.dataRaw.mag.y = imu963ra_mag_transition(rawy_offset / RAWTIMES);
	IMUdata.dataRaw.mag.z = imu963ra_mag_transition(rawz_offset / RAWTIMES);
}

/**
 * @brief ��ȡ�����ǵ�ֵ
 *
 */
void IMU_getdata(void)
{
	imu963ra_get_acc();		// ��ȡ IMU963RA ���ٶȼ�����
	imu963ra_get_gyro();	// ��ȡ IMU963RA ����������
	imu963ra_get_mag();		// ��ȡ IMU963RA ����������

	// ����ת��
	IMUdata.dataOri.accel.x = imu963ra_acc_transition(imu963ra_acc_x);
	IMUdata.dataOri.accel.y = imu963ra_acc_transition(imu963ra_acc_y);
	IMUdata.dataOri.accel.z = imu963ra_acc_transition(imu963ra_acc_z);

	IMUdata.dataOri.angle.x = imu963ra_gyro_transition(imu963ra_gyro_x) - IMUdata.dataRaw.angle.x;
	IMUdata.dataOri.angle.y = imu963ra_gyro_transition(imu963ra_gyro_y) - IMUdata.dataRaw.angle.y;
	IMUdata.dataOri.angle.z = imu963ra_gyro_transition(imu963ra_gyro_z) - IMUdata.dataRaw.angle.z;

	IMUdata.dataOri.mag.x	= imu963ra_mag_transition(imu963ra_mag_x);
	IMUdata.dataOri.mag.y	= imu963ra_mag_transition(imu963ra_mag_y);
	IMUdata.dataOri.mag.z	= imu963ra_mag_transition(imu963ra_mag_z);
}

/**
 * @brief  �Խ��ٶȽ��л��֣��ⲿ�ַ����ж���
 *
 * @return true
 * @return false
 */
bool IMU_ang_integ()
{
	IMU_correct();
	if (IMUdata.calibration_flag) {
		IMU_getdata();

		IMUdata.dataOri.pitch += IMUdata.dataOri.angle.z * irq_interval / 1000;
		IMUdata.dataOri.roll  += IMUdata.dataOri.angle.x * irq_interval / 1000;
		IMUdata.dataOri.yaw	  += IMUdata.dataOri.angle.y * irq_interval / 1000;
	}

	return IMUdata.calibration_flag;	// ����0��ʾδ���У׼��������У׼
}

/**
 * @brief  �����Ƕ�̬У׼����������������whileѭ���У������ۻ���ֻ��G��Сʱ���Ե��ã�
 *
 */
void IMU_correct()
{
	float current_G;
	float x;
	IMU_getdata();
	current_G = sqrtf(IMUdata.dataOri.accel.x * IMUdata.dataOri.accel.x + IMUdata.dataOri.accel.y * IMUdata.dataOri.accel.y
					  + IMUdata.dataOri.accel.z * IMUdata.dataOri.accel.z);
	if (fabsf(current_G - IMUdata.G) < 0.02 * fabsf(IMUdata.G))	   // ���������ˢ�µ��Ͽ��ɶȣ���Ҫ������Χ
	{
		IMUdata.calibration_flag = 0;

		x						 = (IMUdata.dataOri.accel.x > 0 ? 1 : -1) * IMUdata.dataOri.accel.y
			/ sqrtf(IMUdata.dataOri.accel.y * IMUdata.dataOri.accel.y + IMUdata.dataOri.accel.x * IMUdata.dataOri.accel.x);
		IMUdata.dataOri.pitch = 180 / PI * acosf(x);
		x					  = (IMUdata.dataOri.accel.z > 0 ? -1 : 1) * IMUdata.dataOri.accel.y
			/ sqrtf(IMUdata.dataOri.accel.y * IMUdata.dataOri.accel.y + IMUdata.dataOri.accel.z * IMUdata.dataOri.accel.z);
		IMUdata.dataOri.roll = 180 / PI * acosf(x);
		if (IMUdata.dataOri.pitch > 90)
			IMUdata.dataOri.pitch -= 180;
		else if (IMUdata.dataOri.pitch < -90)
			IMUdata.dataOri.pitch += 180;
		if (IMUdata.dataOri.roll > 90)
			IMUdata.dataOri.roll -= 180;
		else if (IMUdata.dataOri.roll < -90)
			IMUdata.dataOri.roll += 180;
		IMUdata.calibration_flag = 1;
	}
	//  oled_show_int(10, 0, (int)(current_G*1000), 5);
}

/**
 * @brief У׼�������ܺ�������ֹ״̬���ã������̣߳����ٶȽ��ٶ����ã���ʱ�ṹ���д洢У׼����ֹ��ʱ��ֵ����
 *
 * @return true
 * @return false
 */
bool IMU_ang_calibration(void)
{
	IMUdata.calibration_flag = 0;
	IMU_acc_Offset();		 // �������ٶ�������Ӱ���ֵ�����᷽��Ʈ�ƣ�
	IMUANG_Offset();		 // �������ٶȳ�ֵ�����᷽��Ʈ�ƣ�
	IMU_ang_ori();			 // ���㳵����̬��ֵ�����᷽��Ʈ�ƣ�//����Ӧ���������ٶ�У׼�����
	IMU_ang_get_oridat();	 // ��������̬��ֵ��ֵ������Ƕ�//����Ӧ��У׼��ֹʱ���Ϻ���ͬʱ����
	IMUdata.calibration_flag = 1;

	return IMUdata.calibration_flag;
}
