#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

float angletemp = 0.f;
int	  core0_main(void)
{
	clock_init();	 // 获取时钟频率<务必保留>
	debug_init();	 // 初始化默认调试串口

	system_delay_ms(500);
	// 此处编写用户代码 例如外设初始化代码等
	oled_init();	// 屏幕初始化
	// mt9v03x_init();	   // 摄像头初始化

	gpio_init(KEY_UP, GPI, 0, GPI_PULL_UP);	   // 按键初始化
	gpio_init(KEY_DOWN, GPI, 0, GPI_PULL_UP);
	gpio_init(KEY_LEFT, GPI, 0, GPI_PULL_UP);
	gpio_init(KEY_RIGHT, GPI, 0, GPI_PULL_UP);

	ServoInit();				  // 舵机控制初始化
	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0通道，中断初始化周期为1ms 中断初始化在前面

	// 此处编写用户代码 例如外设初始化代码等
	cpu_wait_event_ready();	   // 等待所有核心初始化完毕
	system_delay_ms(500);
	while (TRUE) {
		Servo[Fl].angleSet = angletemp;
		OLedDebug();
	}
}

#pragma section all restore
