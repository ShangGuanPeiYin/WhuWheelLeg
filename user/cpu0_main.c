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

	gpio_init(KEY_UP, GPI, 0, GPI_PULL_UP);	   // ������ʼ��
	gpio_init(KEY_DOWN, GPI, 0, GPI_PULL_UP);
	gpio_init(KEY_LEFT, GPI, 0, GPI_PULL_UP);
	gpio_init(KEY_RIGHT, GPI, 0, GPI_PULL_UP);

	ServoInit();				  // ������Ƴ�ʼ��
	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	system_delay_ms(500);
	while (TRUE) {
		Servo[Fl].angleSet = angletemp;
		OLedDebug();
	}
}

#pragma section all restore
