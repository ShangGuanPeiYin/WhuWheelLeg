#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

float	 angletemp = 0.f;
Vector2f point_temp;
extern float YawVecOut;
int		 core0_main(void)
{
	clock_init();	 // ��ȡʱ��Ƶ��<��ر���>
	debug_init();	 // ��ʼ��Ĭ�ϵ��Դ���
	system_delay_ms(500);
	// �˴���д�û����� ���������ʼ�������
	oled_init();	// ��Ļ��ʼ��
	mt9v03x_init();	   // ����ͷ��ʼ��
	mt9v03x_set_exposure_time(200);
	KeyInit();	  // ������ʼ��
	ServoInit();	// ������Ƴ�ʼ��
	BldcInit();		// ��ˢ�����ʼ��
	IMU_init();		// IMU��ʼ��
	robotInit(&robot);
	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	wireless_uart_init();
	seekfree_assistant_interface_init(SEEKFREE_ASSISTANT_WIRELESS_UART);	//ѡ��������ֵ��Դ���
	seekfree_assistant_oscilloscope_data.channel_num = 2;					//ʾ����ͨ����
	//seekfree_assistant_camera_information_config(SEEKFREE_ASSISTANT_MT9V03X, image_copy[0], COL, ROW);	//��������ͷ��Ϣ����λ����ʾ
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	system_delay_ms(500);

	while (TRUE) {
//����Yaw��
#if 1
		ShowTorque();
        AdjustPID(&robot.YawTorPID);
		YawVecOut = AdjustTarget();
        // printf("P : %f	I : %f 	D : %f	Target : %f",robot.YawTorPID.kp,robot.YawTorPID.ki,robot.YawTorPID.kd,YawVecOut);
    	// printf("\r\n");
#endif

#if 0
		vofa_send();
		vofa_receive();
		wireless_uart_read_buffer(DataBuff,10);
		uart_query_byte(UART_2,DataBuff);
		oled_show_int(20,3,DataBuff[1],3);
		uint8 x=0;
		uart_query_byte(UART_2,&x);
		wireless_uart_read_buffer()
		x++;
		Bldc_AskSpeed();
		oled_show_float(60,1,Motor[0].valueNow.speed,4,2);
        oled_show_float(60,3,Motor[1].valueNow.speed,4,2);
		oled_show_float(60,3,Motor[1].valueNow.speed,4,2);
		oled_show_float(60, 3, IMUdata.dataOri.angle.x, 2, 2);
		oled_show_float(60, 5, robot.left_Torque, 2, 2);
		oled_show_float(60, 7, Motor[0].valueNow.speed, 2, 2);
		oled_show_float(60,5,IMUdata.dataOri.pitch,2,2);
		oled_show_uint(60,1,x,3);
		oled_show_int(60,3,(int)Motor[0].pulse.pulseRead*10000,3);
		Bldc_SetDuty(2000,2000);
		oled_show_float(60, 3, IMUdata.dataOri.angle.x, 2, 2);
        oled_show_float(60, 1, IMUdata.dataOri.pitch, 2, 2);
        oled_show_float(60, 3, IMUdata.dataOri.roll, 2, 2);
        oled_show_float(60, 5, IMUdata.dataOri.yaw, 2, 2);
#endif

#if 0
		if (mt9v03x_finish_flag)	// ����ͷ�ɼ���ɱ�־λ
		{
			mt9v03x_finish_flag = 0;
			Binary_Img();
			MainCount++;
			if (MainCount > 8) {
				Image_To_Warp();
				DrawMidLine_Simple();
				OLED_Print_Img128X64(videoData);
			}
		}
#endif
	}
}

/*------------------------------------------------- ��ʱ��1 -------------------------------------------------------*/
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
	interrupt_global_enable(0);	   // �����ж�Ƕ��

	// ��������ʱ
	robot.param.leftTime  += 1;		 // 1ms
	robot.param.rightTime += 1;		 // 1ms
	robot.param.runTime	  += 1.f;	 // 1ms

	static u8 BalanceCnt   = 0;	   // 1k -> 100Hz  ��bldc����ƽ�⣬����Ƶ�ʺ�bldcͬ�� �����bldc����
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

	static u8 IMUCnt = 0;	 // 1k -> 200Hz ������
	if (++IMUCnt >= irq_interval) {
		Get_Attitude();
		IMUCnt = 0;
	}
	pit_clear_flag(CCU60_CH0);
}

/*------------------------------------------------- ����3-BLDC -------------------------------------------------------*/
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)
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
