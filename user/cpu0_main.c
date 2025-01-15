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

	KeyInit();		// ������ʼ��
	ServoInit();	// ������Ƴ�ʼ��
	BldcInit();		// ��ˢ�����ʼ��

	robotInit(&robot);

	pit_ms_init(CCU60_CH0, 1);	  // CCU60_CH0ͨ�����жϳ�ʼ������Ϊ1ms �жϳ�ʼ����ǰ��

	// �˴���д�û����� ���������ʼ�������
	cpu_wait_event_ready();	   // �ȴ����к��ĳ�ʼ�����
	system_delay_ms(500);
	while (TRUE) {
		system_delay_ms(5);	   // 5msִ��һ�Σ���200Hz ��Ҫ<=���FuncƵ��

		// BldcSetCurrent(float leftCur, float rightCur);		// PWM +-4k
		// BldcSetSpeed(float leftSpeed, float rightSpeed);	// rpm

		/*

		��λ�����Ƶ����
		������λ�����Ƶ������������ٶȵĸ�ʽ�� ����
		������������û�з������˾ͻ�һ��

		������Ƶ����
		�ȿ������Ƶ������һ��С��PWM������������
		OLED������λ������ٶ�ֵ
		�������������ٶ�ֵ�����ٶȣ���ֹ�Ҹ��ٶȹ���
		��bldc.c�е���PID��ʵ�ֱջ��ٶȿ��ơ�
		��������λ������ٶȲ��Σ����PID

		��ˢ������Ժ�����ֱ�ӵ��ü���

		���Դ����Լ�д��

		*/

		// // ��˿��Ʋ��� ��һ���ٲ������
		// OLedDebug();
		// AngleCalculate(&legLeft, legLeft.PosSet);
		// AngleCalculate(&legRight, legRight.PosSet);
	}
}

#pragma section all restore
