#include "zf_common_headfile.h"

extern float	DebugTemp;
extern Vector2f point_temp;

/**
 * @brief OLED��Ļ���Ժ������Դ�����е���
 *
 */
void OLedDebug(void)
{
#if 1	 // �������

	OLED_Key_Scan();

	if (keyflag1 == 1)	  // ��
	{
		DebugTemp -= 1.f;
	} else if (keyflag2 == 1)	 // ��
	{
		DebugTemp += 1.f;
	}
	Limit(DebugTemp, -200, 888);

	oled_show_float(50, 5, DebugTemp, 4, 2);

#endif

#if 0	 //  ����

	OLED_Key_Scan();

	if (keyflag1 == 1)	  // ��
	{
		point_temp.x -= 10.f;
	} else if (keyflag2 == 1)	 // ��
	{
		point_temp.x += 10.f;
	} else if (keyflag0 == 1)	 //
	{
		point_temp.x -= 10.f;
	} else if (keyflag3 == 1)	 //
	{
		point_temp.x += 10.f;
	}

	oled_show_float(50, 3, point_temp.x, 4, 2);
	oled_show_float(50, 4, point_temp.y, 4, 2);

#endif
};

void FunctionTest(void)
{
	// TODO ��������λ����Ϣ
	//		static u8 _temp = 0;
	// static u8 Cnt1	= 0;
	// if (++Cnt1 > 5) {
	// 	while (deQueue(&usart2_rec_list, &_temp)) //
	// 	ReadMsg(&U2data, _temp);
	// 	Cnt1 = 0;
	// }

	//		Servo[Bl].angleLeg = 90;
	//		Servo[Fl].angleLeg = 90;
	//		Servo[Br].angleLeg = 90;
	// Servo[Fr].angleLeg = 90;

#if 1	 // ��Ծ����
	static bool OnceFlag = true;
	if (OnceFlag) {	   // ִ��һ��
		OnceFlag			 = false;
		robot.pipeline.state = StatePreparing;
	}
	RobotJumpLine();
#endif
}
