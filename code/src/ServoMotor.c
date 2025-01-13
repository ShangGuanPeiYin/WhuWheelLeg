#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief �����ʼ��
/// @param
void ServoInit(void)
{
	// PWM��������
	Servo[0].pin	  = FL_CHANNEL;
	Servo[1].pin	  = FR_CHANNEL;
	Servo[2].pin	  = BL_CHANNEL;
	Servo[3].pin	  = BR_CHANNEL;

	// ��ʼ���������
	Servo[0].joint	  = Fl;
	Servo[0].angleSet = 0;
	Servo[0].angleAdj = 0;
	Servo[0].PWMSet	  = 0;
	Servo[0].sign	  = -1;

	Servo[1].joint	  = Fr;
	Servo[1].angleSet = 0;
	Servo[1].angleAdj = 0;
	Servo[1].PWMSet	  = 0;
	Servo[1].sign	  = -1;

	Servo[2].joint	  = Bl;
	Servo[2].angleSet = 0;
	Servo[2].angleAdj = 0;
	Servo[2].PWMSet	  = 0;
	Servo[2].sign	  = -1;

	Servo[3].joint	  = Br;
	Servo[3].angleSet = 0;
	Servo[3].angleAdj = 0;
	Servo[3].PWMSet	  = 0;
	Servo[3].sign	  = -1;

	// ���ų�ʼ�� PWMƵ��250Hz

	for (size_t i = 0; i < 4; i++) pwm_init(Servo[i].pin, 250, Servo[i].angleAdj);
}

/// @brief ��ʱ��Func����
/// @param
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++)	 // ѭ��ִ��
	{
		// ���㲿��
		// Servo[id].angleSet = (Servo[id].angleLeg + Servo[id].angleAdj) * Servo[id].sign;

		// �������
		Servo[id].PWMSet = Servo[id].angleSet * ANGLE2PWM;
		Limit(Servo[id].PWMSet, 0, (int32_t) PWM_DUTY_MAX);	   // �޷�����

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // ����PWMռ�ձ�
	}
};

/* ���Բ�ֵ��Ҫ�Ƶ��ϲ�
	// �ж��Ƿ�λ
	if (Servo[id].cntTime <= Servo[id].reachTime) {
		Servo[id].PWMSet = (Servo[id].cntTime / Servo[id].reachTime) * Servo[id].angleSet * ANGLE2PWM;	  // ���Բ�ֵ
		Servo[id].cntTime
			+= 5.f;	   // ���Ƶ��200Hz																		// �ж�Ƶ��
	} else
		Servo[id].PWMSet = Servo[id].angleSet * ANGLE2PWM;

*/
