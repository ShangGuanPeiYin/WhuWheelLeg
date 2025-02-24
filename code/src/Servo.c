/*
 * Servo.c
 * Created on: 2024��10��11��
 * Author: ����
 */
#include "zf_common_headfile.h"

ServoType Servo[4];

/// @brief �����ʼ��
/// @param
void ServoInit(void)
{
	for (size_t i = 0; i < 4; i++) { memset(&Servo[i], 0, sizeof(ServoType)); }

	// PWM��������
	Servo[0].pin	   = FL_CHANNEL;
	Servo[1].pin	   = FR_CHANNEL;
	Servo[2].pin	   = BL_CHANNEL;
	Servo[3].pin	   = BR_CHANNEL;

	// ��ʼ���������
	Servo[0].num	   = Fl;
	Servo[0].angleAdj  = -270;
	Servo[0].sign	   = -1;

	Servo[1].num	   = Fr;
	Servo[1].angleAdj  = -90;
	Servo[1].sign	   = +1;

	Servo[2].num	   = Bl;
	Servo[2].angleAdj  = -90;
	Servo[2].sign	   = -1;

	Servo[3].num	   = Br;
	Servo[3].angleAdj  = +90;
	Servo[3].sign	   = +1;

	Servo[Fl].PWMmin   = 1250;
	Servo[Fl].PWMmax   = 6150;

	Servo[Fr].PWMmin   = 1500;
	Servo[Fr].PWMmax   = 6400;

	Servo[Bl].PWMmin   = 1000;
	Servo[Bl].PWMmax   = 5800;

	Servo[Br].PWMmin   = 1150;
	Servo[Br].PWMmax   = 6150;

	Servo[Fl].angleLeg = 180.f;
	Servo[Fr].angleLeg = 180.f;
	Servo[Bl].angleLeg = 0.f;
	Servo[Br].angleLeg = 0.f;

	// ���ų�ʼ�� PWMƵ��250Hz
	for (size_t i = 0; i < 4; i++) pwm_init(Servo[i].pin, 250, (Servo[i].PWMmax + Servo[i].PWMmin) / 2);
}

/// @brief ��ʱ��Func����
/// @param
void ServoFunc(void)
{
	for (size_t id = 0; id < 4; id++)	 // ѭ��ִ��
	{
		// ���㲿��
		Servo[id].angleSet = (Servo[id].angleLeg + Servo[id].angleAdj) * Servo[id].sign;

		// �������
		Servo[id].PWMSet   = Servo[id].PWMmin + Servo[id].angleSet * (Servo[id].PWMmax - Servo[id].PWMmin) / 180;
		Limit(Servo[id].PWMSet, Servo[id].PWMmin, Servo[id].PWMmax);	// �޷�����

		pwm_set_duty(Servo[id].pin, Servo[id].PWMSet);	  // ����PWMռ�ձ�
	}
};

float directionError = 0;
int	  direction_Kp = 120, direction_Kd = 0;	   // ���PD,ѭ����Ҫ��Ҫ���Ĳ��� 109 405
int	  ServoControlOut = 0;					   // ���ʵ�����ֵ

void Get_Direction_Error()
{
	// ��������һ��
	directionError	= ((float) (MidLine[ControlRow] - (COL / 2))) / COL;

	directionError *= -3.0;	   // �Ŵ���޷���Χ�ɳ�ʵ���������

	// directionError= LimitBoth_float(directionError,-1.0,1.0);

	oled_show_float(60, 1, directionError, 2, 2);
}

void Direction_Control_Error(void)
{
	static float P, D, error_pre;
	/*
	 ���壺��д�����PID��λ�ñջ���������PID����У����������Ҫ�����ʱ����е��Եĵط���������
	 */
	Get_Direction_Error();
	P				= directionError;
	D				= directionError - error_pre;
	error_pre		= directionError;
	ServoControlOut = (direction_Kp * P) + (direction_Kd * D);
	if (StopFlag)
		ServoControlOut = 0;
	/*
	 ���壺
	 ������ͣ��ʱ�Ѷ����������ֹ����һ�
	 ����Ҫ����ɾ��ֻ���� pwm_set_duty(SERVO_PWM,ServoControlOut);����
	*/
}
