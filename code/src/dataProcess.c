#include "zf_common_headfile.h"

// 包头 id 数据 和校验 包尾
// const static char head_char[2] = {0xff, 0xfe};	  // 包头
// const static char end_char[2]  = {'\n', '\r'};	  // 包尾
char head_char[2] = {0xff, 0xfe};	 // 包头
char end_char[2]  = {'\n', '\r'};	 // 包尾

DataProcessType U2data;
//CtrlMsgType		CtrlMsg;

void DataProcessInit(void) { memset(&U2data, 0, sizeof(DataProcessType)); }

/**
 * @brief 读信息
 *
 * @param data
 * @param temp
 */
void ReadMsg(DataProcessType* data, uint8 temp)
{
	if (getHeadMsg(data, temp)) {
		switch (data->head_id)	  // 根据head_id判断出不同的操作命令
		{
			case 1:
				// if (dataDecode<ControlMsgStruct>(temp, &ControlMsg)) {
				// 	Beep.addBeepNum(1);
				// 	Master.RobotMsg.ReceiveMessage++;
				// 	Master.ReceiveControlMsgFlag = true;

				// 	// 复位
				// 	if (ControlMsg.Reset) {
				// 		// __set_FAULTMASK(1);
				// 		// NVIC_SystemReset();
				// 	}
				// }
				break;
				// case 2:
				// 	/* code */
				// 	break;
				// case 3:
				// 	/* code */
				// 	break;
				// case 4:
				// 	/* code */
				// 	break;

			default:
				clearFlag(data);
				break;
		}
	}
}

/**
 * @brief 包头信息校验（2位数据头和1位包头ID），找到包头把get_head置1，赋值head_id并把get_head_id置1，返回get_head_id
 *
 * @param data
 * @param _ch
 * @return true
 * @return false
 */
bool getHeadMsg(DataProcessType* data, u8 _ch)
{
	if (!data->get_head) {
		data->rec_head[0] = data->rec_head[1];	  // 进入两次，得到 2字节包头
		data->rec_head[1] = _ch;

		if (data->rec_head[0] == head_char[0] && data->rec_head[1] == head_char[1]) {
			data->get_head = true;
			data->rec_len  = 0;
		}
	} else if (!data->get_head_id) {	// 进入三次，得到id
		data->head_id	  = _ch;
		data->get_head_id = true;

	} else	  // 进入四次，返回id
		return data->get_head_id;

	return false;
};

/**
 * @brief 和校验
 *
 * @param ch
 * @param n
 * @return char
 */
char checkSum(char* ch, int n)
{
	char _sum = 0;
	for (int i = 0; i < n; i++) _sum += ch[i];
	return _sum;
};

/**
 * @brief 清除
 *
 */
void clearFlag(DataProcessType* data)
{
	data->rec_head[0] = data->rec_head[1] = ' ';
	data->rec_end[0] = data->rec_end[1] = ' ';

	data->get_head_id					= false;
	data->get_head						= false;
	data->get_end						= false;

	data->rec_len						= 0;
};
