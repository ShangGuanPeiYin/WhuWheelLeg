#include "beiyoucontrol.h"
int	  angle_count = 0;
int	  speed_count = 0;
float Tduty1;
float Tduty2;
int	  Tduty3;
float Roll_output1;
float Roll_output2;
float LeftSpeed_output;
float RightSpeed_output;
bool  dir = true;
bool  begin_flag;

void CH1_LOOP(void)	   // �ж���1ms������angle_count��speed_count,ʹ�����������ڷֱ�Ϊ5ms��50ms
{
	speed_count++;
	angle_count++;
	if (speed_count % 50 == 0) {
		// �ٶȻ�
		LeftSpeed_output  = 0;	  // PID_Speed1(Motor[0].valueNow.speed,0);//����PID���
		RightSpeed_output = 0;	  // PID_Speed2(Motor[1].valueNow.speed,0);//����PID���
		speed_count		  = 0;
	}
	if (angle_count % 5 == 0) {
		// �ǶȻ�
		Roll_output1 = PID_Roll(-IMUdata.dataOri.pitch, LeftSpeed_output, -0);
		Roll_output2 = PID_Roll(-IMUdata.dataOri.pitch, RightSpeed_output, -0);
		angle_count	 = 0;
	}
	Tduty1 = PID_Roll_Speed(-IMUdata.dataOri.angle.x, Roll_output1);	// �����
	Tduty2 = PID_Roll_Speed(-IMUdata.dataOri.angle.x, Roll_output2);	// �����
	//    Tduty1 = (int)Tduty1;//ȡ��
	//    Tduty2 = (int)Tduty2;//ȡ��
	//    Tduty3 = (Tduty1+Tduty2)/2;

	// BldcSetCurrent(Tduty1,Tduty2);
	BldcSetCurrent(Tduty1 / 2.5, Tduty2 / 2.5);
}
