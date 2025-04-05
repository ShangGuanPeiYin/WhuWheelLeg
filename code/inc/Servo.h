#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

// �����ʼ��
#define FL_CHANNEL ATOM0_CH3_P14_2	   // ǰ����pwm����
#define FR_CHANNEL ATOM0_CH4_P20_3	   // ǰ�Ҷ��pwm����
#define BL_CHANNEL ATOM0_CH1_P33_9	   // ������pwm����
#define BR_CHANNEL ATOM0_CH2_P33_11	   // ���Ҷ��pwm����

// �ؽ����
typedef enum { Fl, Fr, Bl, Br } JointNum;

// ����ṹ��
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM ����
	JointNum		 num;

	float angleSet;	   // �����ʵ��ת�� ��������ýǶ��� �� ��0-180�㣩
	float angleAdj;	   // ����ĵ���ֵ
	float angleLeg;	   // ��Leg�ϵĻ���Ƕȣ���Leg.h�ġ�1���4
	int8  sign;		   // �����ţ�������

	float deltaAngle;	 // ������װ���Ƕ��� �� ��0-180�㣩

	int32_t PWMSet;
} ServoType;

extern ServoType Servo[4];

void ServoInit(void);
void ServoFunc(void);

#endif
