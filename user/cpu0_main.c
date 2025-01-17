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

	KeyInit();	  // ������ʼ��

	ServoInit();	// ������Ƴ�ʼ��
	BldcInit();		// ��ˢ�����ʼ��

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	system_delay_ms(500);
	while (TRUE) {
		system_delay_ms(5);	   // 5msִ��һ�Σ���200Hz ��Ҫ<=���FuncƵ��

		// BldcSetCurrent(1500, 1500);	   // PWM +-4k
		// BldcSetSpeed(150, 0);		   // rpm

		// // ��˿��Ʋ��� ��һ���ٲ������
		//		Vector2f PosTarget;
		//		RobotDrawLine(PosTarget, 100);
	}
}

#pragma section all restore
