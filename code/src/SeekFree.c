#include "zf_common_headfile.h"
uint8 image_copy[ROW][COL];
/**
 * @brief ��ʾͼ��
 *������seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], COL,
 *ROW);��������ͷ��??����λ����ʾ
 */
void  ShowImage(void)
{
	// ��image_copy??������Ϊ1����??255������Ϊ0����??0
	memcpy(image_copy[0], videoData[0], sizeof(videoData));
	// image_copy??����??1����??255������Ϊ0����??0
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (image_copy[i][j] == 1) {
				image_copy[i][j] = 255;
			}
		}
	}
	seekfree_assistant_camera_send();
}

/**
 * @brief ��ʾ���ҵ������
 *������seekfree_assistant_oscilloscope_data.channel_num;ʾ����ͨ��??
 */
void ShowTorque(void)
{
	seekfree_assistant_oscilloscope_data.data[0] = robot.left_Torque;
	seekfree_assistant_oscilloscope_data.data[1] = robot.right_Torque;
	seekfree_assistant_oscilloscope_send(&seekfree_assistant_oscilloscope_data);
}

/**
 * @brief ��ȡPID����
 * pid[0] = kp
 * pid[1] = ki
 * pid[2] = kd
 * 3~7Ϊ����λ
 * @return float* pid��������
 */
float* ReceivePID(void)
{
	static float pid[8];
	seekfree_assistant_data_analysis();
	for (int i = 0; i < SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT; i++) {
		if (seekfree_assistant_parameter_update_flag[i]) {
			// ������±�־??
			seekfree_assistant_parameter_update_flag[i] = 0;
			switch (i) {
				case 0:
					pid[0] = seekfree_assistant_parameter[i];
					break;
				case 1:
					pid[1] = seekfree_assistant_parameter[i];
					break;
				case 2:
					pid[2] = seekfree_assistant_parameter[i];
					break;
				case 3:
					pid[3] = seekfree_assistant_parameter[i];
					break;
				case 4:
					pid[4] = seekfree_assistant_parameter[i];
					break;
				case 5:
					pid[5] = seekfree_assistant_parameter[i];
					break;
				case 6:
					pid[6] = seekfree_assistant_parameter[i];
					break;
				case 7:
					pid[7] = seekfree_assistant_parameter[i];
					break;
				default:
					break;
			}
		}
	}
	return pid;
}

/**
 * @brief ����PID����
 * @param pid PID�ṹ��ָ??
 */
void AdjustPID(PIDType* pid)
{
	float* pid_value = ReceivePID();
	pid->kp			 = pid_value[0];
	pid->ki			 = pid_value[1];
	pid->kd			 = pid_value[2];
}
float AdjustTarget()
{
	float* value = ReceivePID();
	return value[3];
}
