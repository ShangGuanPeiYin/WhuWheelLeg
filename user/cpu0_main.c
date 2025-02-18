#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

float	 angletemp = 0.f;
Vector2f point_temp;
int		 core0_main(void)
{
	clock_init();	 // ��ȡʱ��Ƶ��<��ر���>
	debug_init();	 // ��ʼ��Ĭ�ϵ��Դ���

	system_delay_ms(500);
	// �˴���д�û����� ���������ʼ�������
	oled_init();	// ��Ļ��ʼ��

	// mt9v03x_init();	   // ����ͷ��ʼ��

	KeyInit();			  // ������ʼ��
	DataProcessInit();	  // ͨѶ��ʼ��

	ServoInit();	// ������Ƴ�ʼ��
	BldcInit();		// ��ˢ�����ʼ��
	IMU_init();		// IMU��ʼ��

	// U2
	uart_init(UART_2, 460800, UART2_TX_P10_5, UART2_RX_P10_6);	  // ����2��ʼ��

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	while (TRUE) {
		// ����д��������� �����޷�ʵ��������ռ
		system_delay_ms(1);
		;
		;
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

    CH1_LOOP();

	static u8 BalanceCnt   = 0;	   // 1k -> 100Hz  ��bldc����ƽ�⣬����Ƶ�ʺ�bldcͬ�� �����bldc����
	if (++BalanceCnt >= 1) {
		//Balance();
		BalanceCnt = 0;
	}

	static u8 BldcCnt = 0;	  // 1k -> 100Hz
	if (++BldcCnt >= 10) {
		BldcFunc();
		BldcCnt = 0;
	}

	static int ServoCnt = 0;
	if (++ServoCnt >= 5) {	  // 1k -> 200Hz
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
	interrupt_global_enable(0);	   // �����ж�Ƕ��

	// TODO : ֮����
	//  static uint8_t receive_data_temp2 = 0;
	//  uart_query_byte(UART_2, &receive_data_temp2);
	//  enQueue(&usart2_rec_list, receive_data_temp2);	  // ���
}

#pragma section all restore
