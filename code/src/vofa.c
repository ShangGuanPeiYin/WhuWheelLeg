#include "Vofa.h"

#include "robot.h"

#include <stdio.h>
#include <string.h>
uint8_t	  RxBuffer[1]	 = {0};	   // ���ڽ��ջ���
uint8_t	  DataBuff[20]	 = {0};	   // ָ������
uint8_t	  data_Start_Num = 0;	   // ��¼����λ��ʼ�ĵط�
uint8_t	  data_End_Num	 = 0;	   // ��¼����λ�����ĵط�
uint8_t	  data_Num		 = 0;	   // ��¼����λ��
uint32_t  read_length	 = 0;
float	  f2			 = 0;
float	  data_return	 = 0;	 // �����õ�������
uint8_t	  data_flag		 = 0;
uint8_t	  FH_flag		 = 0;	 // ��ʼ��֡ͷ��־
/************************************************
*�ļ�˵����          ����vofa+��λ�����������ͼ����պ�����JustFloat��������ͼƬ��
*ʱ    �䣺            2021.11.26
*��    ע��            δ�����������ԣ����ܻ���bug��ע������ã��������޸�
								��λ�����ص�ַhttps://www.vofa.plus/
***************************************************/
JustFloat UploadDataJF;
/*************************************************
 *   ��������: VOFA+���ͺ�����������ʾ����
 *   ʹ�÷���:   VOFAplusUpload_JustFloat(&UploadDataJF);
 *   ��ע    : UploadDataJF��ȫ�ֱ�����ֱ�Ӹ�ֵ���ͼ��ɣ�
 *                 �磺UploadDataJF.CH_Data[0] = 1;
 **************************************************/
void	  VOFAplusUpload_JustFloat(JustFloat* sendbuffer)
{
	uint8 Tail[4] = {0x00, 0x00, 0x80, 0x7f};
	VofaSendStr((uint8*) sendbuffer->CH_Data, sizeof(float) * JFCH_COUNT);
	VofaSendStr(Tail, sizeof(Tail));
}
/*************************************************
 *   ��������: VOFA+���ͺ�������������Ҫ���͵�����
 *   ʹ�÷���: Vofasend;
 **************************************************/
void vofa_send(void)	// vofa���η�������
{
	UploadDataJF.CH_Data[0] = tiaocan[0];
	UploadDataJF.CH_Data[1] = tiaocan[1];
	UploadDataJF.CH_Data[2] = tiaocan[2];
	UploadDataJF.CH_Data[3] = tiaocan[3];
	UploadDataJF.CH_Data[4] = tiaocan[4];
	UploadDataJF.CH_Data[5] = tiaocan[5];
	UploadDataJF.CH_Data[6] = tiaocan[6];
	UploadDataJF.CH_Data[7] = tiaocan[7];
	UploadDataJF.CH_Data[8] = tiaocan[8];
	//    UploadDataJF.CH_Data[9] = encoder2;
	VOFAplusUpload_JustFloat(&UploadDataJF);
}
static int head_position = 20;
void	   vofa_receive(void)
{
	read_length = wireless_uart_read_buffer(DataBuff, sizeof(DataBuff));
	// oled_clear();
	// oled_show_string(30,7,sizeof(DataBuff));

	for (int i = 0; i < read_length; i++) {
		//            if (DataBuff[i] == 0x21 && FH_flag == 0) {//!
		//                FH_flag = 1; // ֡ͷ
		//            } else if (FH_flag == 1 && DataBuff[i] == 0x2B) {//+
		//                FH_flag = 2;
		//            } else if (FH_flag == 2) {
		//
		//                FH_flag = 3;
		//                data_flag=i+1;
		//                USART_PID_Adjust(1); // ���ݽ����Ͳ�����ֵ����
		//            } else if (FH_flag == 3 && DataBuff[i] == 0x23) {//ASCII #
		//                FH_flag = 0;
		//                i = 0; // ��������
		//                data_flag=0;
		//            }
		if (DataBuff[i] == (33) && DataBuff[i + 1] == (43)) {
			//            oled_show_uint(30,1,DataBuff[0],3);
			//            oled_show_uint(30,2,DataBuff[1],3);
			//            oled_show_uint(30,3,DataBuff[2],3);
			//            oled_show_uint(30,4,DataBuff[3],3);
			//            oled_show_uint(30,5,DataBuff[4],3);
			//            oled_show_uint(30,6,DataBuff[5],3);
			head_position = i;
			USART_PID_Adjust(1);
			break;
		}
	}
	memset(DataBuff, 0, sizeof(DataBuff));	  // ��ջ�������
}

float Get_Data(void)
{
	float	Data		  = 0.0;
	uint8_t dot_Flag	  = 0;	  // С�����־λ��������С������С����ǰ 0ΪС����ǰ��1ΪС�����
	uint8_t dot_after_num = 1;	  // С�����ĵڼ�λ
	int8_t	minus_Flag	  = 1;	  // ���ű�־λ -1Ϊ�Ǹ��� 1Ϊ����
	for (; data_flag < read_length; data_flag++) {
		if (DataBuff[data_flag] == 0x2D)	// �����һλΪ����
		{
			minus_Flag = -1;
			continue;	 // ��������ѭ��
		}
		if (dot_Flag == 0) {
			if (DataBuff[data_flag] == 0x2E)	// ���ʶ��С���㣬��dot_Flag��1
			{
				dot_Flag = 1;
			} else	  // ��û����С����ǰ������
			{
				Data = Data * 10 + DataBuff[data_flag] - 48;
			}
		} else	  // ����С����������
		{
			Data = Data + Pow_invert(DataBuff[data_flag] - 48, dot_after_num);
			dot_after_num++;
		}
	}
	return Data * minus_Flag;	 // �����������ݷ��س��� ������ϸ��ű�־λ
}

