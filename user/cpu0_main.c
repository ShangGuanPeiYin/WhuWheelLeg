#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

float	 DebugTemp = 0.f;
Vector2f point_temp;
int		 core0_main(void)
{
	clock_init();	 // ��ȡʱ��Ƶ��<��ر���>
	debug_init();	 // ��ʼ��Ĭ�ϵ��Դ���

	system_delay_ms(1000);
	// U2
	uart_init(UART_2, 115200, UART2_TX_P10_5, UART2_RX_P10_6);	  // ����2��ʼ��

	oled_init();	// ��Ļ��ʼ��

	mt9v03x_init();	   // ����ͷ��ʼ��
	mt9v03x_set_exposure_time(120);

	KeyInit();	  // ������ʼ��

	ServoInit();	// ������Ƴ�ʼ��
	BldcInit();		// ��ˢ�����ʼ��
	IMU_init();		// IMU��ʼ��

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	wireless_uart_init();
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	system_delay_ms(500);

	while (TRUE) {
		// OLedDebug();

		oled_show_float(70, 6, robot.left->PosSet.x, 2, 2);
		oled_show_float(70, 7, robot.left->PosSet.y, 2, 2);

#if 0	 // ��Ծ����
		static bool OnceFlag = true;
		if (OnceFlag) {	   // ִ��һ��
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
		if (mt9v03x_finish_flag)	// ����ͷ�ɼ���ɱ�־λ
		{
			mt9v03x_finish_flag = 0;
			Binary_Img();
			MainCount++;
			OLED_Print_Img128X64(videoData);

			if (MainCount > 8) {
				Image_To_Warp();
				robot.yawPID.kp = 120 + 260 * fabs((float) RealWarp);
				robot.yawPID.kd = 60 + 140 * fabs((float) RealWarp);

				YawCtrlOut		= 3.f * PIDOperation(&robot.yawPID, RealWarp, 0.f);	   // ƽ�⻷Pwm
				DrawMidLine_Simple();
				OLED_Print_Img128X64(videoData);
				oled_show_float(60, 7, (float) RealWarp, 3, 2);
				vofa_send();

				/*
				Binary_Img();
				Find_EndRow();
				CorrectEndRow();
				RealEndRow = EndRow;		// ��¼��ʵ��ֹ��
				FindBorder();
				Find_MidLine();
				DrawMidLine_Simple();
				OLED_Print_Img128X64(videoData);
				if(StopFlag)
				BldcSetSpeed(0,0);
				YawCtrlOut = -3.f * PIDOperation(&robot.yawPID, (COL / 2.f) / COL, (float) MidLine[ControlRow]);	// ƽ�⻷Pwm
				*/
			}
		}
#endif
		;
		;
	}
};
u8 JumpLineState = 0;
/*------------------------------------------------- ��ʱ��1 -------------------------------------------------------*/
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
	interrupt_global_enable(0);	   // �����ж�Ƕ��

	//	 ��������ʱ
	robot.param.leftTime  += 1;		 // 1ms
	robot.param.rightTime += 1;		 // 1ms
	robot.param.runTime	  += 1.f;	 // 1ms

	static u8 BalanceCnt   = 0;	   // 1kHz  ��bldc����ƽ�⣬����Ƶ�ʺ�bldcͬ�� �����bldc����
	{
		Get_Attitude();
		// if (JumpLineState <= 1 || JumpLineState >= 3)
		Balance();

		BalanceCnt = 0;
	}

	static u8 BldcCnt = 0;	  // 1k -> 500Hz  TODO���Ըĵ�1kHz
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

/*------------------------------------------------- ����3-BLDC -------------------------------------------------------*/
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)	 // ����������ȼ� 80
{
	interrupt_global_enable(0);	   // �����ж�Ƕ��

	Bldc_Driver_callback();	   // ��ˢ����жϽ��պ���
}

/*------------------------------------------------- ����2-���� -------------------------------------------------------*/
IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
	// vofa_receive();
	wireless_uart_callback();
	interrupt_global_enable(0);	   // �����ж�Ƕ��

	// TODO : ֮����
	//  static uint8_t receive_data_temp2 = 0;
	//  uart_query_byte(UART_2, &receive_data_temp2);
	//  enQueue(&usart2_rec_list, receive_data_temp2);	  // ���
}

#pragma section all restore
