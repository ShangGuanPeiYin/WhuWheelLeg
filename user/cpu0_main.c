#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

float	 DebugTemp = 0.f;
Vector2f point_temp;
int		 core0_main(void)
{
	clock_init();	 // 获取时钟频率<务必保留>
	debug_init();	 // 初始化默认调试串口

	system_delay_ms(1000);
	// U2
	uart_init(UART_2, 115200, UART2_TX_P10_5, UART2_RX_P10_6);	  // 串口2初始化

	oled_init();	// 屏幕初始化

	mt9v03x_init();	   // 摄像头初始化
	mt9v03x_set_exposure_time(120);

	KeyInit();	  // 按键初始化

	ServoInit();	// 舵机控制初始化
	BldcInit();		// 无刷电机初始化
	IMU_init();		// IMU初始化

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0通道，中断初始化周期为1ms 中断初始化在前面

	// 此处编写用户代码 例如外设初始化代码等
	wireless_uart_init();
	cpu_wait_event_ready();	   // 等待所有核心初始化完毕
	system_delay_ms(500);

	while (TRUE) {
		// OLedDebug();

		oled_show_float(70, 6, robot.left->PosSet.x, 2, 2);
		oled_show_float(70, 7, robot.left->PosSet.y, 2, 2);

#if 0	 // 跳跃测试
		static bool OnceFlag = true;
		if (OnceFlag) {	   // 执行一次
			OnceFlag			 = false;
			robot.pipeline.state = StatePreparing;
		}
		RobotJumpLine();
#endif

		// printf("%f, %f\r\n", IMUdata.dataOri.pitch, IMUdata.dataOri.roll);
		// system_delay_ms(10);
#if 1

		oled_show_float(60, 0, robot.speedNow, 3, 3);

		oled_show_float(60, 2, robot.posture->dataSet.pitch, 3, 3);
		oled_show_float(60, 3, robot.posture->dataSet.angle.x, 3, 3);
		oled_show_float(60, 4, robot.right_Torque, 3, 3);

		oled_show_float(10, 5, IMUdata.dataOri.pitch, 3, 3);

		// oled_show_float(60, 1, IMUdata.dataOri.pitch, 2, 2);
		// oled_show_float(60, 3, IMUdata.dataOri.roll, 2, 2);

		// oled_show_float(60, 1, IMUdata.dataOri.angle.x, 3, 3);
		// oled_show_float(60, 3, IMUdata.dataOri.angle.y, 3, 3);
		// oled_show_float(60, 5, IMUdata.dataOri.angle.z, 3, 3);

		// oled_show_float(60, 5, robot.posture->dataSet.pitch, 2, 2);

#endif
#if 0
		if (mt9v03x_finish_flag)	// 摄像头采集完成标志位
		{
			mt9v03x_finish_flag = 0;
			Binary_Img();
			MainCount++;
			OLED_Print_Img128X64(videoData);

			if (MainCount > 8) {
				Image_To_Warp();
				robot.yawPID.kp = 120 + 260 * fabs((float) RealWarp);
				robot.yawPID.kd = 60 + 140 * fabs((float) RealWarp);

				YawCtrlOut		= 3.f * PIDOperation(&robot.yawPID, RealWarp, 0.f);	   // 平衡环Pwm
				DrawMidLine_Simple();
				OLED_Print_Img128X64(videoData);
				oled_show_float(60, 7, (float) RealWarp, 3, 2);
				vofa_send();

				/*
				Binary_Img();
				Find_EndRow();
				CorrectEndRow();
				RealEndRow = EndRow;		// 记录真实截止行
				FindBorder();
				Find_MidLine();
				DrawMidLine_Simple();
				OLED_Print_Img128X64(videoData);
				if(StopFlag)
				BldcSetSpeed(0,0);
				YawCtrlOut = -3.f * PIDOperation(&robot.yawPID, (COL / 2.f) / COL, (float) MidLine[ControlRow]);	// 平衡环Pwm
				*/
			}
		}
#endif
		;
		;
	}
};
u8 JumpLineState = 0;
/*------------------------------------------------- 定时器1 -------------------------------------------------------*/
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
	interrupt_global_enable(0);	   // 开启中断嵌套

	//	 计数器计时
	robot.param.leftTime  += 1;		 // 1ms
	robot.param.rightTime += 1;		 // 1ms
	robot.param.runTime	  += 1.f;	 // 1ms

	static u8 BalanceCnt   = 0;	   // 1kHz  用bldc控制平衡，所以频率和bldc同步 最好在bldc上面
	{
		Get_Attitude();
		// if (JumpLineState <= 1 || JumpLineState >= 3)
		Balance();

		BalanceCnt = 0;
	}

	static u8 BldcCnt = 0;	  // 1k -> 500Hz  TODO尝试改到1kHz
	if (++BldcCnt >= 1) {
		BldcFunc();
		BldcCnt = 0;
	}

	static int ServoCnt = 0;
	if (++ServoCnt >= 5) {	  // 1k -> 200Hz
		ServoFunc();
		ServoCnt = 0;
	}

	pit_clear_flag(CCU60_CH0);
}

/*------------------------------------------------- 串口3-BLDC -------------------------------------------------------*/
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)	 // 可以提高优先级 80
{
	interrupt_global_enable(0);	   // 开启中断嵌套

	Bldc_Driver_callback();	   // 无刷电机中断接收函数
}

/*------------------------------------------------- 串口2-无线 -------------------------------------------------------*/
IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
	// vofa_receive();
	wireless_uart_callback();
	interrupt_global_enable(0);	   // 开启中断嵌套

	// TODO : 之后用
	//  static uint8_t receive_data_temp2 = 0;
	//  uart_query_byte(UART_2, &receive_data_temp2);
	//  enQueue(&usart2_rec_list, receive_data_temp2);	  // 入队
}

#pragma section all restore
