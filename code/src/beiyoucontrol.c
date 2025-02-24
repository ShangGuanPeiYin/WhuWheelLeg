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

void CH1_LOOP(void)	   // 中断是1ms，设置angle_count和speed_count,使两个计算周期分别为5ms和50ms
{
	speed_count++;
	angle_count++;
	if (speed_count % 50 == 0) {
		// 速度环
		LeftSpeed_output  = 0;	  // PID_Speed1(Motor[0].valueNow.speed,0);//左轮PID输出
		RightSpeed_output = 0;	  // PID_Speed2(Motor[1].valueNow.speed,0);//右轮PID输出
		speed_count		  = 0;
	}
	if (angle_count % 5 == 0) {
		// 角度环
		Roll_output1 = PID_Roll(-IMUdata.dataOri.pitch, LeftSpeed_output, -0);
		Roll_output2 = PID_Roll(-IMUdata.dataOri.pitch, RightSpeed_output, -0);
		angle_count	 = 0;
	}
	Tduty1 = PID_Roll_Speed(-IMUdata.dataOri.angle.x, Roll_output1);	// 左输出
	Tduty2 = PID_Roll_Speed(-IMUdata.dataOri.angle.x, Roll_output2);	// 右输出
	//    Tduty1 = (int)Tduty1;//取整
	//    Tduty2 = (int)Tduty2;//取整
	//    Tduty3 = (Tduty1+Tduty2)/2;

	// BldcSetCurrent(Tduty1,Tduty2);
	BldcSetCurrent(Tduty1 / 2.5, Tduty2 / 2.5);
}
