#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief �����ʼ��
/// @param
void ServoInit(void)
{
	for (size_t i = 0; i < 4; i++) { memset(&Servo[i], 0, sizeof(ServoType)); }

	// PWM��������
	Servo[0].pin		= FL_CHANNEL;
	Servo[1].pin		= FR_CHANNEL;
	Servo[2].pin		= BL_CHANNEL;
	Servo[3].pin		= BR_CHANNEL;

	// ��ʼ���������
	Servo[0].num		= Fl;
	Servo[0].angleAdj	= -270;
	Servo[0].sign		= -1;
	Servo[0].deltaAngle = +7;	 // ��Ҫ�ֶ���������װ���

	Servo[1].num		= Fr;
	Servo[1].angleAdj	= -90;
	Servo[1].sign		= +1;
	Servo[1].deltaAngle = -1;

	Servo[2].num		= Bl;
	Servo[2].angleAdj	= -90;
	Servo[2].sign		= -1;
	Servo[2].deltaAngle = -2;

	Servo[3].num		= Br;
	Servo[3].angleAdj	= +90;
	Servo[3].sign		= +1;
	Servo[3].deltaAngle = -13;

	Servo[Fl].angleLeg	= 180.f;
	Servo[Fr].angleLeg	= 180.f;
	Servo[Bl].angleLeg	= 0.f;
	Servo[Br].angleLeg	= 0.f;

	// ���ų�ʼ�� PWMƵ��200Hz
	for (size_t i = 0; i < 4; i++) {
		Servo[i].angleSet = 90.f;
		pwm_init(Servo[i].pin, 200, 4 * 750);
	}
	ServoFunc();
}

/// @brief ��ʱ��Func����
/// @param �����ϵΪ��
///      	PWMSet = (f/50)*( 250 + (1000 * (AngleSet + deltaAngle) / 180));
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++)	 // ѭ��ִ��
	{
		// ���㲿��
		Servo[id].angleSet = (Servo[id].angleLeg + Servo[id].angleAdj) * Servo[id].sign;

		// �������
		Limit(Servo[id].angleSet, 0, 180);															  // �޷�����
		Servo[id].PWMSet = 4 * (250 + (1000 * (Servo[id].angleSet + Servo[id].deltaAngle) / 180));	  // PWMΪ200Hz��Ϊ50��4��

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // ����PWMռ�ձ�
	}
};
