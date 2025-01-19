#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief �����ʼ��
/// @param
void ServoInit(void)
{
	for (size_t i = 0; i < 4; i++) { memset(&Servo[i], 0, sizeof(ServoType)); }

	// PWM��������
	Servo[0].pin	  = FL_CHANNEL;
	Servo[1].pin	  = FR_CHANNEL;
	Servo[2].pin	  = BL_CHANNEL;
	Servo[3].pin	  = BR_CHANNEL;

	// ��ʼ���������
	Servo[0].num	  = Fl;
	Servo[0].angleAdj = -270;
	Servo[0].sign	  = -1;

	Servo[1].num	  = Fr;
	Servo[1].angleAdj = -90;
	Servo[1].sign	  = +1;

	Servo[2].num	  = Bl;
	Servo[2].angleAdj = -90;
	Servo[2].sign	  = -1;

	Servo[3].num	  = Br;
	Servo[3].angleAdj = +90;
	Servo[3].sign	  = +1;

	Servo[Fl].PWMmin  = 1150;
	Servo[Fr].PWMmin  = 1450;
	Servo[Bl].PWMmin  = 1000;
	Servo[Br].PWMmin  = 1150;
	for (size_t i = 0; i < 4; i++) { Servo[i].PWMmax = Servo[i].PWMmin + 5000; }

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
		Servo[id].PWMSet = Servo[id].PWMmin + Servo[id].angleSet * ANGLE2PWM;
		Limit(Servo[id].PWMSet, Servo[id].PWMmin, Servo[id].PWMmax);	// �޷�����

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // ����PWMռ�ձ�
	}
};
