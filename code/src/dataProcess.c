#include "zf_common_headfile.h"

// ��ͷ id ���� ��У�� ��β
// const static char head_char[2] = {0xff, 0xfe};	  // ��ͷ
// const static char end_char[2]  = {'\n', '\r'};	  // ��β
char head_char[2] = {0xff, 0xfe};	 // ��ͷ
char end_char[2]  = {'\n', '\r'};	 // ��β

DataProcessType U2data;
//CtrlMsgType		CtrlMsg;

void DataProcessInit(void) { memset(&U2data, 0, sizeof(DataProcessType)); }

/**
 * @brief ����Ϣ
 *
 * @param data
 * @param temp
 */
void ReadMsg(DataProcessType* data, uint8 temp)
{
	if (getHeadMsg(data, temp)) {
		switch (data->head_id)	  // ����head_id�жϳ���ͬ�Ĳ�������
		{
			case 1:
				// if (dataDecode<ControlMsgStruct>(temp, &ControlMsg)) {
				// 	Beep.addBeepNum(1);
				// 	Master.RobotMsg.ReceiveMessage++;
				// 	Master.ReceiveControlMsgFlag = true;

				// 	// ��λ
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
 * @brief ��ͷ��ϢУ�飨2λ����ͷ��1λ��ͷID�����ҵ���ͷ��get_head��1����ֵhead_id����get_head_id��1������get_head_id
 *
 * @param data
 * @param _ch
 * @return true
 * @return false
 */
bool getHeadMsg(DataProcessType* data, u8 _ch)
{
	if (!data->get_head) {
		data->rec_head[0] = data->rec_head[1];	  // �������Σ��õ� 2�ֽڰ�ͷ
		data->rec_head[1] = _ch;

		if (data->rec_head[0] == head_char[0] && data->rec_head[1] == head_char[1]) {
			data->get_head = true;
			data->rec_len  = 0;
		}
	} else if (!data->get_head_id) {	// �������Σ��õ�id
		data->head_id	  = _ch;
		data->get_head_id = true;

	} else	  // �����ĴΣ�����id
		return data->get_head_id;

	return false;
};

/**
 * @brief ��У��
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
 * @brief ���
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
