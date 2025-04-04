#include "zf_common_headfile.h"
uint8 image_copy[ROW][COL];
/**
 * @brief 显示图像
 *需设置seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], COL,
 *ROW);设置摄像头信??给上位机显示
 */
void  ShowImage(void)
{
	// 将image_copy??的像素为1的置??255，像素为0的置??0
	memcpy(image_copy[0], videoData[0], sizeof(videoData));
	// image_copy??像素??1则置??255，像素为0则置??0
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
 * @brief 显示左右电机力矩
 *需设置seekfree_assistant_oscilloscope_data.channel_num;示波器通道??
 */
void ShowTorque(void)
{
	seekfree_assistant_oscilloscope_data.data[0] = robot.left_Torque;
	seekfree_assistant_oscilloscope_data.data[1] = robot.right_Torque;
	seekfree_assistant_oscilloscope_send(&seekfree_assistant_oscilloscope_data);
}

/**
 * @brief 获取PID参数
 * pid[0] = kp
 * pid[1] = ki
 * pid[2] = kd
 * 3~7为保留位
 * @return float* pid参数数组
 */
float* ReceivePID(void)
{
	static float pid[8];
	seekfree_assistant_data_analysis();
	for (int i = 0; i < SEEKFREE_ASSISTANT_SET_PARAMETR_COUNT; i++) {
		if (seekfree_assistant_parameter_update_flag[i]) {
			// 清除更新标志??
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
 * @brief 调整PID参数
 * @param pid PID结构体指??
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