/****************************************************
 * С��λ����
 * �����ڲ�����
 ****************************************************/
float Pow_invert(uint8_t X, uint8_t n)	  // x����n��10
{
	float result = X;
	while (n--) { result /= 10; }
	return result;
}

void USART_PID_Adjust(uint8_t Motor_n)
{
#if 0
    float data_Get= Get_Data();
    //oled_show_float(20,6,data_Get,4,2);
        {
            if(DataBuff[1]=='+' && DataBuff[2]=='0') // ���ٶȻ�P//ǰ��λ����ʽ���ٶȻ�pi
                pid_init.pid_roll_speed.kp = data_Get/100;
            else if(DataBuff[1]=='+' && DataBuff[2]=='1') // ���ٶȻ�D
                pid_init.pid_roll_speed.ki = data_Get/1000;
            else if(DataBuff[1]=='+' && DataBuff[2]=='2') // ���ٶȻ�I
                pid_init.pid_roll_speed.kd = data_Get/1000;
            else if(DataBuff[1]=='+' && DataBuff[2]=='3') // �ǶȻ�P//����λλ��ʽ�ǶȻ�pid
                pid_init.pid_roll.kp = data_Get/100;
            else if(DataBuff[1]=='+' && DataBuff[2]=='4') // �ǶȻ�I
                pid_init.pid_roll.ki = data_Get/1000;
            else if(DataBuff[1]=='+' && DataBuff[2]=='5') // �ǶȻ�D
                pid_init.pid_roll.kd = data_Get/1000;
            else if(DataBuff[1]=='+' && DataBuff[2]=='6') // �ٶȻ�P
                {pid_init.pid_speed1.kp = data_Get/1000;pid_init.pid_speed2.kp = data_Get/1000;}
            else if(DataBuff[1]=='+' && DataBuff[2]=='7') // �ٶȻ�I
                {pid_init.pid_speed1.ki = data_Get/1000;pid_init.pid_speed2.ki = data_Get/1000;}
            else if(DataBuff[1]=='+' && DataBuff[2]=='8') // �ٶȻ�D
                {pid_init.pid_speed1.kd = data_Get/1000;pid_init.pid_speed2.kd = data_Get/1000;}
        }
#endif
	if (head_position != sizeof(DataBuff)) {
		int	  select_channel = (DataBuff[head_position + 2] - 48);
		float data_Get		 = (DataBuff[head_position + 3] - 48) * 100 + (DataBuff[head_position + 4] - 48) * 10
						 + (DataBuff[head_position + 5] - 48);
		if (select_channel == 0)	// ���ٶȻ�P//ǰ��λ����ʽ���ٶȻ�pi
			tiaocan[0] = data_Get / 100;
		else if (select_channel == 1)	 // ���ٶȻ�D
			tiaocan[1] = data_Get / 100;
		else if (select_channel == 2)	 // ���ٶȻ�I
			tiaocan[2] = data_Get / 10;
		else if (select_channel == 3)	 // �ǶȻ�P//����λλ��ʽ�ǶȻ�pid
			tiaocan[3] = data_Get / 200;
		else if (select_channel == 4)	 // �ǶȻ�I
			tiaocan[4] = data_Get / 10;
		else if (select_channel == 5)	 // �ǶȻ�D
			tiaocan[5] = data_Get / 10;
		else if (select_channel == 6)	 // �ٶȻ�P
		{
			pid_init.pid_speed1.kp = data_Get / 1000;
			pid_init.pid_speed2.kp = data_Get / 1000;
		} else if (select_channel == 7)	   // �ٶȻ�I
		{
			pid_init.pid_speed1.ki = data_Get / 1000;
			pid_init.pid_speed2.ki = data_Get / 1000;
		} else if (select_channel == 8)	   // �ٶȻ�D
		{
			pid_init.pid_speed1.kd = data_Get / 1000;
			pid_init.pid_speed2.kd = data_Get / 1000;
		}
		head_position = sizeof(DataBuff);
	}

	//    if(Motor_n==2)//�н���
	//       {
	//           if(DataBuff[1]=='+' && DataBuff[2]=='1') // ���ٶȻ�P
	//               NULL = data_Get;
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='2') // ���ٶȻ�I
	//               NULL = data_Get;
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='3') // ���ٶȻ�D
	//               NULL = data_Get;
	//
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='4') // �ǶȻ�P
	//               NULL = data_Get;
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='5') // �ǶȻ�I
	//               NULL = data_Get;
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='6') // �ǶȻ�D
	//               NULL = data_Get;
	//
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='7') // �ٶȻ�P
	//               NULL = data_Get;
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='8') // �ٶȻ�I
	//               NULL = data_Get;
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='9') // �ٶȻ�D
	//               NULL = data_Get;
	//
	//
	//           else if(DataBuff[1]=='+' && DataBuff[2]=='0') //Ŀ��Ƕ�
	//               NULL = data_Get;
	//
	//       }
}
