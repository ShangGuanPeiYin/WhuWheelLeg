#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

float	 angletemp = 0.f;
Vector2f point_temp;
int		 core0_main(void)
{
	clock_init();	 // 获取时钟频率<务必保留>
	debug_init();	 // 初始化默认调试串口

	system_delay_ms(500);
	// 此处编写用户代码 例如外设初始化代码等
	oled_init();	// 屏幕初始化

	// mt9v03x_init();	   // 摄像头初始化

	KeyInit();		// 按键初始化
	ServoInit();	// 舵机控制初始化
	BldcInit();		// 无刷电机初始化

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0通道，中断初始化周期为1ms 中断初始化在前面

	// 此处编写用户代码 例如外设初始化代码等
	cpu_wait_event_ready();	   // 等待所有核心初始化完毕
	system_delay_ms(500);
	while (TRUE) {
		system_delay_ms(5);	   // 5ms执行一次，即200Hz 需要<=舵机Func频率

		// BldcSetCurrent(float leftCur, float rightCur);		// PWM +-4k
		// BldcSetSpeed(float leftSpeed, float rightSpeed);	// rpm

		/*

		上位机控制电机：
		先用上位机控制电机，电机反馈速度的格式是 左，右
		检查接线左右有没有反，反了就换一下

		代码控制电机：
		先开环控制电机，给一个小的PWM，再慢慢提速
		OLED或者上位机输出速度值
		依照这个输出的速度值，给速度，防止乱给速度过大。
		在bldc.c中调整PID，实现闭环速度控制。
		尝试用上位机输出速度波形，搓好PID

		无刷电机测试函数，直接调用即可

		测试代码自己写吧

		*/

		// // 五杆控制测试 等一会再测试这个
		// OLedDebug();
		// AngleCalculate(&legLeft, legLeft.PosSet);
		// AngleCalculate(&legRight, legRight.PosSet);
	}
}

#pragma section all restore
