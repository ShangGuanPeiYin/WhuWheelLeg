#include "zf_common_headfile.h"
#pragma section all "cpu0_dsram"
// ���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

float angletemp = 0.f;
int	  core0_main(void)
{
	clock_init();	 // ��ȡʱ��Ƶ��<��ر���>
	debug_init();	 // ��ʼ��Ĭ�ϵ��Դ���

	system_delay_ms(500);
	// �˴���д�û����� ���������ʼ�������
	oled_init();	// ��Ļ��ʼ��

	// mt9v03x_init();	   // ����ͷ��ʼ��

	KeyInit();			// ������ʼ��
	ServoInit();		// ������Ƴ�ʼ��
	BrushlessInit();	// ��ˢ�����ʼ��

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	system_delay_ms(500);
	while (TRUE) {
		system_delay_ms(5);	   // 5msִ��һ�Σ���200Hz ��Ҫ<=���FuncƵ��

		// �������
		Servo[Fl].angleSet = angletemp;
		Servo[Fr].angleSet = angletemp;
		Servo[Bl].angleSet = angletemp;
		Servo[Br].angleSet = angletemp;

		OLedDebug();

		// ���µ��
	}
}

#pragma section all restore
