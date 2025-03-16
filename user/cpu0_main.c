#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// 将本语句与#pragma section all restore语句之间的全局变量都放在CPU0的RAM中

float	 angletemp = 0.f;
Vector2f point_temp;
uint8 image_copy[ROW][COL];
int		 core0_main(void)
{
	clock_init();	 // 获取时钟频率<务必保留>
	debug_init();	 // 初始化默认调试串口

	system_delay_ms(500);
	// 此处编写用户代码 例如外设初始化代码等
	oled_init();	// 屏幕初始化

	mt9v03x_init();	   // 摄像头初始化
	mt9v03x_set_exposure_time(200);

	KeyInit();	  // 按键初始化

	ServoInit();	// 舵机控制初始化
	BldcInit();		// 无刷电机初始化
	IMU_init();		// IMU初始化

	// U2
	//uart_init(UART_2, 115200, UART2_TX_P10_5, UART2_RX_P10_6);	  // 串口2初始化

	robotInit(&robot);
	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0通道，中断初始化周期为1ms 中断初始化在前面

	// 此处编写用户代码 例如外设初始化代码等
	wireless_uart_init();
	cpu_wait_event_ready();	   // 等待所有核心初始化完毕
	system_delay_ms(500);

	seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);
	seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], COL, ROW);

	while (TRUE) {
		// vofa_send();
		// vofa_receive();

		// wireless_uart_read_buffer(DataBuff,10);
		// uart_query_byte(UART_2,DataBuff);
		// oled_show_int(20,3,DataBuff[1],3);
		// uint8 x=0;
		// uart_query_byte(UART_2,&x);
		// wireless_uart_read_buffer()
		//		x++;
		//		Bldc_AskSpeed();
		//		oled_show_float(60,1,Motor[0].valueNow.speed,4,2);
		//         oled_show_float(60,3,Motor[1].valueNow.speed,4,2);
		// oled_show_float(60,3,Motor[1].valueNow.speed,4,2);

		// oled_show_float(60, 3, IMUdata.dataOri.angle.x, 2, 2);
		// oled_show_float(60, 5, robot.left_Torque, 2, 2);
		// oled_show_float(60, 7, Motor[0].valueNow.speed, 2, 2);

		//		oled_show_float(60,5,IMUdata.dataOri.pitch,2,2);

		//		oled_show_uint(60,1,x,3);
		//		oled_show_int(60,3,(int)Motor[0].pulse.pulseRead*10000,3);
		// Bldc_SetDuty(2000,2000);
#if 0
//	    oled_show_float(60, 3, IMUdata.dataOri.angle.x, 2, 2);
        oled_show_float(60, 1, IMUdata.dataOri.pitch, 2, 2);
        oled_show_float(60, 3, IMUdata.dataOri.roll, 2, 2);
        oled_show_float(60, 5, IMUdata.dataOri.yaw, 2, 2);


#endif

#if 1
		if (mt9v03x_finish_flag)	// 摄像头采集完成标志位
		{
			mt9v03x_finish_flag = 0;
			Binary_Img();
//上位机接收图像
#if 0

			//将image_copy中的像素为1的置为255，像素为0的置为0
			memcpy(image_copy[0], videoData[0], Video_IMAGE_SIZE);
			//image_copy中像素为1则置为255，像素为0则置为0
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if (image_copy[i][j] == 1) {
						image_copy[i][j] = 255;	
					}	
				}		
			}
			seekfree_assistant_camera_send();
#endif
			MainCount++;
			if (MainCount > 8) {
				Image_To_Warp();
				YawCtrlOut = 3.f * PIDOperation(&robot.yawPID, RealWarp, 0.f);	  // 平衡环Pwm
				DrawMidLine_Simple();
				OLED_Print_Img128X64(videoData);

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

	static u8 BalanceCnt   = 0;	   // 1k -> 100Hz  用bldc控制平衡，所以频率和bldc同步 最好在bldc上面
	if (++BalanceCnt >= 5) {
		Balance();
		BalanceCnt = 0;
	}

	static u8 BldcCnt = 0;	  // 1k -> 100Hz
	if (++BldcCnt >= 5) {
		BldcFunc();
		BldcCnt = 0;
	}

	static int ServoCnt = 0;
	if (++ServoCnt >= 10) {	   // 1k -> 200Hz
		ServoFunc();
		ServoCnt = 0;
	}

	static u8 IMUCnt = 0;	 // 1k -> 200Hz 与舵机错开
	if (++IMUCnt >= irq_interval) {
		Get_Attitude();
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
	// vofa_receive();
	wireless_uart_callback();
	interrupt_global_enable(0);	   // 开启中断嵌套

	// TODO : 之后用
	//  static uint8_t receive_data_temp2 = 0;
	//  uart_query_byte(UART_2, &receive_data_temp2);
	//  enQueue(&usart2_rec_list, receive_data_temp2);	  // 入队
}

#pragma section all restore
