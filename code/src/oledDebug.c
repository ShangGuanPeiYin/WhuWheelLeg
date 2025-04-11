#include "zf_common_headfile.h"

extern float	DebugTemp;
extern Vector2f point_temp;

/**
 * @brief OLED屏幕调试函数，对代码进行调试
 *
 */
void OLedDebug(void)
{
#if 1	 // 舵机测试

	OLED_Key_Scan();

	if (keyflag1 == 1)	  // 左
	{
		DebugTemp -= 1.f;
	} else if (keyflag2 == 1)	 // 右
	{
		DebugTemp += 1.f;
	}
	Limit(DebugTemp, -200, 888);

	oled_show_float(50, 5, DebugTemp, 4, 2);

#endif

#if 0	 //  测试

	OLED_Key_Scan();

	if (keyflag1 == 1)	  // 上
	{
		point_temp.x -= 10.f;
	} else if (keyflag2 == 1)	 // 下
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
	// TODO ：接收上位机消息
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

#if 1	 // 跳跃测试
	static bool OnceFlag = true;
	if (OnceFlag) {	   // 执行一次
		OnceFlag			 = false;
		robot.pipeline.state = StatePreparing;
	}
	RobotJumpLine();
#endif
}
