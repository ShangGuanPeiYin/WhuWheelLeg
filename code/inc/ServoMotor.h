#ifndef _SERVOMOTOR_H_
#define _SERVOMOTOR_H_

#include "zf_common_typedef.h"
#include "zf_driver_pwm.h"

// �����ʼ��
#define FL_CHANNEL ATOM0_CH3_P14_2	   // ǰ����pwm����
#define FR_CHANNEL ATOM0_CH4_P20_3	   // ǰ�Ҷ��pwm����
#define BL_CHANNEL ATOM0_CH1_P33_9	   // ������pwm����
#define BR_CHANNEL ATOM0_CH2_P33_11	   // ���Ҷ��pwm����

#define ANGLEMAX  180						   // �����Χ�����Ƕ�
#define ANGLE2PWM (PWM_DUTY_MAX / ANGLEMAX)	   // ��λת�����Ƕȡ㣬ת��ΪPWM

// �ؽ����
typedef enum { Fl, Fr, Bl, Br } JointNum;

// ����ṹ��
typedef struct _Servo {
	pwm_channel_enum pin;	 // PWM ����
	JointNum		 num;

	float angleSet;	   // �����ʵ��ת�� ��������ýǶ��� ��
	float angleAdj;	   // ����ĵ���ֵ
	float angleLeg;	   // ��Leg�ϵĻ���Ƕȣ���Leg.h�ġ�1���4
	u8	  sign;		   // �����ţ�������

	int32_t PWMSet;
} ServoType;

extern ServoType Servo[4];

void ServoInit(void);
void ServoFunc(void);

#endif
