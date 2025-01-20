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

	KeyInit();			  // 按键初始化
	DataProcessInit();	  // 通讯初始化

	ServoInit();	// 舵机控制初始化
	BldcInit();		// 无刷电机初始化
	IMU_init();		// IMU初始化

	// U2
	uart_init(UART_2, 460800, UART2_TX_P10_5, UART2_RX_P10_6);	  // 串口2初始化

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0通道，中断初始化周期为1ms 中断初始化在前面

	// 此处编写用户代码 例如外设初始化代码等
	cpu_wait_event_ready();	   // 等待所有核心初始化完毕
	while (TRUE) {
		// 尝试写个任务调度 不过无法实现任务抢占
		system_delay_ms(1);

		// TODO ：接收上位机消息
		//		static u8 _temp = 0;
		// static u8 Cnt1	= 0;
		// if (++Cnt1 > 5) {
		// 	while (deQueue(&usart2_rec_list, &_temp)) //
		// 	ReadMsg(&U2data, _temp);
		// 	Cnt1 = 0;
		// }

		// Servo[Bl].angleLeg = 90 + 45;
		// Servo[Fl].angleLeg = 90;

		// Servo[Bl].angleLeg = 90;
		// Servo[Fl].angleLeg = 90;

		Servo[Bl].angleLeg = 90;
		Servo[Fl].angleLeg = 90;
		// Servo[Br].angleLeg = 90;
		// Servo[Fr].angleLeg = 90;

#if 0
		robot.jumpLine.Pos[0]	= ForwardKinematics(PI * (5 / 4), PI * (-1 / 4));

		robot.jumpLine.Pos[0].x = 0;
		robot.jumpLine.Pos[0].y = 25;
		AngleCalculate(robot.left, robot.jumpLine.Pos[0]);	  // 更新舵机角
		AngleCalculate(robot.right, robot.jumpLine.Pos[0]);
#endif

#if 0
		static bool OnceFlag = true;
		if (OnceFlag) {	   // 执行一次
			OnceFlag			 = false;
			robot.pipeline.state = StatePreparing;
		}
		RobotJumpLine();

#endif
	}
}

/*------------------------------------------------- 定时器1 -------------------------------------------------------*/
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
	interrupt_global_enable(0);	   // 开启中断嵌套

	// 计数器计时
	robot.param.leftTime  += 1;		 // 1ms
	robot.param.rightTime += 1;		 // 1ms
	robot.param.runTime	  += 1.f;	 // 1ms

	static int ServoCnt	   = 0;
	if (++ServoCnt > 5) {	 // 1k -> 200Hz
		ServoFunc();
		ServoCnt = 0;
	}

	static u8 BldcCnt = 0;	  // 1k -> 100Hz
	if (++BldcCnt > 10) {
		BldcFunc();
		BldcCnt = 0;
	}

	static u8 IMUCnt = 1;	 // 1k -> 200Hz 与舵机错开
	if (++IMUCnt > irq_interval) {
		IMU_ang_integ();
		IMUCnt = 0;
	}

	pit_clear_flag(CCU60_CH0);
}

/*------------------------------------------------- 串口3-BLDC -------------------------------------------------------*/
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)
{
	interrupt_global_enable(0);	   // 开启中断嵌套

	Bldc_Driver_callback();	   // 无刷电机中断接收函数
}

/*------------------------------------------------- 串口2-无线 -------------------------------------------------------*/
IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
	interrupt_global_enable(0);	   // 开启中断嵌套

	// TODO : 之后用
	//  static uint8_t receive_data_temp2 = 0;
	//  uart_query_byte(UART_2, &receive_data_temp2);
	//  enQueue(&usart2_rec_list, receive_data_temp2);	  // 入队
}

#pragma section all restore
